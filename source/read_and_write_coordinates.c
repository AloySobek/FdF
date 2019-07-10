/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_write_coordinates.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 18:54:40 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/10 21:24:23 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			find_centre(t_mlx_var *mlx_var, int x, int y)
{
	int	i;

	i = mlx_var->maps->prev->count + 1;
	while (i--)
	{
		mlx_var->maps->x -= x;
		mlx_var->maps->y -= y;
		mlx_var->maps = mlx_var->maps->next;
	}
}

void			add_color(t_mlx_var *mlx_var)
{
	int i;
	int	r;
	int	g;
	int	b;

	i = mlx_var->maps->prev->count + 1;
	while (i--)
	{
		if (mlx_var->maps->z == mlx_var->color.lowest->z)
			mlx_var->maps->color = mlx_var->color.start;
		else if (mlx_var->maps->z == mlx_var->color.highest->z)
			mlx_var->maps->color = mlx_var->color.end;
		else
		{
			r = ((mlx_var->color.start >> 16) & 0xff) + ((((mlx_var->color.end >> 16) & 0xff) - ((mlx_var->color.start >> 16) & 0xff)) / (mlx_var->color.highest->z - mlx_var->color.lowest->z)) * (mlx_var->maps->z - mlx_var->color.lowest->z);
			g = ((mlx_var->color.start >> 8) & 0xff) + ((((mlx_var->color.end >> 8) & 0xff) - ((mlx_var->color.start >> 8) & 0xff)) / (mlx_var->color.highest->z - mlx_var->color.lowest->z)) * (mlx_var->maps->z - mlx_var->color.lowest->z);
			b = (mlx_var->color.start & 0xff) + (((mlx_var->color.end & 0xff) - (mlx_var->color.start & 0xff)) / (mlx_var->color.highest->z - mlx_var->color.lowest->z)) * (mlx_var->maps->z - mlx_var->color.lowest->z);
			mlx_var->maps->color = (r << 16) | (g << 8) | b;
		}
		mlx_var->maps = mlx_var->maps->next;
	}
}

void			reading_and_write_coordinates(int fd, t_mlx_var *mlx_var)
{
	t_coords	*list_manager[3];
	char		*line;
	int			x;
	int			y;

	list_manager[HEAD] = NULL;
	list_manager[ITER] = NULL;
	list_manager[TEMP] = NULL;
	y = 0;
	while (get_next_line(fd, &line) == 1)
	{
		x = 0;
		while (*line)
		{
			if ((*line >= '0' && *line <= '9') || *line == '-' || *line == '+')
			{
				list_manager[ITER] = new_point_in_space(x, y, ft_atoi(line));
				if (!list_manager[HEAD])
				{
					list_manager[HEAD] = list_manager[ITER];
					mlx_var->color.highest = list_manager[HEAD];
					mlx_var->color.lowest = list_manager[HEAD];
				}
				if (mlx_var->color.highest->z < list_manager[ITER]->z)
					mlx_var->color.highest = list_manager[ITER];
				if (mlx_var->color.lowest->z > list_manager[ITER]->z)
					mlx_var->color.lowest = list_manager[ITER];
				if (list_manager[TEMP])
				{
					list_manager[TEMP]->next = list_manager[ITER];
					list_manager[ITER]->prev = list_manager[TEMP];
					list_manager[ITER]->count = list_manager[TEMP]->count + 1;
				}
				else
					list_manager[ITER]->count = 0;
				if (y > 0)
				{
					while (list_manager[TEMP]->x != list_manager[ITER]->x)
						list_manager[TEMP] = list_manager[TEMP]->prev;
					list_manager[ITER]->upper = list_manager[TEMP];
				}
				else
					list_manager[ITER]->upper = NULL;
				list_manager[TEMP] = list_manager[ITER];
				while (*line && *line != ' ')
					++line;
				++x;
			}
			*line ? line++ : 0;
		}
		++y;
	}
	to_tie_list(&list_manager[HEAD]);
	mlx_var->maps = list_manager[HEAD];
	find_centre(mlx_var, mlx_var->maps->prev->x / 2, mlx_var->maps->prev->y / 2);
	add_color(mlx_var);
}
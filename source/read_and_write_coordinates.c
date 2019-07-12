/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_write_coordinates.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckatelin <ckatelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 18:54:40 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/12 15:54:23 by ckatelin         ###   ########.fr       */
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

int				return_color(int k, t_mlx_var *mlx_var)
{
	if (k == 0)
		return (((mlx_var->color.start >> 16) & 0xff) +
			((((mlx_var->color.end >> 16)
			& 0xff) - ((mlx_var->color.start >> 16) & 0xff)) /
			(mlx_var->color.highest->z - mlx_var->color.lowest->z)) *
			(mlx_var->maps->z - mlx_var->color.lowest->z));
	else if (k == 1)
		return (((mlx_var->color.start >> 8) & 0xff) +
			((((mlx_var->color.end >> 8)
			& 0xff) - ((mlx_var->color.start >> 8) & 0xff)) /
			(mlx_var->color.highest->z - mlx_var->color.lowest->z)) *
			(mlx_var->maps->z - mlx_var->color.lowest->z));
	else
		return ((mlx_var->color.start & 0xff) +
			(((mlx_var->color.end & 0xff) -
			(mlx_var->color.start & 0xff)) /
			(mlx_var->color.highest->z - mlx_var->color.lowest->z)) *
			(mlx_var->maps->z - mlx_var->color.lowest->z));
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
			r = return_color(0, mlx_var);
			g = return_color(1, mlx_var);
			b = return_color(2, mlx_var);
			mlx_var->maps->color = (r << 16) | (g << 8) | b;
		}
		mlx_var->maps = mlx_var->maps->next;
	}
}

void			reading_and_write_coordinates(int fd, t_mlx_var *mlx_var)
{
	t_coords	*list_manager[3];
	char		*line;
	t_vectors	vector;

	nulling(list_manager);
	vector.y = 0;
	while (get_next_line(fd, &line) == 1)
	{
		vector.x = 0;
		while (*line)
		{
			if ((*line >= '0' && *line <= '9') || *line == '-' || *line == '+')
			{
				filler(list_manager, mlx_var, vector, line);
				checking_y(line, vector, list_manager);
				while (*line && *line != ' ')
					++line;
				++vector.x;
			}
			*line ? line++ : 0;
		}
		++vector.y;
	}
	doing_all_stuff(mlx_var, list_manager);
}

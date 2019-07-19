/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_write_coordinates.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 18:54:40 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/19 14:58:46 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			nulling(t_coords **list_manager)
{
	list_manager[HEAD] = NULL;
	list_manager[ITER] = NULL;
	list_manager[TEMP] = NULL;
}

int				center_maps(t_mlx_var *mlx_var)
{
	int			i;
	int			x;
	int			y;

	x = mlx_var->maps->prev->x / 2;
	y = mlx_var->maps->prev->y / 2;
	i = mlx_var->maps->prev->count + 1;
	while (i--)
	{
		mlx_var->maps->x -= x;
		mlx_var->maps->y -= y;
		mlx_var->maps = mlx_var->maps->next;
	}
	return (1);
}

void			main_conditionals(t_mlx_var *mlx_var, t_coords **list_manager, int y)
{
	if (!list_manager[HEAD] && (list_manager[HEAD] = list_manager[ITER])
	&& (mlx_var->color.highest = list_manager[HEAD]))
		mlx_var->color.lowest = list_manager[HEAD];
	if (mlx_var->color.highest->z < list_manager[ITER]->z)
		mlx_var->color.highest = list_manager[ITER];
	if (mlx_var->color.lowest->z > list_manager[ITER]->z)
		mlx_var->color.lowest = list_manager[ITER];
	if (list_manager[TEMP] && (list_manager[TEMP]->next = list_manager[ITER]))
	{
		list_manager[ITER]->prev = list_manager[TEMP];
		list_manager[ITER]->count = list_manager[TEMP]->count + 1;
	}
	else
		list_manager[ITER]->count = 0;
	if (y > 0)
	{
		while (list_manager[TEMP]->x != list_manager[ITER]->x)
			if (!(list_manager[TEMP] = list_manager[TEMP]->prev))
				error_handler(EMPTY_LIST);
		list_manager[ITER]->upper = list_manager[TEMP];
	}
	else
		list_manager[ITER]->upper = NULL;
	list_manager[TEMP] = list_manager[ITER];
}

t_coords		*initialize_maps(int fd, t_mlx_var *mlx_var)
{
	t_coords	*list_manager[3];
	char		*line;
	int			x;
	int			y;

	nulling(&list_manager[HEAD]);
	y = -1;
	while (get_next_line(fd, &line) == 1 && ++y >= 0)
	{
		x = -1;
		while (*line)
		{
			if ((*line >= '0' && *line <= '9') || *line == '-' || *line == '+')
			{
				list_manager[ITER] = new_point_in_space(++x, y, ft_atoi(line));
				main_conditionals(mlx_var, &list_manager[HEAD], y);
				while (*line && *line != ' ')
					++line;
			}
			*line ? line++ : 0;
		}
	}
	if (!(list_manager[HEAD]))
		error_handler(EMPTY_LIST);
	to_tie_list(&list_manager[HEAD]);
	return (list_manager[HEAD]);
}

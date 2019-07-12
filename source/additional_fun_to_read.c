/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_fun_to_read.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckatelin <ckatelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 15:56:34 by ckatelin          #+#    #+#             */
/*   Updated: 2019/07/12 15:58:02 by ckatelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			filler(t_coords *list_manager[3],
					t_mlx_var *mlx_var, t_vectors vector, char *line)
{
	list_manager[ITER] = new_point_in_space(vector.x, vector.y, ft_atoi(line));
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
}

void			checking_y(char *line, t_vectors vector,
					t_coords *list_manager[3])
{
	if (vector.y > 0)
	{
		while (list_manager[TEMP]->x != list_manager[ITER]->x)
			list_manager[TEMP] = list_manager[TEMP]->prev;
		list_manager[ITER]->upper = list_manager[TEMP];
	}
	else
		list_manager[ITER]->upper = NULL;
	list_manager[TEMP] = list_manager[ITER];
}

void			doing_all_stuff(t_mlx_var *mlx_var, t_coords *list_manager[3])
{
	to_tie_list(&list_manager[HEAD]);
	mlx_var->maps = list_manager[HEAD];
	find_centre(mlx_var, mlx_var->maps->prev->x / 2,
		mlx_var->maps->prev->y / 2);
	add_color(mlx_var);
}

void			nulling(t_coords *list_manager[3])
{
	list_manager[HEAD] = NULL;
	list_manager[ITER] = NULL;
	list_manager[TEMP] = NULL;
}

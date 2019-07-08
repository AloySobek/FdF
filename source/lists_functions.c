/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 18:55:58 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/08 14:30:16 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coords	*new_point_in_space(long double x, long double y, long double z)
{
	t_coords *new_point;

	if (!(new_point = (t_coords *)malloc(sizeof(t_coords))))
		error_handler(10);
	new_point->x = x;
	new_point->y = y;
	new_point->z = z;
	new_point->z_tmp = z;
	new_point->next = NULL;
	new_point->prev = NULL;
	return (new_point);
}

void		to_tie_list(t_coords **list)
{
	t_coords *iter;

	iter = *list;
	while (iter->next)
		iter = iter->next;
	(*list)->prev = iter;
	iter->next = *list;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_write_coordinates.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 18:54:40 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/06 21:06:20 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			find_centre(t_coords **list_manager)
{
	int			x_middle;
	int			y_middle;
	int			x;
	int			y;

	list_manager[ITER] = list_manager[HEAD];
	list_manager[TEMP] = list_manager[HEAD]->prev;
	y_middle = list_manager[TEMP]->y / 2 * -1;
	y = list_manager[TEMP]->y;
	while (--y >= -1)
	{
		x = list_manager[TEMP]->x;
		x_middle = list_manager[TEMP]->x / 2 * -1;
		while (--x >= -1)
		{
			list_manager[ITER]->x = x_middle++;
			list_manager[ITER]->y = y_middle;
			list_manager[ITER] = list_manager[ITER]->next;
		}
		y_middle++;
	}
}

t_coords		*reading_and_write_coordinates(int fd)
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
			if (*line >= '0' && *line <= '9')
			{
				list_manager[ITER] = new_point_in_space(x, y, ft_atoi(line));
				if (!list_manager[HEAD])
					list_manager[HEAD] = list_manager[ITER];
				if (list_manager[TEMP])
				{
					list_manager[TEMP]->next = list_manager[ITER];
					list_manager[ITER]->prev = list_manager[TEMP];
					list_manager[ITER]->count = list_manager[TEMP]->count + 1;
				}
				else
					list_manager[ITER]->count = 0;
				list_manager[TEMP] = list_manager[ITER];
				while (*line && *line >= '0' && *line <= '9')
					++line;
				++x;
			}
			*line ? line++ : 0;
		}
		++y;
	}
	to_tie_list(&list_manager[HEAD]);
	find_centre(&list_manager[HEAD]);
	return (list_manager[HEAD]);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 17:53:08 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/02 19:42:32 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <mlx.h>
#include "ft_printf.h"
#include "libft.h"
#include "get_next_line.h"

typedef struct		s_coords
{
	int				x;
	int				y;
	int				z;
	int				count;
	struct s_coords	*next;
	struct s_coords	*prev;

}					t_coords;

typedef enum		e_list_manager
{
	HEAD,
	ITER,
	TEMP,
}					t_list_manager;

t_coords			*reading_and_write_coordinates(char *file);
t_coords			*new_point_in_space(int x, int y, int z);
void				to_tie_list(t_coords **list);
void				error_handler(int code_of_errors);

#endif
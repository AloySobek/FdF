/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 17:53:08 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/06 20:07:16 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <mlx.h>
#include <math.h>
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

typedef	struct		s_mlx_var
{
	void			*connect;
	void			*main_window;
	void			*main_image;
	int				width;
	int				heigh;
	int				scale;
	int				mouse_left_pressed;
	int				mouse_right_pressed;
	long double		basis_vector[3][3];
	long double		angle_x;
	long double		angle_y;
	long double		angle_z;
	long double		x;
	long double		y;
	long double		z;
	long double		x_mouse;
	long double		y_mouse;
	t_coords		*tmp;
	t_coords		*coordinates;
}					t_mlx_var;

typedef enum		e_coord_manager
{
	X,
	Y,
	Z,
}					t_coord_manager;

typedef enum		e_list_manager
{
	HEAD,
	ITER,
	TEMP,
}					t_list_manager;

t_coords			*reading_and_write_coordinates(int fd);
t_coords			*new_point_in_space(int x, int y, int z);
void				add_frame(t_mlx_var *mlx_var);
void				x_axis_rotation(t_mlx_var *mlx_var);
void				y_axis_rotation(t_mlx_var *mlx_var);
void				z_axis_rotation(t_mlx_var *mlx_var);
void				x_y_axis_rotation(t_mlx_var *mlx_var);
void				x_y_z_axis_rotation(t_mlx_var *mlx_var);
void				view_from_above(t_mlx_var *mlx_var);
void				to_mirror_image(t_mlx_var *mlx_var);
void				scalar_product_of_vectors(t_mlx_var *mlx_var, int test);
void				to_tie_list(t_coords **list);
void				error_handler(int code_of_errors);
void				line(t_mlx_var *mlx_var, int x0, int x1, int y0, int y1);
int					key_press(int key_code, t_mlx_var *mlx_var);
int					key_release(int key_code, t_mlx_var *mlx_var);
int					mouse_press(int button, int x, int y, t_mlx_var *mlx_var);
int					mouse_release(int button, int x, int y, t_mlx_var *mlx_var);
int					mouse_moove(int x, int y, t_mlx_var *mlx_var);

#endif
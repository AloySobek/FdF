/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckatelin <ckatelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 17:53:08 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/12 15:55:32 by ckatelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <mlx.h>
#include <math.h>
#include "ft_printf.h"
#include "libft.h"
#include "get_next_line.h"

typedef enum			e_coord_manager
{
	X,
	Y,
	Z,
}						t_coord_manager;

typedef enum			e_list_manager
{
	HEAD,
	ITER,
	TEMP,
}						t_list_manager;

typedef struct			s_flags
{
	int					debug_mode;
	int					hint;
	int					z_axis_mode;
}						t_flags;

typedef struct			s_screen
{
	int					width;
	int					heigh;
	int					scale;
	int					main_scale;
}						t_screen;

typedef struct 			s_vectors
{
	long double			x;
	long double			y;
	long double			z;
}						t_vectors;

typedef struct			s_linear_algebra
{
	long double			basis_vectors[3][3];
	long double			angle_x;
	long double			angle_y;
	long double			angle_z;
	long double			vertical;
	long double			horizontal;
	t_vectors			vectors;
}						t_linear_algebra;

typedef struct			s_mouse
{
	int					left_pressed;
	int					right_pressed;
	long double			x;
	long double			y;
	long double			rot_sensitivity;
	long double			moove_sensitivity;
}						t_mouse;

typedef struct			s_coords
{
	long double			x;
	long double			y;
	long double			z;
	long double			z_tmp;
	int					count;
	int					color;
	struct s_coords		*next;
	struct s_coords		*prev;
	struct s_coords		*upper;
}						t_coords;

typedef struct			s_color
{
	int					x;
	int					y;
	int					start;
	int					end;
	t_coords			*lowest;
	t_coords			*highest;
}						t_color;

typedef	struct			s_mlx_var
{
	void				*connect;
	void				*main_window;
	void				*main_image;
	char				*data_addr;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	t_flags				flags;
	t_screen			screen;
	t_linear_algebra	linear_algebra;
	t_mouse				mouse;
	t_color				color;
	t_coords			*f_col;
	t_coords			*s_col;
	t_coords			*line;
	t_coords			*maps;
}						t_mlx_var;

int					return_color(int k, t_mlx_var *mlx_var);
void				checking_y(char *line, t_vectors vector, t_coords *list_manager[3]);
void				nulling(t_coords *list_manager[3]);
void				doing_all_stuff(t_mlx_var *mlx_var, t_coords *list_manager[3]);
void				filler(t_coords *list_manager[3], t_mlx_var *mlx_var, t_vectors vector, char *line);
void				find_centre(t_mlx_var *mlx_var, int x, int y);
t_coords			*new_point_in_space(long double x, long double y, long double z);
void				reading_and_write_coordinates(int fd, t_mlx_var *mlx_var);
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
void				display_pixels(t_mlx_var *mlx_var);
void				change_altitude(t_mlx_var *mlx_var, int up);
void				pixel_put(t_mlx_var *mlx_var, int x, int y, int colour);
void				add_hint(t_mlx_var *mlx_var);
void				add_color(t_mlx_var *mlx_var);
int					key_press(int key_code, t_mlx_var *mlx_var);
int					key_release(int key_code, t_mlx_var *mlx_var);
int					mouse_press(int button, int x, int y, t_mlx_var *mlx_var);
int					mouse_release(int button, int x, int y, t_mlx_var *mlx_var);
int					mouse_moove(int x, int y, t_mlx_var *mlx_var);
int					expose(t_mlx_var* mlx_var);
int					close_window(t_mlx_var *mlx_var);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_keyboard_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 19:22:56 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/06 21:10:36 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			display_line(t_mlx_var *mlx_var, int x1, int y1, int x2, int y2)
{
	int			x_delta;
	int			y_delta;
	int			x_sign;
	int			y_sign;
	int			error;
	int			error2;

	x_delta = abs(x2 - x1);
	y_delta = abs(y2 - y1);
	x_sign = x1 < x2 ? 1 : -1;
	y_sign = y1 < y2 ? 1 : -1;
	error = x_delta - y_delta;
	mlx_pixel_put(mlx_var->connect, mlx_var->main_window, x2, y2, 0x8b8970);
	while(x1 != x2 || y1 != y2)
	{
		mlx_pixel_put(mlx_var->connect, mlx_var->main_window, x1, y1, 0x8b8970);
		error2 = error * 2;
		if (error2 > -y_delta)
		{
			error -= y_delta;
			x1 += x_sign;
		}
		if (error2 < x_delta)
		{
			error += x_delta;
			y1 += y_sign;
		}
	}
}

void	change_altitude(t_mlx_var *mlx_var, int up)
{
	int i;

	i = mlx_var->coordinates->prev->count + 1;
	if (up)
	{
		while (i--)
		{
			if (mlx_var->coordinates->z > 0)
				mlx_var->coordinates->z++;
			else if (mlx_var->coordinates->z < 0)
				mlx_var->coordinates->z--;
			mlx_var->coordinates = mlx_var->coordinates->next;
		}
	}
	else
	{
		while (i--)
		{
			if (mlx_var->coordinates->z > 1)
				mlx_var->coordinates->z--;
			else if (mlx_var->coordinates->z < -1)
				mlx_var->coordinates->z++;
			mlx_var->coordinates = mlx_var->coordinates->next;
		}
	}
}

void	display_pixels(t_mlx_var *mlx_var)
{
	t_coords *tmp;
	double	x;
	double	y;
	int flag;
	int i;
	int	max;
	int check;

	flag = 0;
	i = mlx_var->coordinates->prev->count + 1;
	max = mlx_var->coordinates->prev->y;
	while (i--)
	{
		scalar_product_of_vectors(mlx_var, 1);
		if (flag && (mlx_var->coordinates->prev->x == (mlx_var->coordinates->x - 1)))
			display_line(mlx_var, x, y, mlx_var->width / 2 + mlx_var->x * mlx_var->scale, mlx_var->heigh / 2 + mlx_var->y * mlx_var->scale);
		x = mlx_var->width / 2 + mlx_var->x * mlx_var->scale;
		y = mlx_var->heigh / 2 + mlx_var->y * mlx_var->scale;
		if (mlx_var->coordinates->y < max)
		{
			check = mlx_var->coordinates->x;
			mlx_var->tmp = mlx_var->coordinates->next;
			while (mlx_var->tmp->x != check)
				mlx_var->tmp = mlx_var->tmp->next;
			scalar_product_of_vectors(mlx_var, 0);
			display_line(mlx_var, x, y, mlx_var->width / 2 + mlx_var->x * mlx_var->scale, mlx_var->heigh / 2 + mlx_var->y * mlx_var->scale);
		}
		mlx_pixel_put(mlx_var->connect, mlx_var->main_window, x, y, 0x8b8970);
		mlx_var->coordinates = mlx_var->coordinates->next;
		flag = 1;
	}
}

int		key_press(int key_code, t_mlx_var *mlx_var)
{
	if (key_code == 13)
		mlx_var->angle_x += 0.02;
	else if (key_code == 1)
		mlx_var->angle_x -= 0.02;
	if (key_code == 2)
		mlx_var->angle_y += 0.02;
	else if (key_code == 0)
		mlx_var->angle_y -= 0.02;
	if (key_code == 69)
		change_altitude(mlx_var, 1);
	else if (key_code == 78)
		change_altitude(mlx_var, 0);
	if (key_code == 12)
		mlx_var->angle_z += 0.02;
	else if (key_code == 14)
		mlx_var->angle_z -= 0.02;
	if (key_code == 53)
	{
		mlx_destroy_window(mlx_var->connect, mlx_var->main_window);
		error_handler(3);
	}
	x_y_z_axis_rotation(mlx_var);
	mlx_clear_window(mlx_var->connect, mlx_var->main_window);
	//add_frame(mlx_var);
	display_pixels(mlx_var);
	return (0);
}

int		mouse_press(int button, int x, int y, t_mlx_var *mlx_var)
{
	if (button == 1)
		mlx_var->mouse_left_pressed = 1;
	else if (button == 2)
		mlx_var->mouse_right_pressed = 1;
	else if (button == 3)
		mlx_var->scale = 25;
	else if (button == 4)
		mlx_var->scale++;
	else if (button == 5)
		mlx_var->scale > 0 ? mlx_var->scale-- : 0;
	mlx_var->x_mouse = x;
	mlx_var->y_mouse = y;
	mlx_clear_window(mlx_var->connect, mlx_var->main_window);
	display_pixels(mlx_var);
	return (0);
}

int		mouse_release(int button, int x, int y, t_mlx_var *mlx_var)
{
	if (button == 1)
		mlx_var->mouse_left_pressed = 0;
	else if (button == 2)
		mlx_var->mouse_right_pressed = 0;
	return (0);
}

int		mouse_moove(int x, int y, t_mlx_var *mlx_var)
{
	if (mlx_var->mouse_left_pressed || mlx_var->mouse_right_pressed)
	{
		if (mlx_var->mouse_left_pressed)
		{
			mlx_var->angle_x += -(0.003 * (y - mlx_var->y_mouse));
			mlx_var->angle_y += (0.003 * (x - mlx_var->x_mouse));
		}
		if (mlx_var->mouse_right_pressed)
		{
			mlx_var->angle_z += (0.003 * (y - mlx_var->y_mouse));
			mlx_var->angle_z += (0.003 * (x - mlx_var->x_mouse));
		}
	}
	mlx_var->y_mouse = y;
	mlx_var->x_mouse = x;
	x_y_z_axis_rotation(mlx_var);
	mlx_clear_window(mlx_var->connect, mlx_var->main_window);
	display_pixels(mlx_var);
	return (0);
}
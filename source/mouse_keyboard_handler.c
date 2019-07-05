/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_keyboard_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 19:22:56 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/05 21:34:56 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			drawLine(t_mlx_var *mlx_var, int x1, int y1, int x2, int y2)
{
	int			deltaX = abs(x2 - x1);
	int			deltaY = abs(y2 - y1);
	int			signX = x1 < x2 ? 1 : -1;
	int			signY = y1 < y2 ? 1 : -1;
	int			error = deltaX - deltaY;
	mlx_pixel_put(mlx_var->connect, mlx_var->main_window, x2, y2, 0x8b8970);
	while(x1 != x2 || y1 != y2)
	{
		mlx_pixel_put(mlx_var->connect, mlx_var->main_window, x1, y1, 0x8b8970);
		const int error2 = error * 2;
		if(error2 > -deltaY)
		{
			error -= deltaY;
			x1 += signX;
		}
		if(error2 < deltaX)
		{
			error += deltaX;
			y1 += signY;
		}
	}
}

void	display_pixels(t_mlx_var *mlx_var)
{
	double	x;
	double	y;
	int flag;
	int i;
	int	max;
	int check;

	flag = 0;
	i = mlx_var->coordinates->prev->count + 1;
	max = mlx_var->coordinates->y;
	while (i--)
	{
		scalar_product_of_vectors(mlx_var);
		if (flag && (mlx_var->coordinates->prev->x == (mlx_var->coordinates->x - 1)))
			drawLine(mlx_var, x, y, mlx_var->width / 2 + mlx_var->x * mlx_var->scale, mlx_var->heigh / 2 + mlx_var->y * mlx_var->scale);
		x = mlx_var->width / 2 + mlx_var->x * mlx_var->scale;
		y = mlx_var->heigh / 2 + mlx_var->y * mlx_var->scale;
		if (mlx_var->coordinates->y > max)
		{
			check = mlx_var->coordinates->x;
			mlx_var->coordinates = mlx_var->coordinates->prev;
			while (mlx_var->coordinates->x != check)
				mlx_var->coordinates = mlx_var->coordinates->prev;
			scalar_product_of_vectors(mlx_var);
			drawLine(mlx_var, x, y, mlx_var->width / 2 + mlx_var->x * mlx_var->scale, mlx_var->heigh / 2 + mlx_var->y * mlx_var->scale);
			mlx_var->coordinates = mlx_var->coordinates->next;
			while (mlx_var->coordinates->x != check)
				mlx_var->coordinates = mlx_var->coordinates->next;
		}
		mlx_pixel_put(mlx_var->connect, mlx_var->main_window, x, y, 0x8b8970);
		mlx_var->coordinates = mlx_var->coordinates->next;
		flag = 1;
	}
}

int		key_press(int key_code, t_mlx_var *mlx_var)
{
	if (key_code == 126)
	{
		mlx_var->angle_x += 0.1;
		x_axis_rotation(mlx_var);
	}
	else if (key_code == 125)
	{
		mlx_var->angle_x -= 0.1;
		x_axis_rotation(mlx_var);
	}
	else if (key_code == 123)
	{
		mlx_var->angle_y += 0.1;
		y_axis_rotation(mlx_var);
	}
	else if (key_code == 124)
	{
		mlx_var->angle_y -= 0.1;
		y_axis_rotation(mlx_var);
	}
	else if (key_code == 12)
	{
		mlx_var->angle_x += 0.1;
		mlx_var->angle_y += 0.1;
		mlx_var->angle_z += 0.1;
		x_y_z_axis_rotation(mlx_var);
	}
	else if (key_code == 53)
	{
		mlx_destroy_window(mlx_var->connect, mlx_var->main_window);
		error_handler(3);
	}
	mlx_clear_window(mlx_var->connect, mlx_var->main_window);
	display_pixels(mlx_var);
	return (0);
}

int		key_release(int key_code, t_mlx_var *mlx_var)
{
	return (0);
}

int		mouse_press(int button, int x, int y, t_mlx_var *mlx_var)
{
	if (button == 1)
		mlx_var->mouse_left_pressed = 1;
	else if (button == 2)
		mlx_var->mouse_right_pressed = 1;
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
	if (mlx_var->mouse_left_pressed == 1)
	{
		mlx_var->angle_x = (0.003 * (y + mlx_var->y_mouse));
		mlx_var->angle_y = (0.003 * (x + mlx_var->x_mouse));
		x_y_axis_rotation(mlx_var);
	}
	else if (mlx_var->mouse_right_pressed == 1)
	{
		mlx_var->angle_z = (0.003 * (x - mlx_var->x_mouse));
		z_axis_rotation(mlx_var);
	}
	mlx_clear_window(mlx_var->connect, mlx_var->main_window);
	display_pixels(mlx_var);
	return (0);
}
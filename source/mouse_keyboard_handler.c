/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_keyboard_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 19:22:56 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/08 15:20:27 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_press(int key_code, t_mlx_var *mlx_var)
{
	int i;

	i = mlx_var->maps->prev->count + 1;
	if (key_code == 13)
		mlx_var->linear_algebra.angle_x += 0.02;
	else if (key_code == 1)
		mlx_var->linear_algebra.angle_x -= 0.02;
	else if (key_code == 2)
		mlx_var->linear_algebra.angle_y += 0.02;
	else if (key_code == 0)
		mlx_var->linear_algebra.angle_y -= 0.02;
	else if (key_code == 12)
		mlx_var->linear_algebra.angle_z += 0.02;
	else if (key_code == 14)
		mlx_var->linear_algebra.angle_z -= 0.02;
	else if (key_code == 125)
		mlx_var->linear_algebra.vertical += 3;
	else if (key_code == 126)
		mlx_var->linear_algebra.vertical -= 3;
	else if (key_code == 124)
		mlx_var->linear_algebra.horizontal += 3;
	else if (key_code == 123)
		mlx_var->linear_algebra.horizontal -= 3;
	else if (key_code == 69)
		change_altitude(mlx_var, 1);
	else if (key_code == 78)
		change_altitude(mlx_var, 0);
	else if (key_code == 49)
	{
		mlx_var->linear_algebra.angle_x = 1.100;
		mlx_var->linear_algebra.angle_y = 0;
		mlx_var->linear_algebra.angle_z = -0.880;
	}
	else if (key_code == 53)
	{
		mlx_destroy_window(mlx_var->connect, mlx_var->main_window);
		error_handler(5);
	}
	else if (key_code == 5)
		!mlx_var->flags.debug_mode ? (mlx_var->flags.debug_mode = 1) : (mlx_var->flags.debug_mode = 0);
	x_y_z_axis_rotation(mlx_var);
	display_pixels(mlx_var);
	return (0);
}

int		key_release(int key_code, t_mlx_var *mlx_var)
{
	if (mlx_var->flags.debug_mode)
	{
		if (key_code == 13)
			ft_printf("linear_algebra.angle_x ++ : %7Lf\n", mlx_var->linear_algebra.angle_x);
		else if (key_code == 1)
			ft_printf("linear_algebra.angle_x -- : %7Lf\n", mlx_var->linear_algebra.angle_x);
		else if (key_code == 2)
			ft_printf("linear_algebra.angle_y ++ : %7Lf\n", mlx_var->linear_algebra.angle_y);
		else if (key_code == 0)
			ft_printf("linear_algebra.angle_y -- : %7Lf\n", mlx_var->linear_algebra.angle_y);
		else if (key_code == 12)
			ft_printf("linear_algebra.angle_z ++ : %7Lf\n", mlx_var->linear_algebra.angle_z);
		else if (key_code == 14)
			ft_printf("linear_algebra.angle_z -- : %7Lf\n", mlx_var->linear_algebra.angle_z);
	}
	return (0);
}

int		mouse_press(int button, int x, int y, t_mlx_var *mlx_var)
{
	if (button == 1)
		mlx_var->mouse.left_pressed = 1;
	else if (button == 2)
		mlx_var->mouse.right_pressed = 1;
	else if (button == 3)
		mlx_var->screen.scale = 25;
	else if (button == 4)
		mlx_var->screen.scale++;
	else if (button == 5)
		mlx_var->screen.scale > 0 ? mlx_var->screen.scale-- : 0;
	mlx_var->mouse.x = x;
	mlx_var->mouse.y = y;
	mlx_clear_window(mlx_var->connect, mlx_var->main_window);
	display_pixels(mlx_var);
	return (0);
}

int		mouse_release(int button, int x, int y, t_mlx_var *mlx_var)
{
	if (button == 1)
		mlx_var->mouse.left_pressed = 0;
	else if (button == 2)
		mlx_var->mouse.right_pressed = 0;
	return (0);
}

int		mouse_moove(int x, int y, t_mlx_var *mlx_var)
{
	if (mlx_var->mouse.left_pressed || mlx_var->mouse.right_pressed)
	{
		if (mlx_var->mouse.left_pressed)
		{
			mlx_var->linear_algebra.angle_x += -(0.003 * (y - mlx_var->mouse.y));
			mlx_var->linear_algebra.angle_y += (0.003 * (x - mlx_var->mouse.x));
		}
		if (mlx_var->mouse.right_pressed)
		{
			mlx_var->linear_algebra.angle_z += (0.003 * (y - mlx_var->mouse.y));
			mlx_var->linear_algebra.angle_z += (0.003 * (x - mlx_var->mouse.x));
		}
	}
	mlx_var->mouse.y = y;
	mlx_var->mouse.x = x;
	x_y_z_axis_rotation(mlx_var);
	display_pixels(mlx_var);
	return (0);
}

int expose(t_mlx_var *mlx_var)
{
	mlx_var->linear_algebra.angle_x = 1.100;
	mlx_var->linear_algebra.angle_y = 0;
	mlx_var->linear_algebra.angle_z = -0.880;
	x_y_z_axis_rotation(mlx_var);
	display_pixels(mlx_var);
	return (0);
}

int	close_window(t_mlx_var *mlx_var)
{
	error_handler(6);
	return (0);
}
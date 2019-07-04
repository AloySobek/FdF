/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_keyboard_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 19:12:21 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/04 mlx_var->scale:26:20 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	line(t_mlx_var *mlx_var, int x0, int x1, int y0, int y1)
{
	int		deltax = abs(x1 - x0);
	int		deltay = abs(y1 - y0);
	int		error = 0;
	int		deltaerr = deltay;
	int		y = y0;
	int		diry = y1 - y0;

	if (diry > 0)
		diry = 1;
	if (diry < 0)
		diry = -1;
	while (x0 <= x1)
	{
		mlx_pixel_put(mlx_var->connect, mlx_var->main_window, x0, y, 185255100);
		error = error + deltaerr;
		if (2 * error >= deltax)
		{
			y = y + diry;
			error = error - deltax;
		}
		x0++;
	}
}

void	scalar_product_of_vectors(t_mlx_var *mlx_var)
{
	mlx_var->x = ((mlx_var->coordinates->x * mlx_var->basis_vector[X][X])
			+ (mlx_var->coordinates->y * mlx_var->basis_vector[Y][X])
			+ (mlx_var->coordinates->z * mlx_var->basis_vector[Z][X]));
	mlx_var->y = ((mlx_var->coordinates->x * mlx_var->basis_vector[X][Y])
			+ (mlx_var->coordinates->y * mlx_var->basis_vector[Y][Y])
			+ (mlx_var->coordinates->z * mlx_var->basis_vector[Z][Y]));
	mlx_var->z = ((mlx_var->coordinates->x * mlx_var->basis_vector[X][Z])
			+ (mlx_var->coordinates->y * mlx_var->basis_vector[Y][Z])
			+ (mlx_var->coordinates->z * mlx_var->basis_vector[Z][Z]));
}

void	display_pixels(t_mlx_var *mlx_var)
{
	double	x;
	double	y;
	int i;

	i = mlx_var->coordinates->prev->count + 1;
	while (i--)
	{
		scalar_product_of_vectors(mlx_var);
		x = mlx_var->width / 2 + mlx_var->x * mlx_var->scale;
		y = mlx_var->heigh / 2 + mlx_var->y * mlx_var->scale;
		mlx_pixel_put(mlx_var->connect, mlx_var->main_window, x, y, 185255100);
		mlx_var->coordinates = mlx_var->coordinates->next;
	}
}

int		key_press(int key_code, t_mlx_var *mlx_var)
{
	int	i;
	int x;
	int y;

	if (key_code == 69)
		mlx_var->scale++;
	else if (key_code == 78)
		mlx_var->scale > 0 ? mlx_var->scale-- : 0;
	else if (key_code == 126)
	{
		mlx_var->angle_x += 0.1;
		x_axis_rotation(mlx_var);
	}
	else if (key_code == 125)
	{
		mlx_var->angle_x -= 0.1;
		x_axis_rotation(mlx_var);
	}
	else if (key_code == 89)
	{
		mlx_var->angle_y += 0.1;
		y_axis_rotation(mlx_var);
	}
	else if (key_code == 83)
	{
		mlx_var->angle_y -= 0.1;
		y_axis_rotation(mlx_var);
	}
	else if (key_code == 123)
	{
		mlx_var->angle_z += 0.1;
		z_axis_ratation(mlx_var);
	}
	if (key_code == 124)
	{
		mlx_var->angle_z -= 0.1;
		z_axis_ratation(mlx_var);
	}
	mlx_clear_window(mlx_var->connect, mlx_var->main_window);
	display_pixels(mlx_var);
	return (0);
}

int		key_release(int key_code, void *param)
{
	return (0);
}

int		mouse_press(int button, int x, int y, void *param)
{
	return (0);
}

int		mouse_release(int button, int x, int y, void *param)
{
	return (0);
}

int		mouse_moove(int x, int y, void *param)
{
	return (0);
}

int		expose(void	*param)
{
	return (0);
}
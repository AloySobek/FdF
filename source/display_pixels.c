/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_pixels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 15:21:11 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/08 16:18:20 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_mlx_var *mlx_var, int x, int y)
{
	if (x < 0 || y < 0 || x >= mlx_var->screen.width || y >= mlx_var->screen.heigh)
		return ;
    *(int *)(mlx_var->data_addr + ((x + y * mlx_var->screen.width) * (mlx_var->bits_per_pixel / 8))) = 0x8b8970;
}

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
	pixel_put(mlx_var, x2, y2);
	while(x1 != x2 || y1 != y2)
	{
		pixel_put(mlx_var, x1, y1);
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

void	display_pixels(t_mlx_var *mlx_var)
{
	t_coords *tmp;
	double	x;
	double	y;
	int flag;
	int i;

	flag = 0;
	i = mlx_var->maps->prev->count + 1;
	ft_bzero(mlx_var->data_addr, mlx_var->screen.width * mlx_var->screen.heigh * 4);
	while (i--)
	{
		scalar_product_of_vectors(mlx_var, 0);
		if (flag && (mlx_var->maps->prev->x == (mlx_var->maps->x - 1)))
			display_line(mlx_var, x, y, mlx_var->screen.width / 2 + mlx_var->linear_algebra.vectors.x * mlx_var->screen.scale + mlx_var->linear_algebra.horizontal, mlx_var->screen.heigh / 2 + mlx_var->linear_algebra.vectors.y * mlx_var->screen.scale + mlx_var->linear_algebra.vertical);
		x = mlx_var->screen.width / 2 + mlx_var->linear_algebra.vectors.x * mlx_var->screen.scale + mlx_var->linear_algebra.horizontal;
		y = mlx_var->screen.heigh / 2 + mlx_var->linear_algebra.vectors.y * mlx_var->screen.scale + mlx_var->linear_algebra.vertical;
		if (mlx_var->maps->upper)
		{
			mlx_var->line = mlx_var->maps->upper;
			scalar_product_of_vectors(mlx_var, 1);
			display_line(mlx_var, x, y, mlx_var->screen.width / 2 + mlx_var->linear_algebra.vectors.x * mlx_var->screen.scale + mlx_var->linear_algebra.horizontal, mlx_var->screen.heigh / 2 + mlx_var->linear_algebra.vectors.y * mlx_var->screen.scale + mlx_var->linear_algebra.vertical);
		}
		pixel_put(mlx_var, x, y);
		mlx_var->maps = mlx_var->maps->next;
		flag = 1;
	}
	mlx_put_image_to_window(mlx_var->connect, mlx_var->main_window, mlx_var->main_image, 0, 0);
}
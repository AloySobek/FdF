/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_pixels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckatelin <ckatelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 15:21:11 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/09 17:25:07 by ckatelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_mlx_var *mlx_var, int x, int y, int colour)
{
	if (x < 0 || y < 0 || x >= mlx_var->screen.width || y >= mlx_var->screen.heigh)
		return ;
    *(int *)(mlx_var->data_addr + ((x + y * mlx_var->screen.width) * (mlx_var->bits_per_pixel / 8))) = colour;
}

void			display_line(t_mlx_var *mlx_var, int x1, int y1, int x2, int y2, t_col current)
{
//	int			delta.x;
//	int			delta.y;
	int			x_sign;
	int			y_sign;
	int			error;
	int			error2;
	t_col		start;
	t_col		end;
	t_col		delta;

	start.x = x1;
	start.y = y1;
	end.x = x2;
	end.y = y2;
	start.color = current.color;
	end.color = 0xfffafa;
//	current.color = 0x80;
	delta.x = abs(x2 - x1);
	delta.y = abs(y2 - y1);
	x_sign = x1 < x2 ? 1 : -1;
	y_sign = y1 < y2 ? 1 : -1;
	error = delta.x - delta.y;
	pixel_put(mlx_var, x2, y2, current.color);
	while(x1 != x2 || y1 != y2)
	{
//		ft_printf("%#x\n", current.color);
		current.color = get_color(current, start, end, delta);
		pixel_put(mlx_var, x1, y1, current.color);
		error2 = error * 2;
		if (error2 > -delta.y)
		{
			error -= delta.y;
			x1 += x_sign;
			current.x = x1;
		}
		if (error2 < delta.x)
		{
			error += delta.x;
			y1 += y_sign;
			current.y = y1;
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
	t_col	current;

	current.color = 0x800000;
	flag = 0;
	i = mlx_var->maps->prev->count + 1;
	ft_bzero(mlx_var->data_addr, mlx_var->screen.width * mlx_var->screen.heigh * 4);
	while (i--)
	{
		scalar_product_of_vectors(mlx_var, 0);
		if (mlx_var->linear_algebra.vectors.z)
			current.flag = 1;
		else
			current.flag = 0;
		if (flag && (mlx_var->maps->prev->x == (mlx_var->maps->x - 1)))
		{
			display_line(mlx_var, x, y, mlx_var->screen.width / 2 + mlx_var->linear_algebra.vectors.x * mlx_var->screen.scale + mlx_var->linear_algebra.horizontal, mlx_var->screen.heigh / 2 + mlx_var->linear_algebra.vectors.y * mlx_var->screen.scale + mlx_var->linear_algebra.vertical, current);
		}
		x = mlx_var->screen.width / 2 + mlx_var->linear_algebra.vectors.x * mlx_var->screen.scale + mlx_var->linear_algebra.horizontal;
		y = mlx_var->screen.heigh / 2 + mlx_var->linear_algebra.vectors.y * mlx_var->screen.scale + mlx_var->linear_algebra.vertical;
		if (mlx_var->maps->upper)
		{
			mlx_var->line = mlx_var->maps->upper;
			scalar_product_of_vectors(mlx_var, 1);
			display_line(mlx_var, x, y, mlx_var->screen.width / 2 + mlx_var->linear_algebra.vectors.x * mlx_var->screen.scale + mlx_var->linear_algebra.horizontal, mlx_var->screen.heigh / 2 + mlx_var->linear_algebra.vectors.y * mlx_var->screen.scale + mlx_var->linear_algebra.vertical, current);
		}
		pixel_put(mlx_var, x, y, current.color);
		mlx_var->maps = mlx_var->maps->next;
		flag = 1;
	}
	mlx_put_image_to_window(mlx_var->connect, mlx_var->main_window, mlx_var->main_image, 0, 0);
}
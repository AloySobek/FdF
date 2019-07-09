/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_pixels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 15:21:11 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/09 21:29:08 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_mlx_var *mlx_var, int x, int y, int color)
{
	int i;

	if (x < 0 || y < 0 || x >= mlx_var->screen.width || y >= mlx_var->screen.heigh)
		return ;
	i = (x * mlx_var->bits_per_pixel / 8) + (y * mlx_var->size_line);
    mlx_var->data_addr[i++] = color;
    mlx_var->data_addr[i++] = color >> 8;
    mlx_var->data_addr[i++] = color >> 16;
    mlx_var->data_addr[i] = 0;
}

int				get_color(t_mlx_var *mlx_var, int x0, int y0, int x1, int y1, int x, int y)
{
	int	red;
	int	red_start;
	int green;
	int green_start;
	int	blue;
	int	blue_start;
	int	color;

	if (x * y <= x0 * y0)
		return (mlx_var->color.start);
	else if (x * y >= x1 * y1)
		return (mlx_var->color.end);
	red_start = mlx_var->color.start >> 16;
	green_start = (mlx_var->color.start << 16) >> 24;
	blue_start = (mlx_var->color.start << 24) >> 24;
	red = mlx_var->color.end >> 16;
	green = (mlx_var->color.end << 16) >> 24;
	blue = (mlx_var->color.end << 24) >> 24;
	color |= blue_start + ((x1 * y1) - (x0 * y0)) / (blue - blue_start == 0 ? 1 : blue - blue_start) * ((x * y) - (x0 * y0));
	color |= (green_start + ((x1 * y1) - (x0 * y0)) / (green - green_start == 0 ? 1 : green - green_start) * ((x * y) - (x0 * y0))) << 8;
	color |= (red_start + ((x1 * y1) - (x0 * y0)) / (red - red_start == 0 ? 1 : red - red_start) * ((x * y) - (x0 * y0))) << 16;
	return (color);
}

void			display_line(t_mlx_var *mlx_var, int x1, int y1, int x2, int y2)
{
	int			x_delta;
	int			y_delta;
	int			x_sign;
	int			y_sign;
	int			error;
	int			error2;
	int			test1;
	int			test2;

	x_delta = abs(x2 - x1);
	y_delta = abs(y2 - y1);
	x_sign = x1 < x2 ? 1 : -1;
	y_sign = y1 < y2 ? 1 : -1;
	error = x_delta - y_delta;
	test1 = x1;
	test2 = x2;
	pixel_put(mlx_var, x2, y2, get_color(mlx_var, test1, test2, x2, y2, x1, y1));
	while(x1 != x2 || y1 != y2)
	{
		pixel_put(mlx_var, x1, y1, get_color(mlx_var, test1, test2, x2, y2, x1, y1));
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
		pixel_put(mlx_var, x, y, mlx_var->color.end);
		mlx_var->maps = mlx_var->maps->next;
		flag = 1;
	}
	mlx_put_image_to_window(mlx_var->connect, mlx_var->main_window, mlx_var->main_image, 0, 0);
}
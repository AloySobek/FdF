/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_pixels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 15:21:11 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/08 20:57:49 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_mlx_var *mlx_var, int x, int y, int colour)
{
	if (x < 0 || y < 0 || x >= mlx_var->screen.width || y >= mlx_var->screen.heigh)
		return ;
    *(int *)(mlx_var->data_addr + ((x + y * mlx_var->screen.width) * (mlx_var->bits_per_pixel / 8))) = colour;
}

void			display_line(t_mlx_var *mlx_var, int x1, int y1, int x2, int y2, int colour_start, int colour_end)
{
	int			x_delta;
	int			y_delta;
	int			x_sign;
	int			y_sign;
	int			error;
	int			error2;
	double		colour_one;
	double		colour_two;
	double		colour;
	int			test1;
	int			test2;

	x_delta = abs(x2 - x1);
	y_delta = abs(y2 - y1);
	x_sign = x1 < x2 ? 1 : -1;
	y_sign = y1 < y2 ? 1 : -1;
	error = x_delta - y_delta;
	pixel_put(mlx_var, x2, y2, colour_start);
	test1 = x1;
	test2 = y1;
	while(x1 != x2 || y1 != y2)
	{
		colour_one = x_delta * test1 + y_delta * test2;
		colour_two = x_delta * x2 + y_delta * y2;
		colour = x_delta * x1 + y_delta * y1;
		if (colour <= colour_one)
			pixel_put(mlx_var, x1, y1, colour_start);
		else if (colour >= colour_two)
			pixel_put(mlx_var, x1, y1, colour_end);
		else
			pixel_put(mlx_var, x1, y1, colour_start * (colour_two - colour) + colour_end * ((colour - colour_one) / (colour_two - colour_one)));
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
			display_line(mlx_var, x, y, mlx_var->screen.width / 2 + mlx_var->linear_algebra.vectors.x * mlx_var->screen.scale + mlx_var->linear_algebra.horizontal, mlx_var->screen.heigh / 2 + mlx_var->linear_algebra.vectors.y * mlx_var->screen.scale + mlx_var->linear_algebra.vertical, 0x80, 0x8b0000);
		x = mlx_var->screen.width / 2 + mlx_var->linear_algebra.vectors.x * mlx_var->screen.scale + mlx_var->linear_algebra.horizontal;
		y = mlx_var->screen.heigh / 2 + mlx_var->linear_algebra.vectors.y * mlx_var->screen.scale + mlx_var->linear_algebra.vertical;
		if (mlx_var->maps->upper)
		{
			mlx_var->line = mlx_var->maps->upper;
			scalar_product_of_vectors(mlx_var, 1);
			display_line(mlx_var, x, y, mlx_var->screen.width / 2 + mlx_var->linear_algebra.vectors.x * mlx_var->screen.scale + mlx_var->linear_algebra.horizontal, mlx_var->screen.heigh / 2 + mlx_var->linear_algebra.vectors.y * mlx_var->screen.scale + mlx_var->linear_algebra.vertical, 0x80, 0x8b0000);
		}
		pixel_put(mlx_var, x, y, 0x8b0000);
		mlx_var->maps = mlx_var->maps->next;
		flag = 1;
	}
	mlx_string_put(mlx_var->connect, mlx_var->main_window, mlx_var->screen.width / 10, mlx_var->screen.heigh / 10, 0xfffafa,  "Hello from that point and you are here");
	mlx_put_image_to_window(mlx_var->connect, mlx_var->main_window, mlx_var->main_image, 0, 0);
}
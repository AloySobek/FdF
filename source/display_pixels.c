/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_pixels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 15:21:11 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/10 21:33:37 by vrichese         ###   ########.fr       */
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

int				get_color(int f_col, int s_col, int length, int i, int fd)
{
	int	r;
	int	g;
	int	b;

	if (f_col == s_col)
		return (s_col);
	r = ((f_col >> 16) & 0xff) + (((s_col >> 16) & 0xff) - ((f_col >> 16) & 0xff)) / length * i;
	g = ((f_col >> 8) & 0xff) + (((s_col >> 8) & 0xff) - ((f_col >> 8) & 0xff)) / length * i;
	b = (f_col & 0xff) + ((s_col & 0xff) - (f_col & 0xff)) / length * i;
	//ft_printf("%d\n", (r << 16) | (g << 8) | b);
	return ((r << 16) | (g << 8) | b);
}

void			display_line(t_mlx_var *mlx_var, int x1, int y1, int x2, int y2)
{
	int			x_delta;
	int			y_delta;
	int			x_sign;
	int			y_sign;
	int			error;
	int			error2;
	int			length;
	int			i;

	i = 1;
	x_delta = abs(x2 - x1);
	y_delta = abs(y2 - y1);
	x_sign = x1 < x2 ? 1 : -1;
	y_sign = y1 < y2 ? 1 : -1;
	error = x_delta - y_delta;
	length = (int)sqrt(x_delta * x_delta + y_delta * y_delta);
	pixel_put(mlx_var, x2, y2, mlx_var->line->color);
	while(x1 != x2 || y1 != y2)
	{
		if (mlx_var->line->color < mlx_var->maps->color)
			pixel_put(mlx_var, x1, y1, get_color(mlx_var->line->color, mlx_var->maps->color, length, i++, mlx_var->test));
		else
			pixel_put(mlx_var, x1, y1, get_color(mlx_var->maps->color, mlx_var->line->color, length, i++, mlx_var->test));
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
		{
			mlx_var->line = mlx_var->maps->prev;
			display_line(mlx_var, x, y, mlx_var->screen.width / 2 + mlx_var->linear_algebra.vectors.x * mlx_var->screen.scale + mlx_var->linear_algebra.horizontal, mlx_var->screen.heigh / 2 + mlx_var->linear_algebra.vectors.y * mlx_var->screen.scale + mlx_var->linear_algebra.vertical);
		}
		x = mlx_var->screen.width / 2 + mlx_var->linear_algebra.vectors.x * mlx_var->screen.scale + mlx_var->linear_algebra.horizontal;
		y = mlx_var->screen.heigh / 2 + mlx_var->linear_algebra.vectors.y * mlx_var->screen.scale + mlx_var->linear_algebra.vertical;
		if (mlx_var->maps->upper)
		{
			mlx_var->line = mlx_var->maps->upper;
			scalar_product_of_vectors(mlx_var, 1);
			display_line(mlx_var, x, y, mlx_var->screen.width / 2 + mlx_var->linear_algebra.vectors.x * mlx_var->screen.scale + mlx_var->linear_algebra.horizontal, mlx_var->screen.heigh / 2 + mlx_var->linear_algebra.vectors.y * mlx_var->screen.scale + mlx_var->linear_algebra.vertical);
		}
		//pixel_put(mlx_var, x, y, mlx_var->maps->color);
		mlx_var->maps = mlx_var->maps->next;
		flag = 1;
	}
	mlx_put_image_to_window(mlx_var->connect, mlx_var->main_window, mlx_var->main_image, 0, 0);
}
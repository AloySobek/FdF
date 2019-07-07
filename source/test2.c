/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 15:23:20 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/07 20:52:09 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			add_frame(t_mlx_var *mlx_var)
{
	int x;
	int y;

	x = -1;
	while (++x < mlx_var->screen.width)
	{
		y = -1;
		while (++y < mlx_var->screen.heigh / 10)
			pixel_put(mlx_var, x, y);
	}
}

void	change_altitude(t_mlx_var *mlx_var, int up)
{
	int i;

	i = mlx_var->maps->prev->count + 1;
	if (up)
	{
		while (i--)
		{
			if (mlx_var->maps->z > 0)
				mlx_var->maps->z++;
			else if (mlx_var->maps->z < 0)
				mlx_var->maps->z--;
			mlx_var->maps = mlx_var->maps->next;
		}
	}
	else
	{
		while (i--)
		{
			if (mlx_var->maps->z > 0 && mlx_var->maps->z > mlx_var->maps->z_tmp)
				mlx_var->maps->z--;
			else if(mlx_var->maps->z < 0 && mlx_var->maps->z < mlx_var->maps->z_tmp)
				mlx_var->maps->z++;
			mlx_var->maps = mlx_var->maps->next;
		}
	}
}

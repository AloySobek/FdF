/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 15:23:20 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/11 20:56:13 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			add_hint(t_mlx_var *mlx_var)
{
	mlx_string_put(mlx_var->connect, mlx_var->main_window, mlx_var->screen.width / 20, mlx_var->screen.heigh / 20, 0xfffafa,  "Control:");
	mlx_string_put(mlx_var->connect, mlx_var->main_window, mlx_var->screen.width / 20, mlx_var->screen.heigh / 20 + 15, 0xfffafa,  "Zoom: Scroll Up(+) Scrool Down(-)");
	mlx_string_put(mlx_var->connect, mlx_var->main_window, mlx_var->screen.width / 20, mlx_var->screen.heigh / 20 + 30, 0xfffafa,  "Rotate: Mouse move(right, left button press)");
	mlx_string_put(mlx_var->connect, mlx_var->main_window, mlx_var->screen.width / 20, mlx_var->screen.heigh / 20 + 45, 0xfffafa,  "Move: 'z' button then left button mouse move");
	mlx_string_put(mlx_var->connect, mlx_var->main_window, mlx_var->screen.width / 20, mlx_var->screen.heigh / 20 + 60, 0xfffafa,  "Debug mode: 'g'");
	mlx_string_put(mlx_var->connect, mlx_var->main_window, mlx_var->screen.width / 20, mlx_var->screen.heigh / 20 + 75, 0xfffafa,  "Change color: 1, 2, 3 button at the left panel");
	mlx_string_put(mlx_var->connect, mlx_var->main_window, mlx_var->screen.width / 20, mlx_var->screen.heigh / 20 + 90, 0xfffafa,  "Change sensitivity rotate: Up(+), Down(-)");
	mlx_string_put(mlx_var->connect, mlx_var->main_window, mlx_var->screen.width / 20, mlx_var->screen.heigh / 20 + 105, 0xfffafa,  "Change sensitivity move: Up_end(+), Down_end(-)");
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

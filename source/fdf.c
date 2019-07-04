/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 16:11:31 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/04 20:51:03 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				main(int argc, char **argv)
{
	t_mlx_var	*mlx_var;
	int			fd;

	mlx_var = (t_mlx_var *)malloc(sizeof(t_mlx_var));
	argc == 1 ? error_handler(8) : 0;
	(fd = open(argv[1], O_RDONLY)) < 0 ? error_handler(9) : 0;
	mlx_var->width = 1920;
	mlx_var->heigh = 1080;
	mlx_var->scale = 15;
	mlx_var->angle_x = 0;
	mlx_var->angle_y = 0;
	mlx_var->angle_z = 0;
	mlx_var->basis_vector[0][0] = 1;
	mlx_var->basis_vector[0][1] = 0;
	mlx_var->basis_vector[0][2] = 0;
	mlx_var->basis_vector[1][0] = 0;
	mlx_var->basis_vector[1][1] = 1;
	mlx_var->basis_vector[1][2] = 0;
	mlx_var->basis_vector[2][0] = 0;
	mlx_var->basis_vector[2][1] = 0;
	mlx_var->basis_vector[2][2] = 1;
	mlx_var->coordinates = reading_and_write_coordinates(fd);
	if (!(mlx_var->connect = mlx_init()))
		error_handler(1);
	if (!(mlx_var->main_window = mlx_new_window(mlx_var->connect, mlx_var->width, mlx_var->heigh, "FdF")))
		error_handler(2);
	mlx_var->width -= mlx_var->coordinates->prev->x / 2 * 15;
	mlx_var->heigh -= mlx_var->coordinates->prev->y / 2 * 15;
	mlx_hook(mlx_var->main_window, 2, 0, key_press, mlx_var);
	mlx_loop(mlx_var->connect);
}
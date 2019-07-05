/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 16:11:31 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/05 18:49:10 by vrichese         ###   ########.fr       */
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
	mlx_var->scale = 25;
	mlx_var->angle_x = 0;
	mlx_var->angle_y = 0;
	mlx_var->angle_z = 0;
	mlx_var->coordinates = reading_and_write_coordinates(fd);
	if (!(mlx_var->connect = mlx_init()))
		error_handler(1);
	if (!(mlx_var->main_window = mlx_new_window(mlx_var->connect, mlx_var->width, mlx_var->heigh, "FdF")))
		error_handler(2);
	view_from_above(mlx_var);
	mlx_var->width -= mlx_var->coordinates->prev->x / 2 * 15;
	mlx_var->heigh -= mlx_var->coordinates->prev->y / 2 * 15;
	mlx_hook(mlx_var->main_window, 2, 0, key_press, mlx_var);
	mlx_hook(mlx_var->main_window, 4, 0, mouse_press, mlx_var);
	mlx_hook(mlx_var->main_window, 5, 0, mouse_release, mlx_var);
	mlx_hook(mlx_var->main_window, 6, 0, mouse_moove, mlx_var);
	mlx_loop(mlx_var->connect);
}
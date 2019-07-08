/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 16:11:31 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/08 14:23:54 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			fasten_event_handlers(t_mlx_var *mlx_var)
{
	mlx_hook(mlx_var->main_window, 2, 0, key_press, mlx_var);
	mlx_hook(mlx_var->main_window, 3, 0, key_release, mlx_var);
	mlx_hook(mlx_var->main_window, 4, 0, mouse_press, mlx_var);
	mlx_hook(mlx_var->main_window, 5, 0, mouse_release, mlx_var);
	mlx_hook(mlx_var->main_window, 6, 0, mouse_moove, mlx_var);
	mlx_hook(mlx_var->main_window, 12, 0, expose, mlx_var);
	mlx_hook(mlx_var->main_window, 17, 0, close_window, mlx_var);
}

int				main(int argc, char **argv)
{
	t_mlx_var	*mlx_var;
	int			fd;

	mlx_var = (t_mlx_var *)malloc(sizeof(t_mlx_var));
	argc == 1 ? error_handler(8) : 0;
	(fd = open(argv[1], O_RDONLY)) < 0 ? error_handler(9) : 0;
	mlx_var->screen.width = 1920;
	mlx_var->screen.heigh = 1080;
	mlx_var->screen.scale = 15;
	mlx_var->linear_algebra.angle_x = 0;
	mlx_var->linear_algebra.angle_y = 0;
	mlx_var->linear_algebra.angle_z = 0;
	mlx_var->maps = reading_and_write_coordinates(fd);
	mlx_var->flags.debug_mode = 0;
	if (!(mlx_var->connect = mlx_init()))
		error_handler(1);
	if (!(mlx_var->main_window = mlx_new_window(mlx_var->connect, mlx_var->screen.width, mlx_var->screen.heigh, "FdF")))
		error_handler(2);
	if (!(mlx_var->main_image = mlx_new_image(mlx_var->connect, mlx_var->screen.width, mlx_var->screen.heigh)))
		error_handler(3);
	if (!(mlx_var->data_addr = mlx_get_data_addr(mlx_var->main_image, &mlx_var->bits_per_pixel, &mlx_var->size_line, &mlx_var->endian)))
		error_handler(4);
	fasten_event_handlers(mlx_var);
	mlx_loop(mlx_var->connect);
}
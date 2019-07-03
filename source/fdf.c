/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 16:11:31 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/03 21:16:03 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				main(int argc, char **argv)
{
	t_coords	*coordinates;
	void		*connect;
	void		*main_window;
	int			width;
	int			heigh;
	int			fd;

	argc == 1 ? error_handler(8) : 0;
	(fd = open(argv[1], O_RDONLY)) < 0 ? error_handler(9) : 0;
	// width = ft_atoi(argv[2]);
	// heigh = ft_atoi(argv[3]);
	width = 1920;
	heigh = 1080;
	coordinates = reading_and_write_coordinates(fd);
	if (!(connect = mlx_init()))
		error_handler(1);
	if (!(main_window = mlx_new_window(connect, width, heigh, "FdF")))
		error_handler(2);
	width -= coordinates->prev->x / 2 * 15;
	heigh -= coordinates->prev->y / 2 * 15;
	int i = coordinates->prev->count + 1;
	while (i--)
	{
		mlx_pixel_put(connect, main_window, width / 2 + (coordinates->x * 15), heigh / 2 + (coordinates->y * 15), 111255211);
		coordinates = coordinates->next;
	}
	mlx_loop(connect);
}
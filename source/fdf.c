/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 16:11:31 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/02 21:16:32 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				main(int argc, char **argv)
{
	t_coords	*test;
	void		*connect;
	void		*main_window;

	if (!(connect = mlx_init()))
		error_handler(1);
	if (!(main_window = mlx_new_window(connect, 1920, 1080, "FdF")))
		error_handler(2);
	mlx_string_put(connect, main_window, 1500, 500, 185255100, "Vanya ti budesh delat fdf???????");
	mlx_loop(connect);
	test = reading_and_write_coordinates(argv[1]);
}
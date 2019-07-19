/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 17:47:45 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/19 13:53:46 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_handler(int code_of_errors)
{
	if (code_of_errors == 1)
		ft_printf("Connection hasn't been established, exit...\n");
	else if (code_of_errors == 2)
		ft_printf("Window hasn't been created, exit...\n");
	else if (code_of_errors == 3)
		ft_printf("Image object hasn't been created, exit...\n");
	else if (code_of_errors == 4)
		ft_printf("Data addres hasn't been got, exit...\n");
	else if (code_of_errors == 5)
		ft_printf("The program has been forsibly completed...\n");
	else if (code_of_errors == 6)
		ft_printf("The program has been closed...\n");
	else if (code_of_errors == 7)
		ft_printf("Main mlx variable hasn't been initializied, exit...\n");
	else if (code_of_errors == 8)
		ft_printf("Number of args is zero, exit...\n");
	else if (code_of_errors == 9)
		ft_printf("File hasn't been opened, exit...\n");
	else if (code_of_errors == 10)
		ft_printf("Memory hasn't been allocated, exit...\n");
	else if (code_of_errors == 11)
		ft_printf("Not valid file! Nothing hasn't been readed\n");
	exit(1);
}

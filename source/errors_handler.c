/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 17:47:45 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/03 20:38:55 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_handler(int code_of_errors)
{
	if (code_of_errors == 1)
		ft_printf("Connection hasn't been established, exit...\n");
	else if (code_of_errors == 2)
		ft_printf("Window hasn't been created, exit...\n");
	else if (code_of_errors == 8)
		ft_printf("Qantity of args is zero, exit...\n");
	else if (code_of_errors == 9)
		ft_printf("File hasn't been opened, exit...\n");
	else if (code_of_errors == 10)
		ft_printf("Memory hasn't been allocated, exit...\n");
	exit(1);
}
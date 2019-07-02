/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 17:47:45 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/02 18:36:18 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_handler(int code_of_errors)
{
	if (code_of_errors == 1)
		ft_printf("Connection hasn't been established, exit...");
	else if (code_of_errors == 2)
		ft_printf("Window hasn't been created, exit...");
	else if (code_of_errors == 9)
		ft_printf("File hasn't been opened, exit...");
	else if (code_of_errors == 10)
		ft_printf("Memory hasn't been allocated, exit...");
	exit(1);
}
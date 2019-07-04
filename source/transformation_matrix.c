/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_matrix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 19:11:46 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/04 22:01:02 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	x_axis_rotation(t_mlx_var *mlx_var)
{
	mlx_var->basis_vector[Y][Y] = cos(mlx_var->angle_x);
	mlx_var->basis_vector[Y][Z] = sin(mlx_var->angle_x);
	mlx_var->basis_vector[Z][Y] = -sin(mlx_var->angle_x);
	mlx_var->basis_vector[Z][Z] = cos(mlx_var->angle_x);
}

void	y_axis_rotation(t_mlx_var *mlx_var)
{
	mlx_var->basis_vector[X][X] = cos(mlx_var->angle_y);
	mlx_var->basis_vector[Z][X] = sin(mlx_var->angle_y);
	mlx_var->basis_vector[X][Z] = -sin(mlx_var->angle_y);
	mlx_var->basis_vector[Z][Z] = cos(mlx_var->angle_y);
}

void	z_axis_ratation(t_mlx_var *mlx_var)
{
	mlx_var->basis_vector[X][X] = cos(mlx_var->angle_z);
	mlx_var->basis_vector[X][Y] = -sin(mlx_var->angle_z);
	mlx_var->basis_vector[Y][X] = sin(mlx_var->angle_z);
	mlx_var->basis_vector[Y][Y] = cos(mlx_var->angle_z);
}
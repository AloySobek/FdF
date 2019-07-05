/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_matrix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 19:11:46 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/05 21:16:18 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	x_axis_rotation(t_mlx_var *mlx_var)
{
	mlx_var->basis_vector[X][X] = 1;
	mlx_var->basis_vector[X][Y] = 0;
	mlx_var->basis_vector[X][Z] = 0;
	mlx_var->basis_vector[Y][X] = 0;
	mlx_var->basis_vector[Y][Y] = cos(mlx_var->angle_x);
	mlx_var->basis_vector[Y][Z] = sin(mlx_var->angle_x);
	mlx_var->basis_vector[Z][X] = 0;
	mlx_var->basis_vector[Z][Y] = -sin(mlx_var->angle_x);
	mlx_var->basis_vector[Z][Z] = cos(mlx_var->angle_x);
}

void	y_axis_rotation(t_mlx_var *mlx_var)
{
	mlx_var->basis_vector[X][X] = cos(mlx_var->angle_y);
	mlx_var->basis_vector[X][Y] = 0;
	mlx_var->basis_vector[X][Z] = -sin(mlx_var->angle_y);
	mlx_var->basis_vector[Y][X] = 0;
	mlx_var->basis_vector[Y][Y] = 1;
	mlx_var->basis_vector[Y][Z] = 0;
	mlx_var->basis_vector[Z][X] = sin(mlx_var->angle_y);
	mlx_var->basis_vector[Z][Y] = 0;
	mlx_var->basis_vector[Z][Z] = cos(mlx_var->angle_y);
}

void	z_axis_rotation(t_mlx_var *mlx_var)
{
	mlx_var->basis_vector[X][X] = cos(mlx_var->angle_z);
	mlx_var->basis_vector[X][Y] = -sin(mlx_var->angle_z);
	mlx_var->basis_vector[X][Z] = 0;
	mlx_var->basis_vector[Y][X] = sin(mlx_var->angle_z);
	mlx_var->basis_vector[Y][Y] = cos(mlx_var->angle_z);
	mlx_var->basis_vector[Y][Z] = 0;
	mlx_var->basis_vector[Z][Z] = 0;
	mlx_var->basis_vector[Z][Y] = 0;
	mlx_var->basis_vector[Z][Z] = 1;
}

void	x_y_axis_rotation(t_mlx_var *mlx_var)
{
	mlx_var->basis_vector[X][X] = cos(mlx_var->angle_y);
	mlx_var->basis_vector[X][Y] = -sin(mlx_var->angle_x) * -sin(mlx_var->angle_y);
	mlx_var->basis_vector[X][Z] = -sin(mlx_var->angle_y) * cos(mlx_var->angle_x);
	mlx_var->basis_vector[Y][X] = 0;
	mlx_var->basis_vector[Y][Y] = cos(mlx_var->angle_x);
	mlx_var->basis_vector[Y][Z] = sin(mlx_var->angle_x);
	mlx_var->basis_vector[Z][X] = sin(mlx_var->angle_y);
	mlx_var->basis_vector[Z][Y] = -sin(mlx_var->angle_x) * cos(mlx_var->angle_y);
	mlx_var->basis_vector[Z][Z] = cos(mlx_var->angle_x) * cos(mlx_var->angle_y);
}
void	x_y_z_axis_rotation(t_mlx_var *mlx_var)
{
	mlx_var->basis_vector[X][X] = cos(mlx_var->angle_y) * cos(mlx_var->angle_z);
	mlx_var->basis_vector[X][Y] = -sin(mlx_var->angle_x) * -sin(mlx_var->angle_y) * cos(mlx_var->angle_z) + (cos(mlx_var->angle_x) * sin(mlx_var->angle_z));
	mlx_var->basis_vector[X][Z] = -sin(mlx_var->angle_y) * cos(mlx_var->angle_x) * cos(mlx_var->angle_z) + (sin(mlx_var->angle_z) * sin(mlx_var->angle_x));
	mlx_var->basis_vector[Y][X] = cos(mlx_var->angle_y) * -sin(mlx_var->angle_z);
	mlx_var->basis_vector[Y][Y] = cos(mlx_var->angle_x) * cos(mlx_var->angle_z) + (-sin(mlx_var->angle_x) * -sin(mlx_var->angle_y) * -sin(mlx_var->angle_z));
	mlx_var->basis_vector[Y][Z] = sin(mlx_var->angle_x) * cos(mlx_var->angle_z) + (-sin(mlx_var->angle_z) * -sin(mlx_var->angle_y) * cos(mlx_var->angle_x));
	mlx_var->basis_vector[Z][X] = sin(mlx_var->angle_y);
	mlx_var->basis_vector[Z][Y] = -sin(mlx_var->angle_x) * cos(mlx_var->angle_y);
	mlx_var->basis_vector[Z][Z] = cos(mlx_var->angle_x) * cos(mlx_var->angle_y);
}
void	view_from_above(t_mlx_var *mlx_var)
{
	mlx_var->basis_vector[X][X] = 1;
	mlx_var->basis_vector[X][Y] = 0;
	mlx_var->basis_vector[X][Z] = 0;
	mlx_var->basis_vector[Y][X] = 0;
	mlx_var->basis_vector[Y][Y] = 1;
	mlx_var->basis_vector[Y][Z] = 0;
	mlx_var->basis_vector[Z][X] = 0;
	mlx_var->basis_vector[Z][Y] = 0;
	mlx_var->basis_vector[Z][Z] = 1;
}

void	to_mirror_image(t_mlx_var *mlx_var)
{
	mlx_var->basis_vector[X][X] = -1;
	mlx_var->basis_vector[X][Y] = 0;
	mlx_var->basis_vector[X][Z] = 0;
	mlx_var->basis_vector[Y][X] = 0;
	mlx_var->basis_vector[Y][Y] = -1;
	mlx_var->basis_vector[Y][Z] = 0;
	mlx_var->basis_vector[Z][X] = 0;
	mlx_var->basis_vector[Z][Y] = 0;
	mlx_var->basis_vector[Z][Z] = 1;
}
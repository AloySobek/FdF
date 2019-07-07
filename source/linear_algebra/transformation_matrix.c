/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_matrix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 19:11:46 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/07 20:51:41 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	x_axis_rotation(t_mlx_var *mlx_var)
{
	mlx_var->linear_algebra.basis_vectors[X][X]
			= 1;
	mlx_var->linear_algebra.basis_vectors[X][Y]
			= 0;
	mlx_var->linear_algebra.basis_vectors[X][Z]
			= 0;
	mlx_var->linear_algebra.basis_vectors[Y][X]
			= 0;
	mlx_var->linear_algebra.basis_vectors[Y][Y]
			= cos(mlx_var->linear_algebra.angle_x);
	mlx_var->linear_algebra.basis_vectors[Y][Z]
			= sin(mlx_var->linear_algebra.angle_x);
	mlx_var->linear_algebra.basis_vectors[Z][X]
			= 0;
	mlx_var->linear_algebra.basis_vectors[Z][Y]
			= -sin(mlx_var->linear_algebra.angle_x);
	mlx_var->linear_algebra.basis_vectors[Z][Z]
			= cos(mlx_var->linear_algebra.angle_x);
}

void	y_axis_rotation(t_mlx_var *mlx_var)
{
	mlx_var->linear_algebra.basis_vectors[X][X]
			= cos(mlx_var->linear_algebra.angle_y);
	mlx_var->linear_algebra.basis_vectors[X][Y]
			= 0;
	mlx_var->linear_algebra.basis_vectors[X][Z]
			= -sin(mlx_var->linear_algebra.angle_y);
	mlx_var->linear_algebra.basis_vectors[Y][X]
			= 0;
	mlx_var->linear_algebra.basis_vectors[Y][Y]
			= 1;
	mlx_var->linear_algebra.basis_vectors[Y][Z]
			= 0;
	mlx_var->linear_algebra.basis_vectors[Z][X]
			= sin(mlx_var->linear_algebra.angle_y);
	mlx_var->linear_algebra.basis_vectors[Z][Y]
			= 0;
	mlx_var->linear_algebra.basis_vectors[Z][Z]
			= cos(mlx_var->linear_algebra.angle_y);
}

void	z_axis_rotation(t_mlx_var *mlx_var)
{
	mlx_var->linear_algebra.basis_vectors[X][X]
			= cos(mlx_var->linear_algebra.angle_z);
	mlx_var->linear_algebra.basis_vectors[X][Y]
			= -sin(mlx_var->linear_algebra.angle_z);
	mlx_var->linear_algebra.basis_vectors[X][Z]
			= 0;
	mlx_var->linear_algebra.basis_vectors[Y][X]
			= sin(mlx_var->linear_algebra.angle_z);
	mlx_var->linear_algebra.basis_vectors[Y][Y]
			= cos(mlx_var->linear_algebra.angle_z);
	mlx_var->linear_algebra.basis_vectors[Y][Z]
			= 0;
	mlx_var->linear_algebra.basis_vectors[Z][Z]
			= 0;
	mlx_var->linear_algebra.basis_vectors[Z][Y]
			= 0;
	mlx_var->linear_algebra.basis_vectors[Z][Z]
			= 1;
}

void	x_y_axis_rotation(t_mlx_var *mlx_var)
{
	mlx_var->linear_algebra.basis_vectors[X][X]
			= cos(mlx_var->linear_algebra.angle_y);
	mlx_var->linear_algebra.basis_vectors[X][Y]
			= -sin(mlx_var->linear_algebra.angle_x)
			* -sin(mlx_var->linear_algebra.angle_y);
	mlx_var->linear_algebra.basis_vectors[X][Z]
			= -sin(mlx_var->linear_algebra.angle_y)
			* cos(mlx_var->linear_algebra.angle_x);
	mlx_var->linear_algebra.basis_vectors[Y][X]
			= 0;
	mlx_var->linear_algebra.basis_vectors[Y][Y]
			= cos(mlx_var->linear_algebra.angle_x);
	mlx_var->linear_algebra.basis_vectors[Y][Z]
			= sin(mlx_var->linear_algebra.angle_x);
	mlx_var->linear_algebra.basis_vectors[Z][X]
			= sin(mlx_var->linear_algebra.angle_y);
	mlx_var->linear_algebra.basis_vectors[Z][Y]
			= -sin(mlx_var->linear_algebra.angle_x)
			* cos(mlx_var->linear_algebra.angle_y);
	mlx_var->linear_algebra.basis_vectors[Z][Z]
			= cos(mlx_var->linear_algebra.angle_x)
			* cos(mlx_var->linear_algebra.angle_y);
}

void	x_z_axis_rotation(t_mlx_var *mlx_var)
{

}

void	y_z_axis_rotation(t_mlx_var *mlx_var)
{

}

void	x_y_z_axis_rotation(t_mlx_var *mlx_var)
{
	mlx_var->linear_algebra.basis_vectors[X][X]
			= cos(mlx_var->linear_algebra.angle_y)
			* cos(mlx_var->linear_algebra.angle_z);
	mlx_var->linear_algebra.basis_vectors[X][Y]
			= -sin(mlx_var->linear_algebra.angle_x)
			* -sin(mlx_var->linear_algebra.angle_y)
			* cos(mlx_var->linear_algebra.angle_z)
			+ (cos(mlx_var->linear_algebra.angle_x)
			* sin(mlx_var->linear_algebra.angle_z));
	mlx_var->linear_algebra.basis_vectors[X][Z]
			= -sin(mlx_var->linear_algebra.angle_y)
			* cos(mlx_var->linear_algebra.angle_x)
			* cos(mlx_var->linear_algebra.angle_z)
			+ (sin(mlx_var->linear_algebra.angle_z)
			* sin(mlx_var->linear_algebra.angle_x));
	mlx_var->linear_algebra.basis_vectors[Y][X]
			= cos(mlx_var->linear_algebra.angle_y)
			* -sin(mlx_var->linear_algebra.angle_z);
	mlx_var->linear_algebra.basis_vectors[Y][Y]
			= cos(mlx_var->linear_algebra.angle_x)
			* cos(mlx_var->linear_algebra.angle_z)
			+ (-sin(mlx_var->linear_algebra.angle_x)
			* -sin(mlx_var->linear_algebra.angle_y)
			* -sin(mlx_var->linear_algebra.angle_z));
	mlx_var->linear_algebra.basis_vectors[Y][Z]
			= sin(mlx_var->linear_algebra.angle_x)
			* cos(mlx_var->linear_algebra.angle_z)
			+ (-sin(mlx_var->linear_algebra.angle_z)
			* -sin(mlx_var->linear_algebra.angle_y)
			* cos(mlx_var->linear_algebra.angle_x));
	mlx_var->linear_algebra.basis_vectors[Z][X]
			= sin(mlx_var->linear_algebra.angle_y);
	mlx_var->linear_algebra.basis_vectors[Z][Y]
			= -sin(mlx_var->linear_algebra.angle_x)
			* cos(mlx_var->linear_algebra.angle_y);
	mlx_var->linear_algebra.basis_vectors[Z][Z]
			= cos(mlx_var->linear_algebra.angle_x)
			* cos(mlx_var->linear_algebra.angle_y);
}

void	view_from_above(t_mlx_var *mlx_var)
{
	mlx_var->linear_algebra.basis_vectors[X][X]
			= 1;
	mlx_var->linear_algebra.basis_vectors[X][Y]
			= 0;
	mlx_var->linear_algebra.basis_vectors[X][Z]
			= 0;
	mlx_var->linear_algebra.basis_vectors[Y][X]
			= 0;
	mlx_var->linear_algebra.basis_vectors[Y][Y]
			= 1;
	mlx_var->linear_algebra.basis_vectors[Y][Z]
			= 0;
	mlx_var->linear_algebra.basis_vectors[Z][X]
			= 0;
	mlx_var->linear_algebra.basis_vectors[Z][Y]
			= 0;
	mlx_var->linear_algebra.basis_vectors[Z][Z]
			= 1;
}

void	to_mirror_image(t_mlx_var *mlx_var)
{
	mlx_var->linear_algebra.basis_vectors[X][X]
			= -1;
	mlx_var->linear_algebra.basis_vectors[X][Y]
			= 0;
	mlx_var->linear_algebra.basis_vectors[X][Z]
			= 0;
	mlx_var->linear_algebra.basis_vectors[Y][X]
			= 0;
	mlx_var->linear_algebra.basis_vectors[Y][Y]
			= -1;
	mlx_var->linear_algebra.basis_vectors[Y][Z]
			= 0;
	mlx_var->linear_algebra.basis_vectors[Z][X]
			= 0;
	mlx_var->linear_algebra.basis_vectors[Z][Y]
			= 0;
	mlx_var->linear_algebra.basis_vectors[Z][Z]
			= 1;
}
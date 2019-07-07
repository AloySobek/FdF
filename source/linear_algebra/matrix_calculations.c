/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_calculations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 17:25:43 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/07 20:24:14 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scalar_product_of_vectors(t_mlx_var *mlx_var, int line)
{
	if (!line)
	{
		mlx_var->linear_algebra.vectors.x
			= ((mlx_var->maps->x * mlx_var->linear_algebra.basis_vectors[X][X])
			+ (mlx_var->maps->y * mlx_var->linear_algebra.basis_vectors[Y][X])
			+ (mlx_var->maps->z * mlx_var->linear_algebra.basis_vectors[Z][X]));
		mlx_var->linear_algebra.vectors.y
			= ((mlx_var->maps->x * mlx_var->linear_algebra.basis_vectors[X][Y])
			+ (mlx_var->maps->y * mlx_var->linear_algebra.basis_vectors[Y][Y])
			+ (mlx_var->maps->z * mlx_var->linear_algebra.basis_vectors[Z][Y]));
		mlx_var->linear_algebra.vectors.z
			= ((mlx_var->maps->x * mlx_var->linear_algebra.basis_vectors[X][Z])
			+ (mlx_var->maps->y * mlx_var->linear_algebra.basis_vectors[Y][Z])
			+ (mlx_var->maps->z * mlx_var->linear_algebra.basis_vectors[Z][Z]));
	}
	else
	{
		mlx_var->linear_algebra.vectors.x
			= ((mlx_var->line->x * mlx_var->linear_algebra.basis_vectors[X][X])
			+ (mlx_var->line->y * mlx_var->linear_algebra.basis_vectors[Y][X])
			+ (mlx_var->line->z * mlx_var->linear_algebra.basis_vectors[Z][X]));
		mlx_var->linear_algebra.vectors.y
			= ((mlx_var->line->x * mlx_var->linear_algebra.basis_vectors[X][Y])
			+ (mlx_var->line->y * mlx_var->linear_algebra.basis_vectors[Y][Y])
			+ (mlx_var->line->z * mlx_var->linear_algebra.basis_vectors[Z][Y]));
		mlx_var->linear_algebra.vectors.z
			= ((mlx_var->line->x * mlx_var->linear_algebra.basis_vectors[X][Z])
			+ (mlx_var->line->y * mlx_var->linear_algebra.basis_vectors[Y][Z])
			+ (mlx_var->line->z * mlx_var->linear_algebra.basis_vectors[Z][Z]));
	}
}

void	linemultiply_three_dimensional_matrix(t_mlx_var *mlx_var, int x, int y, int howmuch)
{
	return ;
}

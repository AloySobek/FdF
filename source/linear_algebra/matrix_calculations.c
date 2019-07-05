/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_calculations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 17:25:43 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/05 21:18:56 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scalar_product_of_vectors(t_mlx_var *mlx_var)
{
	mlx_var->x = ((mlx_var->coordinates->x * mlx_var->basis_vector[X][X])
				+ (mlx_var->coordinates->y * mlx_var->basis_vector[Y][X])
				+ (mlx_var->coordinates->z * mlx_var->basis_vector[Z][X]));
	mlx_var->y = ((mlx_var->coordinates->x * mlx_var->basis_vector[X][Y])
				+ (mlx_var->coordinates->y * mlx_var->basis_vector[Y][Y])
				+ (mlx_var->coordinates->z * mlx_var->basis_vector[Z][Y]));
	mlx_var->z = ((mlx_var->coordinates->x * mlx_var->basis_vector[X][Z])
				+ (mlx_var->coordinates->y * mlx_var->basis_vector[Y][Z])
				+ (mlx_var->coordinates->z * mlx_var->basis_vector[Z][Z]));
}

void	multiply_three_dimensional_matrix(t_mlx_var *mlx_var, int x, int y, int howmuch)
{
	return ;
}

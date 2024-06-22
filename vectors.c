/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwiecek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:26:00 by mwiecek           #+#    #+#             */
/*   Updated: 2024/06/21 16:42:06 by mwiecek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "fdf.h"

t_Vec	vec_add(t_Vec v1, t_Vec v2)
{
	t_Vec	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	return (result);
}

t_Vec	vec_sub(t_Vec v1, t_Vec v2)
{
	t_Vec	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	return (result);
}

t_Vec	vec_mul(t_Vec v, float factor)
{
	t_Vec	result;

	result.x = v.x * factor;
	result.y = v.y * factor;
	return (result);
}

t_Vect	init_vectors(void)
{
	float	vector_scale;
	float	sqrt_3_over_2;
	t_Vect	vectors;

	vector_scale = 10.0f;
	sqrt_3_over_2 = 0.5f;
	vectors.start.x = 0;
	vectors.start.y = 0;
	vectors.next_column.x = vector_scale;
	vectors.next_column.y = -vector_scale * sqrt_3_over_2;
	vectors.next_row.x = vector_scale;
	vectors.next_row.y = vector_scale * sqrt_3_over_2;
	vectors.up.x = 0;
	vectors.up.y = -vector_scale;
	return (vectors);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwiecek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:36:57 by mwiecek           #+#    #+#             */
/*   Updated: 2024/06/21 16:40:43 by mwiecek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "fdf.h"

void	swap(t_Vec *a, t_Vec *b)
{
	t_Vec	tmp;

	tmp = *b;
	*b = *a;
	*a = tmp;
}

void	free_2d_array(int **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	free_board(t_Board board)
{
	free_2d_array(board.array);
	free_2d_array(board.colors);
}

float	my_abs(float a)
{
	if (a > 0)
		return (a);
	else
		return (-a);
}

int	array_length(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		++i;
	}
	return (i);
}

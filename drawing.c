/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwiecek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:19:38 by mwiecek           #+#    #+#             */
/*   Updated: 2024/06/21 16:55:28 by mwiecek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "fdf.h"

void	draw_line_x(t_Mlx m, t_Vec start, t_Vec end, int color)
{
	double	y;
	double	dy;
	double	x;

	if (start.x > end.x)
		swap(&start, &end);
	y = start.y;
	dy = (double)(end.y - start.y) / (double)(end.x - start.x);
	x = start.x;
	while (x <= end.x)
	{
		mlx_pixel_put(m.mlx, m.mlx_win, (int)(x + 0.5), (int)(y + 0.5), color);
		y += dy;
		++x;
	}
}

void	draw_line_y(t_Mlx m, t_Vec start, t_Vec end, int color)
{
	double	x;
	double	dx;
	double	y;

	if (start.y > end.y)
		swap(&start, &end);
	x = start.x;
	dx = (double)(end.x - start.x) / (double)(end.y - start.y);
	y = start.y;
	while (y <= end.y)
	{
		mlx_pixel_put(m.mlx, m.mlx_win, (int)(x + 0.5), (int)(y + 0.5), color);
		x += dx;
		++y;
	}
}

void	draw_line(t_Mlx m, t_Vec start, t_Vec end, int color)
{
	if (my_abs(end.x - start.x) > my_abs(end.y - start.y))
		draw_line_x(m, start, end, color);
	else
		draw_line_y(m, start, end, color);
}

t_Drawing	get_drawing_min_max(t_Drawing drawing, t_Vec current)
{
	if (current.x < drawing.min.x)
		drawing.min.x = current.x;
	if (current.y < drawing.min.y)
		drawing.min.y = current.y;
	if (current.x > drawing.max.x)
		drawing.max.x = current.x;
	if (current.y > drawing.max.y)
		drawing.max.y = current.y;
	return (drawing);
}

t_Drawing	get_drawing_size(t_Board t_Board, t_Vectors t_Vectors)
{
	int			i;
	int			j;
	t_Drawing	drawing;
	t_Vec		current;

	drawing.min.x = +1000000.0f;
	drawing.max.x = -1000000.0f;
	drawing.min.y = +1000000.0f;
	drawing.max.y = -1000000.0f;
	i = 0;
	while (i < t_Board.nbr_of_rows)
	{
		j = 0;
		while (j < t_Board.nbr_of_cols)
		{
			current = get_current_point(t_Vectors, t_Board, i, j++);
			drawing = get_drawing_min_max(drawing, current);
		}
		++i;
	}
	drawing.size.x = drawing.max.x - drawing.min.x;
	drawing.size.y = drawing.max.y - drawing.min.y;
	drawing.center.x = (drawing.max.x + drawing.min.x) * 0.5;
	drawing.center.y = (drawing.max.y + drawing.min.y) * 0.5;
	return (drawing);
}

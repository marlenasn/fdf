/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwiecek <mwiecek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:35:06 by mwiecek           #+#    #+#             */
/*   Updated: 2024/06/21 16:57:02 by mwiecek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "fdf.h"

t_Vec	get_current_point(t_Vectors t_Vectors, t_Board t_Board, int i, int j)
{
	t_Vec	current;
	int		height;

	if (i < 0)
		i = 0;
	if (j < 0)
		j = 0;
	current = t_Vectors.start;
	current = vec_add(current, vec_mul(t_Vectors.next_row, i));
	current = vec_add(current, vec_mul(t_Vectors.next_column, j));
	height = t_Board.array[i][j];
	current = vec_add(current, vec_mul(t_Vectors.up, height));
	return (current);
}

t_Board	get_board_or_error(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
	{
		write(1, "Incorrect number of arguments\n", 31);
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write(1, "Failed to open file\n", 21);
		exit(1);
	}
	return (parse_to_array(argv, fd));
}

t_Vectors	recalculate_vectors(t_Vectors vectors, t_Drawing drawing)
{
	float	ratio;
	float	ratio_w;
	float	ratio_h;
	t_Vec	window_center;
	t_Vec	movement;

	vectors.window.x = 1400.0f;
	vectors.window.y = 800.0f;
	ratio_w = drawing.size.x / vectors.window.x;
	ratio_h = drawing.size.y / vectors.window.y;
	if (vectors.window.y / vectors.window.x < drawing.size.y / drawing.size.x)
		ratio = ratio_h;
	else
		ratio = ratio_w;
	vectors.next_column = vec_mul(vectors.next_column, 1.0 / ratio);
	vectors.next_row = vec_mul(vectors.next_row, 1.0 / ratio);
	vectors.up = vec_mul(vectors.up, 1.0 / ratio);
	window_center.x = vectors.window.x * 0.5f;
	window_center.y = vectors.window.y * 0.5f;
	drawing.center = vec_mul(drawing.center, 1.0 / ratio);
	movement = vec_sub(drawing.center, window_center);
	vectors.start = vec_sub(vectors.start, movement);
	return (vectors);
}

void	draw_board(t_Mlx m, t_Board board, t_Vectors vectors)
{
	int		i;
	int		j;
	t_Vec	current;
	t_Vec	above;
	t_Vec	to_the_left;

	i = 0;
	while (i < board.nbr_of_rows)
	{
		j = 0;
		while (j < board.nbr_of_cols)
		{
			current = get_current_point(vectors, board, i, j);
			above = get_current_point(vectors, board, i - 1, j);
			draw_line(m, above, current, board.colors[i][j]);
			to_the_left = get_current_point(vectors, board, i, j - 1);
			draw_line(m, to_the_left, current, board.colors[i][j]);
			++j;
		}
		++i;
	}
}

int	main(int argc, char **argv)
{
	t_Board		board;
	t_Vectors	vectors;
	t_Drawing	drawing;
	t_Mlx		m;

	board = get_board_or_error(argc, argv);
	vectors = init_vectors();
	drawing = get_drawing_size(board, vectors);
	vectors = recalculate_vectors(vectors, drawing);
	m.mlx = mlx_init();
	m.mlx_win = mlx_new_window(m.mlx, vectors.window.x, vectors.window.y, "F");
	draw_board(m, board, vectors);
	mlx_key_hook(m.mlx_win, handle_key, NULL);
	mlx_hook(m.mlx_win, 17, 0, handle_closing, NULL);
	mlx_loop(m.mlx);
	free_board(board);
}

#include "fdf.h"
/*
int	close_window(t_env *env)
{
	mlx_destroy_window(env->mlx, env->win);
	exit(0);
}

int	key_handler(int keycode, t_env *env)
{
	if (keycode == 53)
		close_window(env);
}
*/

void swap(t_Vec *a, t_Vec *b)
{
	t_Vec	tmp;

	tmp = *b;
	*b = *a;
	*a = tmp;
}

typedef struct t_Mlx {
	void *mlx;
	void *mlx_win;
} t_Mlx;

void draw_line_x(t_Mlx m, t_Vec start, t_Vec end, int color)
{
	double y;
	double dy;
	double x;

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

void draw_line_y(t_Mlx m, t_Vec start, t_Vec end, int color)
{
	double x;
	double dx;
	double y;

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
	if (abs(end.x - start.x) > abs(end.y - start.y))
		draw_line_x(m, start, end, color);
	else
		draw_line_y(m, start, end, color);
}

t_Vec	get_current_point(t_Vectors t_Vectors, t_Board t_Board, int i, int j)
{
	t_Vec	current;
	int	height;

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

t_Drawing get_drawing_min_max(t_Drawing drawing, t_Vec current)
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
	int	i;
	int	j;
	t_Drawing	drawing;
	t_Vec	current;

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

void draw_board(t_Mlx m, t_Board board, t_Vectors vectors)
{
	int	i;
	int	j;
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

t_Board get_board_or_error(int argc, char **argv)
{
	int fd;

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

	return (parse_to_array(argc, argv, fd));
}

t_Vectors init_vectors(void)
{
	float	vector_scale;
	float	sqrt_3_over_2;
	t_Vectors vectors;

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

t_Vectors recalculate_vectors(t_Vectors vectors, t_Drawing drawing)
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

int	handle_key(int keycode, void *param)
{
	if (keycode == ESC_KEY || keycode == ESC_KEY_LINUX)
		exit(0);
	return (0);
}

int	handle_closing(void *param)
{
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_Board	board;
	t_Vectors	vectors;
	t_Drawing	drawing;
	t_Mlx m;

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
}

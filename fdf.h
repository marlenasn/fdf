/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwiecek <mwiecek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:58:12 by mwiecek           #+#    #+#             */
/*   Updated: 2024/06/21 17:14:18 by mwiecek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define ESC_KEY 53
# define ESC_KEY_LINUX 65307

# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>

typedef struct t_Vec
{
	float	x;
	float	y;
}	t_Vec;

t_Vec	vec_add(t_Vec v1, t_Vec v2);
t_Vec	vec_sub(t_Vec v1, t_Vec v2);
t_Vec	vec_mul(t_Vec v, float factor);

typedef struct t_Vect
{
	t_Vec	start;
	t_Vec	next_column;
	t_Vec	next_row;
	t_Vec	up;
	t_Vec	window;
}	t_Vectors;

typedef struct t_Board
{
	int	**array;
	int	**colors;
	int	nbr_of_rows;
	int	nbr_of_cols;
}	t_Board;

typedef struct t_Draw
{
	t_Vec	center;
	t_Vec	size;
	t_Vec	min;
	t_Vec	max;
}	t_Drawing;

typedef struct t_Mlx
{
	void	*mlx;
	void	*mlx_win;
}	t_Mlx;

t_Board	parse_to_array(char **argv, int fd);
int		ft_atoi(const char *str);
int		hexatoi(const char *str);
void	*ft_free(char **element);
int		handle_key(int keycode, void *param);
int		handle_closing(void *param);
void	draw_line_x(t_Mlx m, t_Vec start, t_Vec end, int color);
void	draw_line_y(t_Mlx m, t_Vec start, t_Vec end, int color);
void	draw_line(t_Mlx m, t_Vec start, t_Vec end, int color);
t_Draw	get_drawing_min_max(t_Drawing drawing, t_Vec current);
t_Draw	get_drawing_size(t_Board t_Board, t_Vectors t_Vectors);
void	swap(t_Vec *a, t_Vec *b);
void	free_2d_array(int **array);
void	free_board(t_Board board);
float	my_abs(float a);
t_Vect	init_vectors(void);
t_Vec	vec_mul(t_Vec v, float factor);
t_Vec	vec_sub(t_Vec v1, t_Vec v2);
t_Vec	vec_add(t_Vec v1, t_Vec v2);
#endif

#ifndef FDF_H
# define FDF_H

#define ESC_KEY 53
#define ESC_KEY_LINUX 65307

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

typedef struct t_Vectors
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

typedef struct t_Drawing
{
	t_Vec	center;
	t_Vec	size;
	t_Vec	min;
	t_Vec	max;
}	t_Drawing;

t_Board	parse_to_array(int argc, char **argv, int fd);

#endif

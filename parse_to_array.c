#include "get_next_line.h"
#include "libft.h"
#include "fdf.h"

static int	white_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (9 <= str[i] && str[i] <= 13))
	{
		i++;
	}
	return (i);
}

static int	ft_sign(const char *str)
{
	int	i;

	i = white_spaces(str);
	if (str[i] == '-')
		return (1);
	if (str[i] == '+' || (str[i] >= '0' && str[i] <= '9'))
		return (0);
	return (-1);
}

int	ft_atoi(const char *str)
{
	int	a;
	int	i;

	i = white_spaces(str);
	a = 0;
	if (ft_sign(str) == -1)
		return (0);
	if (ft_sign(str) == 1)
		i++;
	if (ft_sign(str) == 0)
		i += (int)(str[i] == '+');
	while ('0' <= str[i] && str[i] <= '9')
		a = a * 10 + (str[i++] - 48);
	if (ft_sign(str) == 1)
		a = -a;
	return (a);
}

int	hexatoi(const char *str)
{
	int	a;
	int	i;

	i = white_spaces(str);
	i += 2;
	a = 0;
	while (('0' <= str[i] && str[i] <= '9') || ('a' <= str[i] && str[i] <= 'f'))
	{
		if ('0' <= str[i] && str[i] <= '9')
			a = a * 16 + (str[i] - '0');
		else
			a = a * 16 + (str[i] - 'a' + 10);
		++i;
	}
	return (a);
}

int	get_nbr_of_rows(char *file)
{
	int	nbr;
	int	fd;

	nbr = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(1, "Failed to open file\n", 21);
		exit (1);
	}
	while (1)
	{
		if (!get_next_line(fd))
			return (nbr);
		nbr++;
	}
	return (nbr);
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

t_Board	init_board(char **argv)
{
	t_Board board;

	board.nbr_of_rows = get_nbr_of_rows(argv[1]);
	board.nbr_of_cols = 0;
	board.array = (int **)malloc(board.nbr_of_rows * sizeof(int *));
	board.colors = (int **)malloc((board.nbr_of_rows) * sizeof(int *));
	return (board);
}

int	get_color(char *color_element)
{
	if (color_element)
		return (hexatoi(color_element));
	else
		return (0xffffff);
}

t_Board	parse_to_array(char **argv, int fd)
{
	char	**tmp;
	char	**element;
	int		i;
	int		j;
	t_Board	board;

	i = 0;
	board = init_board(argv);
	while (i < board.nbr_of_rows)
	{
		j = 0;
		tmp = ft_split(get_next_line(fd), ' ');
		if (board.nbr_of_cols == 0)
			board.nbr_of_cols = array_length(tmp);
		board.array[i] = (int *)malloc(board.nbr_of_cols * sizeof(int));
		board.colors[i] = (int *)malloc(board.nbr_of_cols * sizeof(int));
		while (j < board.nbr_of_cols)
		{
			element = ft_split(tmp[j], ',');
			board.array[i][j] = ft_atoi(element[0]);
			board.colors[i][j++] = get_color(element[1]);
		}
		i++;
	}
	return (board);
}

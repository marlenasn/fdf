/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwiecek <mwiecek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:22:52 by mwiecek           #+#    #+#             */
/*   Updated: 2024/06/21 16:11:10 by mwiecek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "fdf.h"

int	get_nbr_of_rows(char *file)
{
	int		nbr;
	int		fd;
	char	*line;

	nbr = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(1, "Failed to open file\n", 21);
		exit (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (nbr);
		free(line);
		nbr++;
	}
	return (nbr);
}

t_Board	init_board(char **argv)
{
	t_Board	board;

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

void	setup_board(t_Board *board, int i, char **tmp)
{
	if (board->nbr_of_cols == 0)
		board->nbr_of_cols = array_length(tmp);
	board->array[i] = (int *)malloc(board->nbr_of_cols * sizeof(int));
	board->colors[i] = (int *)malloc(board->nbr_of_cols * sizeof(int));
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
		setup_board(&board, i, tmp);
		while (j < board.nbr_of_cols)
		{
			element = ft_split(tmp[j], ',');
			board.array[i][j] = ft_atoi(element[0]);
			board.colors[i][j++] = get_color(element[1]);
			ft_free(element);
		}
		free(tmp);
		i++;
	}
	return (board);
}

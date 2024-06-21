/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwiecek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:48:51 by mwiecek           #+#    #+#             */
/*   Updated: 2024/03/13 12:47:16 by mwiecek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	str_len(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

static int	words_count(const char *str, char c)
{
	int	how_many_words;
	int	j;

	j = 0;
	how_many_words = 0;
	while (j < str_len(str))
	{
		if (str[j] != c)
		{
			while (str[j] && str[j] != c)
				j++;
			how_many_words++;
		}
		j++;
	}
	return (how_many_words);
}

void	*free_arrays(char **arrays, int j)
{
	while (--j >= 0)
	{
		free(arrays[j]);
	}
	return (NULL);
}

char	**ft_split(const char *str, char c)
{
	char	**final_array;
	size_t	last_i;
	size_t	j;
	size_t	i;

	final_array = (char **)malloc((words_count(str, c) + 1) * sizeof(char *));
	if (final_array == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (j < (size_t)words_count(str, c))
	{
		while (str[i] == c && str[i])
			i++;
		last_i = i;
		while (str[i] != c && str[i])
			i++;
		final_array[j] = (char *)malloc((i - last_i + 1) * sizeof(char));
		if (!final_array[j])
			return (free_arrays(final_array, j));
		ft_strlcpy(final_array[j++], str + last_i, i - last_i + 1);
	}
	final_array[j] = NULL;
	free((void *)str);
	return (final_array);
}

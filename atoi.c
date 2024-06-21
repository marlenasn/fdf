/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwiecek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:24:04 by mwiecek           #+#    #+#             */
/*   Updated: 2024/06/21 16:10:39 by mwiecek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	*ft_free(char **element)
{
	free(element[0]);
	free(element[1]);
	free(element);
}

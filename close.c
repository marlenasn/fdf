/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwiecek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:17:54 by mwiecek           #+#    #+#             */
/*   Updated: 2024/06/21 16:19:32 by mwiecek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "fdf.h"

int	handle_key(int keycode, void *param)
{
	(void)param;
	if (keycode == ESC_KEY || keycode == ESC_KEY_LINUX)
		exit(0);
	return (0);
}

int	handle_closing(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

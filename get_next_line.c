/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:25:50 by vegret            #+#    #+#             */
/*   Updated: 2022/10/13 15:25:50 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int str_index(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*tmp;
	int			r;

	tmp = malloc(BUFFER_SIZE * sizeof(char));
	r = read(fd, tmp, BUFFER_SIZE);
	if (r == -1)
	{
		free(tmp);
		return (NULL);
	}
	stash = malloc(sizeof(char));
	*stash = 0;
	stash = concat(stash, tmp);
	while (str_index(stash, '\n') == -1)
	{
		r = read(fd, tmp, BUFFER_SIZE);
		if (r == -1)
		{
			free(tmp);
			return (NULL);
		}
		stash = concat(stash, tmp);
		if (r < BUFFER_SIZE)
			break;
	}

	
}

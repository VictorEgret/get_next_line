/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:25:50 by vegret            #+#    #+#             */
/*   Updated: 2022/10/20 22:23:20 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_next_line(int fd, char *stash, int *len)
{
	char	*tmp;
	int		rd;

	rd = BUFFER_SIZE;
	*len = ft_strlen(stash);
	tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	*tmp = '\0';
	while (rd == BUFFER_SIZE && strindex(tmp, '\n') == -1)
	{
		rd = read(fd, tmp, BUFFER_SIZE);
		if (rd == -1)
			break ;
		tmp[rd] = '\0';
		stash = strconcat(stash, tmp, *len, rd);
		if (!stash)
			break ;
		*len += rd;
	}
	free(tmp);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FILES];
	int			len;

	if (fd < 0 || BUFFER_SIZE < 1 || fd >= MAX_FILES)
		return (NULL);
	stash[fd] = read_next_line(fd, stash[fd], &len);
	if (!stash[fd] || !*stash[fd])
		return (NULL);
	return (get_line(&stash[fd], len));
}

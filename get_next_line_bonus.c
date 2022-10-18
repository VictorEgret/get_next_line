/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:25:50 by vegret            #+#    #+#             */
/*   Updated: 2022/10/18 15:36:57 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_next_line(int fd, char **stash, int *endl)
{
	char	*tmp;
	int		rd;

	rd = BUFFER_SIZE;
	while (rd == BUFFER_SIZE && *endl == -1)
	{
		tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!tmp)
		{
			free(*stash);
			return (NULL);
		}
		rd = read(fd, tmp, BUFFER_SIZE);
		if (rd == -1)
		{
			free(*stash);
			free(tmp);
			return (NULL);
		}
		tmp[rd] = '\0';
		*stash = strconcat(*stash, tmp);
		free(tmp);
		*endl = strindex(*stash, '\n');
	}
	return (*stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FILES];
	char		*line;
	char		*old_stash;
	int			endl;

	if (fd < 0 || BUFFER_SIZE < 1 || fd >= MAX_FILES)
		return (NULL);
	endl = -1;
	read_next_line(fd, &stash[fd], &endl);
	if (!stash[fd] || !*stash[fd])
		return (NULL);
	if (endl == -1)
		endl = ft_strlen(stash[fd]);
	line = ft_substr(stash[fd], 0, endl + 1);
	old_stash = stash[fd];
	stash[fd] = ft_substr(stash[fd], endl + 1, ft_strlen(stash[fd]) + 1);
	if (old_stash)
		free(old_stash);
	return (line);
}

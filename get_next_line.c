/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:25:50 by vegret            #+#    #+#             */
/*   Updated: 2022/10/18 01:24:39 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_next_line(int fd, char *stash, int *endl)
{
	char	*tmp;
	int		rd;

	rd = BUFFER_SIZE;
	tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	while (rd == BUFFER_SIZE && *endl == -1)
	{
		rd = read(fd, tmp, BUFFER_SIZE);
		if (rd == -1)
			break ;
		tmp[rd] = '\0';
		stash = strconcat(stash, tmp);
		if (!stash)
			break ;
		*endl = strindex(stash, '\n');
	}
	free(tmp);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*old_stash;
	int			endl;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	endl = -1;
	stash = read_next_line(fd, stash, &endl);
	if (!stash || !*stash)
		return (NULL);
	if (endl == -1)
		endl = ft_strlen(stash);
	line = ft_substr(stash, 0, endl + 1);
	old_stash = stash;
	stash = ft_substr(stash, endl + 1, ft_strlen(stash) + 1);
	if (old_stash)
		free(old_stash);
	return (line);
}

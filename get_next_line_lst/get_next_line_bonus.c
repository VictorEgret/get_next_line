/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:25:50 by vegret            #+#    #+#             */
/*   Updated: 2022/11/10 13:54:01 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	read_next_line(int fd, t_list **stash, int *line_length)
{
	int		rd;
	t_list	*new;
	t_list	*prev;

	rd = BUFFER_SIZE;
	prev = ft_lstlast(*stash);
	while (rd == BUFFER_SIZE)
	{
		new = ft_lstnew();
		if (!new)
			break ;
		rd = read(fd, new->content, BUFFER_SIZE);
		if (rd == 0 || rd == -1)
			return (free(new));
		(new->content)[rd] = '\0';
		if (!prev)
			*stash = new;
		else
			prev->next = new;
		prev = new;
		*line_length += rd;
		if (strindex(new->content, '\n') != -1)
			break ;
	}
}

void	remove_first_line(t_list **stash)
{
	t_list	*tmp;
	int		i;
	int		j;

	if (!stash || !*stash)
		return ;
	while (*stash && strindex((*stash)->content, '\n') == -1)
	{
		tmp = (*stash)->next;
		free(*stash);
		*stash = tmp;
	}
	if (!*stash)
		return ;
	i = strindex((*stash)->content, '\n') + 1;
	j = 0;
	while ((*stash)->content[i])
		(*stash)->content[j++] = (*stash)->content[i++];
	(*stash)->content[j] = '\0';
	if (ft_strlstlen(*stash) == 0)
	{
		free(*stash);
		*stash = NULL;
	}
}

char	*get_next_line(int fd)
{
	static t_list	*stashs[MAX_FILES];
	char			*line;
	int				line_length;

	if (fd < 0 || BUFFER_SIZE < 1 || fd >= MAX_FILES)
		return (NULL);
	line_length = ft_strlstlen(stashs[fd]);
	read_next_line(fd, &stashs[fd], &line_length);
	if (!stashs[fd] || line_length == 0)
		return (NULL);
	line = get_line(stashs[fd], line_length);
	remove_first_line(&stashs[fd]);
	return (line);
}

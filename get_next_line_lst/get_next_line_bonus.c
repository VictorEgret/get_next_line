/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:25:50 by vegret            #+#    #+#             */
/*   Updated: 2022/11/06 14:43:29 by vegret           ###   ########.fr       */
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
		if (rd < 1)
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
}

#include <stdio.h>

t_list	*get_stash(t_map **stashs, int fd)
{
	t_map	*tmp;
	t_map	*prev;

	prev = NULL;
	tmp = *stashs;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp->stash);
		prev = tmp;
		tmp = tmp->next;
	}
	tmp = malloc(sizeof(t_map));
	if (!tmp)
		return (NULL);
	tmp->fd = fd;
	tmp->next = NULL;
	tmp->stash = NULL;
	if (!prev)
		*stashs = tmp;
	else
		prev->next = tmp;
	return (tmp->stash);
}

char	*get_next_line(int fd)
{
	static t_map	*stashs;
	t_list			*stash;
	char			*line;
	int				line_length;

	if (fd < 0 || BUFFER_SIZE < 1 || fd >= MAX_FILES)
		return (NULL);
	stash = get_stash(&stashs, fd);
	line_length = ft_strlstlen(stash);
	read_next_line(fd, &stash, &line_length);
	if (!stash || line_length == 0)
		return (NULL);
	line = get_line(stash, line_length);
	remove_first_line(&stash);
	return (line);
}

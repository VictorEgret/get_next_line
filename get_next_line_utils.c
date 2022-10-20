/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:26:22 by vegret            #+#    #+#             */
/*   Updated: 2022/10/20 22:17:37 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*((unsigned char *) dest + i) = *((unsigned char *) src + i);
		i++;
	}
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*get_line(char **stash, int len)
{
	int		endl;
	char	*line;
	char	*new_stash;

	endl = strindex(*stash, '\n') + 1;
	if (endl == 0)
		endl = len;
	line = malloc((endl + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ft_memcpy(line, *stash, endl);
	line[endl] = '\0';
	new_stash = malloc((len - endl + 1) * sizeof(char));
	if (!new_stash)
		return (NULL);
	ft_memcpy(new_stash, *stash + endl, len - endl);
	new_stash[len - endl] = '\0';
	free(*stash);
	*stash = new_stash;
	return (line);
}

char	*strconcat(char *s1, char *s2, int s1len, int s2len)
{
	char	*result;

	result = malloc((s1len + s2len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	if (s1)
		ft_memcpy(result, s1, s1len);
	if (s2)
		ft_memcpy(result + s1len * (s1 != NULL), s2, s2len);
	result[s1len + s2len] = '\0';
	free(s1);
	return (result);
}

int	strindex(char *str, char c)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

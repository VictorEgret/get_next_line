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

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	ft_strcpy(char	*dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

char	*ft_substr(char *s, unsigned int start, size_t len, int f)
{
	char	*result;
	size_t	result_len;

	if (!s || ft_strlen(s) <= start)
	{
		result = malloc(sizeof(char));
		*result = '\0';
		if (f)
			free(s);
		return (result);
	}
	result_len = ft_strlen(s) - start;
	if (result_len > len)
		result_len = len;
	result = malloc(result_len + 1);
	if (!result)
		return (NULL);
	ft_strcpy(result, s + start);
	if (f)
		free(s);
	return (result);
}

char	*ft_strdup(const char *s)
{
	char	*result;
	int		i;

	result = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*strconcat(char *s1, char *s2)
{
	char	*result;

	if (!s1)
		return (ft_strdup(s2));
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	ft_strcpy(result, s1);
	ft_strcpy(result + ft_strlen(s1), s2);
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

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*tmp;
	int			rd;
	int			endl;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	rd = BUFFER_SIZE;
	endl = -1;
	while (rd == BUFFER_SIZE && endl == -1)
	{
		tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!tmp)
			return (NULL);
		rd = read(fd, tmp, BUFFER_SIZE);
		if (rd == -1)
		{
			free(stash);
			free(tmp);
			return (NULL);
		}
		tmp[rd] = '\0';
		stash = strconcat(stash, tmp);
		free(tmp);
		endl = strindex(stash, '\n');
	}
	if (!*stash)
		return (NULL);
	if (endl == -1)
		endl = ft_strlen(stash);
	tmp = ft_substr(stash, 0, endl + 1, 0);
	stash = ft_substr(stash, endl + 1, ft_strlen(stash) + 1, 1);
	return (tmp);
}

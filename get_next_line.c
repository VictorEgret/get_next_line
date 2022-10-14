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
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define BUFFER_SIZE 8

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

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	result_len;

	if (!s || ft_strlen(s) <= start)
	{
		result = malloc(sizeof(char));
		*result = '\0';
		return (result);
	}
	result_len = ft_strlen(s) - start;
	if (result_len > len)
		result_len = len;
	result = malloc(result_len + 1);
	if (!result)
		return (NULL);
	result = ft_memcpy(result, s + start, result_len);
	result[result_len] = '\0';
	return (result);
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
	dest[i] = 0;
}

void	ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i])
		i++;
	j = i;
	while (src[i - j])
	{
		dest[i] = src[i - j];
		i++;
	}
	dest[i] = 0;
}

char	*strconcat(char *s1, char *s2)
{
	char	*result;

	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	*result = 0;
	ft_strcpy(result, s1);
	ft_strcat(result, s2);
	free(s1);
	return (result);
}

int	strindex(char *str, char c)
{
	int	i;

	i = 0;
	while(str[i])
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

	stash = malloc(BUFFER_SIZE * sizeof(char));
	if (!stash)
		return (NULL);
	rd = read(fd, stash, BUFFER_SIZE);
	if (rd == -1)
		return (NULL);
	stash[rd] = 0;
	//write(1, "HERE\n", 5);
	while (rd == BUFFER_SIZE && strindex(stash, '\n') == -1)
	{
		tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
		rd = read(fd, tmp, BUFFER_SIZE);
		if (rd == -1)
		{
			free(stash);
			free(tmp);
			return (NULL);
		}
		tmp[rd] = 0;
		printf("tmp: %s\n", tmp);
		stash = strconcat(stash, tmp); // convertir pour un pointer -> tableau 
		free(tmp);
	}
	return (ft_substr(stash, 0, strindex(stash, '\n') + 1)); // convertir pour un pointer -> tableau 
}

int main()
{
	int fd = open("test.txt", O_RDONLY);
	//get_next_line(fd);
	//get_next_line(fd);
	//printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));

	return 0;
}

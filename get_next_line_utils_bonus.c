/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:26:22 by vegret            #+#    #+#             */
/*   Updated: 2022/10/18 15:37:01 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*ft_substr(char *s, unsigned int start, size_t len)
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

char	*strconcat(char *s1, char *s2)
{
	char	*result;
	int		len;

	len = ft_strlen(s2);
	if (!s1)
	{
		result = malloc((len + 1) * sizeof(char));
		if (!result)
			return (NULL);
		ft_memcpy(result, s2, len);
		result[len] = '\0';
		return (result);
	}
	len += ft_strlen(s1);
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, ft_strlen(s1));
	ft_memcpy(result + ft_strlen(s1), s2, ft_strlen(s2));
	result[len] = '\0';
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

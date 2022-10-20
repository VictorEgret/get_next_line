/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:25:56 by vegret            #+#    #+#             */
/*   Updated: 2022/10/20 22:18:01 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*get_line(char **stash, int len);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*strconcat(char *s1, char *s2, int s1len, int s2len);
size_t	ft_strlen(const char *s);
int		strindex(char *str, char c);

#endif

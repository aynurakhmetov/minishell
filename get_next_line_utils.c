/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 13:18:38 by gmarva            #+#    #+#             */
/*   Updated: 2020/12/25 10:20:43 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	size_t counter;

	counter = 0;
	if (!str)
		return (0);
	while (str[counter] != '\0')
		counter++;
	return (counter);
}

void	*ft_memmove(void *des, const void *src, size_t n)
{
	unsigned char	*to;
	unsigned char	*from;
	size_t			i;

	i = 0;
	if (!des && !src)
		return (NULL);
	to = (unsigned char *)des;
	from = (unsigned char *)src;
	if (to < from)
	{
		while (i < n)
		{
			to[i] = from[i];
			i++;
		}
	}
	if (to > from)
	{
		while (n-- > 0)
			to[n] = from[n];
	}
	return (des);
}

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		m;
	int		index;

	index = 0;
	m = 0;
	if (src == NULL)
		return (NULL);
	while (src[m] != '\0')
		m++;
	dest = (char*)malloc(m + 1);
	if (!dest)
		return (NULL);
	while (src[index] != '\0')
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

char	*ft_strjoin2(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	s1len;
	size_t	s2len;

	j = 0;
	if (!s1 && !s2)
		return (0);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (!(str = (char *)malloc((s1len + s2len + 1) * sizeof(char))))
	{
		free((char *)s1);
		return (0);
	}
	i = -1;
	while (++i < s1len)
		str[i] = s1[i];
	while (j < s2len)
		str[i++] = s2[j++];
	str[i] = '\0';
	free((char *)s1);
	return (str);
}

char	*ft_strchr(const char *str, int ch)
{
	int	i;

	i = 0;
	while (str[i] != ch)
	{
		if (str[i] == '\0')
			return (NULL);
		i++;
	}
	if (str[i] == ch)
		return ((char *)&str[i]);
	return (NULL);
}

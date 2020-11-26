/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 08:14:26 by ajeanett          #+#    #+#             */
/*   Updated: 2020/07/23 10:31:50 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		m;
	int		index;

	index = 0;
	m = 0;
	while (src[m] != '\0')
	{
		m = m + 1;
	}
	dest = (char*)malloc(sizeof(*src) * (m + 1));
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

size_t	ft_strlen(const char *str)
{
	int	m;

	m = 0;
	while (str[m] != '\0')
	{
		m = m + 1;
	}
	return (m);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	unsigned int	buf;
	char			*str;

	buf = ft_strlen(s1) + ft_strlen(s2);
	str = ((char *)malloc(sizeof(char) * (buf + 1)));
	if (!str)
		return (NULL);
	while (*s1 != '\0')
	{
		*str++ = *s1++;
	}
	while (*s2 != '\0')
	{
		*str++ = *s2++;
	}
	*str++ = '\0';
	return (str - (buf + 1));
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (c == '\0')
		return ((char*)s + ft_strlen(s));
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
	return (dest);
}

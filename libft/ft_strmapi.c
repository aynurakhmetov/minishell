/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 19:40:42 by ajeanett          #+#    #+#             */
/*   Updated: 2020/05/30 16:09:54 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	s_strlen(const char *str)
{
	int	m;

	m = 0;
	while (str[m] != '\0')
	{
		m = m + 1;
	}
	return (m);
}

char			*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	size_t			len;
	unsigned int	i;

	i = 0;
	len = s_strlen(s);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

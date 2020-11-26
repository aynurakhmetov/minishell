/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 19:40:11 by ajeanett          #+#    #+#             */
/*   Updated: 2020/11/24 20:55:12 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

// char	*ft_strdup(const char *s)
// {
// 	unsigned char *t;

// 	t = ft_calloc(ft_strlen(s) + 1, sizeof(char));
// 	if (t)
// 		return (ft_memmove(t, s, ft_strlen(s) + 1));
// 	return (NULL);
// }
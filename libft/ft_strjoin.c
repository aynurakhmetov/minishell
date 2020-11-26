/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 19:40:17 by ajeanett          #+#    #+#             */
/*   Updated: 2020/05/30 16:09:37 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
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

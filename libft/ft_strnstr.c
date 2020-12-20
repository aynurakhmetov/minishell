/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 19:40:55 by ajeanett          #+#    #+#             */
/*   Updated: 2020/05/31 19:31:59 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *sml, size_t size)
{
	size_t	i;
	size_t	m;

	i = 0;
	m = 0;
	if (*sml == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < size)
	{
		if (big[i] == sml[0])
		{
			while (big[i + m] == sml[m] && sml[m] != '\0' && i + m < size)
				m++;
			if (sml[m] == '\0')
				return ((char *)big + i);
			m = 0;
		}
		i++;
	}
	return (NULL);
}

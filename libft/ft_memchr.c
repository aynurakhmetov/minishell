/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 19:38:57 by ajeanett          #+#    #+#             */
/*   Updated: 2020/05/30 16:08:44 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	size_t			i;
	unsigned char	*s;

	i = 0;
	s = (unsigned char*)arr;
	while (i < n)
	{
		if (s[i] == (unsigned char)c)
			return (((unsigned char*)arr) + i);
		i++;
	}
	return (NULL);
}

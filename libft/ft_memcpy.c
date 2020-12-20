/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 19:39:11 by ajeanett          #+#    #+#             */
/*   Updated: 2020/05/30 16:08:54 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*s_ptr;
	unsigned char		*d_ptr;

	if (!dst && !src)
		return (NULL);
	s_ptr = (const unsigned char*)src;
	d_ptr = (unsigned char*)dst;
	while (n--)
	{
		*d_ptr++ = *s_ptr++;
	}
	return ((unsigned char *)dst);
}

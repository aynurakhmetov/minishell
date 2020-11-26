/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 19:39:18 by ajeanett          #+#    #+#             */
/*   Updated: 2020/05/30 16:08:58 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	const char	*s_ptr;
	char		*d_ptr;

	if (!n)
		return ((unsigned char *)dst);
	if (!dst && !src)
		return (NULL);
	s_ptr = (const char*)src;
	d_ptr = (char*)dst;
	if (d_ptr <= s_ptr)
	{
		while (n--)
			*d_ptr++ = *s_ptr++;
	}
	else
	{
		d_ptr += n - 1;
		s_ptr += n - 1;
		while (n--)
			*d_ptr-- = *s_ptr--;
	}
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 19:40:24 by ajeanett          #+#    #+#             */
/*   Updated: 2020/05/30 16:09:40 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	const char	*ndst;
	const char	*nsrc;
	size_t		i;
	size_t		dlen;

	ndst = dst;
	nsrc = src;
	i = dsize;
	while (i-- != 0 && *dst != '\0')
		dst++;
	dlen = dst - ndst;
	i = dsize - dlen;
	if (i-- == 0)
		return (dlen + ft_strlen(src));
	while (*src != '\0')
	{
		if (i != 0)
		{
			*dst++ = *src;
			i--;
		}
		src++;
	}
	*dst = '\0';
	return (dlen + (src - nsrc));
}

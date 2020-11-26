/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 10:59:58 by ajeanett          #+#    #+#             */
/*   Updated: 2020/05/31 20:43:56 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	unsigned char	*s;

	size = size * num;
	if (!(s = (unsigned char *)malloc(size)))
		return (NULL);
	ft_memset(s, 0, size);
	return ((void *)s);
}

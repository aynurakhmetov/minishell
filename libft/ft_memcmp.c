/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 19:39:04 by ajeanett          #+#    #+#             */
/*   Updated: 2020/05/30 16:08:48 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *arr1, const void *arr2, size_t n)
{
	const unsigned char	*s_ptr;
	const unsigned char	*d_ptr;
	size_t				i;
	int					result;

	s_ptr = (const unsigned char*)arr1;
	d_ptr = (const unsigned char*)arr2;
	i = 0;
	result = 0;
	while (result == 0 && i < n)
	{
		result = s_ptr[i] - d_ptr[i];
		i++;
	}
	return (result);
}

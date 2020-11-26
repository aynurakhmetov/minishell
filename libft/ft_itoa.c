/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 19:37:28 by ajeanett          #+#    #+#             */
/*   Updated: 2020/05/30 16:07:53 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*ft_strcpy(const char *src)
{
	int		m;
	int		index;
	char	*dest;

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

static size_t		len_string(long nb)
{
	size_t	size;

	if (nb == 0)
		size = 1;
	else
	{
		size = 0;
		while (nb > 0)
		{
			nb = nb / 10;
			size++;
		}
	}
	return (size);
}

static char			*fill_string(long nb, size_t size, size_t znak)
{
	size_t	i;
	char	*string;

	if (!(string = (char *)malloc(sizeof(char) * size)))
		return (NULL);
	i = 0;
	if (znak == 2)
		string[i] = '-';
	i = size - 1;
	string[i] = '\0';
	i--;
	if (nb >= 10)
	{
		while (nb > 0)
		{
			string[i] = nb % 10 + '0';
			nb = nb / 10;
			i--;
		}
	}
	else
		string[i] = nb + '0';
	return (string);
}

char				*ft_itoa(int n)
{
	size_t	nb;
	size_t	size;
	int		znak;
	char	*str;

	if (n == -2147483648)
	{
		str = ft_strcpy("-2147483648");
		return (str);
	}
	nb = n;
	znak = 1;
	if (n < 0)
	{
		znak = 2;
		nb = -1 * nb;
	}
	size = len_string(nb) + znak;
	str = fill_string(nb, size, znak);
	return (str);
}

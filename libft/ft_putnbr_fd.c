/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 19:39:43 by ajeanett          #+#    #+#             */
/*   Updated: 2020/05/30 16:09:16 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	a;
	char			z;

	z = '-';
	a = n;
	if (n < 0)
	{
		write(fd, &z, 1);
		a = -1 * n;
	}
	if (a >= 10)
	{
		ft_putnbr_fd(a / 10, fd);
	}
	ft_putchar_fd((char)(a % 10 + 48), fd);
}

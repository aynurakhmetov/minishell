/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 13:29:45 by ajeanett          #+#    #+#             */
/*   Updated: 2020/11/09 19:39:06 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int					a;
	int					znak;
	unsigned long long	chislo;

	chislo = 0;
	a = 0;
	znak = 1;
	while (str[a] == '\t' || str[a] == ' ' || str[a] == '\n' || str[a] == '\r'
			|| str[a] == '\v' || str[a] == '\f')
		a = a + 1;
	if (str[a] == '-')
	{
		znak = -1;
		a++;
	}
	if (str[a] == '+' && znak == 1)
		a++;
	while (str[a] != '\0' && str[a] <= '9' && str[a] >= '0')
	{
		chislo = chislo + (str[a] - '0');
		chislo = chislo * 10;
		a = a + 1;
	}
	chislo = chislo / 10;
	return (chislo * znak);
}

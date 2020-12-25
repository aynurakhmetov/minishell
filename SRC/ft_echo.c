/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 12:00:13 by gmarva            #+#    #+#             */
/*   Updated: 2020/12/24 20:40:00 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_echo(t_all *all)
{
	int i;
	int k;
	int j;
	int m;

	i = 0;
	k = 0;
	m = 0;
	while(all->arg[++i])
	{
		if (ft_strncmp(all->arg[i],  "-n", ft_strlen("-n")) == 0
		&& ft_strncmp(all->arg[i - k - 1],  "echo", ft_strlen("echo")) == 0)
		{
			j = 0;
			m = 0;
			while(all->arg[i][++j])
			{
				if (all->arg[i][j] != 'n')
					m++;
			}
			if (m == 0)
			{
				k++;
				continue ;
			}
		}
		ft_putstr_fd(all->arg[i], 1);
		if (all->arg[i + 1] != 0)
			ft_putchar_fd(' ', 1);
	}
	if (k == 0)
		ft_putchar_fd('\n', 1);
	
	// Как работает с $?
	all->res = 0;
	return (0);
}

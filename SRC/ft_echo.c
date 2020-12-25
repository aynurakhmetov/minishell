/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 12:00:13 by gmarva            #+#    #+#             */
/*   Updated: 2020/11/23 12:00:19 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo_write(t_all *all, int i, int k, int m)
{
	int j;

	while (all->arg[++i])
	{
		if (ft_strncmp(all->arg[i], "-n", ft_strlen("-n")) == 0
		&& ft_strncmp(all->arg[i - k - 1], "echo", ft_strlen("echo")) == 0)
		{
			j = 0;
			m = 0;
			while (all->arg[i][++j])
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
	return (k);
}

int	ft_echo(t_all *all)
{
	int i;
	int k;
	int m;

	i = 0;
	k = 0;
	m = 0;
	k = ft_echo_write(all, i, k, m);
	if (k == 0)
		ft_putchar_fd('\n', 1);
	all->res = 0;
	return (all->res);
}

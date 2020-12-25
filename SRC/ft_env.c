/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 08:53:46 by gmarva            #+#    #+#             */
/*   Updated: 2020/11/27 08:53:47 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env_write(t_all *all)
{
	int i;
	int j;

	i = -1;
	while (all->env[++i] != 0)
	{
		j = -1;
		while (all->env[i][++j] != 0)
		{
			if (all->env[i][j] == '=')
			{
				ft_putendl_fd(all->env[i], 1);
				continue ;
			}
		}
	}
	all->res = 0;
}

int		ft_env(t_all *all)
{
	int i;

	i = 0;
	while (all->arg[i] != 0)
		i++;
	if (i == 1)
		ft_env_write(all);
	else
	{
		ft_putstr_fd("env: ", 1);
		ft_putstr_fd(all->arg[1], 1);
		ft_putendl_fd(": No such file or directory", 1);
		all->res = 127;
	}
	return (all->res);
}

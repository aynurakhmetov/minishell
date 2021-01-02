/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 08:53:46 by gmarva            #+#    #+#             */
/*   Updated: 2021/01/02 20:27:07 by ajeanett         ###   ########.fr       */
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
	g_res = 0;
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
		g_res = 127;
	}
	return (g_res);
}

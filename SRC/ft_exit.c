/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 10:29:30 by gmarva            #+#    #+#             */
/*   Updated: 2021/01/02 23:36:50 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_all_free(t_all *all, int num)
{
	ft_free_array(all->env);
	ft_free_array(all->arg);
	//if (all->newarg) Если использовать exit с аргументом (код выхода), то из-за этой строки идет дабл фри
	//	ft_free_array(all->newarg);
	exit(num);
}

void	ft_make_exit(t_all *all, int i, size_t j)
{
	if (j != ft_strlen(all->arg[1]) && i > 1)
	{
		ft_putendl_fd("exit", 1);
		ft_putstr_fd("bash: exit: ", 1);
		ft_putstr_fd(all->arg[1], 1);
		ft_putendl_fd(": numeric argument required", 1);
		ft_all_free(all, 255);
	}
	else if (j == ft_strlen(all->arg[1]) && i == 2)
	{
		ft_putendl_fd("exit", 1);
		ft_all_free(all, 0);
		g_res = 1;
	}
	else if (j == ft_strlen(all->arg[1]) && i > 2)
	{
		ft_putendl_fd("exit", 1);
		ft_putendl_fd("bash: exit: too many arguments", 1);
		g_res = 1;
	}
}

void	ft_exit(t_all *all)
{
	int		i;
	size_t	j;

	i = 0;
	while (all->arg[i] != 0)
		i++;
	if (i > 1)
	{
		j = 0;
		while (all->arg[1][j])
		{
			if (ft_isdigit(all->arg[1][j]) == 0)
				break ;
			j++;
		}
		ft_make_exit(all, i, j);
	}
	else if (i == 1)
	{
		ft_putendl_fd("exit", 1);
		ft_all_free(all, 0);
	}
}

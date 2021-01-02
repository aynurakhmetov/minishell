/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:22:24 by gmarva            #+#    #+#             */
/*   Updated: 2021/01/02 22:49:05 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_react_c(void)
{
	if (g_read_start == 0)
	{
		ft_putstr_fd("\b\b  \b\b\n", 1);
		ft_putstr_fd("ajeanett_gmarva ", 1);
		g_res = 1;
	}
	else
	{
		ft_putstr_fd("\b\b  \b\b\n", 1);
		g_res = 130;
	}
}

void	ft_react_slash(void)
{
	ft_putstr_fd("\b\b  \b\b", 1);
	if (g_execve_signal == 1)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		g_execve_signal = 0;
		g_res = 131;
	}
}

void	ft_signal_treatment(t_all *all, char buf_one, char *mem)
{
	if (buf_one == '\0' || buf_one == EOF)
	{
		if (g_read_start == 0)
		{
			if (*mem)
			{
				free(mem);
				mem = NULL;
			}
			if (g_all_start > 0 && all->arg)
			{
				ft_putstr_fd("  \b\b", 1);
				ft_exit(all);
			}
			else
			{
				ft_putstr_fd("exit\n", 1);
				exit(0);
			}
		}
		else
			ft_putstr_fd("  \b\b", 1);
	}
}

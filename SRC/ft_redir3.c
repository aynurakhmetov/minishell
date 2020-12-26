/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 14:46:48 by gmarva            #+#    #+#             */
/*   Updated: 2020/12/26 14:46:50 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_get_newarg2(t_all *all, char **str, int i, int k)
{
	int j;

	if (all->newarg && all->newarg[0])
		ft_free_array(all->newarg);
	j = (i - (k - 1));
	all->newarg = (char **)malloc(sizeof(char *) * (k + 1));
	k = 0;
	while (j < i)
	{
		all->newarg[k] = ft_strdup(str[j]);
		j++;
		k++;
	}
	all->newarg[k] = 0;
}

void	ft_make_newarg2(t_all *all, int pipenum)
{
	int i;
	int k;
	int l;

	i = -1;
	k = 0;
	l = 0;
	while (all->arg[++i] != 0)
	{
		k++;
		if (ft_strncmp(all->arg[i], ">", 1) == 0
		|| ft_strncmp(all->arg[i], ">>", 2) == 0
		|| ft_strncmp(all->arg[i], "<", 1) == 0)
		{
			l++;
			if (l == pipenum)
				ft_get_newarg2(all, all->arg, i, k);
			k = 0;
		}
	}
	if (l + 1 == pipenum)
		ft_get_newarg2(all, all->arg, i, k + 1);
}

void	ft_close_fd(t_all *all)
{
	if (all->r_redir > 0)
	{
		dup2(all->fdtmp[0], 1);
		close(all->fd);
		close(all->fdtmp[0]);
	}
	if (all->l_redir > 0)
	{
		dup2(all->fdtmp[1], 0);
		close(all->fd);
		close(all->fdtmp[1]);
	}
}

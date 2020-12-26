/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 13:55:40 by gmarva            #+#    #+#             */
/*   Updated: 2020/12/26 13:55:43 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_get_number_of_redir(t_all *all)
{
	int i;
	int	k;

	i = -1;
	k = 0;
	while (all->arg[++i])
	{
		if ((ft_strncmp(all->arg[i], ">", 1) == 0
		&& ft_strlen(all->arg[i]) == 1)
		|| (ft_strncmp(all->arg[i], ">>", 2) == 0
		&& ft_strlen(all->arg[i]) == 2)
		|| (ft_strncmp(all->arg[i], "<", 1) == 0
		&& ft_strlen(all->arg[i]) == 1))
			k++;
	}
	return (k);
}

int		ft_get_each_redir2(t_all *all, int *redir, int k, int i)
{
	if (ft_strncmp(all->arg[i], ">", 1) == 0
	&& ft_strlen(all->arg[i]) == 1)
	{
		redir[k] = 1;
		all->r_redir++;
		k++;
	}
	if (ft_strncmp(all->arg[i], ">>", 2) == 0
	&& ft_strlen(all->arg[i]) == 2)
	{
		redir[k] = 2;
		all->r_redir++;
		k++;
	}
	if (ft_strncmp(all->arg[i], "<", 1) == 0
	&& ft_strlen(all->arg[i]) == 1)
	{
		all->l_redir++;
		redir[k] = 3;
		k++;
	}
	return (k);
}

void	ft_get_each_redir(t_all *all, int *redir)
{
	int i;
	int k;

	i = -1;
	k = 0;
	all->r_redir = 0;
	all->l_redir = 0;
	while (all->arg[++i])
		k = ft_get_each_redir2(all, redir, k, i);
}

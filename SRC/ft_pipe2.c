/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 15:46:57 by gmarva            #+#    #+#             */
/*   Updated: 2021/01/03 15:46:59 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_get_newarg(t_all *all, char **str, int i, int k)
{
	int j;
	int len;

	if (all->newarg && all->newarg[0])
		ft_free_array(all->newarg);
	j = (i - (k - 1));
	len = k;
	if (!(all->newarg = (char **)malloc(sizeof(char *) * (k + 1))))
		ft_exit(all);
	k = 0;
	while (j < i)
	{
		if ((ft_strncmp(str[j], ">", 1) == 0 && ft_strlen(str[j]) == 1)
		|| (ft_strncmp(str[j], ">>", 2) == 0 && ft_strlen(str[j]) == 2)
		|| (ft_strncmp(str[j], "<", 1) == 0 && ft_strlen(str[j]) == 1))
			break ;
		all->newarg[k] = ft_strdup(str[j]);
		j++;
		k++;
	}
	all->newarg[k] = 0;
}

void	ft_make_newarg(t_all *all, int pipenum)
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
		if (ft_strncmp(all->arg[i], "|", 1) == 0)
		{
			l++;
			if (l == pipenum)
				ft_get_newarg(all, all->arg, i, k);
			k = 0;
		}
	}
	if (l + 1 == pipenum)
		ft_get_newarg(all, all->arg, i, k + 1);
}

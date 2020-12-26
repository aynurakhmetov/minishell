/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 19:14:04 by ajeanett          #+#    #+#             */
/*   Updated: 2020/12/24 20:25:02 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_all *all)
{
	all->backslash = 0;
	all->pipe = 0;
	all->sq = 0;
	all->dq = 0;
	all->prompt = "ajeanett_gmarva ";
	all->redir = 0;
	all->var = 0;
	all->name_parsed = 0;
	all->size = 2;
	all->arg = NULL;
	all->count = 0;
}

void	init_env(t_all *all, char **envp)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (envp[j])
		j++;
	all->env = (char **)malloc((j + 1) * sizeof(char *));
	all->env[j] = NULL;
	while (i < j)
	{
		all->env[i] = ft_strdup(envp[i]);
		i++;
	}
}

void	init_arg(t_all *all)
{
	all->size = 2;
	if (!(all->arg = (char **)malloc(all->size * (sizeof(char *)))))
		return ;
	all->count = 0;
	all->pipe = 0;
	all->redir = 0;
	all->arg[all->count] = NULL;
	all->arg[all->size - 1] = NULL;
	all->name_parsed = 0;
}

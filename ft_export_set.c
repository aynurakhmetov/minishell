/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 16:34:59 by gmarva            #+#    #+#             */
/*   Updated: 2020/12/18 16:35:00 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
#include <stdio.h>

void	ft_add_to_env(t_all *all, char *newvalue)
{
	char	**array_copy;
	int		i;

	i = 0;
	while(all->env[i] != 0)
		i++;
	array_copy = (char **)malloc(sizeof(char*) * (i + 2));
	i = -1;
	while(all->env[++i] != 0)
		array_copy[i] = ft_strdup(all->env[i]);
	array_copy[i] = ft_strdup(newvalue);
	array_copy[i + 1] = 0;
	ft_free_array(all->env);
	all->env = array_copy;
	//printf("%s %s %s\n", array_copy[i - 1], array_copy[i], array_copy[i + 1]);
}

void	ft_set_value_env(t_all *all)
{
	int i;
	int j;
	int k;

	i = 0;
	while (all->arg[++i] != 0)
	{
		j = -1;
		k = 0;
		while (all->env[++j])
		{
			if (ft_strncmp(all->env[j], all->arg[i], ft_strlen(all->arg[i])) == 0)
				k++;
		}
		if (k == 0)
			ft_add_to_env(all, all->arg[i]);
	}
}

int		ft_export_set(t_all *all)
{
	int i;

	i = 0;
	while (all->arg[++i] != 0)
	{
		if (ft_isalpha(all->arg[i][0]) == 0)
		{
			ft_putstr_fd("bash: export: `", 1);
			ft_putstr_fd(all->arg[i], 1);
			ft_putendl_fd("': not a valid identifier", 1);
			all->$_res = 1;
			return (1);
		}
	}
	ft_set_value_env(all);
	return (0);
}
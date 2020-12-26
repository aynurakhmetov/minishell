/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 09:32:21 by gmarva            #+#    #+#             */
/*   Updated: 2020/11/27 09:32:23 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_delete_str(char **str, int j)
{
	while (str[j] && str[j] != 0)
	{
		if (str[j] && str[j] != 0)
		{
			free(str[j]);
			str[j] = NULL;
		}
		if (str[j + 1] && str[j + 1] != 0)
			str[j] = ft_strdup(str[j + 1]);
		j++;
	}
	if (str[j - 1])
	{
		free(str[j - 1]);
		str[j - 1] = NULL;
	}
	j = 0;
	while (str[j])
		j++;
	return (1);
}

int		ft_unset(t_all *all)
{
	int	i;
	int	j;
	int	k;
	int	l;

	i = 1;
	while (all->arg[i] != 0)
	{
		k = 0;
		j = 0;
		l = 0;
		while (all->arg[i][l] != 0 && all->arg[i][l] != '=')
			l++;
		while (all->env[j] != 0)
		{
			if (ft_strncmp(all->env[j], all->arg[i], l) == 0)
			{
				k = ft_delete_str(all->env, j);
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 08:46:44 by gmarva            #+#    #+#             */
/*   Updated: 2020/11/27 08:46:46 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sort_env(char **sort_env)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (sort_env[++i] != 0)
	{
		j = -1;
		while (sort_env[++j] != 0)
		{
			if (sort_env[i][0] < sort_env[j][0])
			{
				tmp = sort_env[i];
				sort_env[i] = sort_env[j];
				sort_env[j] = tmp;
			}
		}
	}
}

void	ft_free_array(char **str)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i])
		{
			free(str[i]);
			str[i] = NULL;
		}
		i++;
	}
	if (str)
		free(str);
	str = NULL;
}

void	ft_write_export(char **sort_env)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	while (sort_env[++i] != 0)
	{
		ft_putstr_fd("declare -x ", 1);
		j = -1;
		k = 0;
		while (sort_env[i][++j] != 0)
		{
			ft_putchar_fd(sort_env[i][j], 1);
			if (sort_env[i][j] == '=')
			{
				if (k == 0)
					ft_putchar_fd('"', 1);
				k++;
			}
		}
		if (k > 0)
			ft_putendl_fd("\"", 1);
		else
			ft_putendl_fd("", 1);
	}
}

int		ft_export(t_all *all)
{
	char	**sort_env;

	sort_env = ft_array_copy(all->env, 0);
	ft_sort_env(sort_env);
	ft_write_export(sort_env);
	ft_free_array(sort_env);
	all->res = 0;
	return (0);
}

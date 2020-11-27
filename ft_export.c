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

#include "./minishell.h"

void 	ft_sort_env(char **sort_env)
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
	while(str && str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	if (str)
		free(str);
	str = NULL;
}

int		ft_export(t_all *all)
{
	char **sort_env;
	int i;

	i = -1;
	sort_env = ft_array_copy(all->env, 0);
	ft_sort_env(sort_env);
	while (sort_env[++i] != 0)
		ft_putendl_fd(sort_env[i], 1);
	ft_free_array(sort_env);
	// Обработать ошибки
	// Сравнить с выводом оригинальным
	return (0);
}

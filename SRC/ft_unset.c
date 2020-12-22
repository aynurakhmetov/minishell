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
		if (str[j] && str[j]!= 0)
		{
			free(str[j]);
			str[j] = NULL;
		}
		if (str[j + 1] && str[j + 1] != 0)
			str[j] = ft_strdup(str[j + 1]);
		j++;
	}
	//printf("j = %d\n", j);
	if (str[j - 1])
	{
		free(str[j - 1]);
		str[j - 1] = NULL;
	}
	j = 0;
	while (str[j])
	{
		//printf("=2 %d %s=\n", j, str[j]);
		j++;
	}
	return (1);
}

int		ft_unset(t_all *all)
{
	int		i;
	int		j;
	int		k;
	int 	l;

	i = 1;
	while (all->arg[i] != 0)
	{
		k = 0;
		j = 0;
		l = 0;
		//printf("Ya tut 1\n");
		while (all->arg[i][l] != 0 && all->arg[i][l] != '=')
		{
			l++;
			//printf("Ya tut 2 %d\n", l);
		}
		//printf("Ya tut 3\n");
		while (all->env[j] != 0)
		{
			//printf("1 %d %s\n", j, all->env[j]);
			if (ft_strncmp(all->env[j],  all->arg[i], l) == 0)
			{
				k = ft_delete_str(all->env, j);
				break ;
			}
			j++;
		}
		//printf("Ya tut 4\n");
		// if (k == 1)
		// 	free(all->env[j]);
		i++;
	}
	//printf("Ya tut 5\n");
	//ft_env(all); // Убрать потом, пока для проверки стоит
	// s_res
	// правильно удалять без =
	// проверить память
	return (0);
}
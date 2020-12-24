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

void 	ft_sort_env(char **sort_env)
{
	int		i;
	int		j;
	char	*tmp;

	//printf("YA TUT 111\n");
	i = -1;
	while (sort_env[++i] != 0)
	{
		//printf("%d %s\n", i, sort_env[i]);
		j = -1;
		while (sort_env[++j] != 0)
		{
			//printf("%d %s\n", j, sort_env[j]);
			if (sort_env[i][0] < sort_env[j][0])
			{
				tmp = sort_env[i];
				sort_env[i] = sort_env[j];
				sort_env[j] = tmp;
			}
		}
		//printf("j = %d\n", j);
	}
	//printf("YA TUT 112\n");
}

void	ft_free_array(char **str)
{
	int i;

	i = 0;
	//printf("1\n");
	while(str && str[i])
	{
		//printf("11 %s\n", str[i]);
		if (str[i])
		{
			free(str[i]);
			str[i] = NULL;
		}
		i++;
	}
	//printf("2\n");
	if (str)
		free(str);
	str = NULL;
	//printf("3\n");
}

int		ft_export(t_all *all)
{
	char **sort_env;
	int i;
	int j;
	int k;

	//printf("YA TUT 1\n");
	i = -1;
	sort_env = ft_array_copy(all->env, 0);
	//printf("YA TUT 11\n");
	ft_sort_env(sort_env);
	//printf("YA TUT 12\n");
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
				ft_putchar_fd('"', 1);
				k++;
			}
		}
		if (k > 0)
			ft_putendl_fd("\"", 1);
		else
			ft_putendl_fd("", 1);
		
	}
	//printf("YA TUT 2\n");
	ft_free_array(sort_env);
	//printf("YA TUT 3\n");
	// Обработать ошибки, маллоки, память
	// Сравнить с выводом оригинальным
	// s_res как работает
	all->$_res = 0;
	return (0);
}

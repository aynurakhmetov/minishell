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

#include "./minishell.h"

int		ft_delete_str(char **str, int j)
{
	char	*tmp;

	while (str[j] != 0)
	{
		tmp = str[j];
		if (str[j + 1] != 0)
			str[j] = str[j + 1];
		if (tmp)
			free(tmp);
		j++;
	}
	if (str[j - 1])
		str[j - 1] = NULL;
	return (1);
}

int		ft_unset(t_all *all)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = 1;
	while (all->arg[i] != 0)
	{
		k = 0;
		j = 0;
		while (all->env[j] != 0)
		{
			tmp = ft_strjoin(all->arg[i], "="); // Обработка на ошибку
			if (ft_strncmp(all->env[j],  tmp, ft_strlen(tmp)) == 0)
				k = ft_delete_str(all->env, j);
			if (tmp)
				free(tmp);
			j++;
		}
		if (k == 1)
			free(all->env[j]);
		i++;
	}
	ft_env(all); // Убрать потом, пока для проверки стоит
	return (0);
}
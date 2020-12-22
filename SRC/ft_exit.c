/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 10:29:30 by gmarva            #+#    #+#             */
/*   Updated: 2020/11/27 10:29:32 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_all_free(t_all *all, int num)
{
	// Узнать у Вовы что еще вызывается маллоком и почистить
	// Продумать, чтобы при передаче алл ко мне - на его стороне не было утечек
	ft_free_array(all->env);
	ft_free_array(all->arg);
	ft_free_array(all->newarg);
	exit(num);
}

void	ft_exit(t_all *all)
{
	int		i;
	size_t	j;

	i = -1;
	while (all->arg[++i] != 0)
	//printf ("i = %d\n", i);
	if (i > 0)
	{
		j = -1;
		while (all->arg[1][++j]) 
			if (ft_isdigit(all->arg[1][j]) == 0)
				break ;
		if (j == ft_strlen(all->arg[1]) && i == 2)
		{
			ft_putendl_fd("exit", 1);
			ft_all_free(all, 1);
		}
		else if (j != ft_strlen(all->arg[1]) && i > 2)
		{
			ft_putstr_fd("bash: exit: ", 1);
			ft_putstr_fd(all->arg[1], 1);
			ft_putendl_fd(": numeric argument required", 1);
			ft_all_free(all, 255);
		}
		else if (j == ft_strlen(all->arg[1]) && i > 2)
		{
			ft_putendl_fd("bash: exit: too many arguments", 1);
			all->$_res = 1;
		}
	}
	if (i == 1)
		ft_all_free(all, 0);
	// Вроде все готово, но надо проверить коды и разыне кейсы 
	// Количество строк чекнуть
	// exit $PWD при таком кейсе от Вовы уже должно приходить значение $PWD
	// Везде присвоить во всех функциях
}

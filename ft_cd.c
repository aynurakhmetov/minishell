/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:25:24 by gmarva            #+#    #+#             */
/*   Updated: 2020/11/26 17:25:26 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int ft_cd(t_all *all)
{
	int result;

	printf("%s\n", all->arg[1]);
	result = chdir(all->arg[1]);
	if (result == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 1);
		ft_putendl_fd(all->arg[1], 1);
	}
	return (result);
}
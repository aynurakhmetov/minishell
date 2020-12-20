/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 08:53:46 by gmarva            #+#    #+#             */
/*   Updated: 2020/12/20 16:06:55 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_all *all)
{
	int i;

	i = -1;
	while (all->env[++i] != 0)
		ft_putendl_fd(all->env[i], 1);
	return (0);
	// Сравнить подробно с оригинальной выдачей
}
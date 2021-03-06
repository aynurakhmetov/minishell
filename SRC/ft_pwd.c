/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 07:22:02 by gmarva            #+#    #+#             */
/*   Updated: 2021/01/02 20:28:28 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_pwd(t_all *all)
{
	char	dir[10000];
	int		i;

	i = 0;
	if (all->arg[0] != 0)
		i++;
	getcwd(dir, 10000);
	ft_putendl_fd(dir, 1);
	g_res = 0;
	return (0);
}

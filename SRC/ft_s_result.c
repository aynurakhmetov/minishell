/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s_result.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 20:45:07 by gmarva            #+#    #+#             */
/*   Updated: 2020/12/20 16:07:11 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_s_result(t_all *all)
{
	int i = 0;

	while (all->arg[i] != 0)
		i++;
	ft_putstr_fd("bash: ", 1);
	if (all->$_res)
		ft_putnbr_fd(all->$_res, 1);
	else
	{
		if (i > 1)
			i = 127;
		else
			i = 0;
		ft_putnbr_fd(i, 1);
	}
	ft_putendl_fd(": command not found", 1);
}

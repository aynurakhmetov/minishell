/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:25:24 by gmarva            #+#    #+#             */
/*   Updated: 2020/12/20 16:06:48 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_cd(t_all *all)
{
	int	result;
	DIR	*folder;
	// char **args;

	// args = malloc(2 * sizeof(char *));
	// args[0] = "/bin/pwd";
	// args[1] = NULL;
	// execve(args[0], args, NULL);
	folder = opendir(all->arg[1]);
	// printf("%s\n", (char *)folder);
	result = chdir(all->arg[1]);
	free (folder);
	// printf("%s %d\n", all->arg[1], result);
	if (result == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 1);
		ft_putendl_fd(all->arg[1], 1);
	}
	// execve(args[0], args, NULL);
	// Узнать как должна работать
	// Обработка ошибок
	return (result);
}
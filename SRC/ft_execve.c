/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 22:05:14 by gmarva            #+#    #+#             */
/*   Updated: 2020/11/28 22:05:16 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_get_i_enf(char **ienv)
{
	int i;

	i = -1;
	while (ienv[++i])
	{
		if (ft_strncmp(ienv[i], "PATH", ft_strlen("PATH")) == 0)
			return (i);
	}
	return (-1);
}

void	ft_make_exexve(t_all *all, char **tmp, char *mem, int i)
{
	if (i != -1)
	{
		tmp = ft_split(&all->env[i][5], ':');
		mem = ft_strjoin("/", all->arg[0]);
		i = -1;
		while (tmp[++i] != 0)
		{
			if (all->arg[0])
				free(all->arg[0]);
			all->arg[0] = ft_strjoin(tmp[i], mem);
			execve(all->arg[0], all->arg, all->env);
		}
		if (all->arg[0])
			free(all->arg[0]);
		all->arg[0] = &mem[1];
		ft_free_array(tmp);
		if (mem)
			free(mem);
	}
	else
		execve(all->arg[0], all->arg, all->env);
}

void	ft_execve(t_all *all)
{
	char	**tmp;
	char	*mem;
	int		i;

	tmp = NULL;
	mem = NULL;
	i = ft_get_i_enf(all->env);
	all->res = 0;
	ft_make_exexve(all, tmp, mem, i);
	if (execve(all->arg[0], all->arg, all->env) == -1)
	{
		ft_putstr_fd("bash: ", 1);
		ft_putstr_fd(all->arg[0], 1);
		ft_putendl_fd(": command not found", 1);
		all->res = 127;
	}
	exit(0);
}

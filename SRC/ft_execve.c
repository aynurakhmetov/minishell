/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 22:05:14 by gmarva            #+#    #+#             */
/*   Updated: 2021/01/04 13:59:24 by ajeanett         ###   ########.fr       */
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

int		ft_do_execve(t_all *all, char **tmp, char *mem, int i)
{
	int res;

	res = 0;
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
			res = execve(all->arg[0], all->arg, all->env);
		}
		if (all->arg[0])
			free(all->arg[0]);
		all->arg[0] = &mem[1];
		ft_free_array(tmp);
		if (mem)
			free(mem);
	}
	else
		res = execve(all->arg[0], all->arg, all->env);
	return (res);
}

void	ft_execve(t_all *all)
{
	char	**tmp;
	char	*mem;
	int		i;

	tmp = NULL;
	mem = NULL;
	i = ft_get_i_enf(all->env);
	g_res = 0;
	i = ft_do_execve(all, tmp, mem, i);
	if (execve(all->arg[0], all->arg, all->env) == -1)
	{
		ft_putstr_fd("bash: ", 1);
		ft_putstr_fd(all->arg[0], 1);
		ft_putendl_fd(": command not found", 1);
		g_res = 127;
		i = g_res;
	}
	exit(i);
}

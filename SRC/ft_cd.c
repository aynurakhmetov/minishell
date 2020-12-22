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

#include "../minishell.h"

int		ft_cd(t_all *all)
{
	int	result;
	DIR	*folder;
	int i;
	int k;
	int l;
	int h;
	
	i = -1;
	k = - 1;
	l = -1;
	h = -1;
	result = -1;
	
	
	i = -1;
	while (all->env[++i])
	{
		if (ft_strncmp(all->env[i],  "PWD", ft_strlen("PWD")) == 0)
			l = i;
		if (ft_strncmp(all->env[i],  "OLDPWD", ft_strlen("OLDPWD")) == 0)
			k = i;
		if (ft_strncmp(all->env[i],  "HOME=", ft_strlen("HOME=")) == 0)
			h = i;
	}

	int j = -1;
	while(all->arg[++j])
	folder = opendir(all->arg[1]);
	if (j == 1)
	{
		if (h == -1)
		{
			ft_putendl_fd("bash: cd: HOME not set", 1);
			all->$_res = 0;
			return (result);
		}
		else
			result = chdir(&all->env[h][5]);
	}
	else
		result = chdir(all->arg[1]);
	free (folder);
	if (result == -1)
	{
		ft_putstr_fd("bash: cd: ", 1);
		ft_putstr_fd(all->arg[1], 1);
		ft_putendl_fd(": No such file or directory", 1);
	}

	// OLDPWD
	if (k != -1)
	{
		if (all->env[k])
			free(all->env[k]);
		if (l == -1)
			all->env[k] = ft_strdup("OLDDPWD=");
		else
			all->env[k] = ft_strjoin ("OLD", all->env[l]);
	}

	// PWD
	if (l != -1)
	{
		char	dir[10000];
		getcwd(dir, 10000);
		if (all->env[l])
			free(all->env[l]);
		all->env[l] = ft_strjoin ("PWD=", dir);
	}
	
	// что происходит c CD при удалении PWD, OLDPWD
	// порядок PWD OLDPWD в выдаче env - надо ли учитывать
	// обработка ошибок и маллоков , очистка памяти, привести к норме
	// проверить сочетание с $?
	all->$_res = 0;
	return (result);
}
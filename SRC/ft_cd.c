/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:25:24 by gmarva            #+#    #+#             */
/*   Updated: 2021/01/02 20:26:42 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_cd_error(t_all *all)
{
	ft_putstr_fd("bash: cd: ", 1);
	ft_putstr_fd(all->arg[1], 1);
	ft_putendl_fd(": No such file or directory", 1);
	g_res = 1;
}

int		ft_make_cd(t_all *all, int h)
{
	int	result;
	int	j;

	j = 0;
	result = -1;
	while (all->arg[j])
		j++;
	if (j == 1)
	{
		if (h == -1)
		{
			ft_putendl_fd("bash: cd: HOME not set", 1);
			g_res = 0;
			return (result);
		}
		else
			result = chdir(&all->env[h][5]);
	}
	else
		result = chdir(all->arg[1]);
	if (result == -1)
		ft_print_cd_error(all);
	return (result);
}

void	ft_set_pwd(t_all *all, int k, int l)
{
	char	dir[10000];

	if (k != -1)
	{
		if (all->env[k])
			free(all->env[k]);
		if (l == -1)
		{
			if (!(all->env[k] = ft_strdup("OLDDPWD=")))
				ft_exit(all);
		}
		else
			all->env[k] = ft_strjoin("OLD", all->env[l]);
	}
	if (l != -1)
	{
		getcwd(dir, 10000);
		if (all->env[l])
			free(all->env[l]);
		all->env[l] = ft_strjoin("PWD=", dir);
	}
}

int		ft_cd(t_all *all)
{
	int i;
	int k;
	int l;
	int h;

	i = -1;
	k = -1;
	l = -1;
	h = -1;
	while (all->env[++i])
	{
		if (ft_strncmp(all->env[i], "PWD", ft_strlen("PWD")) == 0)
			l = i;
		if (ft_strncmp(all->env[i], "OLDPWD", ft_strlen("OLDPWD")) == 0)
			k = i;
		if (ft_strncmp(all->env[i], "HOME=", ft_strlen("HOME=")) == 0)
			h = i;
	}
	g_res = 0;
	h = ft_make_cd(all, h);
	ft_set_pwd(all, k, l);
	return (h);
}

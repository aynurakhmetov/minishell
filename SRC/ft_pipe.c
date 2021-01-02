/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 15:08:19 by gmarva            #+#    #+#             */
/*   Updated: 2020/12/21 15:08:21 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_get_newarg(t_all *all, char **str, int i, int k)
{
	int j;
	int len;

	if (all->newarg && all->newarg[0])
		ft_free_array(all->newarg);
	j = (i - (k - 1));
	len = k;
	if (!(all->newarg = (char **)malloc(sizeof(char *) * (k + 1))))
		ft_exit(all);
	k = 0;
	while (j < i)
	{
		if ((ft_strncmp(str[j], ">", 1) == 0 && ft_strlen(str[j]) == 1)
		|| (ft_strncmp(str[j], ">>", 2) == 0 && ft_strlen(str[j]) == 2)
		|| (ft_strncmp(str[j], "<", 1) == 0 && ft_strlen(str[j]) == 1))
			break ;
		all->newarg[k] = ft_strdup(str[j]);
		j++;
		k++;
	}
	all->newarg[k] = 0;
}

void	ft_make_newarg(t_all *all, int pipenum)
{
	int i;
	int k;
	int l;

	i = -1;
	k = 0;
	l = 0;
	while (all->arg[++i] != 0)
	{
		k++;
		if (ft_strncmp(all->arg[i], "|", 1) == 0)
		{
			l++;
			if (l == pipenum)
				ft_get_newarg(all, all->arg, i, k);
			k = 0;
		}
	}
	if (l + 1 == pipenum)
		ft_get_newarg(all, all->arg, i, k + 1);
}

void	ft_make_dup(t_all *all, int **fd, int i, int k)
{
	if (i == 0)
		dup2(fd[i][1], 1);
	else if (i < k)
	{
		close(fd[i - 1][1]);
		dup2(fd[i - 1][0], 0);
		dup2(fd[i][1], 1);
	}
	else
	{
		close(fd[i - 1][1]);
		dup2(all->fdtmp_1, 1);
		dup2(fd[i - 1][0], 0);
	}
	all->pid[i] = fork();
	if (all->pid[i] == 0)
	{
		ft_make_newarg(all, i + 1);
		ft_switch_function(all);
		dup2(all->fdtmp_0, 0);
		exit(1);
	}
}

void	ft_make_pipe(t_all *all, int k)
{
	int		**fd;
	int		i;
	int		*status;

	i = -1;
	status = NULL;
	if (!(fd = (int **)malloc(sizeof(int*) * k)))
		ft_exit(all);
	if (!(all->pid = (pid_t *)malloc(sizeof(pid_t) * k)))
		ft_exit(all);
	while (++i <= k)
	{
		if (!(fd[i] = (int *)malloc(sizeof(int) * 2)))
			ft_exit(all);
		fd[i][0] = 1;
		fd[i][0] = 2;
		pipe(fd[i]);
		ft_make_dup(all, fd, i, k);
	}
	i = -1;
	while (++i <= k)
		waitpid(all->pid[i], status, 0);
	i = -1;
	while (++i <= k)
	{
		if (fd[i][0])
			close(fd[i][0]);
		if (fd[i][1])
			close(fd[i][1]);
		free(fd[i]);
		kill(all->pid[i], SIGTERM);
	}
	free(all->pid);
	free(fd);
}

void	ft_pipe(t_all *all)
{
	int i;
	int k;

	k = 0;
	i = -1;
	while (all->arg[++i] != 0)
	{
		if (ft_strncmp(all->arg[i], "|", 1) == 0)
			k++;
	}
	all->fdtmp_1 = dup(1);
	all->fdtmp_0 = dup(0);
	ft_make_pipe(all, k);
	dup2(all->fdtmp_0, 0);
	dup2(all->fdtmp_1, 1);
	all->pipe = 0;
}

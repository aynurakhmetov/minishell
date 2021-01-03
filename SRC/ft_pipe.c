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

void	ft_closefd_and_killpid(int k, int **fd, t_all *all)
{
	int i;

	i = -1;
	while (++i <= k)
	{
		if (fd[i][0])
			close(fd[i][0]);
		if (fd[i][1])
			close(fd[i][1]);
		free((void *)fd[i]);
		fd[i] = NULL;
		kill(all->pid[i], SIGTERM);
	}
	free((void *)all->pid);
	all->pid = NULL;
	free((void *)fd);
	fd = NULL;
}

void	ft_make_pipe(t_all *all, int k)
{
	int		**fd;
	int		i;
	int		status;

	i = -1;
	if (!(fd = (int **)malloc(sizeof(int*) * (k + 1))))
		ft_exit(all);
	if (!(all->pid = (pid_t *)malloc(sizeof(pid_t) * (k + 1))))
		ft_exit(all);
	while (++i <= k)
	{
		if (!(fd[i] = (int *)malloc(sizeof(int) * 2)))
			ft_exit(all);
		pipe(fd[i]);
		ft_make_dup(all, fd, i, k);
	}
	i = -1;
	while (++i <= k)
		waitpid(all->pid[i], &status, 0);
	ft_closefd_and_killpid(k, fd, all);
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
	if (all->fdtmp_0)
		close(all->fdtmp_0);
	if (all->fdtmp_1)
		close(all->fdtmp_1);
	all->pipe = 0;
	g_pipe++;
}

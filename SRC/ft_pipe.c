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
	
	if (all->newarg)
		ft_free_array(all->newarg);
	j = (i - (k - 1)); 
	all->newarg = (char **)malloc(sizeof(char *) * (k + 1));
	k = 0;
	while (j < i)
	{
		all->newarg[k] = ft_strdup(str[j]);
		j++;
		k++;
	}
	//printf("k = %d\n", k);
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
	while(all->arg[++i] != 0)
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
	if (k + 2 == pipenum)
		ft_get_newarg(all, all->arg, i, k + 1);
	//ft_free_array(all->arg);
	//all->arg = all->newarg;
	//all->pipe = 0;
}

void	ft_pipe(t_all *all)
{
	int k;
	int i;
	int **fd;
	pid_t *pid;
	int *status = NULL;

	k = 0;
	i = -1;
	while (all->arg[++i] != 0)
	{
		if (ft_strncmp(all->arg[i], "|", 1) == 0)
			k++;
	}
	k++;
	fd = (int **)malloc(sizeof(int*) * k);
	pid = (pid_t *)malloc(sizeof(pid_t) * k);
	i = 0;
	while (i < k)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		fd[i][0] = 1;
		fd[i][0] = 2;
		pipe(fd[i]);
		pid[i] = fork();
		if (pid[i] == 0)
		{
			// printf("Ya tut 0\n");
			if (i == 0)
			{
				dup2(fd[i][1], 1);
			}
			else if (i < k - 1)
			{
				close(fd[i - 1][1]);
				dup2(fd[i - 1][0], 0);
				dup2(fd[i][1], 1);
			}
			else
			{
				close(fd[i - 1][1]);
				dup2(fd[i - 1][0], 0);
			}
			ft_make_newarg(all, i);
			// Проверка на редирект
			// int j = -1;
			// while (all->newarg[++j] != 0)
			// 	printf("%d %s\n", i, all->newarg[j]);
			ft_switch_function(all);
			exit(129);
		}
		// printf("i = %d, pid = %d\n", i, (int)pid[i]);
		i++;
	}
	i = -1;
	while (++i < k)
		waitpid(pid[i], status, 0);
	all->pipe = 0;
}
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
	
	if (all->newarg && all->newarg[0])
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
	if (l + 1 == pipenum)
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
	//pid_t *pid;
	//int *status = NULL;
	int fdtmp_1;
	int fdtmp_2;

	k = 0;
	i = -1;
	while (all->arg[++i] != 0)
	{
		if (ft_strncmp(all->arg[i], "|", 1) == 0)
			k++;
	}
	printf("1 Ya tut k = %d\n", k);
	//k++;
	fd = (int **)malloc(sizeof(int*) * k);
	//pid = (pid_t *)malloc(sizeof(pid_t) * k);
	i = 0;
	fdtmp_1 = dup(1);
	fdtmp_2 = dup(0);
	while (i <= k)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		fd[i][0] = 1;
		fd[i][0] = 2;
		pipe(fd[i]);
		printf("2 Ya tut\n");
		//pid[i] = fork();
		//if (pid[i] == 0)
		//{
			
			printf("fork %d\n", i);
			if (i == 0)
			{
				//printf("dup1 %d\n", i);
				dup2(fd[i][1], 1);
			}
			else if (i < k)
			{
				//printf("dup2 %d\n", i);
				close(fd[i - 1][1]);
				dup2(fd[i - 1][0], 0);
				dup2(fd[i][1], 1);
			}
			else
			{
				close(fd[i - 1][1]);
				dup2(fdtmp_1, 1);
				dup2(fd[i - 1][0], 0);
				printf("dup3 %d\n", i);
			}
			//printf("fork %d\n", i);
			ft_make_newarg(all, i + 1);
			//printf("fork %d\n", i);
			// int j = -1;
			// while(all->newarg[++j])
			// 	printf("i = %d, newarg = %s\n", i, all->newarg[j]);
			// Проверка на редирект
			ft_switch_function(all);
			//exit(129);
		//}
		//waitpid(pid[i], status, 0);
		// printf("i = %d, pid = %d\n", i, (int)pid[i]);
		i++;
		//printf("3 Ya tut i = %d\n", i);
	}
	
	dup2(fdtmp_2, 0);
	//waitpid(-1, 0, 0);
	// i = -1;
	// while (++i <= k)
	// {
	// 	printf("4 Ya tut i = %d\n", i);
	// 	waitpid(pid[i], status, 0);
	// }
	printf("4 Ya tut\n");
	all->pipe = 0;
	// почистить
}
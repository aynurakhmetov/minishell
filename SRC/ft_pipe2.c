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
	printf("k = %d\n", k);
	all->newarg[k] = 0;
}

char	*ft_get_stdout(t_all *all, int i, int k)
{
	int fd[2];
	int pid;
	int *status = NULL;
	char *buf = ft_calloc(1000, sizeof(char));

	ft_get_newarg(all, all->arg, i, k);
	pipe(fd);

	if ((pid = fork()) == 0)
	{	
		close (0);
		dup(fd[0]);

		close (1);
		dup(fd[1]);

		close(fd[0]);
        close(fd[1]);
		ft_switch_function(all);
		exit(EXIT_FAILURE);
	}
	else
	{
		read(fd[0], buf, 1000);
        close(fd[0]);
        printf("vot - %s\n", buf);
    }
	wait(status);
	return (buf);
}

void	ft_pipe(t_all *all)
{
	int i;
	int k;
	int l;
	char *buf;

	printf("Ya tut 3\n");
	i = -1;
	k = 0;
	l = 0;
	while(all->arg[++i] != 0)
	{
		k++;
		if (ft_strncmp(all->arg[i], "|", 1) == 0)
		{
			buf = ft_get_stdout(all, i, k);
			k = 0;
			l = i;
		}
	}
	ft_get_newarg(all, all->arg, i, k + 1);
	ft_free_array(all->arg);
	all->arg = all->newarg;
	all->pipe = 0;

	i = -1;
	while (all->arg[++i] != 0)
		printf("arg %d = %s\n", i, all->arg[i]);
	printf("ya tut 1\n");

	int fd[2];
	int pid;
	int *status = NULL;
	
	pipe(fd);
	int stdout2 = 0;

	if ((pid = fork()) == 0)
	{	
		close (fd[1]);
		dup2(fd[0], stdout2);
		close(fd[0]);
		write(stdout2, buf, ft_strlen(buf));
		exit(EXIT_FAILURE);
	}
	else
	{
		close(stdout2);
		ft_switch_function(all);
    }
	wait(status);
}
		
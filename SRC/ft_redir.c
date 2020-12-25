/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 11:03:55 by gmarva            #+#    #+#             */
/*   Updated: 2020/12/22 11:03:56 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_get_newarg2(t_all *all, char **str, int i, int k)
{
	int j;
	
	//printf("1 i = %d, k = %d\n", i, k);
	if (all->newarg && all->newarg[0])
		ft_free_array(all->newarg);
	//printf("2 i = %d, k = %d\n", i, k);
	j = (i - (k - 1));
	//printf("3 i = %d, k = %d, j = %d\n", i, k, j); 
	all->newarg = (char **)malloc(sizeof(char *) * (k + 1));
	k = 0;
	while (j < i)
	{
		all->newarg[k] = ft_strdup(str[j]);
		j++;
		k++;
	}
	all->newarg[k] = 0;
	i = -1;
	// while (all->newarg[++i] != 0)
	// 	printf("2 %s\n", all->newarg[i]);
}

void	ft_make_newarg2(t_all *all, int pipenum)
{
	int i;
	int k;
	int l;

	i = -1;
	k = 0;
	l = 0;
	//printf("1 l = %d, pipenum = %d\n", l, pipenum);
	while(all->arg[++i] != 0)
	{
		k++;
		if (ft_strncmp(all->arg[i], ">", 1) == 0 || ft_strncmp(all->arg[i], ">>", 2) == 0 || ft_strncmp(all->arg[i], "<", 1) == 0)
		{
			l++;
			if (l == pipenum)
				ft_get_newarg2(all, all->arg, i, k);
			k = 0;
		}
	}
	//printf("2 l = %d, pipenum = %d, k = %d\n", l, pipenum, k);
	if (l + 1 == pipenum)
		ft_get_newarg2(all, all->arg, i, k + 1);
	//printf("3 l = %d, pipenum = %d, k = %d\n", l, pipenum, k);
}

void	ft_redir(t_all *all)
{
	int i;
	int	k;
	int fd;
	int fdtmp;
	int *redir;
	int j;

	i = -1;
	k = 0;
	//printf("ta tut 1\n");
	while (all->arg[++i])
	{
		if ((ft_strncmp(all->arg[i], ">", 1) == 0 && ft_strlen(all->arg[i]) == 1) || (ft_strncmp(all->arg[i], ">>", 2) == 0 && ft_strlen(all->arg[i]) == 2) || (ft_strncmp(all->arg[i], "<", 1) == 0 && ft_strlen(all->arg[i]) == 1))
			k++;
	}
	//printf("ta tut 2 k = %d\n", k);
	redir = (int *)malloc(sizeof(int) * (k + 1));
	i = -1;
	k = 0;
	all->r_redir = 0;
	all->l_redir = 0;
	while (all->arg[++i])
	{
		//printf("%s %d\n", all->arg[i], (int)ft_strlen(all->arg[i]));
		if (ft_strncmp(all->arg[i], ">", 1) == 0 && ft_strlen(all->arg[i]) == 1)
		{
			redir[k] = 1;
			//printf("1 k = %d, redird = %d\n", k , redir[k]);
			all->r_redir++;
			k++;
		}
		if (ft_strncmp(all->arg[i], ">>", 2) == 0 && ft_strlen(all->arg[i]) == 2)
		{
			redir[k] = 2;
			all->r_redir++;
			k++;
		}
		if (ft_strncmp(all->arg[i], "<", 1) == 0 && ft_strlen(all->arg[i]) == 1)
		{
			all->l_redir++;
			redir[k] = 3;
			k++;
		}
		//printf("2 k = %d, redird = %d\n", k , redir[k]);
	}
	//printf("K = %d\n", k);
	//printf("ta tut 3 i = %d\n", redir[0]);
	i = 0;
	while (i < k)
	{
		
		ft_make_newarg2(all, i + 2);
		
		//int j = -1;
		// while (all->newarg[++j] != 0)
		//printf("2 %d %d %s\n", i, j, all->newarg[j]);
		//printf("%d\n", 1);
		if (redir[i] == 1)
		{
			//printf("2 i = %d, redird = %d, newarg[0] =%s\n", i , redir[i], all->newarg[0]);
			fd = open(all->newarg[0], O_RDWR);
			if (fd == -1)
				fd = open(all->newarg[0], O_RDWR | O_CREAT, 0777);
			fdtmp = dup(1);
			dup2(fd, 1);
		}
		//printf("%d\n", 2);
		if (redir[i] == 2)
		{
			fd = open(all->newarg[0], O_RDWR | O_APPEND);
			if (fd == -1)
				fd = open(all->newarg[0], O_APPEND | O_RDWR | O_CREAT, 0777);
			fdtmp = dup(1);
			dup2(fd, 1);
		}
		if (redir[i] == 3)
		{
			fd = open(all->newarg[0], O_RDWR | O_APPEND);
			if (fd == -1)
				fd = open(all->newarg[0], O_APPEND | O_RDWR | O_CREAT, 0777);
			fdtmp = dup(0);
			dup2(fd, 0);
		}

		//printf("21 k = %d, redird = %d\n", i , redir[i]);
		// j = -1;
		if (i == k - 1)
		{
			break ;
			//ft_make_newarg2(all, 0 + 1);
			// while (all->newarg[++j] != 0)
			// 	printf("3 %d %d %s\n", i, j, all->newarg[j]);
			//ft_switch_function(all);
		}

		//printf("22 k = %d, redird = %d\n", i , redir[i]);
		//printf("3 k = %d, redird = %d\n", i , redir[i]);
		if ((redir[i] == 1 || redir[i] == 2) && all->r_redir > 1)
		{
			//printf("30 k = %d, redird = %d\n", i , redir[i]);
			//ft_make_newarg2(all, i + 2);
			//printf("300 k = %d, redird = %d\n", i , redir[i]);
			//j = 0;
			//while (all->newarg[++j] != 0)
			//	write(1, all->newarg[j], ft_strlen(all->newarg[j]));
			//printf("31 k = %d, redird = %d\n", i , redir[i]);
			all->r_redir--;
			dup2(fdtmp, 1);
			close(fd);
			close(fdtmp);
		}
		if (redir[i] == 3 && all->l_redir > 1)
		{
			all->l_redir--;
			dup2(fdtmp, 0);
			close(fd);
			close(fdtmp);
		}
		//printf("1 YA VNIZY fd VERNULSYA\n");
		i++;
	}
	//printf("2 YA VNIZY fd VERNULSYA\n");
	ft_make_newarg2(all, 0 + 1);
	// while (all->newarg[++j] != 0)
	// 	printf("3 %d %d %s\n", i, j, all->newarg[j]);
	ft_switch_function(all);
	i = 0;
	while (i < k)
	{
		if (redir[i] == 1 || redir[i] == 2 )
		{
			//printf("30 k = %d, redird = %d\n", i , redir[i]);
			ft_make_newarg2(all, i + 2);
			//printf("300 k = %d, redird = %d\n", i , redir[i]);
			j = 0;
			while (all->newarg[++j] != 0)
				write(1, all->newarg[j], ft_strlen(all->newarg[j]));
		}
		i++;
	}
	if (all->r_redir > 0)
	{
		//printf("30 k = %d, redird = %d\n", i , redir[i]);
		//ft_make_newarg2(all, i + 2);
		//printf("300 k = %d, redird = %d\n", i , redir[i]);
		//j = 0;
		//while (all->newarg[++j] != 0)
		//	write(1, all->newarg[j], ft_strlen(all->newarg[j]));
		//printf("31 k = %d, redird = %d\n", i , redir[i]);
		dup2(fdtmp, 1);
		close(fd);
		close(fdtmp);
	}
	if (all->l_redir > 0)
	{
		dup2(fdtmp, 0);
		close(fd);
		close(fdtmp);
	}

	
	// O_APPEND для редиректа >>
}
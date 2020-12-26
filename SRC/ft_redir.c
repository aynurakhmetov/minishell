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

void	ft_close_fd_one(t_all *all, int *redir, int i)
{
	if ((redir[i] == 1 || redir[i] == 2) && all->r_redir > 1)
	{
		all->r_redir--;
		dup2(all->fdtmp[0], 1);
		close(all->fd);
		close(all->fdtmp[0]);
	}
	if (redir[i] == 3 && all->l_redir > 1)
	{
		all->l_redir--;
		dup2(all->fdtmp[1], 0);
		close(all->fd);
		close(all->fdtmp[1]);
	}
}

void	fd_open_file(t_all *all, int *redir, int i)
{
	if (redir[i] == 1)
	{
		all->fd = open(all->newarg[0], O_WRONLY | O_TRUNC, S_IRWXU);
		if (all->fd == -1)
			all->fd = open(all->newarg[0], O_WRONLY
			| O_CREAT | O_TRUNC, S_IRWXU);
		all->fdtmp[0] = dup(1);
		dup2(all->fd, 1);
	}
	if (redir[i] == 2)
	{
		all->fd = open(all->newarg[0], O_WRONLY | O_APPEND, S_IRWXU);
		if (all->fd == -1)
			all->fd =
			open(all->newarg[0], O_APPEND | O_WRONLY | O_CREAT, S_IRWXU);
		all->fdtmp[0] = dup(1);
		dup2(all->fd, 1);
	}
}

void	ft_get_fd(t_all *all, int k, int *redir)
{
	int i;

	i = -1;
	while (++i < k)
	{
		ft_make_newarg2(all, i + 2);
		if (redir[i] == 1 || redir[i] == 2)
			fd_open_file(all, redir, i);
		if (redir[i] == 3)
		{
			all->fd = open(all->newarg[0], O_RDWR | O_APPEND);
			if (all->fd == -1)
			{
				ft_putstr_fd("bash:", 1);
				ft_putstr_fd(all->newarg[0], 1);
				ft_putendl_fd(" No such file or directory", 1);
				break ;
			}
			all->fdtmp[1] = dup(0);
			dup2(all->fd, 0);
		}
		if (i == k - 1)
			break ;
		ft_close_fd_one(all, redir, i);
	}
}

void	ft_add_write_args(t_all *all, int *redir, int k)
{
	int i;
	int j;

	i = 0;
	while (i < k)
	{
		if (redir[i] == 1 || redir[i] == 2)
		{
			ft_make_newarg2(all, i + 2);
			j = 0;
			while (all->newarg[++j] != 0)
				write(1, all->newarg[j], ft_strlen(all->newarg[j]));
		}
		if (redir[i] == 3)
		{
			ft_make_newarg2(all, i + 2);
			j = 0;
			while (all->newarg[++j] != 0)
				ft_switch_function(all);
		}
		i++;
	}
}

void	ft_redir(t_all *all)
{
	int	k;
	int *redir;

	k = ft_get_number_of_redir(all);
	redir = (int *)malloc(sizeof(int) * (k + 1));
	ft_get_each_redir(all, redir);
	ft_get_fd(all, k, redir);
	ft_make_newarg2(all, 0 + 1);
	if (all->pipe == 1)
		ft_pipe(all);
	else
		ft_switch_function(all);
	ft_add_write_args(all, redir, k);
	ft_close_fd(all);
	if (redir)
		free(redir);
}

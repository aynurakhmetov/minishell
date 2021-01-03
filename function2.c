/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 20:15:14 by ajeanett          #+#    #+#             */
/*   Updated: 2021/01/03 12:52:22 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**ft_realloc(char **ptr, size_t newsize)
{
	char	**newptr;
	int		i;

	if (ptr == 0)
		return (malloc(newsize * sizeof(char *)));
	if (!(newptr = (char **)malloc(newsize * sizeof(char *))))
		return (NULL);
	newptr[newsize - 1] = NULL;
	i = 0;
	while (ptr && ptr[i] != 0)
	{
		newptr[i] = ft_strdup(ptr[i]);
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	if (ptr)
		free(ptr);
	ptr = NULL;
	return (newptr);
}

void		clear_arg(t_all *all)
{
	int i;

	i = -1;
	while (all->arg && all->arg[++i])
		if (all->arg[i])
		{
			free(all->arg[i]);
			all->arg[i] = NULL;
		}
	if (all->arg)
		free(all->arg);
	all->arg = NULL;
}

int			check_end(t_all *all, char c)
{
	if (c == ';')
	{
		ft_choice_function(all);
		clear_arg(all);
		init_arg(all);
		return (1);
	}
	return (0);
}

void		set_pipe(t_all *all, int *i, char c, char *line)
{
	int	tmp;

	tmp = *i;
	if (line[tmp - 1] != ' ')
		add_arg(all);
	line_to_arg(&(all->arg[all->count]), c);
	if (line[tmp + 1] != ' ')
		add_arg(all);
	all->pipe = 1;
}

void		set_redir(t_all *all, int *i, char c, char *line)
{
	int tmp;

	tmp = *i;
	if (line[tmp - 1] != ' ')
		add_arg(all);
	line_to_arg(&(all->arg[all->count]), c);
	if (c == '>' && line[tmp + 1] == '>')
	{
		line_to_arg(&(all->arg[all->count]), c);
		tmp++;
	}
	if (line[tmp + 1] != ' ')
		add_arg(all);
	all->redir = 1;
	*i = tmp;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 19:47:21 by ajeanett          #+#    #+#             */
/*   Updated: 2021/01/04 17:58:25 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		check_backslash_m(t_all *all, int *i, char c, char *line)
{
	int	tmp;

	tmp = *i;
	if (c == 92 && all->backslash == 0)
	{
		all->backslash = 1;
		tmp++;
		c = line[tmp];
	}
	else if (c == 92 && all->backslash == 1)
	{
		all->backslash = 0;
		if (!(ft_strchr("\\", line[tmp - 1])))
		{
			tmp++;
			c = line[tmp];
		}
	}
	else if (c != 92 && all->backslash == 1)
		all->backslash = 0;
	*i = tmp;
	return (c);
}

int			check_parser_var(t_all *all, int *i, char c, char *line)
{
	char	*var;
	char	*arg;
	int		tmp;

	tmp = *i;
	if (c == 36 && all->backslash == 0 && line[tmp + 1] == '?')
	{
		arg = all->arg[all->count];
		var = ft_itoa(g_res);
		all->arg[all->count] = ft_strjoin(all->arg[all->count], var);
		all->var = 0;
		if (arg)
			free(arg);
		if (var)
			free(var);
		*i = *i + 1;
		return (1);
	}
	else if (c == 36 && all->backslash == 0 && line[tmp + 1] != '?')
	{
		all->var = 1;
		return (1);
	}
	return (0);
}

void		add_arg(t_all *all)
{
	all->name_parsed = 1;
	all->count++;
	all->size++;
	all->arg = ft_realloc(all->arg, all->size);
	all->arg[all->count] = ft_strdup("");
	all->arg[all->count + 1] = NULL;
}

void		main_parser(t_all *all, char c, char *line, int *i)
{
	if (check_end(all, c) == 1)
		return ;
	check_arg(all);
	if (all->arg[all->count] == NULL)
		all->arg[all->count] = ft_strdup("");
	c = check_backslash_m(all, i, c, line);
	if (check_parser_var(all, i, c, line))
		return ;
	if (c)
	{
		if (c == '|')
			set_pipe(all, i, c, line);
		else if (c == '<' || c == '>')
			set_redir(all, i, c, line);
		else
			line_to_arg(&(all->arg[all->count]), c);
		if (all->name_parsed == 0 || all->name_parsed == 2)
			all->name_parsed = 1;
	}
}

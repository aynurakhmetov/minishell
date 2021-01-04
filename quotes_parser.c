/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 20:19:15 by ajeanett          #+#    #+#             */
/*   Updated: 2021/01/04 17:17:49 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_backslash(t_all *all, int *i, char c, char next)
{
	int	tmp;

	tmp = *i;
	if (c == 92 && ft_strchr("\\$", next))
	{
		all->backslash = 1;
		tmp++;
	}
	else if (c == 92 && all->backslash == 1)
	{
		all->backslash = 0;
	}
	else if (c != 92 && all->backslash == 1)
		all->backslash = 0;
	*i = tmp;
}

int		check_d_var_result(t_all *all, int *i)
{
	char	*var;
	char	*tmp;

	tmp = all->arg[all->count];
	var = ft_itoa(g_res);
	all->arg[all->count] = ft_strjoin(all->arg[all->count], var);
	all->var = 0;
	if (tmp)
	{
		free(tmp);
		tmp = NULL;
	}
	if (var)
	{
		free(var);
		var = NULL;
	}
	*i = *i + 1;
	return (0);
}

void	dqotes_parser(t_all *all, char *line, int *i)
{
	int	tmp;

	check_arg(all);
	all->name_parsed == 0 ? all->name_parsed = 1 : 0;
	tmp = *i;
	if (all->arg[all->count] == NULL)
		all->arg[all->count] = ft_strdup("");
	tmp++;
	while (line[tmp] != '"')
	{
		check_backslash(all, &tmp, line[tmp], line[tmp + 1]);
		if (line[tmp] == '$' && all->backslash == 0 && line[tmp + 1] == '?')
			check_d_var_result(all, &tmp);
		else if (line[tmp] == '$' && all->backslash == 0)
			check_var(line, &tmp, &(all->arg[all->count]), all);
		else
			line_to_arg(&(all->arg[all->count]), line[tmp]);
		tmp++;
	}
	*i = tmp;
}

void	sqotes_parser(t_all *all, char *line, int *i)
{
	int	tmp;

	check_arg(all);
	all->name_parsed == 0 ? all->name_parsed = 1 : 0;
	tmp = *i;
	if (all->arg[all->count] == NULL)
		all->arg[all->count] = ft_strdup("");
	tmp++;
	while (line[tmp] != 39)
	{
		line_to_arg(&(all->arg[all->count]), line[tmp]);
		tmp++;
	}
	*i = tmp;
}

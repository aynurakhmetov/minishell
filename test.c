/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:01:16 by ajeanett          #+#    #+#             */
/*   Updated: 2021/01/02 21:37:50 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		space_skip(t_all *all, int *i)
{
	int	tmp;

	tmp = *i;
	if (all->name_parsed == 1)
		all->name_parsed = 2;
	tmp++;
	*i = tmp;
}

void		parser(char *line, t_all *all)
{
	int	i;

	if (check_syntax(line, all))
		return ;
	init_arg(all);
	g_all_start++;
	i = -1;
	while (line[++i] != '\0')
	{
		while (ft_isspace(line[i]))
			space_skip(all, &i);
		if (line[i] == '"')
			dqotes_parser(all, line, &i);
		if (line[i] == 39)
			sqotes_parser(all, line, &i);
		if (!ft_isspace(line[i]) && (int)line[i] != 39 &&
				line[i] != '"' && line[i] != '\0')
			main_parser(all, line[i], line, &i);
		if (all->var == 1 && all->backslash == 0)
			check_var(line, &i, &(all->arg[all->count]), all);
	}
	if (all->arg[0] != NULL)
		ft_choice_function(all);
	clear_arg(all);
}

static int	check_argc_argv(int argc, char **argv)
{
	if (argc > 1 && argv[1])
	{
		ft_putendl_fd("Error.\nToo many arguments", 2);
		return (1);
	}
	return (0);
}

int			main(int argc, char **argv, char **envp)
{
	t_all	all;
	char	*line;
	int		ret;

	init_struct(&all);
	init_env(&all, envp);
	if (check_argc_argv(argc, argv) == 1)
		return (0);
	while (1)
	{
		if (signal(SIGINT, (void*)ft_react_c) == SIG_ERR)
			ft_exit(&all);
		if (signal(SIGQUIT, (void*)ft_react_slash) == SIG_ERR)
			ft_exit(&all);
		write(1, all.prompt, ft_strlen(all.prompt));
		line = NULL;
		ret = 0;
		ret = get_next_line(&all, 0, &line);
		if (ret >= 0)
			parser(line, &all);
		if (line)
			free(line);
	}
	return (0);
}

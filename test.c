/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:01:16 by ajeanett          #+#    #+#             */
/*   Updated: 2020/12/25 10:14:20 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	space_skip(t_all *all, int *i)
{
	int	tmp;

	tmp = *i;
	if (all->name_parsed == 1)
		all->name_parsed = 2;
	tmp++;
	*i = tmp;
}

void	parser(char *line, t_all *all)
{
	int	i;

	if (check_syntax(line, all))
		return ;
	init_arg(all);
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

int		main(int argc, char **argv, char **envp)
{
	t_all	all;
	char	*line;
	int		ret;

	init_struct(&all);
	init_env(&all, envp);
	all.res = 0;
	if (argc > 1 && argv[1])
	{
		ft_putendl_fd("Error.\nToo many arguments", 2);
		return (0);
	}
	while (1)
	{
		write(1, all.prompt, ft_strlen(all.prompt));
		line = NULL;
		ret = 0;
		ret = get_next_line(0, &line);
		if (ret >= 0)
			parser(line, &all);
		if (signal(SIGINT, ft_react) == (void(*)())-1)
			continue ;
		if (line)
			free(line);
	}
	return (0);
}

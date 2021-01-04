/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 20:36:25 by ajeanett          #+#    #+#             */
/*   Updated: 2021/01/04 17:58:34 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_e(char c)
{
	char *err;

	err = "bash: syntax error near unexpected token `";
	write(2, err, ft_strlen(err));
	write(2, &c, 1);
	ft_putendl_fd("`", 2);
	g_res = 258;
}

void	ft_e_red(char *s)
{
	char *err;

	err = "bash: syntax error near unexpected token `";
	write(2, err, ft_strlen(err));
	write(2, s, ft_strlen(s));
	ft_putendl_fd("`", 2);
	g_res = 258;
}

int		check_left_redir(char *line, int i)
{
	if (line[i] == '<')
	{
		while (ft_isspace(line[i + 1]))
			i++;
		if (line[i + 1] == '\0')
		{
			ft_e_red("newline");
			return (1);
		}
		if (ft_strchr("><;|", line[i + 1]))
		{
			ft_e(line[i + 1]);
			return (1);
		}
	}
	return (0);
}

int		check_right_redir(char *line, int i)
{
	if (line[i] == '>')
	{
		while (ft_isspace(line[i + 1]))
			i++;
		if (line[i + 1] == '\0')
		{
			ft_e_red("newline");
			return (1);
		}
		if (ft_strchr("><;|", line[i + 1]))
		{
			ft_e(line[i + 1]);
			return (1);
		}
	}
	return (0);
}

int		check_redir(char *line, int i)
{
	if (line[i] == '>' && line[i + 1] == '>')
	{
		while (ft_isspace(line[i + 2]))
			i++;
		if (line[i + 2] == '\0')
		{
			ft_e_red("newline");
			return (1);
		}
		if (ft_strchr("><;|", line[i + 2]))
		{
			ft_e(line[i + 2]);
			return (1);
		}
	}
	else if (check_right_redir(line, i))
		return (1);
	if (check_left_redir(line, i))
		return (1);
	return (0);
}

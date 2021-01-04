/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 20:42:17 by ajeanett          #+#    #+#             */
/*   Updated: 2021/01/04 17:58:39 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quotes_flag(char c, t_all *all)
{
	if (c == 39 && all->sq == 0)
		all->sq = 1;
	else if (c == 39 && all->sq == 1)
		all->sq = 0;
	else if (c == '"' && all->dq == 0)
		all->dq = 1;
	else if (c == '"' && all->dq == 1)
		all->dq = 0;
}

int		check_syntax(char *line, t_all *all)
{
	int	i;
	int	check;

	i = -1;
	check = 0;
	while (line[++i] != '\0')
	{
		quotes_flag(line[i], all);
		if (all->sq == 0 && all->dq == 0)
		{
			if (check == 0 && ft_strchr(";|", line[i]))
			{
				ft_e(line[i]);
				return (1);
			}
			if (!ft_isspace(line[i]) && check == 0)
				check = 1;
			if (check == 1 && ft_strchr(";", line[i]))
				check = 0;
			if (line[i] == '<' || line[i] == '>')
				if (check_redir(line, i))
					return (1);
		}
	}
	return (0);
}

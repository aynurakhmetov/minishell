/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 20:36:25 by ajeanett          #+#    #+#             */
/*   Updated: 2020/12/23 20:36:37 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_e(t_all *all, char c)
{
	ft_putendl_fd(ft_chrjoin(ft_chrjoin("bash: syntax error near unexpected token `", c), 39), 2);
    all->$_res = 258;
}

void	ft_e_red(t_all *all, char *s)
{
	ft_putendl_fd(ft_chrjoin(ft_strjoin("bash: syntax error near unexpected token `", s), 39), 2);
    all->$_res = 258;
}

int    check_left_redir(t_all *all, char *line, int i)
{
    if (line[i] == '<')
    {
        while (ft_isspace(line[i + 1]))
            i++;
        if (line[i + 1] == '\0')
        {
            ft_e_red(all, "newline");
            return(1);
        }
        if (ft_strchr("><;|", line[i + 1]))
        {
            ft_e(all, line[i + 1]);
            return(1);
        }
    }
    return(0);
}

int    check_right_redir(t_all *all, char *line, int i)
{
    if (line[i] == '>')
    {
        while (ft_isspace(line[i + 1]))
            i++;
        if (line[i + 1] == '\0')
        {
            ft_e_red(all, "newline");
            return(1);
        }
        if (ft_strchr("><;|", line[i + 1]))
        {
            ft_e(all, line[i + 1]);
            return(1);
        }
    }
    return(0);
}

int    check_redir(t_all *all, char *line, int i)
{
    if (line[i] == '>' && line[i + 1] == '>')
    {
        while (ft_isspace(line[i + 2]))
            i++;
        if (line[i + 2] == '\0')
        {
            ft_e_red(all, "newline");
            return(1);
        }
        if (ft_strchr("><;|", line[i + 2]))
        {
            ft_e(all, line[i + 2]);
            return(1);
        }
    }
    if (check_left_redir(all, line, i))
        return(1);
    if (check_right_redir(all, line, i))
        return(1);
    return(0);
}
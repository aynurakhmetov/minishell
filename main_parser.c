/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 19:47:21 by ajeanett          #+#    #+#             */
/*   Updated: 2020/12/23 19:48:53 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    check_backslash_m(t_all *all, int *i, char c, char *line)
{
    int tmp;

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

int     check_parser_var(t_all *all, int *i, char c, char *line)
{
    char *var;
    char *arg;
    int   tmp;

    tmp = *i;
    if (c == '$' && all->backslash == 0 && line[tmp + 1] == '?')
    {
        arg = all->arg[all->count];
        var = ft_itoa(all->$_res);
        all->arg[all->count] = ft_strjoin(all->arg[all->count], var);
        all->var_$ = 0;
        if (arg)
            free(arg);
        if (var)
            free(var);
        *i = *i + 1;
        return (1);
    }
    else if (c == '$' && all->backslash == 0 && line[tmp + 1] != '?')
    {
        all->var_$ = 1;
        return (1);
    }
    return (0);
}

void    main_parser(t_all *all, char c, char *line, int *i)
{
    if (check_end(all, c) == 1)
        return;
    check_arg(all);
    if (all->arg[all->count] == NULL)
        all->arg[all->count] = ft_strdup("");
    c = check_backslash_m(all, i, c, line);
    if (check_parser_var(all, i, c, line))
        return;
    if (c)
        {
            line_to_arg(&(all->arg[all->count]), c);
            if (all->name_parsed == 0 || all->name_parsed == 2)
                all->name_parsed = 1;
            if (c == '|' && all->pipe == 0)
                all->pipe = 1;
            if (c == '<' || c == '>')
                all->redir = 1;
        }
}
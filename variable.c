/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 20:08:27 by ajeanett          #+#    #+#             */
/*   Updated: 2020/12/23 20:13:35 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *find_var(char *str, char **envp)
{
    char *find;
    int i;

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(str, envp[i], ft_strlen(str)) == 0)
        {
            find = ft_strchr(envp[i], '=');
            find++;
            return(find);
        }
        i++;
    }
    return (NULL);
}

void    var_to_arg(char *var, t_all *all)
{
    int i;

    i = 0;
    while (var[i] != '\0')
    {
        line_to_arg(&(all->arg[all->count]), var[i]);
        i++;
    }
}

int    check_var(char *line, int *i, char **arg, t_all *all)
{
    char *var;
    char *var_tmp;
    int  tmp;
    size_t len; 

    tmp = *i;
    tmp++;
    var = NULL;
    all->var_$ = 0;
    if (ft_isdigit(line[tmp]))
    {
        *i = tmp;
        return (0);
    }
    if ((line[tmp] == ' ') || (line[tmp] == '\0'))
    {
        line_to_arg(arg, line[*i]);
        all->name_parsed == 0 ? all->name_parsed = 1 : 0;
        return (0);
    }
    while (!(ft_strchr(" $;|<>=\"\'", line[tmp])))
        tmp++;
    if ((ft_strchr(" $;|<>=\"\'", line[tmp])))
    {
        len = (size_t)(tmp - *i - 1);
        tmp = *i;
        var = ft_substr(line, (tmp + 1), len);
        var_tmp = var;
    }
    if (var)
    {
        var = find_var(var, all->env);
        if (var != NULL)
        {
            *i = *i + len;
            if (line[*i + 1] == ' ')
                all->name_parsed = 1;
            var_to_arg(var, all);
            return (1);
        }
        free(var_tmp);
    }
    *i = *i + len;
    return (0);
}
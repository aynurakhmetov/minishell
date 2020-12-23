/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:01:16 by ajeanett          #+#    #+#             */
/*   Updated: 2020/12/23 20:45:49 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void parser(char *line, t_all *all)
{
    int i;

    if (check_syntax(line, all))
        return;
    all->size = 2;
    if (!(all->arg = (char **)malloc(all->size * (sizeof(char *)))))
        return;
    i = 0;
    all->count = 0;
    all->pipe = 0;
    all->redir = 0;
    all->arg[all->count] = NULL; //ft_strdup("");
    all->arg[all->size - 1] = NULL;
    all->name_parsed = 0;
    while (line[i] != '\0')
    {
        while (ft_isspace(line[i]))
        {
            if (all->name_parsed == 1)
                all->name_parsed = 2;
            i++;
        }
        if (line[i] == '"')
            dqotes_parser(all, line, &i);
        if (line[i] == 39)
            sqotes_parser(all, line, &i);
        if (!ft_isspace(line[i]) && (int)line[i] != 39 && line[i] != '"' && line[i] != '\0')
            main_parser(all, line[i], line, &i);
        if (all->var_$ == 1 && all->backslash == 0)
            check_var(line, &i, &(all->arg[all->count]), all);
        i++;
    }
    i = 0;
    while(all->arg[i] != 0)
    {
        // printf("\n arg%d: = %s\n", i, all->arg[i]);
        i++;
    }
    if (all->arg[0]!= NULL)
        ft_choice_function(all);
  
    i = -1;
    while(all->arg && all->arg[++i])
        if (all->arg[i])
        {
            free(all->arg[i]);
            all->arg[i] = NULL;
        }
    if (all->arg) free(all->arg);
    all->arg = NULL;
}

int     main(int argc, char **argv, char **envp)
{
    t_all   all;
    char *line;
    int  ret;

    init_struct(&all);
    init_env(&all, envp);
    all.$_res = 0;
    if (argc > 1 && argv[1])
    {
        ft_putendl_fd("Error.\nToo many arguments", 2);
        return (0);
    }
    while(1)
    {
        write(1, all.prompt, ft_strlen(all.prompt));
        line = NULL;
        ret = 0;
        ret = get_next_line(0, &line);
        if (ret >= 0)
            parser(line, &all);
        if (line)
            free(line);
    }
    return (0);
}
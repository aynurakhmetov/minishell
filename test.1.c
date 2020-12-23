/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:01:16 by ajeanett          #+#    #+#             */
/*   Updated: 2020/12/22 23:44:25 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    init_struct(t_all *all)
{
    all->backslash = 0;
    all->pipe = 0;
    all->sq = 0;
    all->dq = 0;
    all->prompt = "ajeanett_gmarva ";
    all->redir = 0;
    all->var_$ = 0;
    all->name_parsed = 0;
    all->size = 2;
    all->arg = NULL;
    all->count = 0;
    all->$_res = 0;
}

void    init_env(t_all *all, char **envp)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (envp[j])
        j++;
    //printf("ft_strlen = %d \n", j);
    all->env = (char **)malloc((j + 1) * sizeof(char *));
    all->env[j] = NULL;
    while (i < j)
    {
        all->env[i] = ft_strdup(envp[i]);
        // printf("all->env[%d] = %s \n", i, all->env[i]);
        i++;
    }
}

int		ft_isspace(int c)
{
	c = (unsigned char)c;
	if (/*c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| */c == ' ')
		return (1);
	return (0);
}

static void		ft_free(char **str)
{
    if (*str)
	    free(*str);
	*str = NULL;
}

char	*ft_chrjoin(char *s1, const char s2)
{
	unsigned int	buf;
	char			*str;
    int             i;
    
    i = 0;
	buf = ft_strlen(s1) + 1;
	str = ((char *)malloc(sizeof(char) * (buf + 1)));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
        i++;
	}
	if (s2 != '\0')
		str[i++] = s2;
	str[i++] = '\0';
	return (str);
}

static int		line_to_arg(char **line, char chr)
{
	char *tmp;

	tmp = *line;
	if (!(*line = ft_chrjoin(*line, chr)))
		return (-1);
	ft_free(&tmp);
	return (0);
}

void    check_arg(t_all *all)
{
    if (all->name_parsed == 2)
    {
        all->name_parsed = 1;
        all->count++;
        all->size++;
        all->arg = ft_realloc(all->arg, all->size);
        all->arg[all->count] = ft_strdup("");
        all->arg[all->count + 1] = NULL;
    }
}

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
        all->arg[all->count] = ft_strjoin(var, all->arg[all->count]);
        all->var_$ = 0;
        if (arg)
            free(arg);
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
    // if (c == '$' && all->backslash == 0)
    // {
    //     all->var_$ == 0 ? all->var_$ = 1 : 0;
    //     return;
    // }
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
        // if (var[i] == ' ')
        // {
        //     all->count++;
        //     all->size++;
        //     all->arg = ft_realloc(all->arg, all->size);
        //     all->arg[all->count] = ft_strdup("");
        //     all->arg[all->count + 1] = NULL;
        // }
        // while(ft_isspace(var[i]))
        //     i++;./m
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
    if (arg)
        printf("1\n");
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
    return (0);
}

char	**ft_realloc(char **ptr, size_t newsize)
{
	char	**newptr;
    int     i;

	if (ptr == 0)
		return (malloc(newsize * sizeof(char *)));
	if (!(newptr = (char **)malloc(newsize * sizeof(char *))))
        return (NULL);
    newptr[newsize - 1] = NULL;
    i = 0;
	while(ptr && ptr[i] != 0)
    {
        newptr[i] = ft_strdup(ptr[i]);
        free(ptr[i]);
        ptr[i] = NULL;
        i++;
    }
    if (ptr)
        free(ptr);
    ptr = NULL;
	return (newptr);
}
void    check_backslash(t_all *all, int *i, char c, char next)
{
    int tmp;

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

void dqotes_parser(t_all *all, char *line,int *i)
{
    int tmp;

    check_arg(all);
    all->name_parsed == 0 ? all->name_parsed = 1 : 0;
    tmp = *i;
    if (all->arg[all->count] == NULL)
        all->arg[all->count] = ft_strdup("");
    tmp++;
    while (line[tmp] != '"')
    {
        check_backslash(all, &tmp, line[tmp], line[tmp + 1]);
        if (line[tmp] == '$' && all->backslash == 0)
            check_var(line, &tmp, &(all->arg[all->count]), all);
        else
            line_to_arg(&(all->arg[all->count]), line[tmp]);
        tmp++;
    }
    *i = tmp;
}

void sqotes_parser(t_all *all, char *line, int *i)
{
    int tmp;

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

void    clear_arg(t_all *all)
{
    int i;

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

void    init_arg(t_all *all)
{
    all->size = 2;
    if (!(all->arg = (char **)malloc(all->size * (sizeof(char *)))))
        return;
    all->count = 0;
    all->pipe = 0;
    all->redir = 0;
    all->arg[all->count] = ft_strdup("");
    all->arg[all->size - 1] = NULL;
    all->name_parsed = 0;
}

int    check_end(t_all *all, char c)
{
    if (c == ';')
    {
        ft_choice_function(all);
        clear_arg(all);
        init_arg(all);
        return (1);
    }
    return (0);
}

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

void    quotes_flag(char c, t_all *all)
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

int    check_syntax(char *line, t_all *all)
{
    int i;
    int check;

    i = -1;
    check = 0;
    while(line[++i] != '\0')
    {
        quotes_flag(line[i], all);
        if (all->sq == 0 && all->dq == 0)
        {
            if (check == 0 && ft_strchr(";|", line[i]))
            {
                ft_e(all, line[i]);
                return (1);
            }
            if (!ft_isspace(line[i]) && check == 0)
                check = 1;
            if (check == 1 && ft_strchr(";", line[i]))
                check = 0;
            if (line[i] == '<' || line[i] == '>')
                if (check_redir(all, line, i))
                    return (1);
        }
    }
    return (0);
}

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
    all->arg[all->count] = ft_strdup("");
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
        printf("\n arg%d: = %s\n", i, all->arg[i]);
        i++;
    }
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

// void	ft_e_nofree(char *str)
// {
// 	ft_putendl_fd(ft_strjoin("Error\n", str), 2);
// 	exit(1);
// }

int     main(int argc, char **argv, char **envp)
{
    t_all   all;

    init_struct(&all);
    init_env(&all, envp);
    // int i = 0;
    if (argc > 1 && argv[1])
    {
        ft_putendl_fd("Error.\nToo many arguments", 2);
        return (0);
    }
    // while(all.env[i])
    // {
    //     //printf("%s\n", all.env[i]);
    //     i++;
    // }
    
    char *line;
    int  ret;

    while(1)
    {
        // size_t len;
            // //printf("%s", get_prompt(&all));
            write(1, all.prompt, ft_strlen(all.prompt));
            line = NULL;
            // len = 0;
            ret = 0;
            ret = get_next_line(0, &line);
            //printf("main line: %d %s\n", ret, line);
            if (ret >= 0)
                parser(line, &all);
            //Ainur function
            if (line)
                free(line);
    }
    return (0);
}
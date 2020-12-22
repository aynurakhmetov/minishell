/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:01:16 by ajeanett          #+#    #+#             */
/*   Updated: 2020/12/21 16:21:35 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    init_struct(t_all *all)
{
    all->backslash = 0;
    all->pipe = 0;
    all->prompt = "ajeanett_gmarva ";
    all->redir = 0;
    all->var_$ = 0;
    all->name_parsed = 0;
    all->size = 2;
    all->arg = NULL;
    all->count = 0;
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

// char	*ft_chrjoin(char *s1, char const s2)
// {
// 	char *c;
// 	char *t;

// 	if (!s1 && s2)
// 		return (ft_strdup(&s2));
// 	if (s1 && !s2)
// 		return (ft_strdup(s1));
//     // if (s1[0] == '\0')
//     // {
//     //     c = malloc(2);
//     //     c[0] = s2;
//     //     c[1] = '\0';
// 	//     return (c);
//     // }
// 	c = s1 && s2 ? malloc(ft_strlen(s1) + 2) : NULL;
// 	if (c)
// 	{
// 		t = c;
// 		while (s1 && *s1)
// 			*t++ = *s1++;
// 		if (ft_isascii(s2))
// 			*t++ = s2;
// 		*t = '\0';
// 	}
// 	return (c);
// }

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
    // printf("all->name_parsed check arg1 %d\n ", all->name_parsed);
    if (all->name_parsed == 2)
    {
        all->name_parsed = 1;
        // printf("all->name_parsed check arg2 %d\n ", all->name_parsed);
        all->count++;
        all->size++;
        all->arg = ft_realloc(all->arg, all->size);
        all->arg[all->count] = ft_strdup("");
        all->arg[all->count + 1] = NULL;
    }
}

void    main_parser(t_all *all, const char c, /*char  **strб*/ int *i)
{
    if (check_end(all, i, c) == 1)
        return;
    check_arg(all);
    if (all->arg[all->count] == NULL)
        all->arg[all->count] = ft_strdup("");
    // if (all->arg[all->count] == NULL)
    //     all->arg[all->count] = ft_strdup("");
    if (c == '$')
    {
        all->var_$ == 0 ? all->var_$ = 1 : 0;
        return;
    }
    if (!(ft_isspace(c)))
        {
            line_to_arg(&(all->arg[all->count]), c);
            // printf("all->name_parsed main_parser1 %d\n ", all->name_parsed);
            if (all->name_parsed == 0 || all->name_parsed == 2)
                all->name_parsed = 1;
            // printf("all->name_parsed main_parser2 %d\n ", all->name_parsed);
            if (c == '|' && all->pipe == 0)
                all->pipe = 1;
            if (c == '<' || c == '>')
                all->redir = 1;
        }
    //printf("2 s1 = %s, char = %c\n", *str, c);
}

char    *find_var(char *str, char **envp)
{
    // char *var;
    char *find;
    int i;

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(str, envp[i], ft_strlen(str)) == 0)
        {
            find = ft_strchr(envp[i], '=');
            find++;
            // printf("value var %s\n", find);
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
        if (var[i] == ' ')
        {
            all->count++;
            all->size++;
            all->arg = ft_realloc(all->arg, all->size);
            all->arg[all->count] = ft_strdup("");
            all->arg[all->count + 1] = NULL;
        }
        while(ft_isspace(var[i]))
            i++;
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
    if (arg && all)
        all->var_$ = 0;
    if ((line[tmp] == ' ') || (line[tmp] == '\0'))
    {
        line_to_arg(arg, line[*i]);
        all->name_parsed == 0 ? all->name_parsed = 1 : 0;
        return (0);
    }
    while (!(ft_strchr(" $;|<>\"\'", line[tmp])))
        tmp++;
    if ((ft_strchr(" $;|<>\"\'", line[tmp])))
    {
        len = (size_t)(tmp - *i - 1);
        tmp = *i;
        var = ft_substr(line, (tmp + 1), len);
        var_tmp = var;
    }
    if (var)
    {
        // printf("var: %s\n", var);
        var = find_var(var, all->env);
        // printf("value var %s\n", var);
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

void dqotes_parser(t_all *all, char *line,int *i)
{
    int tmp;

    all->name_parsed == 0 ? all->name_parsed = 1 : 0;
    tmp = *i;
    if (all->arg[all->count] == NULL)
        all->arg[all->count] = ft_strdup("");
    tmp++;
    while (line[tmp] != '"')
    {
        if (line[tmp] == '$')
            check_var(line, &tmp, &(all->arg[all->count]), all);
        else
            line_to_arg(&(all->arg[all->count]), line[tmp]);
        tmp++;
    }
    // printf("line[tmp] = %c, tmp = %d\n", line[tmp], tmp);
    // tmp++;
    // printf("line[tmp] = %c, tmp = %d\n", line[tmp], tmp);
    *i = tmp;
}

void sqotes_parser(t_all *all, char *line,int *i)
{
    int tmp;

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
    // printf("line[tmp] = %c, tmp = %d\n", line[tmp], tmp);
    // tmp++;
    // printf("line[tmp] = %c, tmp = %d\n", line[tmp], tmp);
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

int    check_end(t_all *all, int *i, char c)
{
    int tmp;

    tmp = *i;
    if (c == ';')
    {
        ft_choice_function(all);
        clear_arg(all);
        init_arg(all);
        // tmp++;
        *i = tmp;
        return (1);
    }
    *i = tmp;
    return (0);
}

void parser(char *line, t_all *all)
{
    int i;

    all->size = 2; //check_size(line);
    // arg = ft_calloc(size, sizeof(char));
    // all->arg = NULL;
    if (!(all->arg = (char **)malloc(all->size * (sizeof(char *)))))
        return;
    i = 0;
    all->count = 0;
    all->pipe = 0;
    all->redir = 0;
    all->arg[all->count] = ft_strdup("");
    all->arg[all->size - 1] = NULL;
    all->name_parsed = 0;
    // printf("line: %s %zu\n\n", line, ft_strlen(line));
    while (line[i] != '\0')
    {
        // write(1,&line[i], 1);
        //printf("0 line [i] = %c i = %d\n", line[i], i);
        // check_end(all, &i, line[i]);
        while (ft_isspace(line[i]) /*&& all->sq_open == 0 && all->dq_open == 0*/)
        {
            //printf("0.1 line [i] = %c i = %d line %s\n", line[i], i, line);
            if (all->name_parsed == 1)
            {
                // printf("all->name_parsed space1 %d\n ", all->name_parsed);
                all->name_parsed = 2;
                // printf("all->name_parsed space2 %d\n ", all->name_parsed);
                // printf("do %s\n ", all->arg[all->count]);
                // all->count++;
                // all->size++;
                // printf("all->count %d, size %d \n", all->count, all->size);
                // all->arg = ft_realloc(all->arg, all->size);
                // printf("0.2 line [i] = %c i = %d line = %s len = %zu\n", line[i], i, line, ft_strlen(line));
                // //printf("posle %s\n ", all->arg[all->count - 1]);
                // arg[all->count] = malloc(1);
                // arg[all->count][0] = '\0';
                // all->arg[all->count] = NULL ;//ft_strdup("");
                //printf("0.22 line [i] = %c i = %d line %s\n", line[i], i, line);
                // all->arg[all->count + 1] = NULL;
            }
            i++;
            //printf("0.3 line [i] = %c i = %d line %s\n", line[i], i, line);
        }
        if (line[i] == '"')
            dqotes_parser(all, line, &i);
        if (line[i] == 39)
            sqotes_parser(all, line, &i);
        //printf("1 line [i] = %c i = %d\n", line[i], i);
        if (!ft_isspace(line[i]) && (int)line[i] != 39 && line[i] != '"' && line[i] != '\0')
            main_parser(all, line[i], /* &(all->arg[all->count]),*/ &i);
        if (all->var_$ == 1)
            check_var(line, &i, &(all->arg[all->count]), all);
        i++;
    }
    // write(1,"\n", 1);
    // all->arg[all->count + 1] = NULL;
    i = 0;
    while(all->arg[i] != 0)
    {
        // printf("\n arg%d: = %s\n", i, all->arg[i]);
        i++;
    }

    // printf("all->pipe is %d\n", all->pipe);
    // printf("all->redir is %d\n", all->redir);
    // printf("all->count is %d\n", all->count);
    // printf("!!! %s\n", all->arg[0]);
    //printf("%d %s\n", 11, all->arg[0]);

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

    // all.prompt = NULL;
    // set_prompt("ajeanett% ", &all);
    // //printf("%s", get_prompt(&all));
    init_struct(&all);
    init_env(&all, envp);
    // int i = 0;
    if (argc > 1 && argv[1])
        ft_putendl_fd("Error.\nToo many arguments", 2);
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
            // ft_choice_function(&all);
            if (line)
                free(line);
    }
    return (0);
}
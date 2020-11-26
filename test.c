/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:01:16 by ajeanett          #+#    #+#             */
/*   Updated: 2020/11/26 18:29:10 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    init_struct(t_all *all)
{
    all->backslash = 0;
    all->dq_open = 0;
    all->pipe = 0;
    all->prompt = "ajeanett_gmarva ";
    all->redir_double = 0;
    all->redir_in = 0;
    all->redir_out = 0;
    all->sq_open = 0;
    all->var_$ = 0;
    all->name_parsed = 0;
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
    all->copy_env = malloc(j + 1);
    all->copy_env[j] = NULL;
    while (i < j)
    {
        all->copy_env[i] = ft_strdup(envp[i]);
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

char	*ft_chrjoin(char const *s1, char const s2)
{
	char *c;
	char *t;

    //printf("s1 = %s, char = %c\n", s1, s2);
	if (!s1 && s2)
		return (ft_strdup(&s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
    // if (s1[0] == '\0')
    // {
    //     c = malloc(2);
    //     c[0] = s2;
    //     c[1] = '\0';
	//     return (c);
    // }
	c = s1 && s2 ? malloc(ft_strlen(s1) + 2) : NULL;
	if (c)
	{
		t = c;
		while (s1 && *s1)
			*t++ = *s1++;
		if (ft_isascii(s2))
			*t++ = s2;
		*t = '\0';
	}
	return (c);
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

// char	*ft_chrjoin(const char *s1, const char s2)
// {
// 	unsigned int	buf;
// 	char			*str;
//     int             i;
    
//     i = 0;
// 	buf = ft_strlen(s1) + 1;
// 	str = ((char *)malloc(sizeof(char) * (buf + 1)));
// 	if (!str)
// 		return (NULL);
// 	while (s1[i] != '\0')
// 	{
// 		str[i] = s1[i];
//         i++;
// 	}
// 	if (s2 != '\0')
// 		str[i++] = s2;
// 	str[i++] = '\0';
// 	return (str);
// }


void    main_parser(t_all *all, const char c, char  **str)
{
    if (c == '$')
    {
        all->var_$ == 0 ? all->var_$ = 1 : 0;
        return;
    }
    //printf("0 s1 = %s, char = %c\n", *str, c);
    if (!(ft_isspace(c)))
        {
        line_to_arg(str, c);
        all->name_parsed == 0 ? all->name_parsed = 1 : 0;
        }
    //printf("2 s1 = %s, char = %c\n", *str, c);
}

// char    *find_var(char *str, char **envp)
// {
//     char *var;
//     char *find;
//     int i;

//     i = 0;
//     while (envp[i])
//     {
//         if (ft_strncmp(str, envp[i], ft_strlen(str)) == 0)
//         {

//         }
//         i++;
//     }
//     return (NULL)
// }

void    check_var(char *line, int i, char **arg, t_all *all)
{
    char *var;
    int  tmp;
    size_t len; 

    tmp = i;
    tmp++;
    var = NULL;
    if (arg && all)
        all->var_$ = 0;
    if ((line[tmp] == ' ') || (line[tmp] == '\0'))
    {
        line_to_arg(arg, line[i]);
        all->name_parsed == 0 ? all->name_parsed = 1 : 0;
        return;
    }
    while (!(ft_strchr(" $;|<>\"\'", line[tmp])))
        tmp++;
    if ((ft_strchr(" $;|<>\"\'", line[tmp])))
    {
        len = (size_t)(tmp - i - 1);
        var = ft_substr(line, (i + 1), len);
    }
    if (var)
    {
        //printf("var: %s\n", var);
        // var = find_var(var, all->copy_env);
    }
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

// int check_size(char *line)
// {
//     int size;
//     int 
//     size = 0;

//     return(size)
// }

void parser(char *line, t_all *all)
{
    char **arg;
    int i;
    int arg_count;
    int size;

    size = 2; //check_size(line);
    // arg = ft_calloc(size, sizeof(char));
    if (!(arg = (char **)malloc(size * (sizeof(char *)))))
        return;
    i = 0;
    arg_count = 0;
    arg[arg_count] = ft_strdup("");
    arg[size - 1] = NULL;
    all->dq_open = 0;
    all->name_parsed = 0;
    printf("line: %s %zu\n\n", line, ft_strlen(line));
    while (line[i] != '\0')
    {
        // write(1,&line[i], 1);
        //printf("0 line [i] = %c i = %d\n", line[i], i);
        while (ft_isspace(line[i]) && all->sq_open == 0 && all->dq_open == 0)
        {
            i++;
            //printf("0.1 line [i] = %c i = %d line %s\n", line[i], i, line);
            if (all->name_parsed == 1)
            {
                all->name_parsed = 0;
                // //printf("do %s\n ", arg[arg_count]);
                arg_count++;
                size++;
                //printf("arg_count %d, size %d \n", arg_count, size);
                arg = ft_realloc(arg, size);
                //printf("0.2 line [i] = %c i = %d line = %s len = %zu\n", line[i], i, line, ft_strlen(line));
                // //printf("posle %s\n ", arg[arg_count - 1]);
                // arg[arg_count] = malloc(1);
                // arg[arg_count][0] = '\0';
                arg[arg_count] = ft_strdup("");
                //printf("0.22 line [i] = %c i = %d line %s\n", line[i], i, line);
                arg[arg_count + 1] = NULL;
            }
            //printf("0.3 line [i] = %c i = %d line %s\n", line[i], i, line);
        }
        //printf("1 line [i] = %c i = %d\n", line[i], i);
        if (all->sq_open == 0 && all->dq_open == 0)
            main_parser(all, line[i], &arg[arg_count]);
        if (all->var_$ == 1)
            check_var(line, i, &arg[arg_count], all);
        i++;
    }
    // write(1,"\n", 1);
    arg[arg_count + 1] = NULL;
    i = 0;
    while(arg[i] != 0)
    {
        printf("\n arg%d: = %s\n", i, arg[i]);
        i++;
    }
    // while(arg[i])
    // {

        // if (arg[i]) 
        //     free(arg[i]);
        // ft_bzero(arg[i], ft_strlen(arg[i]));
    //     i++;
    // }
    i = -1;
    while(arg && arg[++i])
        if (arg[i])
            free(arg[i]);
    if (arg) free(arg);
    arg = NULL;
}

int     main(int argc, char **argv)//, char **envp)
{
    t_all   all;

    // all.prompt = NULL;
    // set_prompt("ajeanett% ", &all);
    // //printf("%s", get_prompt(&all));
    init_struct(&all);
    //init_env(&all, envp);
    // int i = 0;
    if (argc > 1 && argv[1])
        ft_putendl_fd("Error.\nToo many arguments", 2);
    // while(all.copy_env[i])
    // {
    //     //printf("%s\n", all.copy_env[i]);
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
            if (line)
                free(line);
            // if (feof(0))
            // {
			//     exit(0);
			//     return 0;
		    // }
    }
    return (0);
}
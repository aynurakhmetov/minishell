/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:01:16 by ajeanett          #+#    #+#             */
/*   Updated: 2020/11/23 20:47:34 by ajeanett         ###   ########.fr       */
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
    printf("ft_strlen = %d \n", j);
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

	if (!s1 && s2)
		return (ft_strdup(&s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	c = s1 && s2 ? malloc(ft_strlen(s1) + 2) : NULL;
	if (c)
	{
		t = c;
		while (s1 && *s1)
			*t++ = *s1++;
		if (s2)
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



// void    check_line(char chr, t_all *all, int *i)
// {
    
// }

void    main_parser(t_all *all, char c, char  **str)
{
    if (!(ft_isspace(c)))
        {
        line_to_arg(str, c);
        all->name_parsed == 0 ? all->name_parsed = 1 : 0;
        }
}

void parser(char *line, t_all *all)
{
    char **arg;
    int i;
    int arg_count;
    int size;
    
    size = 2;
    arg = ft_calloc(size, sizeof(char));
    i = 0;
    arg_count = 0;
    arg[arg_count] = ft_calloc(1, sizeof(char));
    // ft_bzero(arg[arg_count], 1);
    // arg[arg_count][0] = '\0';
    
    all->dq_open = 0;
    all->name_parsed = 0;
    while (line[i])
    {

        // write(1,&line[i], 1);
        // check_line(line[i], all, &i);
        while (ft_isspace(line[i]) && all->sq_open == 0 && all->dq_open == 0)
        {
            i++;
            if (all->name_parsed == 1)
            {
                all->name_parsed = 0;
                arg_count++;
                arg = realloc(arg, size + 1);
                arg[arg_count] = ft_calloc(1, sizeof(char));
                arg[arg_count][0] = '\0';
            }
        }
        if (all->sq_open == 0 && all->dq_open == 0)
            main_parser(all, line[i], &arg[arg_count]);
        // if (!(ft_isspace(line[i])))
        // {
        // line_to_arg(&arg[arg_count], line[i]);
        // all->name_parsed = 1;
        // }
        i++;
    }
    // write(1,"\n", 1);
    arg[arg_count + 1] = NULL;
    i = 0;
    while(arg[i])
    {
        printf("\n arg%d: = %s\n", i, arg[i]);
        i++;
    }
}

int     main(int argc, char **argv, char **envp)
{
    t_all   all;

    // all.prompt = NULL;
    // set_prompt("ajeanett% ", &all);
    // printf("%s", get_prompt(&all));
    init_struct(&all);
    init_env(&all, envp);
    // int i = 0;
    if (argc > 1 && argv[1])
        ft_putendl_fd("Error.\nToo many arguments", 2);
    // while(all.copy_env[i])
    // {
    //     printf("%s\n", all.copy_env[i]);
    //     i++;
    // }
    
    while(1)
    {
        char *line;
        // size_t len;
            // printf("%s", get_prompt(&all));
            write(1, all.prompt, ft_strlen(all.prompt));
            line = NULL;
            // len = 0;
            get_next_line(0, &line);
            parser(line, &all);
            // if (feof(0))
            // {
			//     exit(0);
			//     return 0;
		    // }
    }
    
    return (0);
}
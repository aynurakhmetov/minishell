/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:01:16 by ajeanett          #+#    #+#             */
/*   Updated: 2020/11/16 21:00:49 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    set_prompt(char* str, t_all *all)
{
    if (all->prompt != NULL)
        free(all->prompt);

    all->prompt = ft_strdup(str);
}

int     get_next_line(char **line)
{
    int ret;
    int i;
    char    *s;
    char    s1;

    i = 0;
    s = malloc(10000);
    while (i < 10000)
        s[i++] = '\0';
    i = 0;
    ret = 1;
    while (ret > 0)
    {
        ret = read(0, &s1, 1);
        if (ret > 0 & s1 != '\n')
            s[i++] = s1;
        if (ret > 0 && s1 == '\n')
        {
            *line = s;
            free(s);
            return (1);
        }
    }
    *line = s;
    free(s);
    return (0);
}

char    *get_prompt(t_all *all)
{
    return (all->prompt);
}

int     main()
{
    t_all   all;



    all.prompt = NULL;
    set_prompt("ajeanett% ", &all);
    printf("%s", get_prompt(&all));
    while(1)
    {
        char *linebuffer;
        size_t len;

  
            // printf("%s", get_prompt(&all));
            write(1, "ajeanett ", 10);
            linebuffer = NULL;
            len = 0;
            get_next_line(&linebuffer);
            printf("success");
            // if (nread <= 0 && errno == EINTR)
            // {
            //     again = 1;
            //     clearerr(0);
            // }
            if (feof(stdin))
            {
			    exit(0);
			    return 0;
		    }
    }
    
    return (0);
}
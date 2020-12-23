/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 19:20:19 by ajeanett          #+#    #+#             */
/*   Updated: 2020/12/23 19:22:07 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == ' ')
		return (1);
	return (0);
}

void    ft_free(char **str)
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

int		line_to_arg(char **line, char chr)
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
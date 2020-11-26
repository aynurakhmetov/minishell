/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:20:04 by ajeanett          #+#    #+#             */
/*   Updated: 2020/10/22 12:58:09 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		ft_free(char **str)
{
	free(*str);
	*str = NULL;
}

static int		buf_to_line(char **line, char *buf)
{
	char *tmp;

	tmp = *line;
	if (!(*line = ft_strjoin(*line, buf)))
		return (-1);
	ft_free(&tmp);
	return (0);
}

static int		check_saved_data(char *saved_data, char **line)
{
	char	*ptr_n;

	ptr_n = NULL;
	if (saved_data)
	{
		if ((ptr_n = ft_strchr(saved_data, '\n')))
		{
			*ptr_n = '\0';
			if (!(*line = ft_strdup(saved_data)))
				return (-1);
			ft_strcpy(saved_data, ++ptr_n);
			return (1);
		}
		else
		{
			if (!(*line = ft_strdup(saved_data)))
				return (-1);
			return (0);
		}
	}
	else if (!(*line = ft_strdup("")))
		return (-1);
	return (0);
}

int				get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	int			count_read;
	char		*ptr_n;
	static char	*saved_data = NULL;
	int			flag;

	flag = 0;
	count_read = 0;
	ptr_n = NULL;
	if ((fd < 0) || (BUFFER_SIZE <= 0) || line == NULL || read(fd, buf, 0) < 0)
		return (-1);
	if ((flag = check_saved_data(saved_data, line)) != 1)
		ft_free(&saved_data);
	while (!ptr_n && !flag && (count_read = read(fd, buf, BUFFER_SIZE)))
	{
		buf[count_read] = '\0';
		if ((ptr_n = ft_strchr(buf, '\n')))
		{
			*ptr_n = '\0';
			if (!(saved_data = ft_strdup(++ptr_n)))
				return (-1);
		}
		buf_to_line(line, buf);
	}
	return ((flag == 1 || count_read) ? 1 : 0);
}

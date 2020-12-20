/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 00:40:10 by gmarva            #+#    #+#             */
/*   Updated: 2020/11/27 19:58:05 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include "minishell.h"

int		ft_get_i(char *src)
{
	int i;

	i = 0;
	while (src[i] && src[i] != '\n')
		i++;
	return (i);
}

char	*ft_newline(char *src)
{
	int		i;
	char	*dst;

	if (!src)
		return (0);
	i = ft_get_i(src);
	if (!(dst = (char *)malloc(sizeof(char) * (i + 1))))
	{
		free(src);
		return (0);
	}
	ft_memmove(dst, src, i);
	dst[i] = '\0';
	return (dst);
}

char	*ft_endtest(char *src)
{
	int i;

	if (src)
	{
		i = ft_get_i(src);
		if (!src[i])
		{
			free(src);
			return (0);
		}
	}
	return (src);
}

char	*ft_newmem(char *src)
{
	int		i;
	int		j;
	char	*dst;

	if (!src)
		return (0);
	i = ft_get_i(src);
	if (!(dst = (char *)malloc(sizeof(char) * (ft_strlen(src) - i + 1))))
	{
		free(src);
		return (0);
	}
	j = 0;
	i++;
	while (src[i])
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	free(src);
	return (dst);
}

int		get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	int			bytes;
	char	*mem;
	mem = NULL;

	bytes = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (mem)
		free(mem);
	mem = ft_calloc(1, 1);
	while (!(ft_strchr(mem, '\n')) && (bytes != 0) && mem)
	{
		if ((bytes = read(fd, buf, BUFFER_SIZE)) == -1)
			free(mem);
		if (bytes == -1)
			return (-1);
		buf[bytes] = '\0';
		mem = ft_strjoin(mem, buf);
	}
	if (!(*line = ft_newline(mem)) || !mem)
		return (-1);
	if ((mem = ft_endtest(mem)) != 0)
		if ((mem = ft_newmem(mem)) == 0)
			return (-1);
	if (bytes == 0 && mem)
	{
		free(mem);
		mem = NULL;
	}
	return (bytes == 0 ? 0 : 1);
}

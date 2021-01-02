/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 00:40:10 by gmarva            #+#    #+#             */
/*   Updated: 2021/01/02 21:14:16 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	ft_memmove2(dst, src, i);
	dst[i] = '\0';
	return (dst);
}

int		get_next_line(t_all *all, int fd, char **line)
{
	char	buf[BUFFER_SIZE + 1];
	int		bytes;
	char	*mem;

	g_read_start = 0;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	mem = ft_calloc(1, 1);
	while (!(ft_strchr2(mem, '\n')) && mem)
	{
		if ((bytes = read(fd, buf, BUFFER_SIZE)) == -1)
			free(mem);
		if (bytes == -1)
			return (-1);
		buf[bytes] = '\0';
		mem = ft_strjoin2(mem, buf);
		ft_signal_treatment(all, buf[0], mem);
		g_read_start++;
	}
	if (!(*line = ft_newline(mem)) || !mem)
		return (-1);
	if (mem)
		ft_free(&mem);
	return (bytes == 0 ? 0 : 1);
}

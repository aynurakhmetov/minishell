/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 19:41:11 by ajeanett          #+#    #+#             */
/*   Updated: 2020/05/30 16:10:13 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*str;
	size_t		begin;
	size_t		end;
	size_t		len;

	begin = 0;
	end = ft_strlen(s1);
	while (s1[begin] != '\0' && ft_strchr(set, s1[begin]))
		begin++;
	while (end != 0 && ft_strchr(set, s1[end]))
		end--;
	if (end < begin)
		len = 0;
	else
		len = end - begin + 1;
	str = ft_substr(s1, begin, len);
	return (str);
}

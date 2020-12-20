/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 19:41:18 by ajeanett          #+#    #+#             */
/*   Updated: 2020/05/30 16:10:17 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	i;
	unsigned int	tmp;

	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	i = 0;
	tmp = len;
	if (!(substr = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i != start && s[i] != '\0')
		i++;
	while (s[i] != '\0' && i >= start && len--)
	{
		*substr++ = s[i];
		i++;
	}
	*substr = '\0';
	return (((char *)substr) - tmp);
}

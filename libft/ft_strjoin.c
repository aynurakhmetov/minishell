/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 19:40:17 by ajeanett          #+#    #+#             */
/*   Updated: 2020/12/20 19:43:17 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	unsigned int	buf;
// 	char			*str;

// 	buf = ft_strlen(s1) + ft_strlen(s2);
// 	str = ((char *)malloc(sizeof(char) * (buf + 1)));
// 	if (!str)
// 		return (NULL);
// 	while (*s1 != '\0')
// 	{
// 		*str++ = *s1++;
// 	}
// 	while (*s2 != '\0')
// 	{
// 		*str++ = *s2++;
// 	}
// 	*str++ = '\0';
// 	return (str - (buf + 1));
// }

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	if (!(str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1)
					* sizeof(char))))
		return (NULL);
	while (i < ft_strlen(s1))
	{
		str[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

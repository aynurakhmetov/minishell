/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 19:39:56 by ajeanett          #+#    #+#             */
/*   Updated: 2020/05/30 16:09:24 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		c_strlen(const char *s, char c, int start)
{
	size_t	i;

	i = 0;
	while (s[start] != c && s[start] != '\0')
	{
		i++;
		start++;
	}
	return (i);
}

static char			**free_memory(char **array, int j)
{
	while (j-- > 0)
		free(array[j]);
	free(array);
	return (NULL);
}

static char			**fill_word(char **array, const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	size;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i] != '\0')
		{
			size = c_strlen(s, c, i);
			array[j] = ft_substr(s, i, size);
			if (array[j] == NULL)
				return (free_memory(array, j));
			i = i + size;
			j++;
		}
		else
			i++;
	}
	array[j] = NULL;
	return (array);
}

static size_t		word_count(char const *s, char c)
{
	size_t	index;
	size_t	words;

	words = 0;
	index = 0;
	while (s[index] == c && s[index] != '\0')
		index++;
	while (s[index] != '\0')
	{
		while (s[index] != c && s[index] != '\0')
			index++;
		words++;
		while (s[index] == c && s[index] != '\0')
			index++;
	}
	return (words);
}

char				**ft_split(char const *s, char c)
{
	char	**array;
	size_t	size;

	size = 0;
	size = word_count(s, c);
	array = ((char **)malloc(sizeof(char *) * (size + 1)));
	if (!array)
		return (NULL);
	fill_word(array, s, c);
	return (array);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 07:04:14 by gmarva            #+#    #+#             */
/*   Updated: 2020/11/26 07:04:18 by gmarva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	**ft_array_copy(char **array_original, int i)
{
	char	**array_copy;
	int		k;
	int		tmp;

	k = 0;
	tmp = i;
	i -= 1;
	while(array_original[++i] != 0)
		k++;
	array_copy = (char **)malloc(sizeof(char*) * (k + 1));
	tmp -= 1;
	i = -1;
	while(array_original[++tmp] != 0)
		array_copy[++i] = ft_strdup(array_original[tmp]);
	return (array_copy);
}

int		main(int argc, char *argv[], char *envp[])
{
	t_all	all;
	int		result;

	if (argc > 1)
	{
		all.env = ft_array_copy(envp, 0);
		all.arg = ft_array_copy(argv, 1);
		if (ft_strncmp(argv[1],  "echo", ft_strlen("echo")) == 0)
			ft_echo(&all);
		if (ft_strncmp(argv[1],  "cd", ft_strlen("cd")) == 0)
			result = ft_cd(&all);
	}
	return (0);
}
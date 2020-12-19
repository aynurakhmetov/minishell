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

void	ft_choice_function(int argc, char *argv[], char *envp[])
{
	t_all	all;
	int		result;

	if (argc > 1)
	{
		all.env = ft_array_copy(envp, 0);
		all.arg = ft_array_copy(argv, 1);
		if (ft_strncmp(argv[1], "echo", ft_strlen("echo")) == 0 && ft_strlen("echo") == ft_strlen(argv[1]))
			ft_echo(&all);
		else if (ft_strncmp(argv[1], "cd", ft_strlen("cd")) == 0 && ft_strlen("cd") == ft_strlen(argv[1]))
			result = ft_cd(&all);
		else if (ft_strncmp(argv[1], "pwd", ft_strlen("pwd")) == 0 && ft_strlen("pwd") == ft_strlen(argv[1]))
			result = ft_pwd(&all);
		else if (ft_strncmp(argv[1], "export", ft_strlen("export")) == 0 && ft_strlen("export") == ft_strlen(argv[1]) && argc == 2)
			result = ft_export(&all);
		else if (ft_strncmp(argv[1], "export", ft_strlen("export")) == 0 && ft_strlen("export") == ft_strlen(argv[1]) && argc > 2)
			result = ft_export_set(&all);
		else if (ft_strncmp(argv[1], "env", ft_strlen("env")) == 0 && ft_strlen("env") == ft_strlen(argv[1]))
			result = ft_env(&all);
		else if (ft_strncmp(argv[1], "unset", ft_strlen("unset")) == 0 && ft_strlen("unset") == ft_strlen(argv[1]))
			result = ft_unset(&all);
		else if (ft_strncmp(argv[1],  "exit", ft_strlen("exit")) == 0 && ft_strlen("exit") == ft_strlen(argv[1]))
			ft_exit(&all);
		else if (ft_strncmp(argv[1],  "$?", ft_strlen("$?")) == 0 && ft_strlen("$?") == ft_strlen(argv[1]))
			ft_s_result(&all);
		else
		{
			// pid_t pid;
			// pid = fork();
			printf("Ya tut\n");
			ft_execve(&all);
		}
		// Сделать ЭКЗЭКВЕЕ для всех остальных
		// Возврат кода функции для $?
		// Еще ддя команд нот фаунд
		// Принимаю редиректы < > “>>” + чекать флаг редиректов
		// Флаг пайп, если поднят -> сохранять открытми fd
	}
}

int		main(int argc, char *argv[], char *envp[])
{
	ft_choice_function(argc, argv, envp);
	return (0);
}
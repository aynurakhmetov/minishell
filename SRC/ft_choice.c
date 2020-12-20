/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_choice.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 07:04:14 by gmarva            #+#    #+#             */
/*   Updated: 2020/12/20 20:56:39 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	ft_choice_function(t_all *all)
{
	// проверить последний аргумент на пустоту
	// проверка на пайп
	// проверка на редирект
	// a->count ++
	int		result;

	// printf("%d\n", 10);
	// printf("%d %s\n", 11, all->arg[0]);
	if (ft_strncmp(all->arg[0], "echo", ft_strlen("echo")) == 0 && ft_strlen("echo") == ft_strlen(all->arg[0]))
	{
		// printf("%f\n", 11.2);
		ft_echo(all);
		// printf("%d\n", 12);
	}
	else if (ft_strncmp(all->arg[0], "cd", ft_strlen("cd")) == 0 && ft_strlen("cd") == ft_strlen(all->arg[0]))
		result = ft_cd(all);
	else if (ft_strncmp(all->arg[0], "pwd", ft_strlen("pwd")) == 0 && ft_strlen("pwd") == ft_strlen(all->arg[0]))
		result = ft_pwd(all);
	else if (ft_strncmp(all->arg[0], "export", ft_strlen("export")) == 0 && ft_strlen("export") == ft_strlen(all->arg[0]) && all->count + 1 == 1)
		result = ft_export(all);
	else if (ft_strncmp(all->arg[0], "export", ft_strlen("export")) == 0 && ft_strlen("export") == ft_strlen(all->arg[0]) && all->count + 1 > 1)
		result = ft_export_set(all);
	else if (ft_strncmp(all->arg[0], "env", ft_strlen("env")) == 0 && ft_strlen("env") == ft_strlen(all->arg[0]))
		result = ft_env(all);
	else if (ft_strncmp(all->arg[0], "unset", ft_strlen("unset")) == 0 && ft_strlen("unset") == ft_strlen(all->arg[0]))
		result = ft_unset(all);
	else if (ft_strncmp(all->arg[0],  "exit", ft_strlen("exit")) == 0 && ft_strlen("exit") == ft_strlen(all->arg[0]))
		ft_exit(all);
	else if (ft_strncmp(all->arg[0],  "$?", ft_strlen("$?")) == 0 && ft_strlen("$?") == ft_strlen(all->arg[0]))
		ft_s_result(all);
	else
	{
		//printf("Ya tut\n");
		int *status = NULL;
		pid_t pid;
		// printf("%d\n", 11);
		if ((pid = fork()) < 0)
			ft_putendl_fd("fork_error", 1);
		else if (pid == 0)
		{
			ft_execve(all);
			exit(0);
		}
		wait(status);
		// printf("%d\n", 12);
		return;
	}
	// Проверить ЭКЗЭКВЕЕ для всех остальных
	// Возврат кода функции для $?
	// Еще ддя команд нот фаунд
	// Принимаю редиректы < > “>>” + чекать флаг редиректов
	// Флаг пайп, если поднят -> сохранять открытми fd
}
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
	//printf("k = %d", k + 1);
	while(array_original[++tmp] != 0)
	{
		array_copy[++i] = ft_strdup(array_original[tmp]);
		//printf("%d %d %s\n", i, tmp, array_copy[i]);
	}
	//printf("i = %d", i + 1);
	array_copy[i + 1] = 0;
	return (array_copy);
}

void	ft_switch_function(t_all *all)
{
	int		result;
	char	**tmp;
	int 	k;

	k = 0;
	if (all->pipe == 1 && all->redir == 1)
		ft_pipe(all);
	if (all->pipe == 1 || all->redir == 1)
	{
		k++;
		tmp = all->arg;
		all->arg = all->newarg;
		//printf("hey %s\n", all->arg[0]);
	}
	// int i = -1;
	// while (all->arg[++i] != 0)
	//printf("TUT %s\n", all->arg[0]);

	printf("arg[0] = %s\n", all->arg[0]);
	if (ft_strncmp(all->arg[0], "echo", ft_strlen("echo")) == 0 && ft_strlen("echo") == ft_strlen(all->arg[0]))
		ft_echo(all);
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
		//printf("Ya tut 2\n");
		// Разобраться с wait
		pid_t pid;
		int *status = NULL;
		
		if ((pid = fork()) < 0)
			ft_putendl_fd("fork_error", 1);
		else if (pid == 0)
			ft_execve(all);
		wait(status);
		// обработка ошибок
	}
	if (k > 0)
	{
		//printf("choise k > 0 1\n");
		//ft_free_array(all->arg);
		all->arg = tmp;
		k = 0;
	}
}

void	ft_choice_function(t_all *all)
{
	// проверить последний аргумент на пустоту
	// проверка на пайп
	// проверка на редирект
	// a->count ++
	
	printf("pipe flag %d\n", all->pipe);
	printf("redir flag %d\n", all->redir);
	//ft_switch_function(all);

	if ((all->pipe == 1 && all->redir == 0))
	{
		printf("0 Ya tut\n");
		ft_pipe(all);
	}
	else if ((all->pipe == 0 && all->redir == 1) || (all->pipe == 1 && all->redir == 1))
		ft_redir(all);
	else
		ft_switch_function(all);
	
	// Проверить ЭКЗЭКВЕЕ для всех остальных
	// Возврат кода функции для $?
	// Еще ддя команд нот фаунд
	// Принимаю редиректы < > “>>” + чекать флаг редиректов
	// Флаг пайп, если поднят -> сохранять открытми fd
	// проверить в гите
}
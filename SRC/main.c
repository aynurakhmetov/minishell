#include "../minishell.h"

int		main(int argc, char *argv[], char *envp[])
{
	t_all	all;
	
	if (argc > 1)
	{
		all.env = ft_array_copy(envp, 0);
		all.arg = ft_array_copy(argv, 1);
		all.count = argc - 2;
		all.pipe = 1;
		ft_choice_function(&all);
	}
	// Сравнить с гитом в мастере
	// Посмотреть кейсы в слаке от Вовы и Ильнура
	// Разобраться как работает exit
	return (0);
}
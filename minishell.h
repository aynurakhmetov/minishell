#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "./libft/libft.h"

typedef struct	s_all
{
	char	**arg;
	char	**env;
	int		fd;
}				t_all;

int		ft_echo(t_all *all);
int		ft_cd(t_all *all);
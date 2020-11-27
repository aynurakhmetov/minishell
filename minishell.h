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


char	**ft_array_copy(char **array_original, int i);
void	ft_free_array(char **str);
int		ft_echo(t_all *all);
int		ft_cd(t_all *all);
int		ft_pwd(t_all *all);
int		ft_export(t_all *all);
int		ft_env(t_all *all);
int		ft_unset(t_all *all);
void	ft_exit(t_all *all);
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 17:31:53 by ajeanett          #+#    #+#             */
/*   Updated: 2020/12/20 22:01:09 by ajeanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
#include <sys/types.h>
#include <dirent.h>

# include "get_next_line.h"

typedef struct		s_list_arg
{
	char			*content;
	struct s_list	*next;
}					t_arg;

typedef struct		s_all
{
	char			*prompt;
	int				backslash;
	int				var_$;
	int				pipe;
	int				redir;
	int				name_parsed;
	char			**env;
	char			**arg;
	int				count;
	int				size;
	int				$_res;
	int				fd;
}					t_all;

int		get_next_line(int fd, char **line);
char	*ft_chrjoin(char *s1, const char s2);
char	**ft_realloc(char **ptr, size_t newsize);
int	    check_end(t_all *all, int *i, char c);
//Ainur func
char	**ft_array_copy(char **array_original, int i);
void	ft_free_array(char **str);
int		ft_echo(t_all *all);
int		ft_cd(t_all *all);
int		ft_pwd(t_all *all);
int		ft_export(t_all *all);
int		ft_export_set(t_all *all);
int		ft_env(t_all *all);
int		ft_unset(t_all *all);
void	ft_exit(t_all *all);
void	ft_s_result(t_all *all);
void	ft_execve(t_all *all);
void	ft_choice_function(t_all *all);

#endif

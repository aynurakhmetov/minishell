/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 17:31:53 by ajeanett          #+#    #+#             */
/*   Updated: 2020/12/20 15:14:48 by ajeanett         ###   ########.fr       */
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
	char			**copy_env;
	char			**arg;
	int				count;
	int				size;
	int				$_ret;
	int				fd;
}					t_all;

int		get_next_line(int fd, char **line);
char	*ft_chrjoin(const char *s1, const char s2);
char	**ft_realloc(char **ptr, size_t newsize);

#endif

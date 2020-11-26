/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 17:31:53 by ajeanett          #+#    #+#             */
/*   Updated: 2020/11/22 22:13:18 by ajeanett         ###   ########.fr       */
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

# define MOVE_SPEED 0.1

typedef struct		s_flag
{
	int				dq_open;
	int				sq_open;
	int				backslash;
}					t_flag;

typedef struct		s_list_arg
{
	char			*content;
	struct s_list	*next;
}					t_arg;

typedef struct		s_all
{
	char			*prompt;
	int				dq_open;
	int				sq_open;
	int				backslash;
	int				var_$;
	int				pipe;
	int				redir_in;
	int				redir_out;
	int				redir_double;
	int				name_parsed;
	char			**copy_env;
}					t_all;

int		get_next_line(int fd, char **line);
char	*ft_chrjoin(const char *s1, const char s2);


#endif

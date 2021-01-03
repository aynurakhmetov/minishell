/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanett <ajeanett@42.ru>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 17:31:53 by ajeanett          #+#    #+#             */
/*   Updated: 2021/01/03 12:54:36 by ajeanett         ###   ########.fr       */
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
# include <sys/types.h>
# include <dirent.h>
# include <unistd.h>
# include <sys/wait.h>
# define BUFFER_SIZE 1

int					g_read_start;
int					g_all_start;
int					g_execve_signal;
int					g_res;

typedef struct		s_list_arg
{
	char			*content;
	struct s_list	*next;
}					t_arg;

typedef struct		s_all
{
	char			*prompt;
	int				backslash;
	int				quotes;
	int				sq;
	int				dq;
	int				var;
	int				pipe;
	int				redir;
	int				name_parsed;
	char			**env;
	char			**arg;
	int				count;
	int				size;
	int				res;
	int				fd;
	char			**newarg;
	int				l_redir;
	int				r_redir;
	int				fdtmp_1;
	int				fdtmp_0;
	pid_t			*pid;
	int				fdtmp[2];
	int				have_read;
}					t_all;

int					get_next_line(t_all *all, int fd, char **line);
size_t				ft_strlen2(const char *str);
char				*ft_strdup2(const char *str);
char				*ft_strjoin2(char const *s1, char const *s2);
char				*ft_strchr2(const char *str, int ch);
void				*ft_memmove2(void *des, const void *src, size_t n);
int					ft_get_i(char *src);
char				*ft_newline(char *src);
char				*ft_chrjoin(char *s1, const char s2);
char				**ft_realloc(char **ptr, size_t newsize);
int					check_end(t_all *all, char c);
void				init_struct(t_all *all);
void				init_env(t_all *all, char **envp);
void				init_arg(t_all *all);
void				clear_arg(t_all *all);
int					ft_isspace(int c);
void				ft_free(char **str);
int					line_to_arg(char **line, char chr);
void				check_arg(t_all *all);
char				check_backslash_m(t_all *all, int *i, char c, char *line);
int					check_parser_var(t_all *all, int *i, char c, char *line);
void				main_parser(t_all *all, char c, char *line, int *i);
char				*find_var(char *str, char **envp);
void				var_to_arg(char *var, t_all *all);
int					check_var(char *line, int *i, char **arg, t_all *all);
void				check_backslash(t_all *all, int *i, char c, char next);
int					check_d_var_result(t_all *all, int *i);
void				dqotes_parser(t_all *all, char *line, int *i);
void				sqotes_parser(t_all *all, char *line, int *i);
void				ft_e(char c);
void				ft_e_red(char *s);
int					check_left_redir(char *line, int i);
int					check_right_redir(char *line, int i);
int					check_redir(char *line, int i);
void				quotes_flag(char c, t_all *all);
int					check_syntax(char *line, t_all *all);
char				**ft_array_copy(char **array_original, int i);
void				ft_free_array(char **str);
int					ft_echo(t_all *all);
int					ft_cd(t_all *all);
int					ft_pwd(t_all *all);
int					ft_export(t_all *all);
int					ft_export_set(t_all *all);
int					ft_env(t_all *all);
int					ft_unset(t_all *all);
void				ft_exit(t_all *all);
void				ft_s_result(t_all *all);
void				ft_execve(t_all *all);
void				ft_choice_function(t_all *all);
void				ft_switch_function(t_all *all);
void				ft_pipe(t_all *all);
void				ft_redir(t_all *all);
void				ft_get_newarg2(t_all *all, char **str, int i, int k);
void				ft_make_newarg2(t_all *all, int pipenum);
int					ft_get_number_of_redir(t_all *all);
void				ft_get_each_redir(t_all *all, int *redir);
void				ft_close_fd(t_all *all);
void				ft_signal_treatment(t_all *all, char buf_one, char *mem);
void				ft_react_c(void);
void				ft_react_slash(void);
void				set_pipe(t_all *all, int *i, char c, char *line);
void				set_redir(t_all *all, int *i, char c, char *line);
void				add_arg(t_all *all);

#endif

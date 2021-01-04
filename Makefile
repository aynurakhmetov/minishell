# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/09 15:15:25 by ajeanett          #+#    #+#              #
#    Updated: 2021/01/04 19:00:59 by ajeanett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS =	SRC/main.c SRC/get_next_line.c SRC/get_next_line_utils.c SRC/ft_choice.c SRC/ft_echo.c SRC/ft_cd.c SRC/ft_pwd.c SRC/ft_export.c SRC/ft_env.c SRC/ft_unset.c \
		SRC/ft_exit.c SRC/ft_execve.c SRC/ft_export_set.c SRC/ft_pipe.c SRC/ft_redir.c SRC/init.c SRC/function.c SRC/main_parser.c SRC/variable.c \
		SRC/function2.c SRC/quotes_parser.c SRC/parser_check.c SRC/parser_check2.c SRC/ft_redir2.c SRC/ft_redir3.c SRC/ft_signal.c SRC/ft_pipe2.c \
		SRC/variable2.c
	
OBJECTS = $(SRCS:.c=.o)
FLAGS = gcc -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS)
	make -C libft/
	gcc $(OBJECTS) -o $(NAME) libft/libft.a

%.o: %.c
	$(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS)
	make clean -C libft/

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft/

re: fclean all

.PHONY: all clean fclean re %.o test

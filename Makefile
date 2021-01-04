# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/09 15:15:25 by ajeanett          #+#    #+#              #
#    Updated: 2021/01/04 17:40:03 by ajeanett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS =	test.c get_next_line.c get_next_line_utils.c SRC/ft_choice.c SRC/ft_echo.c SRC/ft_cd.c SRC/ft_pwd.c SRC/ft_export.c SRC/ft_env.c SRC/ft_unset.c \
		SRC/ft_exit.c SRC/ft_execve.c SRC/ft_export_set.c SRC/ft_pipe.c SRC/ft_redir.c init.c function.c main_parser.c variable.c \
		function2.c quotes_parser.c parser_check.c parser_check2.c SRC/ft_redir2.c SRC/ft_redir3.c SRC/ft_signal.c SRC/ft_pipe2.c \
		variable2.c
	
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

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re %.o test

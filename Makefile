# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/09 15:15:25 by ajeanett          #+#    #+#              #
#    Updated: 2020/12/20 16:33:25 by ajeanett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS =	test.c get_next_line.c get_next_line_utils.c SRC/ft_choice.c SRC/ft_echo.c SRC/ft_cd.c SRC/ft_pwd.c SRC/ft_export.c SRC/ft_env.c SRC/ft_unset.c \
		SRC/ft_exit.c SRC/ft_s_result.c SRC/ft_execve.c SRC/ft_export_set.c
	
OBJECTS = $(SRCS:.c=.o)
FLAGS = gcc -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS)
	make -C libft/
	gcc -g $? -o $(NAME) libft/libft.a

%.o: %.c
	$(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re %.o test

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/09 15:15:25 by ajeanett          #+#    #+#              #
#    Updated: 2020/11/16 21:11:44 by ajeanett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out
SRCS =	main.c ft_echo.c ft_cd.c ft_pwd.c ft_export.c ft_env.c ft_unset.c \
		ft_exit.c ft_s_result.c ft_execve.c
	
OBJECTS = $(SRCS:.c=.o)
FLAGS = gcc -g -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS)
	make -C libft/
	gcc $(OBJECTS) libft/libft.a -o $(NAME) 

%.o: %.c
	$(FLAGS) -o $@ -c $^

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re %.o test

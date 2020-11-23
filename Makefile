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

NAME = minishell
SRCS =	ft_echo.c
	
OBJECTS = $(SRCS:.c=.o)
FLAGS = gcc -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS)
	gcc $(OBJECTS) -o $(NAME) 

%.o: %.c
	$(FLAGS) -o $@ -c $^

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re %.o test

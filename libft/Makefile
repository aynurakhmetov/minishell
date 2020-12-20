# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajeanett <ajeanett@21-school.ru>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/25 14:13:45 by ajeanett          #+#    #+#              #
#    Updated: 2020/10/26 13:15:13 by ajeanett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS =	ft_memset.c			ft_bzero.c		ft_memcpy.c		ft_memccpy.c	ft_memmove.c \
			ft_memchr.c		ft_memcmp.c		ft_strlen.c		ft_strlcpy.c	ft_strlcat.c \
			ft_isalnum.c	ft_isalpha.c	ft_isascii.c	ft_isdigit.c	ft_isprint.c \
			ft_tolower.c	ft_toupper.c \
			ft_strchr.c		ft_strrchr.c	ft_strnstr.c	ft_strncmp.c \
			ft_strdup.c		ft_calloc.c		ft_atoi.c \
			ft_substr.c		ft_strjoin.c	ft_strtrim.c	ft_split.c				 \
			ft_itoa.c		ft_strmapi.c \
			ft_putendl_fd.c	ft_putnbr_fd.c	ft_putchar_fd.c	ft_putstr_fd.c
B_SRCS = 	ft_lstnew.c		ft_lstadd_front.c	ft_lstsize.c	ft_lstlast.c \
			ft_lstadd_back.c	ft_lstdelone.c	ft_lstclear.c \
			ft_lstiter.c	ft_lstmap.c
			
OBJECTS = $(SRCS:.c=.o)
B_OBJECTS = $(B_SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror
H = libft.h

ifdef MAKE_BONUS
SRC = $(B_SRCS)
OBJ = $(B_OBJECTS)
else
SRC = $(SRCS)
OBJ = $(OBJECTS)
endif

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $?
	@ranlib $(NAME)

%.o: %.c $(H)
	@gcc $(FLAGS) -c $< -o $@

bonus:
	$(MAKE) MAKE_BONUS=1 all

clean:
	rm -rf $(OBJECTS)
	rm -rf $(B_OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re %.o so

so:
	gcc $(FLAGS) -c -fPIC $(SRC)
	gcc -shared -o libft.so $(OBJ)
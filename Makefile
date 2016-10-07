# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myoung <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/22 12:51:39 by myoung            #+#    #+#              #
#    Updated: 2016/10/07 16:32:35 by myoung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fillit
CC			=	gcc
CFLAGS		?=	-Wall -Wextra -Werror

FILENAMES	=	read_mino.c place_mino.c print_mino.c

SOURCES		=	$(FILENAMES)
OBJECTS		=	$(FILENAMES:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $^ -o $@

clean:
	@rm -rf $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c
	gcc -c $< -o $@

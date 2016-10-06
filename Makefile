# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myoung <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/22 12:51:39 by myoung            #+#    #+#              #
#    Updated: 2016/10/05 11:10:19 by myoung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fillit
CC			=	gcc
CFLAGS		?=	-Wall -Wextra -Werror
AR			?=	ar

FILENAMES	=	read_minos.c

SOURCES		=	$(FILENAMES)
OBJECTS		=	$(FILENAMES:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

clean:
	@rm -rf $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test:
	gcc test_fillit.c && ./a.out

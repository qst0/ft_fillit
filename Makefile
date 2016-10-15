# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myoung <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/22 12:51:39 by myoung            #+#    #+#              #
#    Updated: 2016/10/07 16:41:21 by myoung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fillit
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

SRC			=	read_mino.c place_mino.c print_mino.c
OBJ			=	$(addprefix $(OBJDIR),$(SRC:.c=.o))
INC			=	./includes/

LIBFT		=	./libft/libft.a
FTINC		=	-I ./libft/
FTLINK		=	-L ./libft/ -lft

OBJDIR		=	./obj/
SRCDIR		=	./src/
INCDIR		=	./includes/

.PHONY: all clean fclean re

all: obj $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c
	gcc $(CFLAGS) $(FTINC) -I $(INC) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(FTLINK) -o $(NAME)

libft: $(LIBFT)

$(LIBFT):
	make -C ./libft/

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

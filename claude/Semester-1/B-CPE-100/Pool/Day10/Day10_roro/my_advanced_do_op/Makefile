##
## EPITECH PROJECT, 2024
## my_advanced_do-op
## File description:
## Makefile for my_advanced_do-op
##

SRC	=	my_advanced_do-op.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_advanced_do-op

CFLAGS	=	-Wall -Wextra -Werror -std=gnu99 -I../include

LIBPATH	=	../lib

LIBNAME	=	libmy.a

LIB	=	$(LIBPATH)/$(LIBNAME)

all:	$(NAME)

$(NAME):	$(OBJ) $(LIB)
	gcc -o $(NAME) $(OBJ) $(LIB)

$(LIB):
	$(MAKE) -C ../lib/my

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
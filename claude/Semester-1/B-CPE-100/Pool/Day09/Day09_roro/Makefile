##
## EPITECH PROJECT, 2024
## Day09
## File description:
## Makefile
##

SRC	=	my_params_to_array.c	\
		my_show_param_array.c	\
		get_color.c		\
		swap_endian_color.c	\
		test_day09.c

OBJ	=	$(SRC:.c=.o)

NAME	=	test_day09

CFLAGS	=	-Wall -Wextra -Werror -std=gnu99 -I./include

LIBPATH	=	./lib/my

LIBNAME	=	libmy.a

LIB	=	$(LIBPATH)/$(LIBNAME)

all:	$(LIB) $(NAME)

$(LIB):
	$(MAKE) -C $(LIBPATH)

$(NAME):	$(OBJ) $(LIB)
	gcc -o $(NAME) $(OBJ) $(LIB)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBPATH) clean

fclean:	clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBPATH) fclean

re:	fclean all

.PHONY:	all clean fclean re
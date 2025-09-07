##
## EPITECH PROJECT, 2024
## Day11
## File description:
## Makefile for Day11
##

SRC	=	my_params_to_list.c		\
		my_list_size.c			\
		my_rev_list.c			\
		my_apply_on_nodes.c		\
		my_apply_on_matching_nodes.c	\
		my_find_node.c			\
		my_delete_nodes.c		\
		my_concat_list.c		\
		my_sort_list.c			\
		my_add_in_sorted_list.c		\
		my_merge.c

OBJ	=	$(SRC:.c=.o)

NAME	=	libday11.a

CFLAGS	=	-Wall -Wextra -Werror -std=gnu99 -I./include

LIBPATH	=	./lib/my

LIBNAME	=	libmy.a

LIB	=	$(LIBPATH)/$(LIBNAME)

all:	$(LIB) $(NAME)

$(LIB):
	$(MAKE) -C $(LIBPATH)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBPATH) clean

fclean:	clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBPATH) fclean

re:	fclean all

.PHONY:	all clean fclean re
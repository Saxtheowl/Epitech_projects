##
## EPITECH PROJECT, 2025
## Setting_up
## File description:
## Makefile
##

SRC	=	src/main.c	\
		src/file_operations.c	\
		src/board_operations.c	\
		src/algorithm.c	\
		src/utils.c

OBJ	=	$(SRC:.c=.o)

NAME	=	setting_up

CFLAGS	=	-Wall -Wextra -Werror -I./include

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
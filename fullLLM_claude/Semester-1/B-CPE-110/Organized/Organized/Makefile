##
## EPITECH PROJECT, 2024
## Organized
## File description:
## Makefile
##

NAME	= organized

SRC	= main.c \
	  utils.c \
	  string_utils.c \
	  material.c \
	  commands.c \
	  sorting.c

OBJ	= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) -L. -lshell

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
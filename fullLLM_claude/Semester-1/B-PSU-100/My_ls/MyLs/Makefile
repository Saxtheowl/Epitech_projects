##
## EPITECH PROJECT, 2024
## My_ls
## File description:
## Makefile
##

NAME	= my_ls

SRC	= main.c \
	  utils.c \
	  options.c \
	  file_operations.c \
	  ls_core.c

OBJ	= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
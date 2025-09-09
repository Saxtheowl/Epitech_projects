##
## EPITECH PROJECT, 2024
## BSQ
## File description:
## Makefile
##

NAME	= bsq

SRC	= main.c \
	  utils.c \
	  file_parser.c \
	  board_generator.c \
	  bsq_algorithm.c

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
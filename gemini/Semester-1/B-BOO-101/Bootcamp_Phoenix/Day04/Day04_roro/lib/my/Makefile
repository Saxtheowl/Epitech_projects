##
## EPITECH PROJECT, 2025
## Day04_roro
## File description:
## Makefile
##

SRC = $(wildcard src/*.c)

OBJ = $(SRC:.c=.o)

NAME = libmy.a

CFLAGS = -I./include

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

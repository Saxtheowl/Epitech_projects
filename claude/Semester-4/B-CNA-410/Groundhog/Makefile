##
## EPITECH PROJECT, 2025
## Groundhog
## File description:
## Makefile for Groundhog weather analysis
##

NAME	= groundhog

SRC	=	src/main.c		\
		src/groundhog.c		\
		src/calculations.c	\
		src/utils.c

OBJ	= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -Werror -std=c99 -I include
LDFLAGS	= -lm

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
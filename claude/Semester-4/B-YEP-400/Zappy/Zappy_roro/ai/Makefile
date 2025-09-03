##
## EPITECH PROJECT, 2025
## Zappy AI
## File description:
## AI client Makefile
##

NAME	=	zappy_ai

SRC	=	src/main.c		\
		src/args.c		\
		src/network.c		\
		src/ai_logic.c		\
		src/ai_run.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -std=c99 -pedantic -I./include

CC	=	gcc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

tests_run:
	@echo "No tests implemented for AI client"

.PHONY: all clean fclean re tests_run
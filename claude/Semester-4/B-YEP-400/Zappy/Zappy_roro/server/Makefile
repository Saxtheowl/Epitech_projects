##
## EPITECH PROJECT, 2025
## Zappy Server
## File description:
## Server Makefile
##

NAME	=	zappy_server

SRC	=	src/main.c		\
		src/args.c		\
		src/server_init.c	\
		src/server_loop.c	\
		src/world.c		\
		src/commands.c		\
		src/command_queue.c	\
		src/player.c		\
		src/cleanup.c

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
	@echo "No tests implemented for server"

.PHONY: all clean fclean re tests_run
##
## EPITECH PROJECT, 2025
## Strace
## File description:
## System call tracer Makefile
##

NAME	=	strace

SRC	=	src/main.c		\
		src/args.c		\
		src/syscalls.c		\
		src/trace.c

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
	@echo "No tests implemented for strace"

.PHONY: all clean fclean re tests_run
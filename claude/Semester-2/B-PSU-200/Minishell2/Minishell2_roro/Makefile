##
## EPITECH PROJECT, 2024
## Minishell2
## File description:
## Makefile for enhanced minishell with pipes and redirections
##

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I./include
NAME = mysh

SRC_DIR = src
SRCFILES = main.c \
           environment.c \
           builtins.c \
           parser.c \
           execution.c \
           shell_loop.c \
           utils.c

SOURCES = $(addprefix $(SRC_DIR)/, $(SRCFILES))
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
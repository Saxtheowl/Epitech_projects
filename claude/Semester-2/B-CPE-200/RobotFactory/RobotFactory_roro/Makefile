##
## EPITECH PROJECT, 2025
## RobotFactory
## File description:
## Makefile for RobotFactory assembler
##

SOURCES = src/main.c \
          src/parser.c \
          src/assembler.c \
          src/bytecode.c \
          src/instructions.c \
          src/utils.c \
          src/header.c

OBJECTS = $(SOURCES:.c=.o)

NAME = asm

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude
LDFLAGS = 

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re debug
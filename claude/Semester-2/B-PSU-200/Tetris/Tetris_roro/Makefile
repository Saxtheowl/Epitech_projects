##
## EPITECH PROJECT, 2024
## Tetris
## File description:
## Makefile for ncurses-based Tetris game
##

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I./include
LDFLAGS = -lncurses
NAME = tetris

SRC_DIR = src
SRCFILES = main.c \
           config.c \
           tetrimino.c \
           game_state.c \
           movement.c \
           display.c \
           game_loop.c \
           utils.c

SOURCES = $(addprefix $(SRC_DIR)/, $(SRCFILES))
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
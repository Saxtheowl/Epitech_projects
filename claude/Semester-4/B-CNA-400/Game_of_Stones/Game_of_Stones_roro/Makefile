##
## EPITECH PROJECT, 2025
## Game of Stones
## File description:
## Makefile for Game of Stones project
##

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -I include
LDFLAGS = -lm

SRC_DIR = src
INCLUDE_DIR = include

SRCFILES = $(SRC_DIR)/main.c \
           $(SRC_DIR)/graph.c \
           $(SRC_DIR)/parser.c \
           $(SRC_DIR)/links.c \
           $(SRC_DIR)/plots.c \
           $(SRC_DIR)/conspiracy.c \
           $(SRC_DIR)/utils.c

OBJFILES = $(SRCFILES:.c=.o)

NAME = game_of_stones

all: $(NAME)

$(NAME): $(OBJFILES)
	$(CC) -o $(NAME) $(OBJFILES) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJFILES)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
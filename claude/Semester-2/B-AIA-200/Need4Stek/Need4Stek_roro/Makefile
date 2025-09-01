##
## EPITECH PROJECT, 2024
## Need4Stek
## File description:
## Makefile for autonomous car AI
##

NAME		= ai

SRC_DIR		= src/
INCLUDE_DIR	= include/

SRC		= $(SRC_DIR)main.c \
		  $(SRC_DIR)protocol.c \
		  $(SRC_DIR)lidar.c \
		  $(SRC_DIR)navigation.c \
		  $(SRC_DIR)controller.c \
		  $(SRC_DIR)utils.c

OBJ		= $(SRC:.c=.o)

CFLAGS		= -Wall -Wextra -I$(INCLUDE_DIR) -g
LDFLAGS		= -lm

CC		= gcc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
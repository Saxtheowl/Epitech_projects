##
## EPITECH PROJECT, 2024
## Corewar
## File description:
## Makefile for Corewar virtual machine
##

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -std=c99 -I./include

NAME	= corewar

SRC_DIR	= src

SRC		= $(SRC_DIR)/main.c \
		  $(SRC_DIR)/parser.c \
		  $(SRC_DIR)/champion.c \
		  $(SRC_DIR)/vm.c \
		  $(SRC_DIR)/process.c \
		  $(SRC_DIR)/instructions.c \
		  $(SRC_DIR)/operations.c \
		  $(SRC_DIR)/operations2.c \
		  $(SRC_DIR)/op.c

OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: $(NAME)
	@echo "Testing Corewar with provided champions..."
	./$(NAME) -dump 100 abel.cor bill.cor

.PHONY: all clean fclean re test
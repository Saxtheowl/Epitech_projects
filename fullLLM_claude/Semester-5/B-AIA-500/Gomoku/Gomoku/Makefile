##
## EPITECH PROJECT, 2024
## Gomoku AI
## File description:
## Makefile for Gomoku AI project
##

NAME		=	pbrain-gomoku-ai

SRC_DIR		=	src
INCLUDE_DIR	=	include

SOURCES		=	$(SRC_DIR)/main.c \
			$(SRC_DIR)/protocol.c \
			$(SRC_DIR)/board.c \
			$(SRC_DIR)/game_logic.c \
			$(SRC_DIR)/pattern_recognition.c \
			$(SRC_DIR)/minimax.c \
			$(SRC_DIR)/evaluation.c \
			$(SRC_DIR)/move_generation.c \
			$(SRC_DIR)/time_management.c

OBJECTS		=	$(SOURCES:.c=.o)

CC		=	gcc
CFLAGS		=	-Wall -Wextra -Werror -std=c99 -I$(INCLUDE_DIR) -O3
LDFLAGS		=

all:		$(NAME)

$(NAME):	$(OBJECTS)
		$(CC) $(OBJECTS) -o $(NAME) $(LDFLAGS)

%.o:		%.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJECTS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
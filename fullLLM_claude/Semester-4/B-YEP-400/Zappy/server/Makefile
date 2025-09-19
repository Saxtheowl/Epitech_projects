##
## EPITECH PROJECT, 2025
## Zappy Server
## File description:
## Server Makefile
##

NAME	=	zappy_server

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -Iinclude -std=c99

SRC_DIR	=	src
OBJ_DIR	=	obj

SRCS	=	$(SRC_DIR)/main.c \
		$(SRC_DIR)/args.c \
		$(SRC_DIR)/server.c \
		$(SRC_DIR)/network.c \
		$(SRC_DIR)/game_logic.c \
		$(SRC_DIR)/commands.c \
		$(SRC_DIR)/commands_ext.c \
		$(SRC_DIR)/gui_protocol.c

OBJS	=	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
##
## EPITECH PROJECT, 2025
## My_teams
## File description:
## Makefile
##

SERVER_NAME	= myteams_server
CLIENT_NAME	= myteams_cli

SRC_DIR		= src
INCLUDE_DIR	= include

SERVER_SRC	= $(SRC_DIR)/server.c \
		  $(SRC_DIR)/protocol.c \
		  $(SRC_DIR)/data.c \
		  $(SRC_DIR)/utils.c \
		  $(SRC_DIR)/commands.c

CLIENT_SRC	= $(SRC_DIR)/client.c \
		  $(SRC_DIR)/utils.c

SERVER_OBJ	= $(SERVER_SRC:.c=.o)
CLIENT_OBJ	= $(CLIENT_SRC:.c=.o)

CC		= gcc
CFLAGS		= -Wall -Wextra -I$(INCLUDE_DIR) -g
LDFLAGS		=

all: $(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME): $(SERVER_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(CLIENT_NAME): $(CLIENT_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ)

fclean: clean
	rm -f $(SERVER_NAME) $(CLIENT_NAME)

re: fclean all

tests_run:
	@echo "No tests implemented yet"

.PHONY: all clean fclean re tests_run
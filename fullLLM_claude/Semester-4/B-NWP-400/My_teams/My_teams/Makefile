##
## EPITECH PROJECT, 2025
## My_teams
## File description:
## Makefile for My_teams project
##

# Executables
SERVER_NAME = myteams_server
CLIENT_NAME = myteams_cli

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -std=gnu99
LDFLAGS =

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Server sources
SERVER_SRCS = $(SRC_DIR)/server/main.c \
              $(SRC_DIR)/server/server.c \
              $(SRC_DIR)/server/protocol.c \
              $(SRC_DIR)/server/commands.c \
              $(SRC_DIR)/server/team_commands.c \
              $(SRC_DIR)/server/persistence.c \
              $(SRC_DIR)/common/utils.c

# Client sources
CLIENT_SRCS = $(SRC_DIR)/client/main.c \
              $(SRC_DIR)/client/client.c \
              $(SRC_DIR)/common/utils.c

# Object files
SERVER_OBJS = $(SERVER_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CLIENT_OBJS = $(CLIENT_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default target
all: $(SERVER_NAME) $(CLIENT_NAME)

# Server target
$(SERVER_NAME): $(SERVER_OBJS)
	$(CC) $(SERVER_OBJS) -o $(SERVER_NAME) $(LDFLAGS)

# Client target
$(CLIENT_NAME): $(CLIENT_OBJS)
	$(CC) $(CLIENT_OBJS) -o $(CLIENT_NAME) $(LDFLAGS)

# Object files compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -rf $(OBJ_DIR)

# Clean everything
fclean: clean
	rm -f $(SERVER_NAME) $(CLIENT_NAME)
	rm -f myteams_data.dat

# Rebuild
re: fclean all

# Test targets
test_server: $(SERVER_NAME)
	./$(SERVER_NAME) 8080

test_client: $(CLIENT_NAME)
	./$(CLIENT_NAME) 127.0.0.1 8080

.PHONY: all clean fclean re test_server test_client
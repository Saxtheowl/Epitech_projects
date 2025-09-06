##
## EPITECH PROJECT, 2025
## ftrace
## File description:
## Makefile for ftrace project
##

NAME        = ftrace

SRC_DIR     = src
INC_DIR     = include
OBJ_DIR     = obj

SRCS        = $(SRC_DIR)/main.c \
              $(SRC_DIR)/ftrace.c \
              $(SRC_DIR)/ptrace_utils.c \
              $(SRC_DIR)/symbol_table.c \
              $(SRC_DIR)/syscall_table.c \
              $(SRC_DIR)/signal_handler.c

OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -std=c99
CPPFLAGS    = -I$(INC_DIR)
LDFLAGS     = 

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

tests_run:
	@echo "No tests implemented yet"

.PHONY: all clean fclean re tests_run
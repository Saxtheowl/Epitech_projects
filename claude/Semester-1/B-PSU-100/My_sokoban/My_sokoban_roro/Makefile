##
## EPITECH PROJECT, 2025
## my_sokoban
## File description:
## Makefile for sokoban game
##

NAME = my_sokoban

SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include
TESTS_DIR = tests

SOURCES = $(SRC_DIR)/main.c \
          $(SRC_DIR)/map.c \
          $(SRC_DIR)/game.c \
          $(SRC_DIR)/display.c \
          $(SRC_DIR)/utils.c

OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TEST_SOURCES = $(TESTS_DIR)/test_sokoban.c \
               $(SRC_DIR)/map.c \
               $(SRC_DIR)/game.c \
               $(SRC_DIR)/utils.c

TEST_NAME = tests_run

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=gnu99 -I$(INCLUDE_DIR) -D_GNU_SOURCE
LDFLAGS = -lncurses
TEST_LDFLAGS = -lcriterion --coverage

.PHONY: all clean fclean re tests_run

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

tests_run:
	$(CC) $(CFLAGS) $(TEST_SOURCES) -o $(TEST_NAME) $(TEST_LDFLAGS)
	./$(TEST_NAME)
	gcovr --exclude tests/

clean:
	rm -rf $(OBJ_DIR)
	rm -f *.gcno *.gcda

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)

re: fclean all

debug: CFLAGS += -g3 -DDEBUG
debug: re

install:
	sudo apt-get update
	sudo apt-get install -y libncurses5-dev libcriterion-dev gcovr

help:
	@echo "Available targets:"
	@echo "  all       - Build the program (default)"
	@echo "  clean     - Remove object files"
	@echo "  fclean    - Remove object files and binary"
	@echo "  re        - Rebuild everything"
	@echo "  tests_run - Run unit tests with coverage"
	@echo "  debug     - Build with debug symbols"
	@echo "  help      - Show this help"
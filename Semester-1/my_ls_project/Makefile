##
## EPITECH PROJECT, 2025
## MY_LS
## File description:
## Makefile for my_ls project
##
NAME    =   my_ls

SRC_DIR =   src
INC_DIR =   include

SRC     =   $(SRC_DIR)/main.c             $(SRC_DIR)/options.c             $(SRC_DIR)/utils_print.c             $(SRC_DIR)/utils_str.c             $(SRC_DIR)/permissions.c             $(SRC_DIR)/listing.c             $(SRC_DIR)/sort.c             $(SRC_DIR)/entry.c

OBJ     =   $(SRC:.c=.o)

CFLAGS  =   -Wall -Wextra -std=c99 -I$(INC_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

tests_run: all
	@echo "Running tests..."
	@python3 tests/tests_run.py

.PHONY: all clean fclean re tests_run

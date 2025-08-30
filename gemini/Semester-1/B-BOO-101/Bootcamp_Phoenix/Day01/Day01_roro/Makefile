##
## EPITECH PROJECT, 2025
## Day01_roro
## File description:
## Makefile
##

SRC = $(wildcard src/*.c)

OBJ = $(SRC:.c=.o)

NAME = my_project

CFLAGS = -I./include -I./lib/my/include -W -Wall -Wextra

LDFLAGS = -L./lib/my -lmy

TEST_SRC = $(wildcard tests/*.c)

TEST_NAME = unit_tests

all: $(NAME)

libmy:
	@make -C lib/my

$(NAME): libmy $(OBJ)
	@gcc $(OBJ) -o $(NAME) $(LDFLAGS)

tests_run: libmy
	@gcc -o $(TEST_NAME) $(SRC) $(TEST_SRC) -I./include -I./lib/my/include -L./lib/my -lmy --coverage -lcriterion
	@./$(TEST_NAME)

clean:
	@make clean -C lib/my
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C lib/my
	@rm -f $(NAME)
	@rm -f $(TEST_NAME)
	@rm -f *.gcda
	@rm -f *.gcno

re: fclean all

.PHONY: all clean fclean re libmy tests_run
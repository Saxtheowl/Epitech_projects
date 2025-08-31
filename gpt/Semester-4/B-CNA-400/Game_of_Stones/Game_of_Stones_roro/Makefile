##
## EPITECH PROJECT, 2025
## Game_of_Stones_roro
## File description:
## Makefile
##

NAME	=	game_of_stones

SRC_DIR	=	src
INC_DIR	=	include
TEST_DIR	=	tests

SRC	=	$(SRC_DIR)/main.c \
		$(SRC_DIR)/parse.c \
		$(SRC_DIR)/fr_cr.c \
		$(SRC_DIR)/graph.c \
		$(SRC_DIR)/links.c \
		$(SRC_DIR)/plots.c \
		$(SRC_DIR)/utils.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -I$(INC_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f unit_tests
	rm -f *.gcno *.gcda *.gcov

re: fclean all

unit_tests: CFLAGS += --coverage -I$(INC_DIR)
unit_tests: LDFLAGS += -lcriterion -lgcov
unit_tests: $(filter-out $(SRC_DIR)/main.c,$(SRC)) $(TEST_DIR)/test_parse.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

tests_run: unit_tests
	./unit_tests
	gcovr --exclude tests --branches --print-summary || true

.PHONY: all clean fclean re tests_run unit_tests

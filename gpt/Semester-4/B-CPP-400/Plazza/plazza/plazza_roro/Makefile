##
## EPITECH PROJECT, 2025
## Plazza_roro
## File description:
##   Build rules
##

NAME	=	plazza

SRC_DIR	=	src
INC_DIR	=	include
TEST_DIR	=	tests


SRC	=	$(SRC_DIR)/main.cpp \
	$(SRC_DIR)/parser.cpp \
	$(SRC_DIR)/args.cpp \
	$(SRC_DIR)/reception.cpp \
	$(SRC_DIR)/kitchen.cpp \
	$(SRC_DIR)/ipc.cpp \
	$(SRC_DIR)/rt.cpp

OBJ	=	$(SRC:.cpp=.o)

CXX	=	g++
CXXFLAGS	=	-Wall -Wextra -std=c++17 -I$(INC_DIR)
LDFLAGS	=	-pthread

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f unit_tests
	rm -f *.gcno *.gcda *.gcov

re: fclean all

unit_tests: CXXFLAGS += --coverage
unit_tests: LDFLAGS += -lcriterion
unit_tests:	$(OBJ) $(TEST_DIR)/test_basic.o
	$(CXX) -o $@ $(OBJ) $(TEST_DIR)/test_basic.o $(LDFLAGS)

tests_run: unit_tests
	./unit_tests

.PHONY: all clean fclean re tests_run

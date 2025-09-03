##
## EPITECH PROJECT, 2025
## Rtype_roro
## File description:
##   Build rules (C++)
##

NAME	=	rtype_roro

SRC_DIR	=	src
INC_DIR	=	include
TEST_DIR	=	tests

SRC	=	$(SRC_DIR)/main.cpp

OBJ	=	$(SRC:.cpp=.o)

CXX	=	g++
CXXFLAGS	=	-std=c++17 -Wall -Wextra -I$(INC_DIR)
LDFLAGS	=

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f unit_tests
	rm -f *.gcno *.gcda *.gcov

re: fclean all

unit_tests: CXXFLAGS += --coverage
unit_tests: LDFLAGS += -lcriterion
unit_tests:	$(TEST_DIR)/test_basic.o
	$(CXX) -o $@ $(TEST_DIR)/test_basic.o $(LDFLAGS)

tests_run: unit_tests
	./unit_tests

.PHONY: all clean fclean re tests_run


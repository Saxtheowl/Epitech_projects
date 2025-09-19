##
## EPITECH PROJECT, 2025
## NanoTekSpice
## File description:
## Makefile
##

NAME	=	nanotekspice

CXX		=	g++
CXXFLAGS =	-Wall -Wextra -Werror -std=c++17 -Iinclude

SRC_DIR	=	src
OBJ_DIR	=	obj

SRCS	=	$(SRC_DIR)/main.cpp \
		$(SRC_DIR)/components/AComponent.cpp \
		$(SRC_DIR)/components/basic/Input.cpp \
		$(SRC_DIR)/components/basic/Output.cpp \
		$(SRC_DIR)/components/basic/AndGate.cpp \
		$(SRC_DIR)/components/basic/OrGate.cpp \
		$(SRC_DIR)/components/basic/XorGate.cpp \
		$(SRC_DIR)/components/basic/NotGate.cpp \
		$(SRC_DIR)/components/basic/Clock.cpp \
		$(SRC_DIR)/components/basic/TrueComponent.cpp \
		$(SRC_DIR)/components/basic/FalseComponent.cpp \
		$(SRC_DIR)/components/chipsets/Chipset4081.cpp \
		$(SRC_DIR)/components/chipsets/Chipset4071.cpp \
		$(SRC_DIR)/core/ComponentFactory.cpp \
		$(SRC_DIR)/core/Parser.cpp \
		$(SRC_DIR)/core/Simulator.cpp

OBJS	=	$(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
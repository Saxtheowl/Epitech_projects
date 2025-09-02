##
## EPITECH PROJECT, 2025
## Plazza
## File description:
## Makefile
##

CXX		= g++

CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -I./include -pthread

SRCDIR	= src
INCDIR	= include
OBJDIR	= obj

SOURCES	= $(SRCDIR)/main.cpp \
		  $(SRCDIR)/Pizza.cpp \
		  $(SRCDIR)/ThreadPool.cpp \
		  $(SRCDIR)/IPC.cpp \
		  $(SRCDIR)/Kitchen.cpp \
		  $(SRCDIR)/Reception.cpp

OBJECTS	= $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

NAME	= plazza

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CXX) -o $(NAME) $(OBJECTS) $(CXXFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) -rf $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
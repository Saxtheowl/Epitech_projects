##
## EPITECH PROJECT, 2025
## Gomoku
## File description:
## Makefile for Gomoku AI
##

NAME        =   pbrain-gomoku-ai

SRCDIR      =   src
INCDIR      =   include
OBJDIR      =   obj
TESTDIR     =   tests

SRCS        =   $(SRCDIR)/main.cpp       \
                $(SRCDIR)/gomoku.cpp     \
                $(SRCDIR)/protocol.cpp

OBJS        =   $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

CPPFLAGS    =   -I$(INCDIR) -Wall -Wextra -std=c++17
LDFLAGS     =

CC          =   g++

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) -rf $(OBJDIR)
	$(RM) -f $(TESTDIR)/*.gcno $(TESTDIR)/*.gcda
	$(RM) -f *.gcno *.gcda

fclean: clean
	$(RM) $(NAME)
	$(RM) -f $(TESTDIR)/unit_tests

re: fclean all

tests_run:
	@mkdir -p $(TESTDIR)
	$(CC) $(CPPFLAGS) -o $(TESTDIR)/unit_tests \
		$(SRCDIR)/gomoku.cpp $(SRCDIR)/protocol.cpp $(TESTDIR)/test_gomoku.cpp
	./$(TESTDIR)/unit_tests

debug: CPPFLAGS += -g3 -DDEBUG
debug: re

.PHONY: all clean fclean re tests_run debug
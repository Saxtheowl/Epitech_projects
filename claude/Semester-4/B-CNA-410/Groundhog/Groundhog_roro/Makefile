##
## EPITECH PROJECT, 2025
## Groundhog
## File description:
## Makefile
##

NAME        = groundhog

SRCDIR      = src
INCDIR      = include
TESTDIR     = tests

SRC         = $(SRCDIR)/main.c             \
              $(SRCDIR)/args.c             \
              $(SRCDIR)/temperature_data.c \
              $(SRCDIR)/indicators.c       \
              $(SRCDIR)/switch_detection.c

OBJ         = $(SRC:.c=.o)

CFLAGS      = -Wall -Wextra -Werror -std=c99 -I$(INCDIR)
LDFLAGS     = -lm

CC          = gcc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(TESTDIR)/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

tests_run: all
	@echo "Running tests..."
	@if [ -f $(TESTDIR)/test_groundhog.c ]; then \
		$(CC) $(CFLAGS) -o test_groundhog $(TESTDIR)/test_groundhog.c \
		$(filter-out $(SRCDIR)/main.o, $(OBJ)) $(LDFLAGS) -lcriterion; \
		./test_groundhog; \
		rm -f test_groundhog; \
	else \
		echo "No tests found"; \
	fi

.PHONY: all clean fclean re tests_run
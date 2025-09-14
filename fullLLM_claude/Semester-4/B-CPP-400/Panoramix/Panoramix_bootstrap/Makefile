##
## EPITECH PROJECT, 2025
## Panoramix Bootstrap
## File description:
## Makefile for concurrent train simulation
##

CC = gcc

CFLAGS = -Wall -Wextra -Werror -lpthread

STEP1_NAME = step1

STEP2_NAME = step2

STEP1_SRC = step1.c

STEP2_SRC = step2.c

STEP1_OBJ = $(STEP1_SRC:.c=.o)

STEP2_OBJ = $(STEP2_SRC:.c=.o)

all: $(STEP1_NAME)

$(STEP1_NAME): $(STEP1_OBJ)
	$(CC) -o $(STEP1_NAME) $(STEP1_OBJ) $(CFLAGS)

$(STEP2_NAME): $(STEP2_OBJ)
	$(CC) -o $(STEP2_NAME) $(STEP2_OBJ) $(CFLAGS)

step1: $(STEP1_NAME)

step2: $(STEP2_NAME)

clean:
	rm -f $(STEP1_OBJ) $(STEP2_OBJ)

fclean: clean
	rm -f $(STEP1_NAME) $(STEP2_NAME)

re: fclean all

.PHONY: all step1 step2 clean fclean re
##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile for Organized workshop management project
##

CC = gcc
CFLAGS = -Wall -Wextra -I./include

SRC_FILES = src/main.c \
           src/utils.c \
           src/material.c \
           src/workshop.c \
           src/print.c \
           src/parsing.c \
           src/sorting.c \
           src/commands.c

OBJ_FILES = $(SRC_FILES:.c=.o)

NAME = organized

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) -o $(NAME) $(OBJ_FILES) -L. -lshell

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

tests_run: $(NAME)
	@echo "add WIRE usb" | ./$(NAME)
	@echo ""
	@echo "add WIRE usb, ACTUATOR button, DEVICE recorder" | ./$(NAME)
	@echo ""
	@echo "add WIRE usb, ACTUATOR button, DEVICE recorder" > test_input && \
	echo "disp" >> test_input && \
	echo "sort NAME" >> test_input && \
	echo "disp" >> test_input && \
	echo "exit" >> test_input && \
	cat test_input | ./$(NAME) && \
	rm -f test_input

.PHONY: all clean fclean re tests_run
##
## EPITECH PROJECT, 2025
## MiniLibC
## File description:
## Makefile for x86_64 ASM library
##

NAME = libasm.so

SRC = libasm.s

OBJ = $(SRC:.s=.o)

AS = as
AS_FLAGS = --64

all: $(NAME)

$(NAME): $(OBJ)
	ld -shared -o $(NAME) $(OBJ)

%.o: %.s
	$(AS) $(AS_FLAGS) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
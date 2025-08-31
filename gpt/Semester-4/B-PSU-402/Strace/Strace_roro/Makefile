##
## EPITECH PROJECT, 2025
## Strace_roro
## File description:
## Makefile
##

NAME	=	strace

SRC_DIR	=	src
INC_DIR	=	include

SRC	=	$(SRC_DIR)/main.c \
		$(SRC_DIR)/args.c \
		$(SRC_DIR)/tracer.c \
		$(SRC_DIR)/arch_x86_64.c \
		$(SRC_DIR)/mem.c \
		$(SRC_DIR)/format.c \
		$(SRC_DIR)/syscalls.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -I$(INC_DIR)
LDFLAGS	=

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


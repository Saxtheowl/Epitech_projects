##
## EPITECH PROJECT, 2025
## MiniLibC
## File description:
## Makefile
##

NAME		= libasm.so

SRC_DIR		= src
TEST_DIR	= tests
OBJ_DIR		= obj

SRC_FILES	= strlen.s \
		  strchr.s \
		  memset.s \
		  memcpy.s \
		  strcmp.s \
		  memmove.s \
		  strncmp.s \
		  strcasecmp.s \
		  rindex.s \
		  strstr.s \
		  strpbrk.s \
		  strcspn.s

SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.s=.o))

ASM		= as
ASMFLAGS	= --64
LD		= ld
LDFLAGS		= -shared

CC		= gcc
CFLAGS		= -Wall -Wextra -fPIC
TEST_LDFLAGS	= -L. -lasm

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s | $(OBJ_DIR)
	$(ASM) $(ASMFLAGS) $< -o $@

$(NAME): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

tests_run: $(NAME)
	$(CC) $(CFLAGS) $(TEST_DIR)/test_minilib.c -o test_minilib $(TEST_LDFLAGS)
	LD_LIBRARY_PATH=. ./test_minilib

.PHONY: all clean fclean re tests_run
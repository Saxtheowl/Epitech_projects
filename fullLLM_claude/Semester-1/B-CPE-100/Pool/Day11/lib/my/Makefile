##
## EPITECH PROJECT, 2024
## Day11 - libmy Makefile
## File description:
## Makefile for libmy library
##

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar
RANLIB = ranlib

SRC = ../../delivery/my_params_to_list.c \
      ../../delivery/my_list_size.c \
      ../../delivery/my_rev_list.c \
      ../../delivery/my_apply_on_nodes.c \
      ../../delivery/my_apply_on_matching_nodes.c \
      ../../delivery/my_find_node.c \
      ../../delivery/my_delete_nodes.c \
      ../../delivery/my_concat_list.c \
      ../../delivery/my_sort_list.c \
      ../../delivery/my_add_in_sorted_list.c \
      ../../delivery/my_merge.c

OBJ = $(SRC:.c=.o)

NAME = libmy.a

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) rc $(NAME) $(OBJ)
	$(RANLIB) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I../../include/ -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
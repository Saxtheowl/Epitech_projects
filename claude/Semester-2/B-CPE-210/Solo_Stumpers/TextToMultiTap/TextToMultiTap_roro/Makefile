##
## EPITECH PROJECT, 2025
## TextToMultiTap
## File description:
## Makefile for text_to_multi_tap project
##

NAME	= text_to_multi_tap

SRCDIR	= src
INCDIR	= include

SRCFILES = main.c \
           converter.c \
           utils.c \
           char_utils.c

SRC	= $(addprefix $(SRCDIR)/, $(SRCFILES))
OBJ	= $(SRC:.c=.o)
CFLAGS	= -Wall -Wextra -I$(INCDIR)

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
##
## EPITECH PROJECT, 2024
## my_top
## File description:
## Makefile
##

NAME	= my_top

SRC	= main.c \
	  system_info.c \
	  process_info.c \
	  display.c \
	  input.c \
	  args.c

OBJ	= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -Werror
LDFLAGS	= -lncurses

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
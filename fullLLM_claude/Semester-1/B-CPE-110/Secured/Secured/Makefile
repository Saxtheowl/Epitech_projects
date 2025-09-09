##
## EPITECH PROJECT, 2024
## Secured
## File description:
## Makefile
##

NAME	= libhashtable.a

SRC	= hash.c \
	  hashtable.c \
	  ht_operations.c

OBJ	= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
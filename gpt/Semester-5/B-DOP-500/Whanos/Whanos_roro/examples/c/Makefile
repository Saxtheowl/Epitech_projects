##
## EPITECH PROJECT, 2025
## Whanos_roro example C
## File description:
##   Simple C app Makefile
##

NAME	=	compiled-app
SRC	=	main.c

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(NAME)

fclean: clean
	@true

re: fclean all

.PHONY: all clean fclean re


##
## EPITECH PROJECT, 2025
## Rush 1
## File description:
## Makefile for pushswap_checker
##

NAME = pushswap_checker

SRC = Main.hs

all: $(NAME)

$(NAME): $(SRC)
	ghc -o $(NAME) $(SRC)

clean:
	rm -f *.hi *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
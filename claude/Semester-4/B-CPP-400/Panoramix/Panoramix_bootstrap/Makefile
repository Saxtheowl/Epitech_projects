##
## EPITECH PROJECT, 2025
## Panoramix Bootstrap
## File description:
## Makefile for Panoramix Bootstrap
##

NAME	= panoramix_bootstrap

SRC	=	src/main.cpp		\
		src/train.cpp

OBJ	= $(SRC:.cpp=.o)

CPPFLAGS = -Wall -Wextra -Werror -std=c++17 -I include
LDFLAGS = -lpthread

all: $(NAME)

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
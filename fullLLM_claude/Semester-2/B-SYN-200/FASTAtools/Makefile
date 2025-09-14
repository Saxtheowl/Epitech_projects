##
## EPITECH PROJECT, 2024
## FASTAtools
## File description:
## Makefile for FASTAtools project
##

NAME = FASTAtools

SRC = main.c \
      fasta_parser.c \
      dna_processing.c \
      analysis.c \
      processor.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
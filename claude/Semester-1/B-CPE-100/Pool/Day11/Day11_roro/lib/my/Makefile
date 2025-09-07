##
## EPITECH PROJECT, 2024
## libmy
## File description:
## Makefile for libmy
##

SRC	=	my_putchar.c		\
		my_isneg.c		\
		my_put_nbr.c		\
		my_swap.c		\
		my_putstr.c		\
		my_strlen.c		\
		my_compute_power_rec.c	\
		my_compute_square_root.c\
		my_is_prime.c		\
		my_find_prime_sup.c	\
		my_strcat.c		\
		my_show_word_array.c	\
		my_str_to_word_array.c	\
		my_strcmp.c

OBJ	=	$(SRC:.c=.o)

NAME	=	libmy.a

CFLAGS	=	-Wall -Wextra -Werror -std=gnu99

all:	$(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	cp $(NAME) ../

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)
	rm -f ../$(NAME)

re:	fclean all

.PHONY:	all clean fclean re
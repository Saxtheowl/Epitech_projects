##
## EPITECH PROJECT, 2024
## Day07 - B-CPE-100
## File description:
## Makefile for libmy.a
##

NAME	= libmy.a

SRC	= my_putchar.c		\
	  my_putstr.c		\
	  my_strlen.c		\
	  my_putnbr.c		\
	  my_getnbr.c		\
	  my_strcpy.c		\
	  my_strncpy.c		\
	  my_revstr.c		\
	  my_strstr.c		\
	  my_strcmp.c		\
	  my_strncmp.c		\
	  my_strupcase.c	\
	  my_strlowcase.c	\
	  my_strcapitalize.c	\
	  my_str_isalpha.c	\
	  my_str_isnum.c	\
	  my_str_islower.c	\
	  my_str_isupper.c	\
	  my_str_isprintable.c	\
	  my_showstr.c		\
	  my_showmem.c		\
	  my_strcat.c		\
	  my_strncat.c		\
	  my_putnbr_base.c	\
	  my_getnbr_base.c	\
	  my_put_nbr.c		\
	  my_compute_power_rec.c	\
	  my_compute_factorial_rec.c	\
	  my_compute_square_root.c	\
	  my_is_prime.c

OBJ	= $(SRC:.c=.o)

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror -I.

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
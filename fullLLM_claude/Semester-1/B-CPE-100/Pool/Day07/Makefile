##
## EPITECH PROJECT, 2024
## Day07 - B-CPE-100
## File description:
## Makefile
##

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror -Ilib/my

LIBPATH	= lib/my/

LIB	= -Llib/my -lmy

all: libmy my_params my_rev_params my_sort_params

libmy:
	$(MAKE) -C $(LIBPATH)

my_params: my_params.c libmy
	$(CC) $(CFLAGS) -o my_params my_params.c $(LIB)

my_rev_params: my_rev_params.c libmy
	$(CC) $(CFLAGS) -o my_rev_params my_rev_params.c $(LIB)

my_sort_params: my_sort_params.c libmy
	$(CC) $(CFLAGS) -o my_sort_params my_sort_params.c $(LIB)

clean:
	$(MAKE) -C $(LIBPATH) clean
	rm -f *.o

fclean: clean
	$(MAKE) -C $(LIBPATH) fclean
	rm -f my_params my_rev_params my_sort_params

re: fclean all

.PHONY: all libmy clean fclean re
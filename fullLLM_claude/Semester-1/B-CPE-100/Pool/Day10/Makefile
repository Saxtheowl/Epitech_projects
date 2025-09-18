##
## EPITECH PROJECT, 2024
## Day10 - Main Makefile
## File description:
## Main Makefile for all Day10 tasks
##

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: libmy do_op my_advanced_do_op

libmy:
	@$(MAKE) -C lib/my/

do_op:
	@$(MAKE) -C do_op/

my_advanced_do_op: libmy operations.o my_advanced_do_op.o
	$(CC) $(CFLAGS) -o my_advanced_do_op operations.o my_advanced_do_op.o -Llib/ -lmy

operations.o: operations.c
	$(CC) $(CFLAGS) -Iinclude/ -c operations.c

my_advanced_do_op.o: my_advanced_do_op.c
	$(CC) $(CFLAGS) -Iinclude/ -c my_advanced_do_op.c

clean:
	@$(MAKE) -C lib/my/ clean
	@$(MAKE) -C do_op/ clean
	rm -f *.o

fclean:
	@$(MAKE) -C lib/my/ fclean
	@$(MAKE) -C do_op/ fclean
	rm -f *.o my_advanced_do_op

re: fclean all

.PHONY: all clean fclean re libmy do_op
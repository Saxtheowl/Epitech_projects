##
## EPITECH PROJECT, 2024
## Day10
## File description:
## Main Makefile for Day10
##

all:
	$(MAKE) -C lib/my
	$(MAKE) -C do_op
	$(MAKE) -C my_advanced_do_op

clean:
	$(MAKE) -C lib/my clean
	$(MAKE) -C do_op clean
	$(MAKE) -C my_advanced_do_op clean

fclean: clean
	$(MAKE) -C lib/my fclean
	$(MAKE) -C do_op fclean
	$(MAKE) -C my_advanced_do_op fclean

re: fclean all

.PHONY: all clean fclean re
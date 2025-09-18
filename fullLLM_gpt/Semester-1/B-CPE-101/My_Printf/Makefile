.PHONY: all clean fclean re test

all:
	$(MAKE) -C mini_printf
	$(MAKE) -C my_printf

clean:
	$(MAKE) -C mini_printf clean
	$(MAKE) -C my_printf clean

fclean:
	$(MAKE) -C mini_printf fclean
	$(MAKE) -C my_printf fclean

re: fclean all

test:
	$(MAKE) -C mini_printf test
	$(MAKE) -C my_printf test


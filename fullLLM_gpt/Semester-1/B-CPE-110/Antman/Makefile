.PHONY: all clean fclean re test

all:
	$(MAKE) -C antman
	$(MAKE) -C giantman

clean:
	$(MAKE) -C antman clean
	$(MAKE) -C giantman clean

fclean:
	$(MAKE) -C antman fclean
	$(MAKE) -C giantman fclean

re: fclean all

test:
	$(MAKE) -C antman test
	$(MAKE) -C giantman test

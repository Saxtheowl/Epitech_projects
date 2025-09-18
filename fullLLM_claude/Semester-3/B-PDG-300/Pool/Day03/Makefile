HSFILES = Game.hs Tree.hs

all: $(HSFILES)
	ghc --make $(HSFILES)

clean:
	rm -f *.hi *.o

fclean: clean
	rm -f Game Tree

re: fclean all

.PHONY: all clean fclean re
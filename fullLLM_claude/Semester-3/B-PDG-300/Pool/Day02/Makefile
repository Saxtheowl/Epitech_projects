NAME = doop

all: $(NAME)

$(NAME): DoOp.hs
	ghc -o $(NAME) DoOp.hs

clean:
	rm -f *.hi *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
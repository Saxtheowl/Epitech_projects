##
## EPITECH PROJECT, 2025
## pushswap_checker
## File description:
## Makefile for pushswap_checker in Haskell
##

NAME        = pushswap_checker

SRCDIR      = src
SOURCES     = $(SRCDIR)/Main.hs \
              $(SRCDIR)/PushSwap.hs \
              $(SRCDIR)/Operations.hs \
              $(SRCDIR)/Parser.hs

GHC         = ghc
GHCFLAGS    = -Wall -Wextra -O2 -outputdir build

all: $(NAME)

$(NAME): $(SOURCES)
	mkdir -p build
	$(GHC) $(GHCFLAGS) $(SRCDIR)/Main.hs -o $(NAME)

clean:
	$(RM) -rf build

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
##
## EPITECH PROJECT, 2024
## Wolfram
## File description:
## Makefile for Wolfram Elementary Cellular Automaton
##

NAME = wolfram
SRC_DIR = src
APP_DIR = app
SOURCES = $(SRC_DIR)/Wolfram.hs $(APP_DIR)/Main.hs

all: $(NAME)

$(NAME): $(SOURCES)
	@if command -v stack >/dev/null 2>&1; then \
		echo "Building with Stack..."; \
		stack build && stack install --local-bin-path .; \
	elif command -v ghc >/dev/null 2>&1; then \
		echo "Building with GHC..."; \
		ghc -O2 -i$(SRC_DIR) -o $(NAME) $(APP_DIR)/Main.hs; \
	else \
		echo "Error: Neither Stack nor GHC found. Please install Haskell toolchain."; \
		exit 1; \
	fi

clean:
	@if command -v stack >/dev/null 2>&1; then \
		stack clean; \
	fi
	rm -f $(APP_DIR)/*.hi $(APP_DIR)/*.o $(SRC_DIR)/*.hi $(SRC_DIR)/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
##
## EPITECH PROJECT, 2025
## Wolfram_roro
## File description:
## Makefile
##

NAME=	wolfram

all:
	stack build --quiet
	cp $$(stack path --local-install-root)/bin/$(NAME) $(NAME)

clean:
	stack clean --quiet || true
	rm -f $(NAME)

fclean: clean
	rm -rf .stack-work

re: fclean all

tests_run:
	@echo "No tests for this project" && true

.PHONY: all clean fclean re tests_run

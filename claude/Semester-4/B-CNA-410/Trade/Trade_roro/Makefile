##
## EPITECH PROJECT, 2025
## Trade
## File description:
## Makefile
##

NAME		= trade

SRC_DIR		= src
SRC_FILE	= trade.py

all: $(NAME)

$(NAME):
	cp $(SRC_DIR)/$(SRC_FILE) $(NAME)
	chmod +x $(NAME)

clean:
	find . -name "*.pyc" -delete
	find . -name "__pycache__" -delete

fclean: clean
	rm -f $(NAME)

re: fclean all

tests_run:
	python3 -m pytest tests/ -v

.PHONY: all clean fclean re tests_run
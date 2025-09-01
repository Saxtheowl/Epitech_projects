##
## EPITECH PROJECT, 2025
## FASTAtools
## File description:
## Makefile for FASTAtools project
##

SOURCES = main.c \
          parser.c \
          utils.c \
          processors.c \
          kmers.c \
          coding_sequences.c \
          requirement.c

OBJECTS = $(SOURCES:.c=.o)

NAME = FASTAtools

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = 

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: CFLAGS += -g
debug: re

test: $(NAME)
	@echo "Testing FASTAtools..."
	@echo "Test 1: Help"
	@./$(NAME) -h
	@echo "\nTest 2: Create test FASTA file"
	@echo ">seq1" > test.fasta
	@echo "ATATGCAGAGTTAGT" >> test.fasta
	@echo ">seq2" >> test.fasta
	@echo "catCATGCC TADGACGAA" >> test.fasta
	@echo "GAGATGCTTTGAATGGRAATGAA" >> test.fasta
	@echo "\nTest 3: DNA output"
	@./$(NAME) 1 < test.fasta
	@echo "\nTest 4: RNA output"
	@./$(NAME) 2 < test.fasta
	@echo "\nTest 5: Reverse complement"
	@./$(NAME) 3 < test.fasta
	@rm -f test.fasta

.PHONY: all clean fclean re debug test
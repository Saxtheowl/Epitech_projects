##
## EPITECH PROJECT, 2025
## My_ftp
## File description:
## Makefile for FTP server
##

CC		= gcc
CFLAGS	= -Wall -Wextra -std=c99
NAME	= myftp

SRCDIR	= src
INCDIR	= include

SOURCES	= $(SRCDIR)/main.c \
		  $(SRCDIR)/server.c \
		  $(SRCDIR)/client.c \
		  $(SRCDIR)/commands.c \
		  $(SRCDIR)/utils.c

OBJECTS	= $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
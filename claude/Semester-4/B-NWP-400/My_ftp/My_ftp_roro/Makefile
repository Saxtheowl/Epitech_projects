##
## EPITECH PROJECT, 2025
## My_ftp
## File description:
## Makefile for My_ftp project
##

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -I include
LDFLAGS =

SRC_DIR = src
INCLUDE_DIR = include

SRCFILES = $(SRC_DIR)/main.c \
           $(SRC_DIR)/server.c \
           $(SRC_DIR)/client.c \
           $(SRC_DIR)/commands.c \
           $(SRC_DIR)/ftp_commands.c \
           $(SRC_DIR)/utils.c

OBJFILES = $(SRCFILES:.c=.o)

NAME = myftp

all: $(NAME)

$(NAME): $(OBJFILES)
	$(CC) -o $(NAME) $(OBJFILES) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJFILES)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
##
## EPITECH PROJECT, 2024
## Navy's Bootstrap
## File description:
## Makefile for signal handling programs
##

CC = gcc
CFLAGS = -Wall -Wextra -Werror

PROGRAMS = process_info kill_it who_sig_me signal_me

all: $(PROGRAMS)

process_info: process_info.c
	$(CC) $(CFLAGS) -o $@ $<

kill_it: kill_it.c
	$(CC) $(CFLAGS) -o $@ $<

who_sig_me: who_sig_me.c
	$(CC) $(CFLAGS) -o $@ $<

signal_me: signal_me.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(PROGRAMS)

re: fclean all

.PHONY: all clean fclean re
##
## EPITECH PROJECT, 2025
## NmObjdump
## File description:
## Makefile
##

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -std=c99 -I./include

SRCDIR	= src
INCDIR	= include
OBJDIR	= obj

NM_SOURCES = $(SRCDIR)/my_nm.c \
			 $(SRCDIR)/nm.c \
			 $(SRCDIR)/elf_loader.c \
			 $(SRCDIR)/utils.c

OBJDUMP_SOURCES = $(SRCDIR)/my_objdump.c \
				  $(SRCDIR)/objdump.c \
				  $(SRCDIR)/elf_loader.c \
				  $(SRCDIR)/utils.c

NM_OBJECTS = $(NM_SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJDUMP_OBJECTS = $(OBJDUMP_SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

NM_NAME		= my_nm
OBJDUMP_NAME = my_objdump

.PHONY: all nm objdump clean fclean re

all: nm objdump

nm: $(NM_NAME)

objdump: $(OBJDUMP_NAME)

$(NM_NAME): $(NM_OBJECTS)
	$(CC) -o $(NM_NAME) $(NM_OBJECTS)

$(OBJDUMP_NAME): $(OBJDUMP_OBJECTS)
	$(CC) -o $(OBJDUMP_NAME) $(OBJDUMP_OBJECTS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -rf $(OBJDIR)

fclean: clean
	$(RM) $(NM_NAME) $(OBJDUMP_NAME)

re: fclean all
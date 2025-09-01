##
## EPITECH PROJECT, 2025
## .
## File description:
## Generated Makefile
##

# Project configuration
PROJECT_DIR = .
SOURCES_DIR = .
HEADERS_DIR = include
LIBS_DIR = librarys
BCK_DIR = backup

# Compilation
CC = gcc
CFLAGS = -ftest-coverage -O2
LDFLAGS = 

# Archive tools
ZIP = tar
ZIPFLAGS = -cvvf
UNZIP = tar
UNZIPFLAGS = -xzf

# Binary name
NAME = fakeProj

# Sources and objects
SRCS = \
	$(SOURCES_DIR)/main.c \
	$(SOURCES_DIR)/calc.c

OBJS = $(SRCS:.c=.o)

# Include directories
INCLUDES = -I$(HEADERS_DIR)

# Library directories
LIBDIRS = -L$(LIBS_DIR)

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) $(LIBDIRS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Version management
archive:
	@if [ ! -d "$(BCK_DIR)" ]; then mkdir -p "$(BCK_DIR)"; fi
	@version=$$(ls $(BCK_DIR)/*.tar.gz 2>/dev/null | wc -l); \
	version=$$((version + 1)); \
	archive_name="$(BCK_DIR)/backup_v$$version.tar.gz"; \
	$(ZIP) $(ZIPFLAGS) $$archive_name $(SRCS); \
	echo "$$(basename $$archive_name) file generated."

revert:
	@latest=$$(ls -t $(BCK_DIR)/*.tar.gz 2>/dev/null | head -1); \
	if [ -n "$$latest" ]; then \
		$(UNZIP) $(UNZIPFLAGS) $$latest; \
	else \
		echo "No backup found"; \
	fi

num:
	@version=$$(ls $(BCK_DIR)/*.tar.gz 2>/dev/null | wc -l); \
	echo "$$version"

delete:
	@latest=$$(ls -t $(BCK_DIR)/*.tar.gz 2>/dev/null | head -1); \
	if [ -n "$$latest" ]; then \
		rm -f $$latest; \
		echo "Latest backup deleted"; \
	else \
		echo "No backup to delete"; \
	fi

.PHONY: all clean fclean re archive revert num delete

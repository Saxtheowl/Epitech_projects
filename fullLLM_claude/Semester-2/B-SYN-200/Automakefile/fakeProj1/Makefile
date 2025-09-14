##
## EPITECH PROJECT, 2025
## fakeProj1
## File description:
## Generated Makefile by automakefile
##

NAME = fakeProj

SRC = calc.c main.c 

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -ftest-coverage -O2

LDFLAGS = 

SOURCES_DIR = .

HEADERS_DIR = include

LIBS_DIR = librarys

BCK_DIR = backup

ZIP = tar

ZIPFLAGS = -cvvf

UNZIP = tar

UNZIPFLAGS = -xzf

VERSION_FILE = $(BCK_DIR)/.version

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Version management rules
archive:
	@mkdir -p $(BCK_DIR)
	@if [ ! -f $(VERSION_FILE) ]; then echo "0" > $(VERSION_FILE); fi
	@VERSION=$$(($$(cat $(VERSION_FILE)) + 1)); \
	echo "$$VERSION" > $(VERSION_FILE); \
	ARCHIVE_NAME="$(NAME)_v$$VERSION.tgz"; \
	$(ZIP) $(ZIPFLAGS) $(BCK_DIR)/$$ARCHIVE_NAME $(SRC) $(HEADERS_DIR) Makefile; \
	echo "$$ARCHIVE_NAME file generated."

revert:
	@if [ ! -f $(VERSION_FILE) ]; then echo "No backup available"; exit 1; fi
	@VERSION=$$(cat $(VERSION_FILE)); \
	if [ "$$VERSION" = "0" ]; then echo "No backup available"; exit 1; fi; \
	ARCHIVE_NAME="$(NAME)_v$$VERSION.tgz"; \
	if [ -f $(BCK_DIR)/$$ARCHIVE_NAME ]; then \
		$(UNZIP) $(UNZIPFLAGS) $(BCK_DIR)/$$ARCHIVE_NAME; \
	else \
		echo "Backup file $$ARCHIVE_NAME not found"; \
		exit 1; \
	fi

num:
	@if [ ! -f $(VERSION_FILE) ]; then echo "0"; else cat $(VERSION_FILE); fi

delete:
	@if [ ! -f $(VERSION_FILE) ]; then echo "No backup to delete"; exit 1; fi
	@VERSION=$$(cat $(VERSION_FILE)); \
	if [ "$$VERSION" = "0" ]; then echo "No backup to delete"; exit 1; fi; \
	ARCHIVE_NAME="$(NAME)_v$$VERSION.tgz"; \
	rm -f $(BCK_DIR)/$$ARCHIVE_NAME; \
	VERSION=$$(($$VERSION - 1)); \
	echo "$$VERSION" > $(VERSION_FILE)

.PHONY: all clean fclean re archive revert num delete


main.o: $(SOURCES_DIR)/main.c $(HEADERS_DIR)/fakeProj.h
	$(CC) $(CFLAGS) -I$(HEADERS_DIR) -c $(SOURCES_DIR)/main.c -o main.o

calc.o: $(SOURCES_DIR)/calc.c $(HEADERS_DIR)/calc/calc.h $(HEADERS_DIR)/fakeProj.h
	$(CC) $(CFLAGS) -I$(HEADERS_DIR) -c $(SOURCES_DIR)/calc.c -o calc.o

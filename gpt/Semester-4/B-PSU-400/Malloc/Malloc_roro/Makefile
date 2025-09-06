##
## EPITECH PROJECT, 2025
## Malloc
## File description:
##   Build shared lib libmy_malloc.so
##

NAME	=	libmy_malloc.so

SRC_DIR	=	src
INC_DIR	=	include
TEST_DIR	=	tests
CRIT_DIR	=	lib/criterion
CRIT_VER	=	v2.4.2
CRIT_ARCH	=	linux-x86_64

SRC	=	\
	$(SRC_DIR)/malloc.c \
	$(SRC_DIR)/free.c \
	$(SRC_DIR)/realloc.c \
	$(SRC_DIR)/calloc.c \
	$(SRC_DIR)/arena.c \
	$(SRC_DIR)/utils.c

OBJ	=	$(SRC:.c=.o)
TOBJ	=	$(SRC:%.c=%.tests.o)

CFLAGS	=	-fPIC -Wall -Wextra -I$(INC_DIR)
LDFLAGS	=
SO_LDFLAGS	=	-shared

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(SO_LDFLAGS)

clean:
	rm -f $(OBJ) $(TOBJ)

fclean: clean
	rm -f $(NAME)
	rm -f unit_tests tester
	rm -f *.gcno *.gcda *.gcov

re: fclean all

unit_tests: TCFLAGS = -fPIC -Wall -Wextra -I$(INC_DIR) --coverage -I$(CRIT_DIR)/include
unit_tests: TLDFLAGS = --coverage -L$(CRIT_DIR)/lib -Wl,-rpath,$(CRIT_DIR)/lib -lcriterion -lpthread -lm
unit_tests: criterion $(TOBJ) $(TEST_DIR)/test_basic.o
	$(CC) -o $@ $(TOBJ) $(TEST_DIR)/test_basic.o $(TLDFLAGS)

tests_run: unit_tests
	LD_LIBRARY_PATH=$(CRIT_DIR)/lib ./unit_tests

tester: $(NAME)
	$(CC) -I$(INC_DIR) -L. -o tester $(TEST_DIR)/tester.c -lmy_malloc

.PHONY: all clean fclean re tests_run criterion

criterion:
	@mkdir -p $(CRIT_DIR)
	@if [ -f $(CRIT_DIR)/include/criterion/criterion.h ]; then exit 0; fi; \
	set -e; \
	echo "Fetching Criterion into $(CRIT_DIR) ..."; \
	tmp=$$(mktemp -d); \
	urls="\
	  https://github.com/Snaipe/Criterion/releases/download/v2.4.2/criterion-2.4.2-linux-x86_64.tar.xz \
	  https://github.com/Snaipe/Criterion/releases/download/v2.4.1/criterion-v2.4.1-linux-x86_64.tar.xz \
	  https://github.com/Snaipe/Criterion/releases/download/v2.4.1/criterion-v2.4.1-linux-x86_64.tar.bz2"; \
	dl_ok=0; \
	for u in $$urls; do \
	  echo "Trying $$u"; \
	  if command -v curl >/dev/null 2>&1; then curl -fL "$$u" -o "$$tmp/crit.tar" && dl_ok=1 && break; fi; \
	  if command -v wget >/dev/null 2>&1; then wget -qO "$$tmp/crit.tar" "$$u" && dl_ok=1 && break; fi; \
	done; \
	if [ $$dl_ok -ne 1 ]; then echo "Error: download failed; install Criterion manually" >&2; exit 1; fi; \
	tar -xf "$$tmp/crit.tar" -C "$$tmp"; \
	found=$$(find "$$tmp" -maxdepth 1 -type d -name 'criterion-*' | head -n1); \
	if [ -z "$$found" ]; then echo "Error: unpack failed" >&2; exit 1; fi; \
	mkdir -p $(CRIT_DIR); \
	cp -r "$$found"/* $(CRIT_DIR)/; \
	rm -rf "$$tmp"

# Tests object build rule
$(SRC_DIR)/%.tests.o: $(SRC_DIR)/%.c
	$(CC) $(TCFLAGS) -c $< -o $@

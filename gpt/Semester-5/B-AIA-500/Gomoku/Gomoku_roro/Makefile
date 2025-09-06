##
## EPITECH PROJECT, 2025
## Gomoku_roro
## File description:
##   Build rules
##

NAME	=	gomoku_roro

SRC_DIR	=	src
INC_DIR	=	include
TEST_DIR	=	tests

SRC	=	\
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/parser.c \
	$(SRC_DIR)/board.c \
	$(SRC_DIR)/ai.c \
	$(SRC_DIR)/utils.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -I$(INC_DIR)
LDFLAGS	=

# Criterion (for tests)
CRIT_DIR	=	lib/criterion
CRIT_VER	=	v2.4.2
CRIT_ARCH	=	linux-x86_64

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)
	ln -sf $(NAME) pbrain-gomoku-ai

clean:
	rm -f $(OBJ)
	rm -f $(TEST_DIR)/*.test.o

fclean: clean
	rm -f $(NAME)
	rm -f pbrain-gomoku-ai
	rm -f unit_tests
	rm -f *.gcno *.gcda *.gcov

re: fclean all

unit_tests: CFLAGS += --coverage -I$(CRIT_DIR)/include
unit_tests: LDFLAGS += --coverage -L$(CRIT_DIR)/lib -Wl,-rpath,$(CRIT_DIR)/lib -lcriterion -lpthread -lm
SRC_NO_MAIN	=	$(filter-out $(SRC_DIR)/main.c,$(SRC))
TESTS	=	$(wildcard $(TEST_DIR)/*.c)
TEST_OBJS	=	$(TESTS:.c=.o)
TEST_SRC_OBJS	=	$(patsubst $(SRC_DIR)/%.c,$(TEST_DIR)/%.test.o,$(SRC_NO_MAIN))
unit_tests: criterion $(TEST_OBJS) $(TEST_SRC_OBJS)
	$(CC) -o $@ $(TEST_OBJS) $(TEST_SRC_OBJS) $(LDFLAGS)

$(TEST_DIR)/%.test.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

tests_run: unit_tests
	LD_LIBRARY_PATH=$(CRIT_DIR)/lib ./unit_tests

.PHONY: criterion
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
.PHONY: all clean fclean re tests_run

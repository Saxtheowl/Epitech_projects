##
## EPITECH PROJECT, 2025
## NmObjdump_roro
## File description:
## Makefile
##

CC	=	cc
CFLAGS	=	-Wall -Wextra -Werror -Iinclude
LDFLAGS	=

NM_NAME	=	my_nm
OD_NAME	=	my_objdump

SRC_DIR	=	src
TEST_DIR	=	tests
CRIT_DIR	=	lib/criterion
CRIT_VER	=	v2.4.2
CRIT_ARCH	=	linux-x86_64

NM_SRC	=	$(SRC_DIR)/common.c \
		$(SRC_DIR)/nm_main.c \
		$(SRC_DIR)/nm_symbols.c

OD_SRC	=	$(SRC_DIR)/common.c \
		$(SRC_DIR)/objdump_main.c \
		$(SRC_DIR)/objdump_dump.c \
		$(SRC_DIR)/objdump_file.c

NM_OBJ	=	$(NM_SRC:.c=.o)
OD_OBJ	=	$(OD_SRC:.c=.o)

all: nm objdump

nm: $(NM_NAME)
objdump: $(OD_NAME)

$(NM_NAME): $(NM_OBJ)
	$(CC) -o $@ $(NM_OBJ) $(LDFLAGS)

$(OD_NAME): $(OD_OBJ)
	$(CC) -o $@ $(OD_OBJ) $(LDFLAGS)

clean:
	rm -f $(NM_OBJ) $(OD_OBJ)

fclean: clean
	rm -f $(NM_NAME) $(OD_NAME)

re: fclean all

unit_tests: CFLAGS += --coverage -I$(CRIT_DIR)/include
unit_tests: LDFLAGS += --coverage -L$(CRIT_DIR)/lib -Wl,-rpath,$(CRIT_DIR)/lib -lcriterion -lpthread -lm
unit_tests: criterion $(TEST_DIR)/test_basic.o
	$(CC) -o $@ $(TEST_DIR)/test_basic.o $(LDFLAGS)

tests_run: unit_tests
	LD_LIBRARY_PATH=$(CRIT_DIR)/lib ./unit_tests

.PHONY: all nm objdump clean fclean re tests_run criterion

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

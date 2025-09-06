##
## EPITECH PROJECT, 2025
## Rtype_roro
## File description:
##   Build rules (C++)
##

NAME	=	rtype_roro

SRC_DIR	=	src
INC_DIR	=	include
TEST_DIR	=	tests
CRIT_DIR	=	lib/criterion
CRIT_VER	=	v2.4.2
CRIT_ARCH	=	linux-x86_64

SRC	=	$(SRC_DIR)/main.cpp

OBJ	=	$(SRC:.cpp=.o)

CXX	=	g++
CXXFLAGS	=	-std=c++17 -Wall -Wextra -I$(INC_DIR)
LDFLAGS	=

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LDFLAGS)
	ln -sf $(NAME) r-type_server
	ln -sf $(NAME) r-type_client

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f r-type_server r-type_client
	rm -f unit_tests
	rm -f *.gcno *.gcda *.gcov

re: fclean all

unit_tests: CXXFLAGS += --coverage -I$(CRIT_DIR)/include
unit_tests: LDFLAGS += --coverage -L$(CRIT_DIR)/lib -Wl,-rpath,$(CRIT_DIR)/lib -lcriterion -lpthread -lm
unit_tests: criterion $(TEST_DIR)/test_basic.o
	$(CXX) -o $@ $(TEST_DIR)/test_basic.o $(LDFLAGS)

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

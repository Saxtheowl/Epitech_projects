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

unit_tests: CFLAGS += --coverage
unit_tests: LDFLAGS += -lcriterion
unit_tests:	$(TEST_DIR)/test_basic.o
	$(CC) -o $@ $(TEST_DIR)/test_basic.o $(LDFLAGS)

tests_run: unit_tests
	./unit_tests

.PHONY: all nm objdump clean fclean re tests_run

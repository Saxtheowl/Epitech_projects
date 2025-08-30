##
## EPITECH PROJECT, 2025
## Antman_roro
## File description:
## Makefile
##

BINARIES	=	antman giantman
SRC_DIR	=	src
INC_DIR	=	include

CFLAGS	=	-Wall -Wextra -Werror -I $(INC_DIR)
LDFLAGS	=

SRCS_COMMON	=	$(SRC_DIR)/common.c

SRCS_antman	=	$(SRCS_COMMON) $(SRC_DIR)/ant_main.c
SRCS_giantman	=	$(SRCS_COMMON) $(SRC_DIR)/giant_main.c

OBJS_antman	=	$(SRCS_antman:.c=.o)
OBJS_giantman	=	$(SRCS_giantman:.c=.o)

all:	$(BINARIES)

antman:	$(OBJS_antman)
	$(CC) $(OBJS_antman) -o $@ $(LDFLAGS)

giantman:	$(OBJS_giantman)
	$(CC) $(OBJS_giantman) -o $@ $(LDFLAGS)

clean:
	$(RM) $(OBJS_antman) $(OBJS_giantman) *.gcno *.gcda

fclean:	clean
	$(RM) $(BINARIES) unit_tests

re:	fclean all

TESTS_SRCS	=	tests/test_rle.c

tests_run:	CFLAGS+=" --coverage"
tests_run:	LDFLAGS+=" --coverage -lcriterion"
tests_run:	$(SRCS_COMMON) $(TESTS_SRCS)
	$(CC) $(CFLAGS) $(SRCS_COMMON) $(TESTS_SRCS) -o unit_tests $(LDFLAGS)
	./unit_tests

.PHONY:	all clean fclean re tests_run

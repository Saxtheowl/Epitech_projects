##
## EPITECH PROJECT, 2025
## Rush2_roro
## File description:
## Makefile
##

BINARIES	=	step01 step02 step03 step04

SRC_DIR	=	src
INC_DIR	=	include

CFLAGS	=	-Wall -Wextra -Werror -I $(INC_DIR)
LDFLAGS	=

SRCS_COMMON	=	$(SRC_DIR)/common.c

SRCS_step01	=	$(SRCS_COMMON) $(SRC_DIR)/step01.c
SRCS_step02	=	$(SRCS_COMMON) $(SRC_DIR)/step02.c
SRCS_step03	=	$(SRCS_COMMON) $(SRC_DIR)/step03.c
SRCS_step04	=	$(SRCS_COMMON) $(SRC_DIR)/step04.c

OBJS_step01	=	$(SRCS_step01:.c=.o)
OBJS_step02	=	$(SRCS_step02:.c=.o)
OBJS_step03	=	$(SRCS_step03:.c=.o)
OBJS_step04	=	$(SRCS_step04:.c=.o)

all:	$(BINARIES)

step01:	$(OBJS_step01)
	$(CC) $(OBJS_step01) -o $@ $(LDFLAGS)

step02:	$(OBJS_step02)
	$(CC) $(OBJS_step02) -o $@ $(LDFLAGS)

step03:	$(OBJS_step03)
	$(CC) $(OBJS_step03) -o $@ $(LDFLAGS)

step04:	$(OBJS_step04)
	$(CC) $(OBJS_step04) -o $@ $(LDFLAGS)

clean:
	$(RM) $(OBJS_step01) $(OBJS_step02) $(OBJS_step03) $(OBJS_step04) *.gcno *.gcda

fclean:	clean
	$(RM) $(BINARIES) unit_tests

re:	fclean all

TESTS_SRCS	=	tests/test_steps.c

tests_run:	CFLAGS+=" --coverage"
tests_run:	LDFLAGS+=" --coverage -lcriterion"
tests_run:	$(SRCS_COMMON) $(TESTS_SRCS)
	$(CC) $(CFLAGS) $(SRCS_COMMON) $(TESTS_SRCS) -o unit_tests $(LDFLAGS)
	./unit_tests

.PHONY:	all clean fclean re tests_run

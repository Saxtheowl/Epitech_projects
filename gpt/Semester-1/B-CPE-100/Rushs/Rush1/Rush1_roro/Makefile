##
## EPITECH PROJECT, 2025
## Rush1_roro
## File description:
## Makefile
##

BINARIES	=	rush1-1 rush1-2 rush1-3 rush1-4 rush1-5

SRC_DIR	=	src
INC_DIR	=	include

CFLAGS	=	-Wall -Wextra -Werror -I $(INC_DIR)
LDFLAGS	=

SRCS_COMMON	=	$(SRC_DIR)/draw.c $(SRC_DIR)/common.c

SRCS_rush1-1	=	$(SRCS_COMMON) $(SRC_DIR)/rush1_1.c
SRCS_rush1-2	=	$(SRCS_COMMON) $(SRC_DIR)/rush1_2.c
SRCS_rush1-3	=	$(SRCS_COMMON) $(SRC_DIR)/rush1_3.c
SRCS_rush1-4	=	$(SRCS_COMMON) $(SRC_DIR)/rush1_4.c
SRCS_rush1-5	=	$(SRCS_COMMON) $(SRC_DIR)/rush1_5.c

OBJS_rush1-1	=	$(SRCS_rush1-1:.c=.o)
OBJS_rush1-2	=	$(SRCS_rush1-2:.c=.o)
OBJS_rush1-3	=	$(SRCS_rush1-3:.c=.o)
OBJS_rush1-4	=	$(SRCS_rush1-4:.c=.o)
OBJS_rush1-5	=	$(SRCS_rush1-5:.c=.o)

all:	$(BINARIES)

rush1-1:	$(OBJS_rush1-1)
	$(CC) $(OBJS_rush1-1) -o $@ $(LDFLAGS)

rush1-2:	$(OBJS_rush1-2)
	$(CC) $(OBJS_rush1-2) -o $@ $(LDFLAGS)

rush1-3:	$(OBJS_rush1-3)
	$(CC) $(OBJS_rush1-3) -o $@ $(LDFLAGS)

rush1-4:	$(OBJS_rush1-4)
	$(CC) $(OBJS_rush1-4) -o $@ $(LDFLAGS)

rush1-5:	$(OBJS_rush1-5)
	$(CC) $(OBJS_rush1-5) -o $@ $(LDFLAGS)

clean:
	$(RM) $(OBJS_rush1-1) $(OBJS_rush1-2) $(OBJS_rush1-3) $(OBJS_rush1-4) $(OBJS_rush1-5) *.gcno *.gcda

fclean:	clean
	$(RM) $(BINARIES) unit_tests

re:	fclean all

TESTS_SRCS	=	tests/test_rush1.c

tests_run:	CFLAGS+=" --coverage"
tests_run:	LDFLAGS+=" --coverage -lcriterion"
tests_run:	$(SRCS_COMMON) $(TESTS_SRCS)
	$(CC) $(CFLAGS) $(SRCS_COMMON) $(TESTS_SRCS) -o unit_tests $(LDFLAGS)
	./unit_tests

.PHONY:	all clean fclean re tests_run

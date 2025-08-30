##
## EPITECH PROJECT, 2025
## WorkshopLib_roro
## File description:
## Makefile
##

NAME	=	libmy.a
SRC_DIR	=	src
INC_DIR	=	include

SRCS	=	$(SRC_DIR)/my_putchar.c \
			$(SRC_DIR)/my_putstr.c \
			$(SRC_DIR)/my_strlen.c \
			$(SRC_DIR)/my_strcmp.c \
			$(SRC_DIR)/my_strcpy.c

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -I $(INC_DIR)

all:	$(NAME)

$(NAME):	$(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS) *.gcno *.gcda

fclean:	clean
	$(RM) $(NAME) unit_tests

re:	fclean all

TESTS_SRCS	=	tests/test_my.c

tests_run:	CFLAGS+=" --coverage"
tests_run:	LDFLAGS+=" --coverage -lcriterion"
tests_run:	$(OBJS) $(TESTS_SRCS)
	$(CC) $(CFLAGS) $(OBJS) $(TESTS_SRCS) -o unit_tests $(LDFLAGS)
	./unit_tests

.PHONY:	all clean fclean re tests_run

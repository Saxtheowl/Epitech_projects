##
## EPITECH PROJECT, 2025
## My_teams_roro
## File description:
##   Build rules (server + client)
##

NAME_S	=	myteams_server
NAME_C	=	myteams_cli

SRC_DIR	=	src
INC_DIR	=	include
TEST_DIR	=	tests


SRC_S	=	$(SRC_DIR)/server.c \
	$(SRC_DIR)/server_loop.c \
	$(SRC_DIR)/server_cmds.c \
	$(SRC_DIR)/util.c \
	libs/myteams/logging_server.c

SRC_C	=	$(SRC_DIR)/client.c \
	$(SRC_DIR)/util.c \
	libs/myteams/logging_client.c

OBJ_S	=	$(SRC_S:.c=.o)
OBJ_C	=	$(SRC_C:.c=.o)

CFLAGS	=	-Wall -Wextra -I$(INC_DIR) -Ilibs/myteams
LDFLAGS	=

all: $(NAME_S) $(NAME_C)

$(NAME_S): $(OBJ_S)
	$(CC) -o $@ $(OBJ_S) $(LDFLAGS)

$(NAME_C): $(OBJ_C)
	$(CC) -o $@ $(OBJ_C) $(LDFLAGS)

clean:
	rm -f $(OBJ_S) $(OBJ_C)

fclean: clean
	rm -f $(NAME_S) $(NAME_C)
	rm -f unit_tests
	rm -f *.gcno *.gcda *.gcov

re: fclean all

unit_tests: CFLAGS += --coverage
unit_tests: LDFLAGS += -lcriterion
unit_tests:
	@echo "No unit tests provided" && true

tests_run: unit_tests
	@true

.PHONY: all clean fclean re tests_run

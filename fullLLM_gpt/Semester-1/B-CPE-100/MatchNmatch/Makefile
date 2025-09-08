NAME_MATCH	=	match
NAME_NMATCH	=	nmatch

SRC_MATCH	=	src/match.c
SRC_NMATCH	=	src/nmatch.c

OBJ_MATCH	=	$(SRC_MATCH:.c=.o)
OBJ_NMATCH	=	$(SRC_NMATCH:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -Iinclude

all: $(NAME_MATCH) $(NAME_NMATCH)

$(NAME_MATCH): $(OBJ_MATCH)
	$(CC) $(OBJ_MATCH) -o $(NAME_MATCH)

$(NAME_NMATCH): $(OBJ_NMATCH)
	$(CC) $(OBJ_NMATCH) -o $(NAME_NMATCH)

clean:
	$(RM) $(OBJ_MATCH) $(OBJ_NMATCH)

fclean: clean
	$(RM) $(NAME_MATCH) $(NAME_NMATCH)

re: fclean all

.PHONY: all clean fclean re test

test: all
	@tests/test.sh

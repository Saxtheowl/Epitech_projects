NAME		= my_popup

SRCDIR		= ./
SRCFILES	= my_popup.c

OBJFILES	= $(SRCFILES:.c=.o)

CFLAGS		+= -Wall -Wextra
LDFLAGS		+= -lncurses

all: $(NAME)

$(NAME): $(OBJFILES)
	@gcc -o $(NAME) $(OBJFILES) $(LDFLAGS)
	@echo "Built executable: $(NAME)"

%.o: %.c
	@gcc -c $< -o $@ $(CFLAGS)
	@echo "Compiled: $<"

clean:
	@rm -f $(OBJFILES)
	@echo "Cleaned object files"

fclean: clean
	@rm -f $(NAME)
	@echo "Cleaned executable"

re: fclean all

.PHONY: all clean fclean re
NAME		= ai

SRCDIR		= ./
SRCFILES	= main.c \
		  communication.c \
		  sensors.c \
		  ai_logic.c

OBJFILES	= $(SRCFILES:.c=.o)

CFLAGS		+= -Wall -Wextra
CFLAGS		+= -lm

all: $(NAME)

$(NAME): $(OBJFILES)
	@gcc -o $(NAME) $(OBJFILES) $(CFLAGS)
	@echo "Built executable: $(NAME)"

%.o: %.c
	@gcc -c $< -o $@ -Wall -Wextra
	@echo "Compiled: $<"

clean:
	@rm -f $(OBJFILES)
	@echo "Cleaned object files"

fclean: clean
	@rm -f $(NAME)
	@echo "Cleaned executable"

re: fclean all

.PHONY: all clean fclean re
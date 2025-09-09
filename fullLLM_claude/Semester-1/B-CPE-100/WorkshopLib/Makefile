LIBDIR = lib/my
INCDIR = include
SRCDIR = $(LIBDIR)

NAME = $(LIBDIR)/libmy.a

SRC = $(SRCDIR)/my_putchar.c \
      $(SRCDIR)/my_putstr.c \
      $(SRCDIR)/my_strlen.c \
      $(SRCDIR)/my_put_nbr.c \
      $(SRCDIR)/my_strcpy.c \
      $(SRCDIR)/my_strcmp.c \
      $(SRCDIR)/my_isneg.c \
      $(SRCDIR)/my_swap.c \
      $(SRCDIR)/my_getnbr.c \
      $(SRCDIR)/my_strcat.c \
      $(SRCDIR)/my_revstr.c \
      $(SRCDIR)/my_compute_power_rec.c \
      $(SRCDIR)/my_is_prime.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -I./$(INCDIR)

CC = gcc

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	@echo "libmy.a created successfully"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
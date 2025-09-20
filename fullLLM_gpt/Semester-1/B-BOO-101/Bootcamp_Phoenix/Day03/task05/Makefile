CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -std=c99 -I../../includes
LDFLAGS = -L../../lib/phoenix
LDLIBS  = -lphoenix
TARGET  = sorted_params
SRC     = sorted_params.c
OBJ     = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(MAKE) -C ../../lib/phoenix
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(OBJ)
	$(MAKE) -C ../../lib/phoenix clean

fclean: clean
	rm -f $(TARGET)
	$(MAKE) -C ../../lib/phoenix fclean

re: fclean all

.PHONY: all clean fclean re

CC      = gcc
AR      = ar
CFLAGS  = -Wall -Wextra -Werror -std=c99 -I../../includes
BUILD_DIR = build

SRC = \
    my_putchar.c \
    show_number.c \
    show_string.c \
    reverse_string.c \
    to_number.c \
    is_prime_number.c \
    my_strcpy.c \
    my_strncmp.c \
    my_strstr.c

VPATH = . ../../Day01 ../../Day02

OBJ = $(addprefix $(BUILD_DIR)/,$(notdir $(SRC:.c=.o)))

all: libphoenix.a

libphoenix.a: $(OBJ)
	$(AR) rcs $@ $(OBJ)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f libphoenix.a

re: fclean all

.PHONY: all clean fclean re

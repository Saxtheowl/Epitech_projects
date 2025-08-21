#!/bin/bash

# Build libmy.a library
echo "Building libmy.a..."

# Compile all .c files in lib/my/
gcc -c my_putchar.c -o my_putchar.o -I../../include
gcc -c my_putstr.c -o my_putstr.o -I../../include
gcc -c my_strlen.c -o my_strlen.o -I../../include
gcc -c my_putnbr.c -o my_putnbr.o -I../../include

# Create the library
ar rc libmy.a my_putchar.o my_putstr.o my_strlen.o my_putnbr.o
ranlib libmy.a

# Clean object files
rm -f *.o

echo "libmy.a created successfully!"
#!/bin/bash

gcc -c *.c -Wall -Wextra -I../../include/
ar rc libmy.a *.o
ranlib libmy.a
rm -f *.o
echo "libmy.a built successfully"
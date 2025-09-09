#!/bin/bash

gcc -c -fPIC *.c -I../../include
ar rc libmy.a *.o
ranlib libmy.a
rm -f *.o
echo "libmy.a built successfully"
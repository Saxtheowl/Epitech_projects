#!/bin/bash
ar rc libmy.a *.o
ranlib libmy.a
echo "libmy.a built successfully"
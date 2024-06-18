#!/bin/bash

# Compiler options
CC=gcc
CFLAGS="-g -z noexecstack"
ASFLAGS="-g -gstabs"

# Compile myAlloc-INCOMPLETO.s
$CC $CFLAGS -c -o myAlloc.o myAlloc-INCOMPLETO.s

# Compile main.c
$CC $CFLAGS -o main main.c myAlloc.o

./main 8192 10

# Clean up object files
rm -f myAlloc.o
rm -f main

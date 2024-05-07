CC=gcc
CFLAGS=-g -z noexecstack
ASFLAGS=-gstabs 

all: mandel

mandel: mandel.c mandel_ASM.o
	$(CC) $(CFLAGS) -o mandel mandel.c  mandel_ASM.o

mandel_ASM.o: mandel_ASM.s
	as $(ASFLAGS) -o mandel_ASM.o mandel_ASM.s

clean:
	rm -f *.o mandel *~




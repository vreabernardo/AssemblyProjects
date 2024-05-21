CC=gcc
CFLAGS=-g -z noexecstack 
ASFLAGS=-g -gstabs

main: main.c myAlloc.h myAlloc.o
	$(CC) $(CFLAGS) -o main main.c myAlloc.o

%.o: %.s
	as $(ASFLAGS) -o $@ $<

clean:
	rm -f *.o  main

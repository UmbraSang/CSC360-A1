CFLAGS=-Wall -Werror

all: kapish

kapish: kapish.o
	gcc $(CFLAGS) kapish.o -o kapish

kapish.o: kapish.c kapish.h
	gcc -c $(CFLAGS) kapish.c

clean:
	rm -rf *.o kapish
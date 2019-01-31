CFLAGS=-Wall -Werror

all: kapish

kapish: kapish.o DoublyLinkedList.o
	gcc $(CFLAGS) kapish.o DoublyLinkedList.o -o kapish 

kapish.o: kapish.c kapish.h
	gcc $(CFLAGS) -c kapish.c -I /Kapish/Kapish/DoublyLinkedList.h

DoublyLinkedList.o: DoublyLinkedList.c DoublyLinkedList.h
	gcc $(CFLAGS) -c DoublyLinkedList.c

clean:
	rm -rf *.o kapish
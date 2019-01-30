CFLAGS=-Wall -Werror

all: kapish

kapish: kapish.o DoublyLinkedList.o
	gcc $(CFLAGS) -o kapish kapish.o DoublyLinkedList.o

kapish.o: kapish.c kapish.h
	gcc $(CFLAGS) -c kapish.c -I /Kapish/Kapish/DoublyLinkedList.h

DoublyLinkedList.o: DoublyLinkedList.c DoublyLinkedList.h
	gcc $(CFLAGS) -c DoublyLinkedList.c

clean:
	rm -rf *.o kapish DoublyLinkedList
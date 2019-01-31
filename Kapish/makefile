CFLAGS=-Wall -Werror

all: kapish

kapish: kapish.o
	gcc $(CFLAGS) kapish.o -o kapish 

kapish.o: kapish.c kapish.h
	gcc $(CFLAGS) -c kapish.c

# DoublyLinkedList.o: DoublyLinkedList.c DoublyLinkedList.h
# 	gcc $(CFLAGS) -c DoublyLinkedList.c

clean:
	rm -rf *.o kapish
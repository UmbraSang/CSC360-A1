#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
	char* data;
	struct Node* next;
	struct Node* prev;
};

struct List {
	int length;
	struct Node* head;
	struct Node* tail;
};

//constructors
struct Node* makeNode(char* data);
struct List* makeList();
//adds
void add(int x, struct Node* newNode, struct List* nodeList);
void addLast(struct Node* newNode, struct List* nodeList);
void push(struct Node* newHead, struct List* nodeList);
//removes
char* removeNode(int index, struct List* nodeList);
char* pop(struct List* nodeList);
char* removeLast(struct List* nodeList);
//utility
int getLength(struct List* nodeList);
bool isEmpty(struct List* nodeList);
void printList(struct List* nodeList);
void printListRev(struct List* nodeList);
void surgery(struct List* nodeList);
//extra credit
void adjSwap(struct Node* a, struct Node* b, struct Node* p, struct Node* n);
void shiftLeft(struct List* list, int n);
void swap(struct List* nodeList, struct Node* ref1, struct Node* ref2);
struct List* reverse(struct List* nodeList);
struct List* concat(struct List* a, struct List* b);
void unique(struct List* nodeList);
int distance(struct Node* ref1, struct Node* ref2);
void rotateLeft(struct List* nodeList, int n);
bool includes(struct List* nodeList, struct Node* ref2);

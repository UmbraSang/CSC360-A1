#include "DoublyLinkedList.h"


/*
 * List
 *
 *  Created on: Jan 10, 2019
 *      Author: Connor
 */


void surgery(struct List* nodeList) {
	struct Node* curr = nodeList->head;
	while (curr->next != NULL) {
		if (curr->next->prev != curr) {
			curr->next->prev = curr;
		}
		curr = curr->next;
	}
}

int getLength(struct List* nodeList) {
	return nodeList->length;
}

bool isEmpty(struct List* nodeList) {
	if (getLength(nodeList)<=0) {
		return true;
	} else {
		return false;
	}
}

struct Node* makeNode(char* data) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

struct List* makeList() {
	struct List* nodeList = (struct List*)malloc(sizeof(struct List));
	nodeList->length = 0;
	nodeList->head = NULL;
	nodeList->tail = NULL;
	return nodeList;
}

void push(struct Node* newHead, struct List* nodeList) {
	if (isEmpty(nodeList)) {
		nodeList->head = newHead;
		nodeList->tail = newHead;
	}
	else {
		newHead->next = nodeList->head;
		nodeList->head->prev = newHead;
		nodeList->head = newHead;
	}
	nodeList->length++;
}

void addLast(struct Node* newNode, struct List* nodeList) {
	if (isEmpty(nodeList)) {
		nodeList->head = newNode;
		nodeList->tail = newNode;
	}
	else {
		nodeList->tail->next = newNode;
		newNode->prev = nodeList->tail;
		nodeList->tail = newNode;
	}
	nodeList->length++;
}

void add(int x, struct Node* newNode, struct List* nodeList) {
	if (x == 0) {
		push(newNode, nodeList);
	}
	else if (x >= nodeList->length) {
		addLast(newNode, nodeList);
	}
	else {
		struct Node* curr = nodeList->head;
		int i;
        for (i = 0; i < x; i++) {
			curr = curr->next;
		}
		struct Node* currPrev = curr->prev;
		currPrev->next = newNode;
		newNode->prev = currPrev;
		newNode->next = curr;
		curr->prev = newNode;

		nodeList->length++;
	}
}

char* pop(struct List* nodeList) {
	struct Node* oldHead = nodeList->head;
	if (getLength(nodeList) == 1) {
		nodeList->head = NULL;
		nodeList->tail = NULL;
	} else {
		nodeList->head = nodeList->head->next;
		nodeList->head->prev = NULL;
		oldHead->next = NULL;
	}
	nodeList->length--;
	char* data = oldHead->data;
	free(oldHead);
	return data;
}

char* removeLast(struct List* nodeList) {
	struct Node* oldTail = nodeList->tail;
	if (getLength(nodeList) == 1) {
		nodeList->head = NULL;
		nodeList->tail = NULL;
	}
	else {
		nodeList->tail = nodeList->tail->prev;
		nodeList->tail->next = NULL;
	}
	oldTail->prev = NULL;
	nodeList->length--;
	char* data = oldTail->data;
	free(oldTail);
	return data;
}

char* removeNode(int index, struct List* nodeList) {
	if (index == 0) {
		return pop(nodeList);
	}
	else if (index >= nodeList->length-1) {
		return removeLast(nodeList);
	}
	else {
		struct Node* curr = nodeList->head;
		int i;
		for (i = 0; i < index; i++) {
			curr = curr->next;
		}
		struct Node* currPrev = curr->prev;
		struct Node* currNext = curr->next;
		currPrev->next = currNext;
		currNext->prev = currPrev;
		curr->next = NULL;
		curr->prev = NULL;

		nodeList->length--;
		char* data = curr->data;
		free(curr);
		return data;
	}
}

void adjSwap(struct Node* a, struct Node* b, struct Node* p, struct Node* n) {
	if (p != NULL) {
		p->next = b;
	}
	b->next = a;
	a->next = n;
	if (n != NULL) {
		n->prev = a;
	}
	a->prev = b;
	b->prev = p;
}

void swap(struct List* nodeList, struct Node* ref1, struct Node* ref2) {
	struct Node* prev1 = ref1->prev;
	struct Node* next1 = ref1->next;
	struct Node* prev2 = ref2->prev;
	struct Node* next2 = ref2->next;

	
	if (next1 == ref2) {
		adjSwap(ref1, ref2, prev1, next2);
	}
	else if (next2 == ref1) {
		adjSwap(ref2, ref1, prev2, next1);
	}
	else {
		ref1->next = next2;
		ref1->prev = prev2;
		ref2->next = next1;
		ref2->prev = prev1;
		prev1->next = ref2;
		prev2->next = ref1;
		next1->prev = ref2;
		next2->prev = ref1;
	}
	surgery(nodeList);
}

void shiftLeft(struct List* list, int n) {
	if (getLength(list)<=n) {
		n = getLength(list);
	}
	int i;
	for (i = 0; i < n; i++) {
		pop(list);
	}
	//list->head->prev = NULL;
}

struct List* reverse(struct List* nodeList) {
	struct List* reversed = makeList();
	int i;
	int length = getLength(nodeList);
	for (i = 0; i < length; i++) {
		push(makeNode(pop(nodeList)), reversed);
	}
	free(nodeList);
	return reversed;
}

struct List* concat(struct List* a, struct List* b) {
	if (isEmpty(a)) {
		free(a);
		return b;
	}
	if (isEmpty(b)) {
		free(b);
		return a;
	}
	a->tail->next = b->head;
	b->head->prev = a->tail;
	a->tail = b->tail;
	a->length = a->length + b->length;
	free(b);
	return a;
}

void unique(struct List* nodeList) {
	struct Node* curr = nodeList->head;
	struct Node* temp = curr->next;
	int i;
	int j;
	for (i = 0; curr!=NULL; i++) {
		for (j = 1; temp!=nodeList->tail->next; j++) {
			if (temp->data == curr->data) {
				removeNode(j + i, nodeList);
				temp = curr->next;
			}
			temp = temp->next;
		}

		curr = curr->next;
		if (curr != NULL) {
			temp = curr->next;
		}
	}
	//surgery(nodeList);
}

int distance(struct Node* ref1, struct Node* ref2) {
	if (ref1 == ref2) {
		return 0;
	}
	struct Node* curr = ref1->next;
	int i = 1;
	while (curr != NULL) {
		if (curr == ref2) {
			return i;
		}
		curr = curr->next;
		i++;
	}
	curr = ref2->next;
	i = 1;
	while (curr != NULL) {
		if (curr == ref1) {
			return i;
		}
		curr = curr->next;
		i++;
	}
	return -1;
}

void rotateLeft(struct List* nodeList, int n) {
	nodeList->tail->next = nodeList->head;
	nodeList->head->prev = nodeList->tail;
	int i;
	for (i = 0; i < (n%getLength(nodeList)); i++) {
		nodeList->head = nodeList->head->next;
	}
	nodeList->tail = nodeList->head->prev;
	nodeList->head->prev = NULL;
	nodeList->tail->next = NULL;
}

/*
void minMax(struct List* nodeList, int* min, int* max) {
	if (isEmpty(nodeList)) {
		return;
	}
	struct Node* curr = nodeList->head;
	int i;
	*min = curr->data;
	*max = curr->data;
	curr = curr->next;
	for (i = 1; curr!=NULL; i++) {
		if (curr->data < *min) {
			*min = curr->data;
		}
		if (curr->data > *max) {
			*max = curr->data;
		}
		curr = curr->next;
	}
}
*/

bool includes(struct List* nodeList, struct Node* ref2) {
	if (isEmpty(nodeList) ){
		return false;
	}
	int i;
	struct Node* curr = nodeList->head;
	for (i = 0; curr!=NULL; i++) {
		if (curr == ref2) {
			return true;
		}
		curr = curr->next;
	}
	return false;
}

void emptyList(struct List* nodeList) {
	while(nodeList->head!=NULL){
		pop(nodeList);
	}
}

void printList(struct List* nodeList) {
	if (isEmpty(nodeList)) {
		printf("Empty List\n");
	}
	else {
		struct Node* curr = nodeList->head;
		while (curr!=NULL) {
			printf("%s\n", curr->data);
			curr = curr->next;
		}
	}
}

void printListRev(struct List* nodeList) {
	if (isEmpty(nodeList)) {
		printf("Empty List\n");
	}
	else {
		struct Node* curr = nodeList->tail;
		while (curr != NULL) {
			printf("%s\n", curr->data);
			curr = curr->prev;
		}
	}
}

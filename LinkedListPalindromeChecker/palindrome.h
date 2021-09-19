// Header (function definitions)

#include <stdio.h>
#include <stdlib.h>

struct Node {
	struct Node *next;
	int data;
};

typedef struct {
	struct Node *head;
	int size;
} List;

List* initList();
void insertArrToLinkedList(int *arr, int arr_size, List *list);
int palindrome(List *list);
void freeList(List *list);

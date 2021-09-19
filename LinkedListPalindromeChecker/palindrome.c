// Functions

#include "palindrome.h"

// Initializes an empty list
List* initList()
{
  List* emptyList = malloc(sizeof(List));

  if (emptyList == NULL)
  {
    printf("Malloc failed.");
    exit(0);
  }

  emptyList->size = 0;
  emptyList->head = NULL;

  return emptyList;
}

// Inserts array values into a linked list
void insertArrToLinkedList(int *arr, int arr_size, List *list)
{
  struct Node *nodePtr = NULL;
  list->head = nodePtr;
  list->size = 0;

  for (int i=0; i<arr_size; i++)
  {
    if (list->head == NULL){
      list->head = malloc(sizeof(struct Node));
      nodePtr = list->head;
    }
    else {
      nodePtr->next = malloc(sizeof(struct Node));
      nodePtr = nodePtr->next;
    }

    nodePtr->next = NULL;
    nodePtr->data = arr[i];
    printf("linked list %d = %d\n", i, nodePtr->data);
    list->size = list->size + 1;
  }
}

// Checks to see if linked list is a palindrome
int palindrome(List *list) // O(n)
{
  int size = list->size;

  if (size < 2){
    return 1; // yes
  }

  int arr[size];
  struct Node* checker = list->head;
  int last_index;

  // Puts 1st half of linked list in an array
  for (int i=0; i<size/2; i++){
    arr[i] = checker->data;
    checker = checker->next;
    last_index = i; 
  }

  // Skip the middle if odd # of entries
  int odd_add = 0;
  if (size % 2 == 1){
    checker = checker->next; 
    odd_add = 1;
  }

  // Compares 2nd half of linked list to 1st half array
  int j = last_index;
  for (int i=size-1; i>=(size/2)+odd_add; i--){
    printf("checker->data = %d, arr[j] = %d, j = %d.\n", checker->data, arr[j], j);
    if (checker->data != arr[j]){
      return 0; // no
    }
    checker = checker->next;
    j--;
  }
  return 1; // yes
}

// Frees all necessary memory
void freeList(List *list)
{
  struct Node* mainPtr = list->head;
  struct Node* tempPtr;

  while (mainPtr != NULL){
    tempPtr = mainPtr;
    free(mainPtr);
    mainPtr = tempPtr->next;
  }

  list->head = NULL;
  free(list);
  list = NULL;
}

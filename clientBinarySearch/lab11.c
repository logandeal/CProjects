// Logan Deal Section F
#include "lab11.h"

void* createArray(size_t size, size_t elemSize)
{
  void* array = malloc(elemSize*size+sizeof(size_t));

  if (array == NULL)
  {
    printf("Malloc failed.\n");
    exit(0);
  }

  ((size_t*)array)[0] = size;
  array = array + sizeof(size_t);

  return (void*)array;
}

size_t arraySize(void *array)
{
  return (*(size_t*)(array - sizeof(size_t))); 
}

void freeArray(void *array)
{
  array = array - sizeof(size_t);
  free(array);
  array = NULL;
  if (array == NULL)
  {
    printf("Memory freed.\n");
  }
  else
  {
    printf("Memory free failed.\n");
  }
}

int compareClients(Client *a, Client *b)
{
  if (a->accountWorth < b->accountWorth) 
  {
    return -1;
  }
  if (a->accountWorth > b->accountWorth)
  {
    return 1;
  }
  return 0;
}

size_t search(void* orderedArray, int first, int last, void* query)
{
  if (first > last)
  {
    return SIZE_MAX;
  }
  int mid;
  mid = (first+last)/2;
  int result = compareClients(query, &((Client*)orderedArray)[mid]);
  if (result > 0)
  {
    return search(orderedArray, mid+1, last, query);
  }
  else if (result < 0)
  {
    return search(orderedArray, first, mid-1, query);
  }
  else
  {
    return mid;
  }
}

size_t searchClients(Client *array, Client *query)
{
  size_t result = search(array, 0, arraySize(array), query);
  return result;
}
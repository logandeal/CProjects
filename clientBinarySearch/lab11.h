#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// Complexity: O(1)
void* createArray(size_t size, size_t elemSize);

// Complexity: O(1)
size_t arraySize(void *array);

// Complexity: O(1)
void freeArray(void *array);

#define SECT_F

typedef struct {
	unsigned long accountNumber;
	float accountWorth;
	int daysActive;
} Client;

// Complexity: O(log(n))
size_t search(void* orderedArray, int first, int last, void* query);
size_t searchClients(Client *array, Client *query);

// Complexity: O(1)
int compareClients(Client *a, Client *b);

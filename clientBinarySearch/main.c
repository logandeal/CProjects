#include "lab11.h"

int main(void)
{
  int size = 6;
  Client *clientsArray = createArray(size, sizeof(Client));

  for(int i = 0; i < 6; ++i) 
  {
    clientsArray[i].accountNumber = i;
    clientsArray[i].accountWorth = i*i;
    clientsArray[i].daysActive = i;
  }

  Client query;
  query.accountWorth = 24;

  int sizeOfArray = arraySize(clientsArray);
  printf("sizeOfArray = %d\n", sizeOfArray);
  int clientCompare = compareClients(&clientsArray[0], &clientsArray[1]);
  printf("clientCompare = %d\n", clientCompare);

  int indexOfQuery = searchClients(clientsArray, &query);
  printf("indexOfQuery = %d\n", indexOfQuery);

  freeArray(clientsArray);
}
// Main code

#include "palindrome.h"

int main(void)
{
  // Example array (a palindrome)
  int arr[7] = {1, 2, 1, 6, 1, 2, 1};

  List* testList = initList();

  insertArrToLinkedList(arr, 7, testList);

  int result = palindrome(testList);
  if (result == 1){
    printf("PALINDROME.\n");
  }
  else {
    printf("NOT A PALINDROME.\n");
  }

  freeList(testList);
}

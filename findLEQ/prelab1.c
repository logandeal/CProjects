#include "prelab1.h"

int findBigSmall(int arraySize, float* array, float* userNum, float* largestInArrayLessThanUser, float* smallestInArrayGreaterThanUser)
{
  int foundOne1 = 0;
  // Find largestInArrayLessThanUser
  for (int i=0; i<arraySize; ++i)
  {
    if (array[i] < *userNum)
    {
      if (foundOne1 == 0)
      {
        *largestInArrayLessThanUser = array[i];
        foundOne1 = 1;
      }
      else if (array[i] > *largestInArrayLessThanUser)
      {
        *largestInArrayLessThanUser = array[i];
      }
    }
  }

  int foundOne2 = 0;
  // Find smallestInArrayGreaterThanUser
  for (int i=0; i<arraySize; ++i)
  {
    if (array[i] > *userNum)
    {
      if (foundOne2 == 0)
      {
        *smallestInArrayGreaterThanUser = array[i];
        foundOne2 = 1;
      }
      else if (array[i] < *smallestInArrayGreaterThanUser)
      {
        *smallestInArrayGreaterThanUser = array[i];
      }
    }
  }

  if (*largestInArrayLessThanUser == 0)
  {
    return -1;
  }
  else if (*smallestInArrayGreaterThanUser == 0)
  {
    return -2;
  }
  else
  {
    return 1;
  }
}
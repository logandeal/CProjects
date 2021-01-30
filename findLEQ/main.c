#include "prelab1.h"

int main(void) 
{
  float array[] = {1.023, 92.3, 283.3, 324.2};
  int arraySize = 4;

  float userFloat;
  float largestInArrayLessThanUser;
  float smallestInArrayGreaterThanUser;

  printf("Please enter a float number: ");

  scanf("%f", &userFloat);

  int result = findBigSmall(arraySize, array, &userFloat, &largestInArrayLessThanUser, &smallestInArrayGreaterThanUser);

  if (result == 1)
  {
    float sum = largestInArrayLessThanUser + smallestInArrayGreaterThanUser;
    printf("The sum of largestInArrayLessThanUser and smallestInArrayGreaterThanUser is %f",sum);
  }
  else if (result == -1)
  {
    printf("Could not calculate sum because largestInArrayLessThanUser was not found.");
  }
  else if (result == -2)
  {
    printf("Could not calculate sum because smallestInArrayGreaterThanUser was not found.");
  }
}
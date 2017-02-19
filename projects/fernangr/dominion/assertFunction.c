#include <stdlib.h>
#include <stdio.h>
#include "assertFunction.h"

int assertTrue(int a)
{
  if (a)
    printf("TEST SUCCESSFULLY COMPLETED!\n");
  else
    printf("TEST FAILED!\n");

  return a;
}

/*
    Tests that parameters are equal to each other, returning the result of the
    test and printing status messages.
*/

int assertEquals(int a, int b)
{
    int result = (a == b);

    printf("--> EXPECTED: %d\n--> GOT: %d\n", a, b);

    if (result)
        printf("--> TEST PASSES!\n");
    else
        printf("--> TEST FAILS!\n");

    return result;
}

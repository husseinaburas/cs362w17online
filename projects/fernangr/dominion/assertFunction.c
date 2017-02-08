#include <stdlib.h>
#include "assertFunction.h"

int assertTrue(int a)
{
  if (a)
    printf("TEST SUCCESSFULLY COMPLETED!\n");
  else
    printf("TEST FAILED!\n");

  return a;
}

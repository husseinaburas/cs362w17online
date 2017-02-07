#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "dominion.h"
#include "rngs.h"
#include <time.h>

// gcc -o unittest1 unittest1.c dominion.o rngs.o $(CFLAGS)
// gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest3.c rngs.c -o unittest3 -lm -g
int zdi_assert(int a, char * string)
{
  if(a == 1)
  {
    printf("Test Passed: \t %s \n\n\n", string);
    return 0;
  }
  else if( a == 2)
  {
    printf("Test Failed: \t %s\n\n\n", string);
  }
  return 0;

}


int main ()
{
    printf("Unit Test 3\n\n");
  if(getCost(adventurer) == 6)
  {
    zdi_assert(1, "Get Cost function test on adventurer card");
  }
  else
  {
    zdi_assert(2, "Get Cost function test on adventurer card");
  }

  if(getCost(village) == 3)
  {
    zdi_assert(1, "Get Cost function test on village card ");
  }
  else
  {
    zdi_assert(2, "Get Cost function test on village card ");
  }

  return 0;
}

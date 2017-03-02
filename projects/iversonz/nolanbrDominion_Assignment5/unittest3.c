#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "dominion.h"
#include "rngs.h"
#include <time.h>

// gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest3.c rngs.c -o unittest3 -lm -g

//ZDI assert is a function that receives a integer and a character.
// It checks if the integer is one or 2, if it is one that means the test Passed.
// If the integer is 2 it means the test failed
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
  //Checking the get cost function
  printf("Unit Test 3\n\n");
  if(getCost(adventurer) == 6) // adventurer has a cost of 6, 6 means the test passed
  {
    zdi_assert(1, "Get Cost function test on adventurer card");
  }
  else
  {
    zdi_assert(2, "Get Cost function test on adventurer card");
  }

  if(getCost(village) == 3) // village has a cost of 3, 3 means the tes passed
  {
    zdi_assert(1, "Get Cost function test on village card ");
  }
  else
  {
    zdi_assert(2, "Get Cost function test on village card ");
  }

  return 0;
}

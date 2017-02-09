#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "dominion.h"

bool pass = true;

int asserttrue(int i, char* s){
    if(i == 0){
        printf("Test failed");
        pass = false;
    }
    return 0;
}

int main(void) {

  srand(time(NULL));
  int randomSupplyCount = rand();
  struct gameState G;
  struct gameState *p = &G;
  p->supplyCount[0] = randomSupplyCount;
  asserttrue(supplyCount(0,p) == randomSupplyCount, "Supply count is wrong");

  return 0;
}

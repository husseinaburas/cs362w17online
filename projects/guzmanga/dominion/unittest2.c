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
  int randomHandCount = rand();
  struct gameState G;
  struct gameState *p = &G;
  p->handCount[0] = randomHandCount;
  asserttrue(numHandCards(p) == randomHandCount, "Hand Count is wrong");

  return 0;
}

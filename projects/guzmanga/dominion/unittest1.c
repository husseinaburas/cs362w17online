#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>

//unittest1.c
//buyCard unit test

bool pass = true;

int asserttrue(int i, char* s){
    if(i == 0){
        printf("Test failed");
        pass = false;
    }

    return 0;
}

int main(void) {

	struct gameState G;
  struct gameState *p = &G;
	p->whoseTurn = 1;
  p->supplyCount[cutpurse] = 1;
  p->numBuys = 1;
  p->coins = r;

  int buyCardResult = buyCard(feast, p);

  asserttrue(buyCardResult == 0, "Failed\n");
  assertrue(p->supplyCount[cutpurse]==0, "# of cutpurses wrong\n");
  assertrue(p->numBuys == 0, "Buys incorrect");
  assertrue(p->coins == 0, "Coins incorrect");

  if(pass){
	    printf("Test passed \n");
	}

	return 0;
}

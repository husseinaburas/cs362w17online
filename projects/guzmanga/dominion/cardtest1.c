#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dominion.h"

//cardtest3.c
//gardens unit test

bool pass = true;

int asserttrue(int i, char* s){
    if(i == 0){
        printf("Test failed");
        pass = false;
    }

    return 0;
}

int main(void) {
	int kingdomCards[10] = {adventurer, council_room, feast, village, ambassador, cutpurse,
	                        outpost, sea_hag, minion, gardens};
	struct gameState G;
  struct gameState *p = &G;
	initializeGame(2,kingdomCards, 3, p);
	p->hand[0][0] = adventurer;
	playCard(0,0,0,0,p);

	asserttrue(p->hand[0][p->handCount[0]-2] == copper, "Treasure Card bug \n");
  asserttrue(p->hand[0][p->handCount[0]-1] == copper, "Treasure Card bug \n");
  asserttrue(p->handCount[0] == 6, "Add cards bug");

  if(pass){
	    printf("Test passed \n");
	}

	return 0;
}

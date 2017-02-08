#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"

//cardtest1.c
//smithy unit test

bool pass = true;

int asserttrue(int i, char* s){
    if(i == 0){
        printf("Test failed");
        pass = false;
    }

    return 0;
}

int main(void) {
	// your code goes here
	int kingdomCards[10] = {adventurer, council_room, feast, village, ambassador, cutpurse,
	                        outpost, sea_hag, minion, tribute};
	struct gameState G;
	initializeGame(2,kingdomCards, 3, &G);
	G.hand[0][0] = smithy;
	playCard(0,0,0,0,p);

	int handCount = numHandCards(&G);

  asserttrue(handCount == 7, "Smithy bug \n");
	if(pass){
	    printf("Test passed \n");
	}

	return 0;
}

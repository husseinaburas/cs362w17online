#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dominion.h"

//cardtest4.c
//council room test

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
	struct gameState *p = &G;

	initializeGame(2,kingdomCards, 3, p);
	p->hand[0][0] = council_room;
	playCard(0,0,0,0,p);


	asserttrue(p->handCount[0] == 7, "Incorrect number of cards \n");
	asserttrue(p->numBuys == 2, "Incorrect number of buy \n");
	asserttrue(p->handCount[1]== 6, "Other players drawing incorrectly \n");

	if(pass){
	    printf("Test passed \n");
	}

	return 0;
}

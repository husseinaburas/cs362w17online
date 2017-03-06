/*Card Test for Mine */

#include "dominion.h"
#include "dominion_helpers.h"
#include "stdlib.h"
#include "stdio.h"
#include "rngs.h"
#include <string.h>
#include <assert.h>
#define TESTCARD "mine"

int main(){
	printf("\n Test for Mine card \n");
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
			
	int handpos = 0;
	int choice1 = 1, choice2 = 5, choice3 = -1, bonus = 0;
	initializeGame(2,k,1000,&G);
	
	G.hand[0][0] = mine; //set in hand
	G.hand[0][1] = copper;
	G.handCount[0] = 1;
	cardEffect(mine, choice1, choice2,choice3, &G, handpos, bonus);
	
	printf("testing mine: handcount should be 1, actual %d ", G.handCount[0]);
	if(G.handCount[0] == 1){
		printf(". test Pass\n");
	}else{
		printf(". test Fail\n");
	
	}
	
	printf("testing mine: card should be silver");
	if(G.hand[0][0] == silver){
		printf(". test Pass\n");
		
	}else{
		printf(".test Fail\n");
		
	}
	return 0;
	
}


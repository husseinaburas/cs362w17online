/* Name: Nipun Bathini
   Assignment: 3
   
   cardtest2.c village
   */
   
#include "dominion.h"
#include "dominion_helpers.h"
#include "stdlib.h"
#include "stdio.h"
#include "rngs.h" 
#include <string.h>
#include <assert.h>
#define TESTCARD "village"

int main(){
	printf("\n --Card Test 2 (village)-- \n");
	struct gameState G, Gtwo;
	int thisPlayer = 0;
	int handpos = 0;
	int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	initializeGame(2, k, 1000, &G);
	
	memcpy(&Gtwo, &G, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &Gtwo, handpos, &bonus);
	//Test 1
	printf("Testing village: handCount should be %d, actual  ", G.handCount[thisPlayer]);
	if(Gtwo.handCount[thisPlayer] == G.handCount[thisPlayer]){
		printf("%d, test PASS\n",Gtwo.handCount[thisPlayer]);
	}else{
		printf("%d, test FAIL\n",Gtwo.handCount[thisPlayer]);
	}
	
	//Test 2
	memcpy(&Gtwo, &G, sizeof(struct gameState));
	G.numActions = G.numActions + 2;
	cardEffect(village, choice1, choice2, choice3, &Gtwo, handpos, &bonus);
	printf("Testing village: number of actions should be %d, actual ", G.numActions);
	
	if(Gtwo.numActions == G.numActions){
		printf("%d, test PASS\n",Gtwo.numActions);
	}else{
		printf("%d, test FALL\n",Gtwo.numActions);
	}
	
	return 0;
}
		
		

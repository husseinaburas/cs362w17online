#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

int cardCount(int player, struct gameState G, int card){
	int x;
	int t=0;
	for(x=0; x<(G.handCount[player]); x++){
		if(G.hand[player][x] == card){
			t++;
		}
	}
	return t;
}

//Test Village card
int main(int argc, char const *argv[])
{
	int errorFlag=0;
	int players=2;
	int seed=999;
	struct gameState G, copyG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("Running Card Test 3: Village Card\n");
	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("\n");

	initializeGame(players, k, seed, &G);
	memcpy(&copyG, &G, sizeof(struct gameState));

	//Add village card to hands
	G.handCount[0]++;
	G.hand[0][5]=village;
	copyG.handCount[0]++;
	copyG.hand[0][5]=village;
	playVillage(&G, 5);

	//make sure there is one new card minus the played card
	if( G.handCount[0] != copyG.handCount[0] ){
		printf("Error with hand card count. Expected 6 has %d\n", G.handCount[0]);
		errorFlag++;
	}
	//make sure there are two actions left after using first action
	if(G.numActions != (copyG.numActions + 2)){
		printf("Error with number of actions count. Expected 2 has %d\n", G.numActions);
		errorFlag++;
	}
	//make sure village card is discarded
	if( cardCount(0, G, village) != 0){
		printf("Error village card still in hand (not discarded)\n");
		errorFlag++;
	}

	printf("\n");
	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("Completed Card Test 3, Village Card. %d total errors.\n", errorFlag);
	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	return 0;
}
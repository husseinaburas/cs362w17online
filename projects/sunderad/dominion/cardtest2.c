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

//Test function playSmithy()
int main(int argc, char const *argv[])
{
	int errorFlag=0;
	int players=2;
	int seed=999;
	struct gameState G, copyG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("Running Card Test 2: Smithy Card\n\n");
	initializeGame(players, k, seed, &G);
	memcpy(&copyG, &G, sizeof(struct gameState));

	//Add smithy card to hands
	G.handCount[0]++;
	G.hand[0][5]=smithy;
	copyG.handCount[0]++;
	copyG.hand[0][5]=smithy;
	playSmithy(&G, 5);

	//make sure there are three new cards minus the played card
	if( G.handCount[0] != (copyG.handCount[0] + 2) ){
		printf("Error with hand card count\n");
		errorFlag++;
	}
	//make sure card totals are correct
	if( (G.discardCount[0] + G.deckCount[0] + G.handCount[0]) != (copyG.discardCount[0] + copyG.deckCount[0] + copyG.handCount[0]) ){
		printf("Error with overall card count (sum of deck+hand+discard)\n");
		errorFlag++;
	}
	//make sure smithy card is discarded
	if( cardCount(0, G, smithy) != 0){
		printf("Error smithy card still in hand (not discarded)\n");
		errorFlag++;
	}

	printf("\n");
	printf("Completed Card Test 2, Smithy Card. %d total errors.\n", errorFlag);
	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	return 0;
}
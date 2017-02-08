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

//Test council_room card
int main(int argc, char const *argv[])
{
	int i, j;
	int errorFlag=0;
	int players=2;
	int seed=999;
	struct gameState G, copyG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("Running Card Test 4: Council Room Card\n\n");
	initializeGame(players, k, seed, &G);
	memcpy(&copyG, &G, sizeof(struct gameState));

	//Add council_room card to hands
	G.handCount[0]++;
	G.hand[0][5]=council_room;
	copyG.handCount[0]++;
	copyG.hand[0][5]=council_room;
	playCouncil_Room(&G, 5);

	//make sure there are four new cards minus the played card
	if( G.handCount[0] != (copyG.handCount[0] + 3) ){
		printf("Error with hand card count\n");
		errorFlag++;
	}
	//make sure there are now 2 buys
	if( G.numBuys != 2 ){
		printf("Error with numBuys count\n");
		errorFlag++;
	}
	//make sure other player has an extra card
	if(G.handCount[1] != 1){
		printf("Error with player 2 hand count, no extra card\n");
		errorFlag++;
	}
	//make sure council_room card is discarded
	if( cardCount(0, G, council_room) != 0){
		printf("Error council_room card still in hand (not discarded)\n");
		errorFlag++;
	}

	printf("\n");
	printf("Completed Card Test 4, Council Room Card. %d total errors.\n", errorFlag);
	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	return 0;
}
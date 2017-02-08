;
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

int treasureCardCount(int player, struct gameState G){
	int x;
	int t=0;
	for(x=0; x<(G.handCount[player]); x++){
		if(G.hand[player][x] == copper || G.hand[player][x] == silver || G.hand[player][x] == gold){
			t++;
		}
	}
	return t;
}

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

// Testing playAdventurer() function from dominion.c
int main(int argc, char const *argv[])
{
	int errorFlag=0;
	int players=2;
	int seed=999;
	struct gameState G, copyG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("Running Card Test 1: Adventurer Card\n\n");
	//Setup Game
	initializeGame(players, k, seed, &G);
	memcpy(&copyG, &G, sizeof(struct gameState));
	//Add adventurer card to hands
	G.handCount[0]++;
	G.hand[0][5]=adventurer;
	copyG.handCount[0]++;
	copyG.hand[0][5]=adventurer;
	playAdventurer(&G);

	//make sure there are two new treasure cards
	if( treasureCardCount(0, G) != (treasureCardCount(0, copyG) + 2) ){
		printf("Error with treasure card count in hand\n");
		errorFlag++;
	}
	//make sure there are two new cards minus the played card
	if( G.handCount[0] != (copyG.handCount[0] + 1) ){
		printf("Error with hand card count\n");
		errorFlag++;
	}
	//make sure card totals are correct
	if( (G.discardCount[0] + G.deckCount[0] + G.handCount[0]) != (copyG.discardCount[0] + copyG.deckCount[0] + copyG.handCount[0]) ){
		printf("Error with overall card count (sum of deck+hand+discard)\n");
		errorFlag++;
	}

	if( cardCount(0, G, adventurer) != 0){
		printf("Error adventurer card still in hand (not discarded)\n");
		errorFlag++;
	}

	printf("\n");
	printf("Completed Card Test 1, Adventurer Card. %d total errors.\n", errorFlag);
	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	return 0;
}
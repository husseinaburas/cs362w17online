#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

void asserttrue(int num){
    if(num) printf("TEST PASSED. \n");
    else printf("TEST FAILED.\n");
    return;
}

int main(int argc, char **argv) {
	printf("\n--- TESTING Smithy ---\n");
			
	//initialize game
	struct gameState G;
	int result, randomNum = 0;
	int k[10] = {adventurer, smithy, council_room, feast, mine, gardens, remodel, village, great_hall, baron};
	randomNum = rand() % 10;
	result = initializeGame(2, k, randomNum, &G);
	int whoseTurn = G.whoseTurn;
	
	//test smithy when there are enough cards in deck
	printf("testing player 1 playing smithy when there are enough cards in deck\n");
	//set decks for both players
	G.handCount[whoseTurn] = 1;
	G.hand[whoseTurn][0] = smithy;
	G.handCount[1] = 2;
	G.deckCount[whoseTurn] = 7;
	G.deckCount[1] = 8;
	G.supplyCount[curse] = 4;
	G.supplyCount[estate] = 4;
	G.supplyCount[duchy] = 4;
	G.supplyCount[province] = 4;
	
	//test wat happens when a card is played
	result = playCard(0, 0, 0, 0, &G);
	printf("testing whether card correctly plays \n");
	asserttrue(result == 0);
	printf("testing the turn still belongs to the same player\n");
	asserttrue(whoseTurn == G.whoseTurn);
	printf("testing player1 deck count\n");
	asserttrue(G.deckCount[whoseTurn] == 4);
	printf("testing player2 deck count\n");
	asserttrue(G.deckCount[1] == 8);
	printf("testing player1 hand count\n");
	asserttrue(G.handCount[whoseTurn] == 3);
	printf("testing player2 hand count\n");
	asserttrue(G.handCount[1] == 2);
	
	printf("testing supply count on curse cards\n");
	asserttrue(G.supplyCount[curse] == 4);
	printf("testing supply count on estate cards\n");
	asserttrue(G.supplyCount[estate] == 4);
	printf("testing supply count on duchy cards\n");
	asserttrue(G.supplyCount[duchy] == 4);
	printf("testing supply count on province cards\n");
	asserttrue(G.supplyCount[province] == 4);

	
	//test smithy when there are not enough cards in deck
	printf("testing player 1 smithy when there are not enough cards in deck\n");
	//set decks for both players
	G.handCount[whoseTurn] = 1;
	G.hand[whoseTurn][0] = smithy;
	G.handCount[1] = 2;
	G.deckCount[whoseTurn] = 2;
	G.deckCount[1] = 8;
	G.supplyCount[curse] = 4;
	G.supplyCount[estate] = 4;
	G.supplyCount[duchy] = 4;
	G.supplyCount[province] = 4;
	
	//test conditions while playing the card
	result = playCard(0, 0, 0, 0, &G);
	printf("testing card correctly plays \n");
	asserttrue(result == -1);
	printf("testing the turn still belongs to the same player\n");
	asserttrue(whoseTurn == G.whoseTurn);
	printf("testing player1 hand count\n");
	asserttrue(G.handCount[whoseTurn] == 1);
	printf("testing player2 hand count\n");
	asserttrue(G.handCount[1] == 2);
	printf("testing player1 deck count\n");
	asserttrue(G.deckCount[whoseTurn] == 2);
	printf("testing player2 deck count\n");
	asserttrue(G.deckCount[1] == 8);
	
	//test supply cards
	printf("testing supply count on curse cards\n");
	asserttrue(G.supplyCount[curse] == 4);
	printf("testing supply count on estate cards\n");
	asserttrue(G.supplyCount[estate] == 4);
	printf("testing supply count on duchy cards\n");
	asserttrue(G.supplyCount[duchy] == 4);
	printf("testing supply count on province cards\n");
	asserttrue(G.supplyCount[province] == 4);
	
	
	printf("\n--- END TESTING ---\n");
	return 0;
}
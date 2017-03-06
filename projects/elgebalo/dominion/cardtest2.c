#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


void asserttrue(int num){
    if(num) printf("TEST PASSED. \n");
    else printf("TEST FAILED.\n");
    return;
}


int main(int argc, char **argv) {
	printf("\n--- TESTING Adventurer ---\n");
	
	
	//initialize game
	struct gameState G;
	int result, randomNum = 0;
	int k[10] = {adventurer, smithy, council_room, feast, mine, gardens, remodel, village, great_hall, baron};
	randomNum = rand() % 10;
	result = initializeGame(2, k, randomNum, &G);
	int whoseTurn = G.whoseTurn;
	G.phase = 0;
	G.numActions = G.numActions > 0 ? G.numActions : 1;
	G.handCount[whoseTurn] = G.handCount[whoseTurn] > 0 ? G.handCount[whoseTurn] : 1;
	int coins = G.coins;
	
	//test adventurer when deck is empty
	printf("------------------testing player1 playing adventurer with empty deck--------------------------\n");
	
	G.handCount[whoseTurn] = 1;
	G.handCount[1] = 2;
	G.hand[whoseTurn][0] = adventurer;
	G.deckCount[whoseTurn] = 0;
	G.deckCount[1] = 3;
	G.supplyCount[curse] = 4;
	G.supplyCount[estate] = 4;
	G.supplyCount[duchy] = 4;
	G.supplyCount[province] = 4;
	G.discard[whoseTurn][0] = estate;
	G.discard[whoseTurn][1] = copper;
	G.discard[whoseTurn][2] = copper;
	G.discard[whoseTurn][3] = curse;
	G.deck[whoseTurn][0] = estate;
	G.deck[whoseTurn][1] = duchy;
	
	result = playCard(0, 0, 0, 0, &G);
	printf("testing if card correctly plays \n");
	asserttrue(result == 0);
	printf("testing if coin count is correct\n");
	asserttrue(coins + 2 == G.coins);
	printf("testing if whoseTurn works correctly\n");
	asserttrue(whoseTurn == G.whoseTurn);
	printf("testing player1 hand count\n");
	asserttrue(G.handCount[whoseTurn] == 3);
	printf("testing player2 hand count\n");
	asserttrue(G.handCount[1] == 2);
	printf("testing player1 deck count\n");
	asserttrue(G.deckCount[whoseTurn] == 0);
	printf("testing player2 deck count\n");
	asserttrue(G.deckCount[1] == 3);
	printf("testing player1 discard count\n");
	asserttrue(G.discardCount[whoseTurn] == 0);
	printf("testing player2 discard count\n");
	asserttrue(G.discardCount[1] == 0);
	printf("testing supply count on curse cards\n");
	asserttrue(G.supplyCount[curse] == 4);
	printf("testing supply count on estate cards\n");
	asserttrue(G.supplyCount[estate] == 4);
	printf("testing supply count on duchy cards\n");
	asserttrue(G.supplyCount[duchy] == 4);
	printf("testing supply count on province cards\n");
	asserttrue(G.supplyCount[province] == 4);
	
	//test adventurer when 2 treasure cards are at the beginning of the deck
	printf("------------------testing player1 playing adventurer with 2 treasure cards at beginning of deck--------------\n");
	
	G.hand[whoseTurn][0] = adventurer;
	G.deck[whoseTurn][0] = copper;
	G.deck[whoseTurn][1] = copper;
	G.deck[whoseTurn][2] = estate;
	G.deck[whoseTurn][3] = curse;
	G.handCount[whoseTurn] = 1;
	G.deckCount[whoseTurn] = 4;
	G.handCount[1] = 2;
	G.deckCount[1] = 3;
	G.supplyCount[curse] = 4;
	G.supplyCount[estate] = 4;
	G.supplyCount[duchy] = 4;
	G.supplyCount[province] = 4;
	result = playCard(0, 0, 0, 0, &G);
	printf("testing that card correctly plays \n");
	asserttrue(result == 0);
	printf("testing if whoseTurn works correctly\n");
	asserttrue(whoseTurn == G.whoseTurn);
	printf("testing if coin count is correct\n");
	asserttrue(coins + 2 == G.coins);
	printf("testing player1 hand count\n");
	asserttrue(G.handCount[whoseTurn] == 1);
	printf("testing player2 hand count\n");
	asserttrue(G.handCount[1] == 2);
	printf("testing player1 deck count\n");
	asserttrue(G.deckCount[whoseTurn] == 2);
	printf("testing player2 deck count\n");
	asserttrue(G.deckCount[1] == 3);
	printf("testing player1 discard count\n");
	asserttrue(G.discardCount[whoseTurn] == 2);
	printf("testing player2 discard count\n");
	asserttrue(G.discardCount[1] == 0);
	printf("testing supply count on curse cards\n");
	asserttrue(G.supplyCount[curse] == 4);
	printf("testing supply count on estate cards\n");
	asserttrue(G.supplyCount[estate] == 4);
	printf("testing supply count on duchy cards\n");
	asserttrue(G.supplyCount[duchy] == 4);
	printf("testing supply count on province cards\n");
	asserttrue(G.supplyCount[province] == 4);
		
	//test deck when 2 treasure cards are at the end of the deck
	printf("---------testing adventurer with 2 treasure cards at end of deck--------------------\n");
	
	G.hand[whoseTurn][0] = adventurer;
	G.deck[whoseTurn][0] = estate;
	G.deck[whoseTurn][1] = curse;
	G.deck[whoseTurn][2] = copper;
	G.deck[whoseTurn][3] = copper;
	G.handCount[whoseTurn] = 1;
	G.deckCount[whoseTurn] = 4;
	G.handCount[1] = 2;
	G.deckCount[1] = 3;
	G.supplyCount[curse] = 4;
	G.supplyCount[estate] = 4;
	G.supplyCount[duchy] = 4;
	G.supplyCount[province] = 4;
	result = playCard(0, 0, 0, 0, &G);
	printf("testing if card correctly plays \n");
	asserttrue(result == 0);
	printf("testing if whoseTurn works correctly\n");
	asserttrue(whoseTurn == G.whoseTurn);
	printf("testing if coin count is correct\n");
	asserttrue(coins + 2 == G.coins);
	printf("testing player1 hand count\n");
	asserttrue(G.handCount[whoseTurn] == 1);
	printf("testing player2 hand count\n");
	asserttrue(G.handCount[1] == 2);
	printf("testing player1 deck count\n");
	asserttrue(G.deckCount[whoseTurn] == 0);
	printf("testing player2 deck count\n");
	asserttrue(G.deckCount[1] == 3);
	printf("testing player1 discard count\n");
	asserttrue(G.discardCount[whoseTurn] == 4);
	printf("testing player2 discard count\n");
	asserttrue(G.discardCount[1] == 0);
	printf("testing supply count on curse cards\n");
	asserttrue(G.supplyCount[curse] == 4);
	printf("testing supply count on estate cards\n");
	asserttrue(G.supplyCount[estate] == 4);
	printf("testing supply count on duchy cards\n");
	asserttrue(G.supplyCount[duchy] == 4);
	printf("testing supply count on province cards\n");
	asserttrue(G.supplyCount[province] == 4);
	
	//test deck when 1 treasure card is at the beginning of the deck and 1 at the end
	printf("------testing adventurer with 1 treasure card at the end and one at the beginning----------------\n");
	
	G.hand[whoseTurn][0] = adventurer;
	G.deck[whoseTurn][0] = copper;
	G.deck[whoseTurn][1] = curse;
	G.deck[whoseTurn][2] = estate;
	G.deck[whoseTurn][3] = copper;
	G.handCount[whoseTurn] = 1;
	G.deckCount[whoseTurn] = 4;
	G.handCount[1] = 2;
	G.deckCount[1] = 3;
	G.supplyCount[curse] = 4;
	G.supplyCount[estate] = 4;
	G.supplyCount[duchy] = 4;
	G.supplyCount[province] = 4;
	result = playCard(0, 0, 0, 0, &G);
	printf("testing if card correctly plays \n");
	asserttrue(result == 0);
	printf("testing if whoseTurn works correctly\n");
	asserttrue(whoseTurn == G.whoseTurn);
	printf("testing if coin count is correct\n");
	asserttrue(coins + 2 == G.coins);
	printf("testing player1 hand count\n");
	asserttrue(G.handCount[whoseTurn] == 1);
	printf("testing player2 hand count\n");
	asserttrue(G.handCount[1] == 2);
	printf("testing player1 deck count\n");
	asserttrue(G.deckCount[whoseTurn] == 0);
	printf("testing player2 deck count\n");
	asserttrue(G.deckCount[1] == 3);
	printf("testing player1 discard count\n");
	asserttrue(G.discardCount[whoseTurn] == 4);
	printf("testing player2 discard count\n");
	asserttrue(G.discardCount[1] == 0);
	printf("testing supply count on curse cards\n");
	asserttrue(G.supplyCount[curse] == 4);
	printf("testing supply count on estate cards\n");
	asserttrue(G.supplyCount[estate] == 4);
	printf("testing supply count on duchy cards\n");
	asserttrue(G.supplyCount[duchy] == 4);
	printf("testing supply count on province cards\n");
	asserttrue(G.supplyCount[province] == 4);
	
	
	
	//test deck when 2 treasure cards are in the middle of the deck
	printf("--------testing adventurer with 2 treasure cards in middle of deck------------\n");
	
	G.hand[whoseTurn][0] = adventurer;
	G.deck[whoseTurn][0] = estate;
	G.deck[whoseTurn][1] = copper;
	G.deck[whoseTurn][2] = copper;
	G.deck[whoseTurn][3] = curse;
	G.handCount[whoseTurn] = 1;
	G.deckCount[whoseTurn] = 4;
	G.handCount[1] = 2;
	G.deckCount[1] = 3;
	G.supplyCount[curse] = 4;
	G.supplyCount[estate] = 4;
	G.supplyCount[duchy] = 4;
	G.supplyCount[province] = 4;
	result = playCard(0, 0, 0, 0, &G);
	printf("testing if card correctly plays \n");
	asserttrue(result == 0);
	printf("testing if whoseTurn works correctly\n");
	asserttrue(whoseTurn == G.whoseTurn);
	printf("testing if coin count is correct\n");
	asserttrue(coins + 2 == G.coins);
	printf("testing player1 hand count\n");
	asserttrue(G.handCount[whoseTurn] == 1);
	printf("testing player2 hand count\n");
	asserttrue(G.handCount[1] == 2);
	printf("testing player1 deck count\n");
	asserttrue(G.deckCount[whoseTurn] == 1);
	printf("testing player2 deck count\n");
	asserttrue(G.deckCount[1] == 3);
	printf("testing player1 discard count\n");
	asserttrue(G.discardCount[whoseTurn] == 3);
	printf("testing player2 discard count\n");
	asserttrue(G.discardCount[1] == 0);
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
#include <stdlib.h>
#include <stdio.h>
#include "asserttrue.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(int argc, char** argv){
	printf("******begin unit test on great_hall card******\n");
	
	//initialize game
	struct gameState G;
	int result, randomVar = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	randomVar = rand() % 10;
	result = initializeGame(2, k, randomVar, &G);
	int whoseTurn = G.whoseTurn;
	G.phase = 0;
	G.numActions = G.numActions > 0 ? G.numActions : 1;
	G.handCount[whoseTurn] = G.handCount[whoseTurn] > 0 ? G.handCount[whoseTurn] : 1;
	int coins = G.coins;
	
	//test player 1 playing great_hall when player 1 deck is empty
	printf("testing player1 playing great_hall with empty deck\n");
	G.handCount[whoseTurn] = 1;
	G.handCount[1] = 2;
	G.hand[whoseTurn][0] = great_hall;
	G.deckCount[whoseTurn] = 0;
	G.deckCount[1] = 3;
	G.supplyCount[whoseTurn] = 5;
	G.supplyCount[1] = 5;
	G.discardCount[whoseTurn] = 0;
	G.discardCount[1] = 0;
	G.numActions = 2;
	G.supplyCount[curse] = 4;
	G.supplyCount[estate] = 4;
	G.supplyCount[duchy] = 4;
	G.supplyCount[province] = 4;
	result = playCard(0, 0, 0, 0, &G);
	printf("testing whether card correctly plays \n");
	asserttrue(result == 0);
	printf("testing whether the turn still belongs to the same player\n");
	asserttrue(whoseTurn == G.whoseTurn);
	printf("testing player1 hand count\n");
	asserttrue(G.handCount[whoseTurn] == 1);
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
	printf("testing player1 victory points\n");
	asserttrue(G.supplyCount[whoseTurn] == 6);
	printf("testing player2 victory points\n");
	asserttrue(G.supplyCount[1] == 5);
	printf("testing number of actions count\n");
	asserttrue(G.numActions == 3);
	printf("testing supply count on curse cards\n");
	asserttrue(G.supplyCount[curse] == 4);
	printf("testing supply count on estate cards\n");
	asserttrue(G.supplyCount[estate] == 4);
	printf("testing supply count on duchy cards\n");
	asserttrue(G.supplyCount[duchy] == 4);
	printf("testing supply count on province cards\n");
	asserttrue(G.supplyCount[province] == 4);
	
	//test player 1 playing great_hall when player 1 deck is not empty
	printf("testing player1 playing great_hall with non-empty deck\n");
	G.handCount[whoseTurn] = 1;
	G.handCount[1] = 2;
	G.hand[whoseTurn][0] = great_hall;
	G.deckCount[whoseTurn] = 3;
	G.deckCount[1] = 3;
	G.supplyCount[whoseTurn] = 5;
	G.supplyCount[1] = 5;
	G.discardCount[whoseTurn] = 0;
	G.discardCount[1] = 0;
	G.numActions = 2;
	G.supplyCount[curse] = 4;
	G.supplyCount[estate] = 4;
	G.supplyCount[duchy] = 4;
	G.supplyCount[province] = 4;
	result = playCard(0, 0, 0, 0, &G);
	printf("testing whether card correctly plays \n");
	asserttrue(result == 0);
	printf("testing whether the turn still belongs to the same player\n");
	asserttrue(whoseTurn == G.whoseTurn);
	printf("testing player1 hand count\n");
	asserttrue(G.handCount[whoseTurn] == 2);
	printf("testing player2 hand count\n");
	asserttrue(G.handCount[1] == 2);
	printf("testing player1 deck count\n");
	asserttrue(G.deckCount[whoseTurn] == 2);
	printf("testing player2 deck count\n");
	asserttrue(G.deckCount[1] == 3);
	printf("testing player1 discard count\n");
	asserttrue(G.discardCount[whoseTurn] == 0);
	printf("testing player2 discard count\n");
	asserttrue(G.discardCount[1] == 0);
	printf("testing player1 victory points\n");
	asserttrue(G.supplyCount[whoseTurn] == 6);
	printf("testing player2 victory points\n");
	asserttrue(G.supplyCount[1] == 5);
	printf("testing number of actions count\n");
	asserttrue(G.numActions == 3);
	printf("testing supply count on curse cards\n");
	asserttrue(G.supplyCount[curse] == 4);
	printf("testing supply count on estate cards\n");
	asserttrue(G.supplyCount[estate] == 4);
	printf("testing supply count on duchy cards\n");
	asserttrue(G.supplyCount[duchy] == 4);
	printf("testing supply count on province cards\n");
	asserttrue(G.supplyCount[province] == 4);
	
	printf("******begin unit test on great_hall card******\n");
	return 0;
}
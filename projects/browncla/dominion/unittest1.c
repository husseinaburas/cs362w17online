/*unittest1.c */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#define FUNCTION_NAME "shuffle"
//testing int shuffle(int player, struct gameState *state)
// shuffle reorganizes the deck of the player, assumes all cards are in the deck, not
// in hand or discard pile


// Test that the deck count before and after are the same
// Test that the deck is in a different order
// Test that all the same cards are still in the deck
// Test that it only affects the deck of the current player

//Own assert function
int asserttrue(int input, int number){
	if (input){
		printf("\tTEST %d SUCCESSFUL\n", number);
	}
	else
		printf("\tTEST %d FAILED\n", number);
	return 0;
}

// compare function for sorting

int cmpfunc	(const void* a, const void* b) {
  if (*(int*)a > *(int*)b)
    return 1;
  if (*(int*)a < *(int*)b)
    return -1;
  return 0;
}

/*
 * Include the following lines in your makefile:
 
unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

Add unittest1 to all: ... line
 */

int main() {
    int success;

    int i;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int otherPlayer = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	printf("----------------- Function: %s ----------------\n", FUNCTION_NAME);
	printf("\nTESTS WITH INITIALIZED CARDS\n");
	printf("TEST 1: Same number of cards before and after\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));


	shuffle(thisPlayer, &testG);
	asserttrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer], 1);


	// ----------- TEST 2: Cards are in a different order --------------

	printf("TEST 2: Cards are in a different order\n");
	for (i = 0; i < testG.deckCount[thisPlayer]; i++){
		if (testG.deck[thisPlayer][i] != G.deck[thisPlayer][i]){
			asserttrue(1, 2);
			success = 0;
			break;
		}
		else{
			success = 1;
		}
		
	}
	if (success == 1){
			asserttrue(0, 2);
		}


	// ----------- TEST 3: Same cards are still in the deck with right counts --------------
	printf("TEST 3: Same cards are still in the deck with right counts\n");

	qsort ((void*)(testG.deck[thisPlayer]), testG.deckCount[thisPlayer], sizeof(int), cmpfunc); 
	qsort ((void*)(	G.deck[thisPlayer]), G.deckCount[thisPlayer], sizeof(int), cmpfunc); 

	for (i = 0; i < testG.deckCount[thisPlayer]; i++){
			if (testG.deck[thisPlayer][i] != G.deck[thisPlayer][i]){

				asserttrue(0, 3);
				success = 0;
			    break;
			}
			else {
				success = 1;
			}
	}
	if (success == 1){
		asserttrue(1, 3);
	}

		// ----------- TEST 4: Testing deck of other player stays the same -----------
	printf("TEST 4: Testing deck of other player stays the same\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	
	shuffle(thisPlayer, &testG);
	for (i = 0; i < testG.deckCount[otherPlayer]; i++){
		if (testG.deck[otherPlayer][i] != G.deck[otherPlayer][i]){

				asserttrue(0, 4);
				success = 0;
			    break;
			}
			else {
				success = 1;
			}
	}
	if (success == 1)
		asserttrue(1, 4);

	printf("\nTESTS AFTER ADDING 3 CARDS TO PLAYER 1\n");
	// ----------- TEST 5: Adding 3 cards and testing count  -----------
	printf("TEST 5: Same number of cards before and after\n");

	G.deckCount[thisPlayer] += 3;

	G.deck[thisPlayer][5] = 8;
	G.deck[thisPlayer][6] = 3;
	G.deck[thisPlayer][7] = 9;

	memcpy(&testG, &G, sizeof(struct gameState));

	shuffle(thisPlayer, &testG);

	asserttrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer], 5);

		// ----------- TEST 6: Adding 3 cards and testing cards are in a different order --------------

	printf("TEST 6: Cards are in a different order\n");
	for (i = 0; i < testG.deckCount[thisPlayer]; i++){
		if (testG.deck[thisPlayer][i] != G.deck[thisPlayer][i]){
			asserttrue(1, 2);
			success = 0;
			break;
		}
		else{
			success = 1;
		}
		
	}
	if (success == 1){
			asserttrue(0, 6);
		}

	// ---------- TEST 7: Adding 3 cards and testing all cards still in deck -----------
	printf("TEST 7: Same cards are still in the deck with right counts\n");

	qsort ((void*)(testG.deck[thisPlayer]), testG.deckCount[thisPlayer], sizeof(int), cmpfunc); 
	qsort ((void*)(	G.deck[thisPlayer]), G.deckCount[thisPlayer], sizeof(int), cmpfunc); 

	for (i = 0; i < testG.deckCount[thisPlayer]; i++){
			if (testG.deck[thisPlayer][i] != G.deck[thisPlayer][i]){

				asserttrue(0, 7);
				success = 0;
			    break;
			}
			else {
				success = 1;
			}
	}
	if (success == 1)
			asserttrue(1, 7);

	// ----------- TEST 8: Testing deck of other player stays the same -----------
	printf("TEST 8: Testing deck of other player stays the same\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	
	shuffle(thisPlayer, &testG);
	for (i = 0; i < testG.deckCount[otherPlayer]; i++){
		if (testG.deck[otherPlayer][i] != G.deck[otherPlayer][i]){

				asserttrue(0, 8);
				success = 0;
			    break;
			}
			else {
				success = 1;
			}
	}
	if (success == 1)
		asserttrue(1, 8);
	return 0;
}

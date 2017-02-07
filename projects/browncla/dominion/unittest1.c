/*unittest1.c */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#define FUNCTION_NAME "shuffle"

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

// ADD FAILURE STATE

int main() {
    int success;

    int i, result, tester1;
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
	printf("TESTS WITH INITIALIZED CARDS\n");
	printf("%s TEST 1: Same number of cards before and after\n", FUNCTION_NAME);

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));


	result = shuffle(thisPlayer, &testG);
	if (result == 0){
		asserttrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer], 1);


		// ----------- TEST 2: Cards are in a different order --------------

		printf("%s TEST 2: Cards are in a different order\n", FUNCTION_NAME);
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
		printf("%s TEST 3: Same cards are still in the deck with right counts\n", FUNCTION_NAME);

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
		printf("%s TEST 4: Deck of other player stays the same\n", FUNCTION_NAME);
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
		}
	else{
		printf("Tests 1-4 could not be run because %s was not performed\n", FUNCTION_NAME);
	}
	printf("\nTESTS AFTER ADDING 3 CARDS TO PLAYER 1\n");
	// ----------- TEST 5: Adding 3 cards and testing count  -----------
	printf("%s TEST 5: Same number of cards before and after\n", FUNCTION_NAME);

	G.deckCount[thisPlayer] += 3;

	G.deck[thisPlayer][5] = 8;
	G.deck[thisPlayer][6] = 3;
	G.deck[thisPlayer][7] = 9;

	memcpy(&testG, &G, sizeof(struct gameState));

	result = shuffle(thisPlayer, &testG);
	if (result == 0){
		asserttrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer], 5);

			// ----------- TEST 6: Adding 3 cards and testing cards are in a different order --------------

		printf("%s TEST 6: Cards are in a different order\n", FUNCTION_NAME);
		for (i = 0; i < testG.deckCount[thisPlayer]; i++){
			if (testG.deck[thisPlayer][i] != G.deck[thisPlayer][i]){
				asserttrue(1, 2);
				success = 1;
				break;
			}
			else{
				success = 0;
			}
			
		}
		if (success == 0){
				asserttrue(0, 6);
			}

		// ---------- TEST 7: Adding 3 cards and testing all cards still in deck -----------
		printf("%s TEST 7: Same cards are still in the deck with right counts\n", FUNCTION_NAME);

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
	printf("%s TEST 8: Deck of other player stays the same\n", FUNCTION_NAME);
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
	}
	else{
		printf("Test 5-8 could not be run because %s was not performed\n", FUNCTION_NAME);
	}

	// ----------- TEST 9: Test failure state of shuffle -----------
	printf("%s TEST 9: Shuffle does not occur when deck is empty\n", FUNCTION_NAME);
	
	G.deckCount[thisPlayer] = 0;
	memcpy(&testG, &G, sizeof(struct gameState));
	result = shuffle(thisPlayer, &testG);
	if (result == -1){
		asserttrue(1, 9);
	}
	else{
		asserttrue(0, 9);
	}
	// ----------- TEST 10: Failure of shuffle does not change state-----------
	printf("%s TEST 10: Failure of shuffle does not change state\n", FUNCTION_NAME);
	if (result == -1){
		//checking card decks are the same before and after
		for (i = 0; i < testG.deckCount[otherPlayer]; i++){
				if (testG.deck[otherPlayer][i] != G.deck[otherPlayer][i]){

					tester1 = 1; // 1 if in different order
					break;
				}
				else {
					tester1 = 0;
				}
		}
		if (testG.deckCount[thisPlayer] != G.deckCount[thisPlayer]){
			asserttrue(0, 10);
		}
		else if (testG.deckCount[otherPlayer] != G.deckCount[otherPlayer]){
			asserttrue(0, 10);
		}
		else if (testG.deckCount[thisPlayer != 0]){
			asserttrue(0, 10);
		}
		else if (tester1){
			asserttrue(0, 10);
		}
		else{
			asserttrue(1, 10);
		}
	}
	return 0;
}

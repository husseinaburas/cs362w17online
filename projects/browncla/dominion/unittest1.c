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
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	printf("----------------- Function: %s ----------------\n", FUNCTION_NAME);

	result = shuffle(thisPlayer, &testG);

	printf("TESTS WITH CURRENT PLAYER'S DECK\n");
	// ----------- TEST 1: Same number of cards before and after --------------
	printf("%s TEST 1: Same number of cards before and after\n", FUNCTION_NAME);
	if (result == 0){
		
		asserttrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer], 1);
	}
	else{
		printf("TEST 1 could not be run due to invalid input\n");
	}


		// ----------- TEST 2: Cards are in a different order --------------
	printf("%s TEST 2: Cards are in a different order\n", FUNCTION_NAME);
	if (result == 0){
		
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
	}
	else{
		printf("TEST 2 could not be run due to invalid input\n");
	}
		// ----------- TEST 3: Same cards are still in the deck with right counts --------------
	printf("%s TEST 3: Same cards are still in the deck with right counts\n", FUNCTION_NAME);
	if (result == 0){	
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
	}
	else{
		printf("TEST 3 could not be run due to invalid input\n");
	}

		// ----------- TEST 4: Testing deck of other player stays the same -----------
	printf("%s TEST 4: Deck of other player stays the same\n", FUNCTION_NAME);
	if (result == 0){
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
		printf("TEST 4 could not be run due to invalid input\n");
	}
	
	printf("\nTESTS WITH NON-PLAYING PLAYER'S DECK\n");
	// ----------- TEST 5: Testing count  -----------
	printf("%s TEST 5: Same number of cards before and after\n", FUNCTION_NAME);

	result = shuffle(otherPlayer, &testG);
	if (result == 0){
		asserttrue(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer], 5);
	}
	else{
		printf("TEST 5 could not be run due to invalid input\n");
	}

	// ----------- TEST 6: Testing cards are in a different order --------------
	printf("%s TEST 6: Cards are in a different order\n", FUNCTION_NAME);
	if (result == 0){
		for (i = 0; i < testG.deckCount[otherPlayer]; i++){
			if (testG.deck[otherPlayer][i] != G.deck[otherPlayer][i]){
				asserttrue(1, 6);
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
	}
	else{
		printf("TEST 6 could not be run due to invalid input\n");
	}

	// ---------- TEST 7: Testing all cards still in deck -----------
	printf("%s TEST 7: Same cards are still in the deck with right counts\n", FUNCTION_NAME);
	if (result == 0){
		qsort ((void*)(testG.deck[otherPlayer]), testG.deckCount[otherPlayer], sizeof(int), cmpfunc); 
		qsort ((void*)(	G.deck[otherPlayer]), G.deckCount[otherPlayer], sizeof(int), cmpfunc); 

		for (i = 0; i < testG.deckCount[otherPlayer]; i++){
				if (testG.deck[otherPlayer][i] != G.deck[otherPlayer][i]){

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
	}
	else{
		printf("TEST 7 could not be run due to invalid input\n");
	}


	// ----------- TEST 8: Testing deck of other player stays the same -----------
	printf("%s TEST 8: Deck of other player stays the same\n", FUNCTION_NAME);
	if (result == 0){
		for (i = 0; i < testG.deckCount[thisPlayer]; i++){
			if (testG.deck[thisPlayer][i] != G.deck[thisPlayer][i]){

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
		printf("TEST 8 could not be run due to invalid input\n");
	}

	printf("\nTESTING INVALID INPUT\n");
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
	else{
		printf("TEST 10 could not be run due to unplanned input\n");
	}
	return 0;
}

/* 
* unittest3.c
*/
/* Unit test for method:
*		int drawCard(
*		int player, 
*		struct gameState *state)	
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//int drawCard(int player, struct gameState *state)
//{
//	int count;
//	int deckCounter;
//	if (state->deckCount[player] <= 0) {//Deck is empty
//
//										//Step 1 Shuffle the discard pile back into a deck
//		int i;
//		//Move discard to deck
//		for (i = 0; i < state->discardCount[player]; i++) {
//			state->deck[player][i] = state->discard[player][i];
//			state->discard[player][i] = -1;
//		}
//
//		state->deckCount[player] = state->discardCount[player];
//		state->discardCount[player] = 0;//Reset discard
//
//										//Shufffle the deck
//		shuffle(player, state);//Shuffle the deck up and make it so that we can draw
//
//		if (DEBUG) {//Debug statements
//			printf("Deck count now: %d\n", state->deckCount[player]);
//		}
//
//		state->discardCount[player] = 0;
//
//		//Step 2 Draw Card
//		count = state->handCount[player];//Get current player's hand count
//
//		if (DEBUG) {//Debug statements
//			printf("Current hand count: %d\n", count);
//		}
//
//		deckCounter = state->deckCount[player];//Create a holder for the deck count
//
//		if (deckCounter == 0)
//			return -1;
//
//		state->hand[player][count] = state->deck[player][deckCounter - 1];//Add card to hand
//		state->deckCount[player]--;
//		state->handCount[player]++;//Increment hand count
//	}
//
//	else {
//		int count = state->handCount[player];//Get current hand count for player
//		int deckCounter;
//		if (DEBUG) {//Debug statements
//			printf("Current hand count: %d\n", count);
//		}
//
//		deckCounter = state->deckCount[player];//Create holder for the deck count
//		state->hand[player][count] = state->deck[player][deckCounter - 1];//Add card to the hand
//		state->deckCount[player]--;
//		state->handCount[player]++;//Increment hand count
//	}
//
//	return 0;
//}


int main()
{
	printf("-------------------------------------------Testing Funtion: drawCard-----------------------------------------\n");
	// Initialize required variables for pre-conditions
	struct gameState G;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	int numPlayers = 2;
	int seed = 1234;

	int initCheck = initializeGame(numPlayers, k, seed, &G);
	assert(initCheck == 0);

	// begin running various tests and checking post-conditions
	int drawCardCheck;
	//set player 
	int player = 0;
	//get the deck count
	int initDeck = G.deckCount[player] + G.discardCount[player];
	int initHandCount = G.handCount[player];
	printf("------------------------------------------Test 1: Initial discard + deck = new deck -----------------------------------------\n");
	//check the deck count 
	assert(initDeck == G.deckCount[player]);

	printf("------------------------------------------Test 2: Discard = 0 -----------------------------------------\n");
	//check the discard =0
	assert(G.discardCount[player]==0);

	printf("------------------------------------------Test 3: Deck count >0 -----------------------------------------\n");
	//check the deck count is >0
	assert(G.deckCount[player]>0);

	printf("------------------------------------------Test 4: HandCount > 0 -----------------------------------------\n");
	//check the hand count 
	assert(G.handCount[player]>0);

	printf("------------------------------------------Test 5: Initial hand count has been increased  -----------------------------------------\n");
	//check the hand count has been increased
	assert(G.handCount[player]==initHandCount+1);
	
	printf("------------------------------------------Test 6: Deck count has been decreases -----------------------------------------\n");
	//check the deck count has been decreased
	assert(G.deckCount[player] == initDeck - 1);
	printf("\n------------------------------------------SUCCESS: TESTING COMPLETE FOR drawCard FUNCTION-----------------------------------------\n\n");
}
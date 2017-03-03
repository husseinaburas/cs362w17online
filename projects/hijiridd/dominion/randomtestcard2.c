// ***************
// * assignment4
// * randomtestcard1.c
// * Desc: random tester for VILLAGE card for dominion.c
//****************
#include "dominion.h"
#include "dominion_helpers.h"
#include "dominion_refactorwk2.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int getRandIntLowHigh (int low, int high);
int printGameState (struct gameState * G);
int randomGameInit (int p, int * k, int r, struct gameState * G);
int fillValidCards (int k[10], int p, struct gameState * G);
int chooseCard (int k[10]);
int randomizeSupply (struct gameState * G);
int checkVillage (int p, struct gameState * G);


int getRandIntLowHigh (int low, int high) {
	//srand(time(NULL));
	int randInt = (rand()%(high+1-low))+low;
	return randInt;
}

// *********************
// For debugging, this prints out all variables of the game state
// *********************
int printGameState (struct gameState * G) {
	int i, p, j;
	int totalsupply = 0;
	printf ("\n--START PRINTING GAME STATE -------------------\n");
	printf ("numPlayers = %d\n", G->numPlayers);
	for (i = 0; i< (treasure_map+1); i++) {	totalsupply += G->supplyCount[i]; }
	printf ("SUPPLY TOTAL=%d, supplyCount: ", totalsupply);
	for (i = 0; i< (treasure_map+1); i++) {	printf ("#%d: %d, ", i, G->supplyCount[i]); }
	printf ("\n");
	printf ("embargoTokens: ");
	for (i = 0; i< (treasure_map+1); i++) { printf ("#%d: %d, ", i, G->embargoTokens[i]); }
	printf ("\n");
	printf ("outpostPlayed = %d, ", G->outpostPlayed);
	printf ("outpostTurn = %d, ", G->outpostTurn);
	printf ("whoseTurn = %d, ", G->whoseTurn);
	printf ("phase = %d, ", G->phase);
	printf ("numActions = %d, ", G->numActions);
	printf ("coins = %d, ", G->coins);
	printf ("numBuys = %d\n", G->numBuys);
	printf ("playedCardCount = %d, playedCards[x]: ", G->playedCardCount);
	for (j=0; j< (G->playedCardCount); j++) { printf ("[%d] = %d", j, G->playedCards[j]);}
	printf ("\n");
	for (p=0; p< G->numPlayers; p++) {
		printf ("---------------------\n");
		int handCount = G->handCount[p];
		printf ("PLAYER #%d, HANDCOUNT=%d, hand[player][hand]: ", p, handCount);
		for (j = 0; j<handCount; j++) { printf("[%d][hand:%d] = %d, ",p,j,G->hand[p][j]);}
		printf ("\n");
		int deckCount = G->deckCount[p];
		printf ("PLAYER #%d, DECKCOUNT=%d, deck[player][hand]: ", p, deckCount);
		for (j = 0; j<deckCount; j++) {printf("[%d][deck:%d] = %d, ",p,j,G->deck[p][j]);}
		printf ("\n");
		int discardCount = G->discardCount[p];
		printf ("PLAYER #%d, DISCARDCOUNT=%d, discard[player][hand]: ", p, discardCount);
		for (j = 0; j<discardCount; j++) {printf("[%d][discard: %d] = %d, ",p,j,G->discard[p][j]);}
		printf ("\n");
	}
	printf ("--END PRINTING GAME STATE -------------------\n\n");
	return 0;
}


int randomGameInit (int p, int k[10], int r, struct gameState * G) {
	int response = initializeGame (p, k, r, G);
	return response;
}

int chooseCard (int k[10]) {
	int response = getRandIntLowHigh (0, 26);
	return response;
}

// *********************
// This systematically fills deck, hand, and discard with cards
// *********************
int fillValidCards (int k[10], int p, struct gameState * G) {
	int i;

	// fill hand, track if Village in hand
	int villageInHand = 0;
	for (i=0; i<G->handCount[p]; i++){
		G->hand[p][i] = chooseCard(k);
		if (G->hand[p][i] == village) {
			villageInHand++;
		}
	}
	// bias to add village in hand
	// check if no card in hand, then 75% of the time add it to hand
	if (villageInHand == 0) {
		//printf ("*** Found no village in hand for player %i***\n", p);
		if (getRandIntLowHigh(0,3) > 0){ // 75% of the time add
			// pick random spot in hand
			if (G->handCount[p] > 0){
				i = getRandIntLowHigh (0, (G->handCount[p]-1));
				// replace with village
				G->hand[p][i] = village;
				//printf ("*** add village hand player %i, position %i***\n", p, i);
			}
		}
	}
	return 0;
}

int randomizeSupply (struct gameState * G) {
	G->supplyCount[curse] = getRandIntLowHigh (0, 30);
	G->supplyCount[estate] = getRandIntLowHigh (0, 12);
	G->supplyCount[duchy] = getRandIntLowHigh (0, 12);
	G->supplyCount[province] = getRandIntLowHigh (0, 12);
	G->supplyCount[copper] = getRandIntLowHigh (0, 60);
	G->supplyCount[silver] = getRandIntLowHigh (0, 40);
	G->supplyCount[gold] = getRandIntLowHigh (0, 30);
	int i;
	for (i=adventurer; i<=treasure_map; i++){
		G->supplyCount[i] = getRandIntLowHigh (-1, 12);
	}
	return 0;
}

// **********************
// tests for VILLAGE
// **********************
int checkVillage(int p, struct gameState * G) {
	int errorval = 0;
	int testresponse, controlresponse;
	int response;
	testresponse = 0; controlresponse = 0; response = 0; // to silence unused var warning

	struct gameState Gpre, Gcontrol;
	// Create a pre and control Game state that is copy of G
	memcpy (&Gpre, G, sizeof(struct gameState));
	memcpy (&Gcontrol, G, sizeof(struct gameState));

	G->whoseTurn = p; // setting the turn of the player to play card

	// find the location of card in player p's hand
	int handPos = -1; // default is that there is no village in hand
	int c;
	for (c=0; c < G->handCount[p]; c++) {
		if (G->hand[p][c] == village) { handPos = c; }
	}
	if (handPos == -1) {
		printf ("NOTE Player %d: did NOT find Village in player's hand\n", p);
		//printGameState (G);
	}

	// call the function to test
	int card = village;
	int choice1 = 0; // not used for village
	int choice2 = 0; // not used for village
	int choice3 = 0; // not used for village
	int bonus = 0;  // not used for village
	testresponse =  cardEffect (card, choice1, choice2, choice3, G,
								handPos, &bonus);

	//Test1: check if played card has increased corectly
	printf ("Test1 (check played card change): ");
	if (handPos > -1) {
		if ((G->playedCardCount - Gpre.playedCardCount) == 1) {
			printf ("SUCCESS: player #%d, check if played card has increased by 1\n", p);
		} else {
			printf ("FAILED: player #%d, check if played card has increased by 1\n", p);
			printf ("Debug: G->playedCardCount: %d, Gpre.playedCardCount: %d\n", G->playedCardCount, Gpre.playedCardCount);
			errorval--;
		}
	} else { // if no Village card to play, played card should be zero
		if ((G->playedCardCount - Gpre.playedCardCount) == 0) {
			printf ("SUCCESS: player #%d, check if played card has increased by 0\n", p);
		} else {
			printf ("FAILED: player #%d, check if played card has increased by 0\n", p);
			printf ("Debug: G->playedCardCount: %d, Gpre.playedCardCount: %d\n", G->playedCardCount, Gpre.playedCardCount);
			errorval--;
		}
	}

	//  Test2: check if total supply count has not changed
	int supplyTotalPost = 0;
	int supplyTotalPre = 0;
	for (c=0; c < (treasure_map+1); c++) {
		supplyTotalPost += G->supplyCount[c];
		supplyTotalPre += Gpre.supplyCount[c];
		//printf ("supplyTotalPost: %d, supplyTotalPre:%d\n", supplyTotalPost, supplyTotalPre);
	}
	printf ("Test2 (check supply count): ");
	if ((supplyTotalPost - supplyTotalPre) == 0) {
		printf ("SUCCESS: player #%d, check if total supply count has not changed\n", p);
	} else {
		printf ("FAILED: player #%d, check if total supply count has not changed\n", p);
		printf ("Debug Data: supplyTotalPost: %d, supplyTotalPre: %d\n", supplyTotalPost, supplyTotalPre);
		errorval--;
	}

	// Test3: check if hand count went up currently
	printf ("Test3 (check hand count): ");
	if (handPos > -1) { // if there is a Village card
		if ((G->handCount[p] - Gpre.handCount[p]) == 0) {
			printf ("SUCCESS: player #%d, check if hand count is unchanged (minus Village + 1 card)\n", p);
		} else {
			printf ("FAILED: player #%d, check if hand count is unchanged (minus Village + 1 card)\n", p);
			printf ("G->handCount[p]: %d, Gpre.handCount[p]: %d\n", G->handCount[p], Gpre.handCount[p]);
			errorval--;
		}
	} else { // if no card to play, hand count should not change
		if ((G->handCount[p] - Gpre.handCount[p]) == 0) {
			printf ("SUCCESS: player #%d, check if hand count has not changed\n", p);
		} else {
			printf ("FAILED: player #%d, check if hand count has not changed\n", p);
			printf ("Debug Data: G->handCount[p]: %d, Gpre.handCount[p]: %d\n", G->handCount[p], Gpre.handCount[p]);
			errorval--;
		}
	}

	// Test4: check deck+discard count decreased
	printf ("Test4 (check deck + discard count): ");
	if (handPos > -1) { // if card exists
		if (((G->deckCount[p] + G->discardCount[p]) - (Gpre.deckCount[p] + Gpre.discardCount[p])) == -1) {
			printf ("SUCCESS: player #%d, check deck+discard count decreased 1 (1 card moved to hand)\n", p);
		} else {
			printf ("FAILED: player #%d, check deck+discard count decreased 1 (1 card moved to hand)\n", p);
			printf ("Debug Data: G->deckCount[p] + G->discardCount[p]): %d, (Gpre.deckCount[p] + Gpre.discardCount[p]): %d\n",
					(G->deckCount[p] + G->discardCount[p]), (Gpre.deckCount[p] + Gpre.discardCount[p]) );
			errorval--;
		}
	} else { // if no Village card to play no change
		if ((G->deckCount[p] - Gpre.deckCount[p]) == 0) {
			printf ("SUCCESS: player #%d, check if deck count has not changed\n", p);
		} else {
			printf ("FAILED: player #%d, check if deck+discard count has not changed\n", p);
			printf ("Debug Data: G->deckCount[p] + G->discardCount[p]): %d, (Gpre.deckCount[p] + Gpre.discardCount[p]): %d\n",
					(G->deckCount[p] + G->discardCount[p]), (Gpre.deckCount[p] + Gpre.discardCount[p]) );
			errorval--;
		}
	}


	// Test5: check if numActions is changed
	printf ("Test5 (check num Actions: ");
	if (handPos > -1) { // if card exists
		if ((G->numActions - Gpre.numActions) == 1) {
			printf ("SUCCESS: player #%d, numActions increased +1 (minus 1 for Village, +2 new) \n", p);
		} else {
			printf ("FAILED: player #%d, numActions increased +1 (minus 1 for Village, +2 new)\n", p);
			printf ("G->numActions: %d, Gpre.numActions: %d\n", G->numActions, Gpre.numActions);
			errorval--;
		}
	} else { // if no Village card to play no change
		if ((G->numActions - Gpre.numActions) == 0) {
			printf ("SUCCESS: player #%d, check if numActions has not changed\n", p);
		} else {
			printf ("FAILED: player #%d, check if numActions has not changed\n", p);
			printf ("G->numActions: %d, Gpre.numActions: %d\n", G->numActions, Gpre.numActions);
			errorval--;
		}
	}

	return errorval;
}


int main () {
	printf ("Starting ramdom test for VILLAGE\n\n");
	// NOTE: MAX_HAND = 500, MAX_DECK = 500, MAX_PLAYERS = 4
	srand((unsigned int)time(NULL)); // set random seed with clock
	// PART A: Randomize initial inputs for creating base game configuration
	// Inputs to set up a game include:
	// # of players p (0, 1, 2, 3, 4...)

	int player = getRandIntLowHigh(1,4); // default # players to be replaced later

	printf ("player # = %i\n", player);

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	           sea_hag, smithy, treasure_map}; // default hand to be replaced
	struct gameState G; // test game state
	memset(&G, 23, sizeof(struct gameState)); // resets game memory
	printf ("created new game state G\n");

	int response;

	// LOOP OVER NUMBER OF RANDOM INITIAL GAME STATE
	int numGame;
	for (numGame=0; numGame < 1000; numGame++) {
		printf ("------------ ITERATION # %i\n", numGame);
		int randSeed = getRandIntLowHigh(1,10000);
		response = randomGameInit (player, k, randSeed, &G); // -1 for PutSeed func. x<0, state from system clock
		if (response == -1) {
			printf ("not a valid game state, randSeed = %d\n", randSeed);
			continue; // it means this was not a valid game state so continue on with for loop.
		}
		//printf ("response = %i\n", response);

		// PART B: Given an initialized game state, randomize the state of play.
		// Inputs we consider for state of play

		//randomly select a player
		int numPlayer = G.numPlayers;
		int p = getRandIntLowHigh (0, numPlayer-1);

		//printf ("numPlayer = %i, random player = %i\n", numPlayer, p);

		// ------------------------------
		//for given player, set deckCount, disardCount, and handCount
		// ------------------------------
		//G.deckCount[p] = getRandIntLowHigh (0, MAX_DECK);
		//G.discardCount[p] = getRandIntLowHigh (0, MAX_DECK);
		//G.handCount[p] = getRandIntLowHigh (0, MAX_HAND);
		G.deckCount[p] = getRandIntLowHigh (0, 5);
		G.discardCount[p] = getRandIntLowHigh (0, 5);
		G.handCount[p] = getRandIntLowHigh (0, 5);

		// ------------------------------
		//for given player, deck, discard and hand counts, fill with random cards
		// ------------------------------
		fillValidCards (k, p, &G);
		randomizeSupply (&G);
		//printGameState (&G);

		response = checkVillage (p, &G);
		if (response == 0) {
			printf ("Village test - iteration %i -> successfully passed tests\n", numGame);
		} else {
			printf ("Village test - iteration %i -> FAILED tests\n", numGame);
			//printGameState (&G);
		}

	}
	return 0;
}







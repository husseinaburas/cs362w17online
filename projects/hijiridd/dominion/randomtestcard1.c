// ***************
// * assignment4
// * randomtestcard1.c
// * Desc: random tester for SMITHY card for dominion.c
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
int checkSmithy (int p, struct gameState * G);


int getRandIntLowHigh (int low, int high) {
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

	// fill hand, track if smithy in hand
	int smithyInHand = 0;
	for (i=0; i<G->handCount[p]; i++){
		G->hand[p][i] = chooseCard(k);
		if (G->hand[p][i] == smithy) {
			smithyInHand++;
		}
	}
	// bias to add smithy in hand
	// check if no smithy card in hand, then 75% of the time add it to hand
	if (smithyInHand == 0) {
		//printf ("*** Found no smithy in hand for player %i***\n", p);
		if (getRandIntLowHigh(0,3) > 0){ // 75% of the time add
			// pick random spot in hand
			if (G->handCount[p] > 0){
				i = getRandIntLowHigh (0, (G->handCount[p]-1));
				// replace with smithy
				G->hand[p][i] = smithy;
				//printf ("*** add smithy hand player %i, position %i***\n", p, i);
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
// tests for SMITHY
// **********************
int checkSmithy (int p, struct gameState * G) {
	int errorval = 0;
	int testresponse, controlresponse;
	int response;
	testresponse = 0; controlresponse = 0; response = 0; // to silence unused var warning

	struct gameState Gpre, Gcontrol;
	// Create a pre and control Game state that is copy of G
	memcpy (&Gpre, G, sizeof(struct gameState));
	memcpy (&Gcontrol, G, sizeof(struct gameState));

	G->whoseTurn = p; // setting the turn of the player to play

	// find the location of card in player p's hand
	int handPos = -1; // default is that there is no smithy in hand
	int c;
	for (c=0; c < G->handCount[p]; c++) {
		if (G->hand[p][c] == smithy) { handPos = c; }
	}
	if (handPos == -1) {
		printf ("NOTE Player %d: did NOT find Smithy in player's hand\n", p);
		//printGameState (G);
	}

	// call the function to test
	int card = smithy;
	int choice1 = 0; // not used for smithy
	int choice2 = 0; // not used for smithy
	int choice3 = 0; // not used for smithy
	int bonus = 0;  // not used for smithy
	testresponse =  cardEffect (card, choice1, choice2, choice3, G,
								handPos, &bonus);

	//Test1: check if played card has increased by 1 (or zero if no smithy)
	printf ("Test1 (check played card change): ");
	if (handPos > -1) {
		if ((G->playedCardCount - Gpre.playedCardCount) == 1) {
			printf ("SUCCESS: player #%d, check if played card has increased by 1\n", p);
		} else {
			printf ("FAILED: player #%d, check if played card has increased by 1\n", p);
			printf ("Debug: G->playedCardCount: %d, Gpre.playedCardCount: %d\n", G->playedCardCount, Gpre.playedCardCount);
			errorval--;
		}
	} else { // if no Smithy card to play, played card should be zero
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
	if (handPos > -1) { // if there is a Smithy card
		if ((G->handCount[p] - Gpre.handCount[p]) == 2) {
			printf ("SUCCESS: player #%d, check if hand count went up by 2 (minus Smith + 3 cards)\n", p);
		} else {
			printf ("FAILED: player #%d, check if hand count went up by 2 (minus Smith + 3 cards)\n", p);
			printf ("Debug Data: G->handCount[p]: %d, Gpre.handCount[p]: %d\n", G->handCount[p], Gpre.handCount[p]);
			errorval--;
		}
	} else { // if no Smithy card to play, hand count should not change
		if ((G->handCount[p] - Gpre.handCount[p]) == 0) {
			printf ("Test3: SUCCESS: player #%d, check if hand count has not changed\n", p);
		} else {
			printf ("Test3: FAILED: player #%d, check if hand count has not changed\n", p);
			printf ("Debug Data: G->handCount[p]: %d, Gpre.handCount[p]: %d\n", G->handCount[p], Gpre.handCount[p]);
			errorval--;
		}
	}


	// Test4: check deck+discard count decreased
	printf ("Test4 (check deck + discard count): ");
	if (handPos > -1) { // if there is a Smithy card
		if (((G->deckCount[p] + G->discardCount[p]) - (Gpre.deckCount[p] + Gpre.discardCount[p])) == -3) {
			printf ("SUCCESS: player #%d, check deck+discard count decreased 3 (only 3 cards moved to hand)\n", p);
		} else {
			printf ("FAILED: player #%d, check deck+discard count decreased 3 (only 3 cards moved to hand)\n", p);
			printf ("Debug Data: G->deckCount[p] + G->discardCount[p]): %d, (Gpre.deckCount[p] + Gpre.discardCount[p]): %d\n",
					(G->deckCount[p] + G->discardCount[p]), (Gpre.deckCount[p] + Gpre.discardCount[p]) );
			errorval--;
		}
	} else { // if no Smithy card to play no change
		if ((G->deckCount[p] - Gpre.deckCount[p]) == 0) {
			printf ("SUCCESS: player #%d, no Smithy card, check if deck count has not changed\n", p);
		} else {
			printf ("FAILED: player #%d, no Smithy card, check if deck+discard count has not changed\n", p);
			printf ("Debug Data: G->deckCount[p] + G->discardCount[p]): %d, (Gpre.deckCount[p] + Gpre.discardCount[p]): %d\n",
					(G->deckCount[p] + G->discardCount[p]), (Gpre.deckCount[p] + Gpre.discardCount[p]) );
			errorval--;
		}
	}
	return errorval;
}


int main () {
	printf ("Starting ramdom test for SMITHY\n\n");
	// NOTE: MAX_HAND = 500, MAX_DECK = 500, MAX_PLAYERS = 4
	// set a reandom seed with time ??  srand((unsigned int)time(NULL));
	// PART A: Randomize initial inputs for creating base game configuration
	// Inputs to set up a game include:
	// # of players p (0, 1, 2, 3, 4...)
	// initial 10 cards chosen from 20 cards (#7 through 26) # of combinations C(20, 10) = 184,756

	// Debug random number
	/* int i;
	for (i=0; i<100; i++) { printf ("%i ", getRandIntLowHigh (0, 10));}
	printf ("\n\n");
	*/

	int player = getRandIntLowHigh(1,4); // default # players to be replaced later
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	           sea_hag, smithy, treasure_map}; // default hand to be replaced
	struct gameState G; // test game state
	memset(&G, 23, sizeof(struct gameState)); // resets game memory
	int randSeed = 1; // to be replaced
	int response;

	// LOOP OVER NUMBER OF RANDOM INITIAL GAME STATE
	int numGame;
	for (numGame=0; numGame < 100; numGame++) {
		printf ("------------ ITERATION # %i\n", numGame);
		response = randomGameInit (player, k, randSeed, &G);
		//printf ("response = %i\n", response);

		// PART B: Given an initialized game state, randomize the state of play.
		// Inputs we consider for state of play

		//radomly select a player
		int numPlayer = G.numPlayers;
		int p = getRandIntLowHigh (0, numPlayer-1);

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

		response = checkSmithy (p, &G);
		if (response == 0) {
			printf ("Smithy test - iteration %i -> successfully passed tests\n", numGame);
		} else {
			printf ("Smithy test - iteration %i -> FAILED tests\n", numGame);
			//printGameState (&G);
		}

	}
	return 0;
}





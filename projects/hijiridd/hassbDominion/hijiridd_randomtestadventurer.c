// ***************
// * assignment5
// * hijiridd_randomtestadventurer.c
// * Desc: random tester for adventurer card for dominion.c
//****************
#include "dominion.h"
#include "dominion_helpers.h"
//#include "dominion_refactorwk2.h"
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
int checkAdventurer (int p, struct gameState * G);


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

	// fill hand, track if adventurer in hand
	int adventurerInHand = 0;
	for (i=0; i<G->handCount[p]; i++){
		G->hand[p][i] = chooseCard(k);
		if (G->hand[p][i] == adventurer) {
			adventurerInHand++;
		}
	}
	// bias to add an adventure card in hand
	// check if no adventure card in hand, then 75% of the time add it to hand
	if (adventurerInHand == 0) {
		//printf ("*** Found no adventurer in hand for player %i***\n", p);
		if (getRandIntLowHigh(0,3) > 0){ // 75% of the time ad adventurer
			// pick random spot in hand
			if (G->handCount[p] > 0){
				i = getRandIntLowHigh (0, (G->handCount[p]-1));
				// replace with adventurer
				G->hand[p][i] = adventurer;
				//printf ("*** add adventurer hand player %i, position %i***\n", p, i);
			}
		}
	}

	// fill discard, track if treasure card
	int treasureInDiscard = 0;
	for (i=0; i<G->discardCount[p]; i++){
		G->discard[p][i] = chooseCard(k);
		if ((G->discard[p][i] == copper) || (G->discard[p][i] == silver) ||
				(G->discard[p][i] == gold))  {
			treasureInDiscard++;
			//printf ("i = i%/n", i);
		}
	}
	// fill deck, track if treasure card exists
	int treasureInDeck = 0;
	for (i=0; i<G->deckCount[p]; i++){
		G->deck[p][i] = chooseCard(k);
		if ((G->deck[p][i] == copper) || (G->deck[p][i] == silver) ||
				(G->deck[p][i] == gold))  {
			treasureInDeck++;
			//printf ("i = i%/n", i);
		}
	}

	// bias to add 2 treasure cards if no treasure cards in deck or discard
	// 90% of time, add 2 treasure cards to deck or discard
	//printf ("treasure Deck: %i, treasure discard: %i\n", treasureInDeck, treasureInDiscard);
	if ((treasureInDeck + treasureInDiscard) < 2) {
		//printf ("*** Found less than 2 treasure for player %i***\n", p);
		int addScenario = getRandIntLowHigh(0,10);
		switch (addScenario) {
			case 0: // do nothing
				break;
			case 1 : // add 1 treasure to deck
				if (G->deckCount[p] > 0){
					i = getRandIntLowHigh (0, (G->deckCount[p]-1));
					// replace with copper(4), silver(5) or gold (6)
					G->deck[p][i] = getRandIntLowHigh(4,6);
					//printf ("*** add treasure to deck player %i, position %i, card %i***\n", p,i,G->deck[p][i]);
				}
				break;
			case 2 : // add 1 treasure to discard
				if (G->discardCount[p] > 0){
					i = getRandIntLowHigh (0, (G->discardCount[p]-1));
					// replace with copper(4), silver(5) or gold (6)
					G->discard[p][i] = getRandIntLowHigh(4,6);
					//printf ("*** add treasure to discard player %i, position %i, card %i***\n", p,i,G->discard[p][i]);
				}
				break;
			case 3 : // add 2 treasure to deck
				if (G->deckCount[p] > 2){
					// pick the top of the deck
					i = 0;
					// replace with copper(4), silver(5) or gold (6)
					G->deck[p][i] = getRandIntLowHigh(4,6);
					//printf ("*** add treasure to deck player %i, position %i, card %i***\n", p,i,G->deck[p][i]);
					i = G->deckCount[p]-1;
					// replace with copper(4), silver(5) or gold (6)
					G->deck[p][i] = getRandIntLowHigh(4,6);
					//printf ("*** add treasure to deck player %i, position %i, card %i***\n", p,i,G->deck[p][i]);
				}
				break;

			case 4 : // add 2 treasure to discard
				if (G->discardCount[p] > 2){
					// pick the top of the deck
					i = 0;
					// replace with copper(4), silver(5) or gold (6)
					G->deck[p][i] = getRandIntLowHigh(4,6);
					//printf ("*** add treasure to discard player %i, position %i, card %i***\n", p,i,G->discard[p][i]);
					i = G->discardCount[p]-1;
					// replace with copper(4), silver(5) or gold (6)
					G->deck[p][i] = getRandIntLowHigh(4,6);
					//printf ("*** add treasure to discard player %i, position %i, card %i***\n", p,i,G->discard[p][i]);
				}
				break;

			default : // add 1 treasure to deck, add 1 to discard
				if (G->deckCount[p] > 0){
					i = getRandIntLowHigh (0, (G->deckCount[p]-1));
					// replace with copper(4), silver(5) or gold (6)
					G->deck[p][i] = getRandIntLowHigh(4,6);
					//printf ("*** add treasure to deck player %i, position %i, card %i***\n", p,i,G->deck[p][i]);
				}
				if (G->discardCount[p] > 0){
					i = getRandIntLowHigh (0, (G->discardCount[p]-1));
					// replace with copper(4), silver(5) or gold (6)
					G->discard[p][i] = getRandIntLowHigh(4,6);
					//printf ("*** add treasure to discard player %i, position %i, card %i***\n", p,i,G->discard[p][i]);
				}
				break;

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


// **************** TODO FIX TESTS FOR ADVENTURER **********************

// **********************
// tests for Adventurer
// **********************
int checkAdventurer (int p, struct gameState * G) {
	int errorval = 0;
	int testresponse, controlresponse;
	int response;
	testresponse = 0; controlresponse = 0; response = 0; // to silence unused var warning

	struct gameState Gpre, Gcontrol;
	// Create a pre and control Game state that is copy of G
	memcpy (&Gpre, G, sizeof(struct gameState));
	memcpy (&Gcontrol, G, sizeof(struct gameState));

	G->whoseTurn = p; // setting the turn of the player to play Adventurer

	// find the location of adventurer in player p's hand
	int handPos = -1; // default is that there is no adventurer in hand
	int c;
	for (c=0; c < G->handCount[p]; c++) {
		if (G->hand[p][c] == adventurer) { handPos = c; }
	}
	if (handPos == -1) {
		printf ("NOTE Player %d: did NOT find Adventurer in player's hand\n", p);
		//printGameState (G);
	}

	// find # of treasure cards in player's deck
	int treasureDeckCount = 0;
	for (c=0; c < G->deckCount[p]; c++) {
		if ((G->deck[p][c] == copper) ||(G->deck[p][c] == silver) ||
				(G->deck[p][c] == gold)) { treasureDeckCount++; }
	}
	if (treasureDeckCount == 0) {
		printf ("NOTE Player %d: did NOT find treasure in player's deck\n", p);
		//printGameState (G);
	}

	// find # of treasure cards in player's discard
	int treasureDiscardCount = 0;
	for (c=0; c < G->discardCount[p]; c++) {
		if ((G->discard[p][c] == copper) ||(G->discard[p][c] == silver) ||
				(G->discard[p][c] == gold)) { treasureDiscardCount++; }
	}
	if (treasureDiscardCount == 0) {
		printf ("NOTE Player %d: did NOT find treasure in player's discard\n", p);
		//printGameState (G);
	}

	int totalTreasure = treasureDeckCount + treasureDiscardCount;
	if (totalTreasure == 0) {
		printf ("NOTE Player %d: did NOT find treasure in player's DISCARD + DECK *********\n", p);
		printGameState (G);
	} else {
		printf ("NOTE Player %d: found %i treasure in player's DISCARD + DECK\n", p, totalTreasure);
	}


	// call the function to test
	int card = adventurer;
	int choice1 = 0; // not used for Adventurer
	int choice2 = 0; // not used for Adventurer
	int choice3 = 0; // not used for Adventurer
	int bonus = 0;  // not used for Adventurer
	testresponse =  cardEffect(card, choice1, choice2, choice3, G,
									handPos, &bonus);
	//controlresponse = myOwnTreasureMap (p, &Gcontrol, handPos);

	//test1: check if played card has increased by 1 (or zero if no adventurer)
	printf ("Test1 (check played card change): ");
	if (handPos > -1) {
		if ((G->playedCardCount - Gpre.playedCardCount) == 1) {
			printf ("SUCCESS: player #%d, check if played card has increased by 1\n", p);
		} else {
			printf ("FAILED: player #%d, check if played card has increased by 1\n", p);
			printf ("Debug: G->playedCardCount: %d, Gpre.playedCardCount: %d\n", G->playedCardCount, Gpre.playedCardCount);
			errorval--;
		}
	} else { // if no adventurer card to play, played card should be zero
		if ((G->playedCardCount - Gpre.playedCardCount) == 0) {
			printf ("SUCCESS: player #%d, check if played card has increased by 0\n", p);
		} else {
			printf ("FAILED: player #%d, check if played card has increased by 0\n", p);
			printf ("Debug: G->playedCardCount: %d, Gpre.playedCardCount: %d\n", G->playedCardCount, Gpre.playedCardCount);
			errorval--;
		}
	}

	//  test2: check if total supply count has not changed
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
		//printf("Printing Pre Game State \n");
		//printGameState (&Gpre);
		//printf ("Printing Post Game State \n");
		//printGameState(G);
	}


	//  test3: check if hand count changed correctly
	printf ("Test3 (check hand count): ");
	if ((handPos > -1) && (totalTreasure > 1)) {
		// with 2 treasure cards
		//  test3: check if hand count went up by 1 (minus Adventurer + 2 treasure cards)
		if ((G->handCount[p] - Gpre.handCount[p]) == 1) {
			printf ("SUCCESS: player #%d, check if hand count went up by 1 (minus Adventurer + 2 treasure cards)\n", p);
		} else {
			printf ("FAILED: player #%d, check if hand count went up by 1 (minus Adventurer + 2 treasure cards)\n", p);
			printf ("Debug Data: G->handCount[p]: %d, Gpre.handCount[p]: %d\n", G->handCount[p], Gpre.handCount[p]);
			//printf("Printing Pre Game State \n");
			//printGameState (&Gpre);
			//printf ("Printing Post Game State \n");
			//printGameState(G);
			errorval--;
		}
	} else if ((handPos > -1) && (treasureDeckCount+treasureDiscardCount > 0)) {
		// hand count should go down by 0 (minus adventurer + 1 treasure)
		if ((G->handCount[p] - Gpre.handCount[p]) == 0) {
			printf ("SUCCESS: player #%d, check if hand count went up by 0 (minus Adventurer + 1 treasure cards)\n", p);
		} else {
			printf ("FAILED: player #%d, check if hand count went up by 0 (minus Adventurer + 1 treasure cards)\n", p);
			printf ("Debug Data: G->handCount[p]: %d, Gpre.handCount[p]: %d\n", G->handCount[p], Gpre.handCount[p]);
			//printf("Printing Pre Game State \n");
			//printGameState (&Gpre);
			//printf ("Printing Post Game State \n");
			//printGameState(G);
			errorval--;
		}
	} else if (handPos > -1) {
		// hand count should go down by 1 (minus adventurer)
		if ((G->handCount[p] - Gpre.handCount[p]) == -1) {
			printf ("SUCCESS: player #%d, check if hand count went up by -1 (minus Adventurer)\n", p);
		} else {
			printf ("FAILED: player #%d, check if hand count went up by -1 (minus Adventurer)\n", p);
			printf ("Debug Data: G->handCount[p]: %d, supplyTotalPre: %d\n", G->handCount[p], Gpre.handCount[p]);
			errorval--;
			//printf("Printing Pre Game State \n");
			//printGameState (&Gpre);
			//printf ("Printing Post Game State \n");
			//printGameState(G);
		}
	} else {
		printf ("********** no assert performed\n");
	}

	//  test4: check deck+discard count decreased 2 (only 2 treasure moves to hand, rest are discard)
	printf ("Test4 (check deck+discard count): ");
	if ((handPos > -1) && (totalTreasure > 1)){
		if (((G->deckCount[p] + G->discardCount[p]) - (Gpre.deckCount[p] + Gpre.discardCount[p])) == -2) {
			printf ("branch-1 SUCCESS: player #%d, check deck+discard count decreased 2 (only 2 treasure moves to hand, rest are discard)\n", p);
		} else {
			printf ("branch-1 FAILED: player #%d, ccheck deck+discard count decreased 2 (only 2 treasure moves to hand, rest are discard)\n", p);
			printf ("(G->deckCount[p] + G->discardCount[p]): %d, (Gpre.deckCount[p] + Gpre.discardCount[p]): %d\n",
						(G->deckCount[p] + G->discardCount[p]), (Gpre.deckCount[p] + Gpre.discardCount[p]));
			errorval--;
			//printf("Printing Pre Game State \n");
			//printGameState (&Gpre);
			//printf ("Printing Post Game State \n");
			//printGameState(G);
		}
	} else if ((handPos > -1) && (totalTreasure > 0)) {
		// check deck+discard count decreased 1 (only 1 treasure moves to hand, rest are discard)
		if (((G->deckCount[p] + G->discardCount[p]) - (Gpre.deckCount[p] + Gpre.discardCount[p])) == -1) {
			printf ("branch-2 SUCCESS: player #%d, check deck+discard count decreased 1 (only 1 treasure moves to hand, rest are discard)\n", p);
		} else {
			printf ("branch-2 FAILED: player #%d, ccheck deck+discard count decreased 1 (only 1 treasure moves to hand, rest are discard)\n", p);
			printf ("(G->deckCount[p] + G->discardCount[p]): %d, (Gpre.deckCount[p] + Gpre.discardCount[p]): %d\n",
						(G->deckCount[p] + G->discardCount[p]), (Gpre.deckCount[p] + Gpre.discardCount[p]));

			errorval--;
			//printf("Printing Pre Game State \n");
			//printGameState (&Gpre);
			//printf ("Printing Post Game State \n");
			//printGameState(G);
		}
	} else if (handPos > -1) {
		// check deck+discard count decreased 0 (only 0 treasure moves to hand, rest are discard)
		if (((G->deckCount[p] + G->discardCount[p]) - (Gpre.deckCount[p] + Gpre.discardCount[p])) == 0) {
			printf ("branch-3 SUCCESS: player #%d, check deck+discard count decreased 0 (only 0 treasure moves to hand, rest are discard)\n", p);
		} else {
			printf ("branch-3 FAILED: player #%d, check deck+discard count decreased 0 (only 0 treasure moves to hand, rest are discard)\n", p);
			errorval--;
			//printf("Printing Pre Game State \n");
			//printGameState (&Gpre);
			//printf ("Printing Post Game State \n");
			//printGameState(G);
		}
	} else {
		printf ("********** no assert performed\n");
	}


	//  test5: check if top 2 cards of hand are treasure cards
	// in this case top 2 cards in hand correspond to highest index in deck array with a valid card
	// loop backward from top of hand
	printf ("Test5 (check top cards of hand): ");
	int topHand = G->handCount[p];
	printf ("topHand == %d\n", topHand);
	if ((handPos > -1) && (totalTreasure > 1)) { // if treasure exists and 2 treasure cards exists
		int d;
		int treasureCounter = 0;
		for (d = 1; d <= 2; d++) {
			if ((G->hand[p][ topHand - d ] == gold) || (G->hand[p][ topHand - d ] == silver) || (G->hand[p][ topHand - d ] == copper)) {
						treasureCounter++; }
		}
		if (treasureCounter == 2) {
			printf ("Branch-1 SUCCESS: player #%d, check if top 2 cards of hand are treasure cards\n", p);
		} else {
			printf ("Branch-1 FAILED: player #%d, check if top 2 cards of hand are treasure cards\n", p);
			printf ("Debug Data: G->hand[topHand-2]: %d, Gpre.hand[topHand-2]): %d\n", G->hand[topHand-2], Gpre.hand[topHand-2]);
			//printf ("printing POST game state: \n");
			//printGameState(G);
			//printf ("printing PRE game state: \n");
			//printGameState (&Gpre);
			errorval--;
		}
	} else if ((handPos > -1) && (totalTreasure >= 1)) { // if treasure exists and 1 treasure card
		// check if the top 1 cards of hand are treasure cards
		int d;
		int treasureCounter = 0;
		for (d = 1; d <= 1; d++) {
			if ((G->hand[p][ topHand - d ] == gold) || (G->hand[p][ topHand - d ] == silver) || (G->hand[p][ topHand - d ] == copper)) {
						treasureCounter++; }
		}
		if (treasureCounter == 1) {
			printf ("Branch-2 SUCCESS: player #%d, check if top 1 cards of hand are treasure cards\n", p);
		} else {
			printf ("Branch-2 FAILED: player #%d, check if top 1 cards of hand are treasure cards\n", p);
			printf ("Debug Data: G->hand[topHand-1]: %d, Gpre.hand[topHand-1]): %d\n", G->hand[topHand-1], Gpre.hand[topHand-1]);
			//printf("Printing Pre Game State \n");
			//printGameState (&Gpre);
			//printf ("Printing Post Game State \n");
			//printGameState(G);
			errorval--;
		}
	} else { // if treasure card may or may not exist
		if (topHand != 0) {
			if (G->hand[topHand-1] == Gpre.hand[topHand-1]) {
				printf ("Branch-3 SUCCESS: player #%d, check if top card of hand is unchanged\n", p);
			} else {
				printf ("Branch-3 FAILED: player #%d, check if top card of hand is unchanged\n", p);
				printf ("Debug Data: G->hand[topHand-2]: %d, Gpre.hand[topHand-2]): %d\n", G->hand[topHand-2], Gpre.hand[topHand-2]);
				//printf("Printing Pre Game State \n");
				//printGameState (&Gpre);
				//printf ("Printing Post Game State \n");
				//printGameState(G);
				errorval--;
			}
		} else {
			printf ("********** no assert performed, hand count was zero!!!!\n");
		}
	}
	return errorval;
}


int main () {
	printf ("Starting ramdom test adventurer. ");
	// NOTE: MAX_HAND = 500, MAX_DECK = 500, MAX_PLAYERS = 4
	srand((unsigned int)time(NULL)); // set random seed with clock
	printf ("clock seed for random number set\n\n");
	// PART A: Randomize initial inputs for creating base game configuration
	// Inputs to set up a game include:
	// # of players p (0, 1, 2, 3, 4...)
	// initial 10 cards chosen from 20 cards (#7 through 26) # of combinations C(20, 10) = 184,756

	int player = getRandIntLowHigh(1,4); // default # players to be replaced later
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	           sea_hag, smithy, treasure_map}; // default hand to be replaced
	struct gameState G; // test game state
	memset(&G, 23, sizeof(struct gameState)); // resets game memory
	int response;

	// LOOP OVER NUMBER OF RANDOM INITIAL GAME STATE
	int numGame;
	for (numGame=0; numGame < 1000; numGame++) {
		printf ("*************** ITERATION # %i ***************  \n", numGame);
		int randSeed = getRandIntLowHigh(1,10000);
		response = randomGameInit (player, k, randSeed, &G);
		if (response == -1) {
			printf ("Program could not create a valid game state!\n");
			printf ("player = %i\n", player);
			//printGameState (&G);
			continue; // it means this was not a valid game state so continue on with for loop.
		}
		//printf ("response = %i\n", response);

		// PART B: Given an initialized game state, randomize the state of play.
		// Inputs we consider for state of play

		//radomly select a player
		int numPlayer = G.numPlayers;
		int p = getRandIntLowHigh (0, numPlayer-1);

		// ------------------------------
		//for given player, set deckCount, disardCount, and handCount
		// ------------------------------
		G.deckCount[p] = getRandIntLowHigh (0, MAX_DECK);
		G.discardCount[p] = getRandIntLowHigh (0, MAX_DECK);
		G.handCount[p] = getRandIntLowHigh (0, MAX_HAND);
		//G.deckCount[p] = getRandIntLowHigh (0, 5);
		//G.discardCount[p] = getRandIntLowHigh (0, 5);
		//G.handCount[p] = getRandIntLowHigh (0, 5);

		// ------------------------------
		//for given player, deck, discard and hand counts, fill with random cards
		// ------------------------------
		fillValidCards (k, p, &G);
		randomizeSupply (&G);
		//printGameState (&G);

		response = checkAdventurer (p, &G);
		if (response == 0) {
			printf ("adventurer test - iteration %i -> successfully passed tests\n", numGame);
		} else {
			printf ("adventurer test - iteration %i -> FAILED tests\n", numGame);
			//printGameState (&G);
		}

	}
	return 0;
}

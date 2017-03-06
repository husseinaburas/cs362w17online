// ***************
// * hijiridd_unittest1.c
// * Desc: Unit test for scorFor() function in domion.c
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

int assertTrue();
int anyRandCard ();
int getRandIntLowHigh (int low, int high);
int printGameState (struct gameState * G);
int fillHandWithCards (struct gameState * G, int handCt);
int fillDiscardWithCards (struct gameState * G, int discardCt);
int fillDeckWithCards(struct gameState * G, int deckCt);
int myOwnScoreFor (int p, struct gameState *G);
int checkScoreFor (struct gameState * G);

// ***************
// assertTrue() - custom assert function
// ****************
int assertTrue(int control, int test) {
	printf ("** assertTrue result: ");
	if (control == test) {
		printf ("assert successful -- control: %d, test: %d\n", control, test);
		return 0;
	}
	printf ("assert FAILED -- control: %d, test: %d\n", control, test);
	return 0;
}

int anyRandCard () {
	int cardnum = getRandIntLowHigh (0, 26);
	// printf ("anyRandCard = %d\n", cardnum);
	return cardnum;
}

// *********************
// getRandIntLowHigh - selects an int between low and high inclusive
// input: low and high int
// return: integer
// *********************
int getRandIntLowHigh (int low, int high) {
	int randInt = (rand()%(high+1-low))+low;
	return randInt;
}

// *********************
// This systematically fills a HAND of given size with cards
// FOR FUTUERE: you can make this a random tester by assigning random cards
// *********************
int fillHandWithCards (struct gameState * G, int handCt) {
	int p, i;
	int card = 0; // card #s are 0 through 26
	// loop through each player
	for (p=0; p < G->numPlayers; p++) {
		// loop across each hand card
		for (i=0; i < handCt; i++) {
			G->hand[p][i] = card;
			card ++;
			if (card > 26) { card = 0; } // max card # is 26
		}
	}
	return 0;
}

// *********************
// This systematically fills a DISCARD of given size with cards
// FOR FUTUERE: you can make this a random tester by assigning random cards
// *********************
int fillDiscardWithCards (struct gameState * G, int discardCt) {
	int p, i;
	int card = 0; // card #s are 0 through 26
	// loop through each player
	for (p=0; p < G->numPlayers; p++) {
		// loop across each hand card
		for (i=0; i < discardCt; i++) {
			G->discard[p][i] = card;
			//printf ("fillDiscardWithCards card = %d\n", card);
			card ++;
			if (card > 26) { card = 0; } // max card # is 26
		}
	}
	return 0;
}

// *********************
// This systematically fills a DECK of given size with cards
// FOR FUTUERE: you can make this a random tester by assigning random cards
// *********************
int fillDeckWithCards(struct gameState * G, int deckCt) {
	int p, i;
	int card = 0; // card #s are 0 through 26
	// loop through each player
	for (p=0; p < G->numPlayers; p++) {
		// loop across each hand card
		for (i=0; i < deckCt; i++) {
			G->deck[p][i] = card;
			card ++;
			if (card > 26) { card = 0; } // max card # is 26
		}
	}
	return 0;
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


int checkScoreFor (struct gameState * G) {
	int errorval = 0;
	int testresponse, controlresponse;
	int p;
	int response;

	// Create a control state that is copy of G
	struct gameState Gcontrol;
	memcpy (&Gcontrol, G, sizeof(struct gameState));

	// calculate score for each player
	for (p=0; p< G->numPlayers; p++) {

		// call the function to test
		testresponse = scoreFor(p, G);

		// call the control function to compare against
		controlresponse = myOwnScoreFor (p, &Gcontrol);

		// compare the two results
		// Assert test and control are equal
		if (testresponse == controlresponse) {
			printf ("player #%d, point calculation successful: testresponse = controlresponse = %d\n",
					p, testresponse);
		} else {
			printf ("player #%d, FAILED point calculation: testresponse: %d, controlresponse %d\n",
					p, testresponse, controlresponse);
			printf ("Printing game state for Gcontrol:\n");
			printGameState (&Gcontrol);
			printf ("Printing game state for G (test):\n");
			printGameState (G);
			errorval--; // subtract -1 for each error encountered.
		}

		// second, compare that the gamestate itself was not changed!
		// assert that G and Gcontrol are equal
		response = memcmp(&Gcontrol, G, sizeof(struct gameState));
		if (response == 0) {
			printf ("player #%d, gameState compare successful: memcmp response = %d\n", p, response);
		} else {
			printf ("player #%d, FAILED gameState compare\n", p);
			printf ("\nPrinting game state for Gcontrol:\n");
			printGameState (&Gcontrol);
			printf ("\nPrinting game state for G (test):\n");
			printGameState (G);
			errorval--; // subtract -1 for each error encountered.
		}
	}
	return errorval;
}

int myOwnScoreFor (int p, struct gameState * G) {
	int i;
	int curseTot = 0;
	int estateTot = 0;
	int great_hallTot = 0;
	int duchyTot = 0;
	int provinceTot = 0;
	int gardensTot = 0;
	int c;

	// walk through deck
	for (i = 0; i < G->deckCount[p]; i++) {
		c = G->deck[p][i];
		if (c == curse) {
			curseTot++;
		} else if (c == estate) {
			estateTot++;
		} else if (c == great_hall) {
			great_hallTot++;
		} else if (c == duchy) {
			duchyTot++;
		} else if (c == province) {
			provinceTot++;
		} else if (c == gardens) {
			gardensTot++;
		}
	}
	// walk through hand
	for (i = 0; i < G->handCount[p]; i++) {
		c = G->hand[p][i];
		if (c == curse) {
			curseTot++;
		} else if (c == estate) {
			estateTot++;
		} else if (c == great_hall) {
			great_hallTot++;
		} else if (c == duchy) {
			duchyTot++;
		} else if (c == province) {
			provinceTot++;
		} else if (c == gardens) {
			gardensTot++;
		}
	}
	// walk through discard
	for (i = 0; i < G->discardCount[p]; i++) {
		c = G->discard[p][i];
		if (c == curse) {
			curseTot++;
		} else if (c == estate) {
			estateTot++;
		} else if (c == great_hall) {
			great_hallTot++;
		} else if (c == duchy) {
			duchyTot++;
		} else if (c == province) {
			provinceTot++;
		} else if (c == gardens) {
			gardensTot++;
		}
	}

	int vp = 0;
	// curse -1 victory points
	vp += (curseTot * -1);
	//printf ("vp = %d\n", vp);

	// estate +1 victory points
	vp += (estateTot * 1);
	//printf ("vp = %d\n", vp);

	// great_hall +1 victory points
	vp += (great_hallTot * 1);
	//printf ("vp = %d\n", vp);

	// duchy +3 victory pionts
	vp += (duchyTot * 3);
	//printf ("vp = %d\n", vp);

	// province +6 victory points
	vp += (provinceTot * 6);
	//printf ("vp = %d\n", vp);

	// gardens variable +(total cords div 10) points
	int cTot = G->deckCount[p] + G->handCount[p] + G->discardCount[p];
	int cTotdiv10 = cTot / 10;
	//printf ("cTot = %d, cTotdiv10 = %d\n", cTot, cTotdiv10);
	vp += (gardensTot * cTotdiv10);
	//printf ("vp = %d\n", vp);

	//printf ("LOG PLAYER %d KEY VP STATS -> curse: %d, estate: %d, great: %d, duchy: %d, province:%d, gardens:%d, TotalCards: %d \n",
	//		p, curseTot, estateTot, great_hallTot, duchyTot, provinceTot, gardensTot, cTot);
	return vp;
}


int main () {
	printf ("\n\nstarting unittest1 -- testing scoreFor() function\n\n");
	// MAX_HAND = 500, MAX_DECK = 500, MAX_PLAYERS = 4

	// -----------------
	// setup a standard game
	// -----------------
	struct gameState G; // test game state
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	           sea_hag, tribute, smithy};

	// -------------------
	// setup unit tests  !!! WE ARE NOT DOING RANDOM TESTS!!!
	// We are looping through different input spaces
	// for deck, hand and discard size. we also fill in the card positions for each
	// deck, hand and discard by looping through all 26 available cards
	// -------------------
	int player = 0;
	int deckCt = 0;
	int discardCt = 0;
	int handCt = 0;
	int response;
	int trial = 0;

	// Loop through # of players
	// Note: to pass initializeGAme, the number of players must be between 2 and MAX_Players
	// for (player = 2; player <= MAX_PLAYERS; player++) {
	for (player = 2; player <= 5; player++) {
		// initialize the standard game
		response = initializeGame (player, k, 1, &G);
		if (response < 0) { // then an error in initialize game
			printf ("Unittest1 SETUP ERROR: Failed to initialize game. num players:%d.\n", player);
			printGameState (&G);
			exit (1); // exit the program with value of 1
		}

		// now loop through different sizes of deck, hand, and discard counts
		// Cases to consider:
		// very large and very small decks, discards and hand counts

		// USE THIS OPTION TO GENERATE ALL POSSIBLE COMBINATIONS OF DECK SIZE
		//for (deckCt = 0; deckCt < MAX_DECK; deckCt++) {
		//	for (discardCt = 0; discardCt < MAX_DECK; discardCt++) {
		//		for (handCt = 0; handCt < MAX_HAND; handCt++) {

		// USE THIS OPTION TO GENERATE SOE REASONABLE COMBINATIONS OF DECK SIZE
		for (deckCt = 8; deckCt < 10; deckCt++) {
			for (discardCt = 8; discardCt < 10; discardCt++) {
				for (handCt = 8; handCt < 10; handCt++) {

					// set the counts for each card stack for each player
					int pCt;
					for (pCt = 0; pCt < player; pCt++) {
						G.handCount[pCt] = handCt;
						G.discardCount[pCt] = discardCt;
						G.deckCount[pCt] = deckCt;
					}

					// fill in the hand, discard, and deckCount with valid cards
					fillHandWithCards (&G, handCt);
					fillDiscardWithCards (&G, discardCt);
					fillDeckWithCards(&G, deckCt);

					// each loop is a "trial"
					trial++;
					printf ("--- Trial #%d --- # players: %d, deckCt: %d, discardCt: %d, handCt: %d\n",
							trial, player, deckCt, discardCt, handCt);

					// submit the game to check ScoreFor
					response = checkScoreFor (&G);

					// ASSERT TO TEST IF CHECK COMPLETED
					if (!(response == 0)) {
						printf ("\nUnittest1: scoreFore did not pass our unit test for TRIAL #%d\n", trial);
						printf ("Debug data: trial #%d, handCt = %d, discardCt = %d, deckCt = %d, players = %d, response = %d\n\n",
								trial, handCt, discardCt, deckCt, player, response);
					} else {
						printf ("\nUnittest1: TEST SUCCESSFULLY COMPLETED for Trial #%d\n\n", trial);
					}
				}
			}
		}
	}
	return 0;
}



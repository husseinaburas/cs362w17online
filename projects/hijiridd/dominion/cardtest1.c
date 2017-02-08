// ***************
// * cardtest1.c
// * Desc: Unit test for smithy card function in domion.c
//****************
#include "dominion.h"
#include "dominion_helpers.h"
#include "dominion_refactorwk2.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int assertTrue();
int anyRandCard ();
int getRandIntLowHigh (int low, int high);
int printGameState (struct gameState * G);
int fillHandWithCards (struct gameState * G, int handCt);
int fillDiscardWithCards (struct gameState * G, int discardCt);
int fillDeckWithCards(struct gameState * G, int deckCt);
int checkSmithy (struct gameState * G, int scenario);

// ***************
// assertTrue() - custom assert function
// ****************
int assertTrue(int control, int test) {
	printf ("** assertTrue result: ");
	if (control == test) {
		printf ("assert successful -- control: %d, test: %d\n", control, test);
		return 1;
	}
	printf ("assert FAILED -- control: %d, test: %d\n", control, test);
	return 0;
}

int anyRandCard () {
	int cardnum = getRandIntLowHigh (0, 26);
	//printf ("anyRandCard = %d\n", cardnum);
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
	int i;
	int p, j;
	int totalsupply = 0;
	printf ("\n--START PRINTING GAME STATE -------------------\n");
	printf ("numPlayers = %d\n", G->numPlayers);
	for (i = 0; i< (treasure_map+1); i++) {
		totalsupply += G->supplyCount[i];
	}
	printf ("SUPPLY TOTAL=%d, supplyCount: ", totalsupply);
	for (i = 0; i< (treasure_map+1); i++) {
		printf ("#%d: %d, ", i, G->supplyCount[i]);
	}
	printf ("\n");
	printf ("embargoTokens: ");
	for (i = 0; i< (treasure_map+1); i++) {
		printf ("#%d: %d, ", i, G->embargoTokens[i]);
	}
	printf ("\n");
	printf ("outpostPlayed = %d, ", G->outpostPlayed);
	printf ("outpostTurn = %d, ", G->outpostTurn);
	printf ("whoseTurn = %d, ", G->whoseTurn);
	printf ("phase = %d, ", G->phase);
	printf ("numActions = %d, ", G->numActions);
	printf ("coins = %d, ", G->coins);
	printf ("numBuys = %d\n", G->numBuys);
	printf ("playedCardCount = %d, playedCards[x]: ", G->playedCardCount);
	for (j=0; j< (G->playedCardCount); j++) {
		printf ("[%d] = %d", j, G->playedCards[j]);
	}
	printf ("\n");

	for (p=0; p< G->numPlayers; p++) {
		printf ("---------------------\n");
		int handCount = G->handCount[p];
		printf ("PLAYER #%d, HANDCOUNT=%d, hand[player][hand]: ", p, handCount);
		for (j = 0; j<handCount; j++) {
			printf ("[%d][hand:%d] = %d, ", p, j, G->hand[p][j]);
		}
		printf ("\n");

		int deckCount = G->deckCount[p];
		printf ("PLAYER #%d, DECKCOUNT=%d, deck[player][hand]: ", p, deckCount);
		for (j = 0; j<deckCount; j++) {
			printf ("[%d][deck:%d] = %d, ", p, j, G->deck[p][j]);
		}
		printf ("\n");

		int discardCount = G->discardCount[p];
		printf ("PLAYER #%d, DISCARDCOUNT=%d, discard[player][hand]: ", p, discardCount);
		for (j = 0; j<discardCount; j++) {
			printf ("[%d][discard: %d] = %d, ", p, j, G->discard[p][j]);
		}
		printf ("\n");
	}
	printf ("--END PRINTING GAME STATE -------------------\n\n");
	return 0;
}

// **********************
// tests for SMITHY
// **********************
int checkSmithy (struct gameState * G, int scenario) {
	int errorval = 0;
	int testresponse, controlresponse;
	int p;
	int response;
	testresponse = 0; controlresponse = 0; response = 0; // to silence unused var warning

	struct gameState Gpre, Gcontrol;
	// Create a pre and control Game state that is copy of G
	memcpy (&Gpre, G, sizeof(struct gameState));
	memcpy (&Gcontrol, G, sizeof(struct gameState));

	// loop through each player
	for (p=0; p< G->numPlayers; p++) {

		G->whoseTurn = p; // setting the turn of the player to play Smithy

		// find the location of Smithy in player p's hand
		int handPos = -1; // default is that there is no Smithy in hand
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
	}

	// SCENARIO 1:
	// # Smithy in each player's Hand = 1
	if (scenario == 1) {
		printf ("---- in checkSmithy Scenario 1 test loop\n");
		// loop through each player
		for (p=0; p< G->numPlayers; p++) {
			printf ("---- in checkSmmithy Scenario 1 player %d test loop\n", p);

			// Scenario1-test1: check if played card has increased by 1 * # players
			if ((G->playedCardCount - Gpre.playedCardCount) == (1 * G->numPlayers)) {
				printf ("Scenario1-test1: SUCCESS: player #%d, check if played card has increased by 1 * # players\n", p);
			} else {
				printf ("Scenario1-test1: FAILED: player #%d, check if played card has increased by 1 * # players\n", p);
				printf ("Debug: G->playedCardCount: %d, Gpre.playedCardCount: %d\n", G->playedCardCount, Gpre.playedCardCount);
				errorval--;
			}

			// Scenario1-test2: check if total supply count has not changed
			int c;
			int supplyTotalPost = 0;
			int supplyTotalPre = 0;
			for (c=0; c < (treasure_map+1); c++) {
				supplyTotalPost += G->supplyCount[c];
				supplyTotalPre += Gpre.supplyCount[c];
				//printf ("supplyTotalPost: %d, supplyTotalPre:%d\n", supplyTotalPost, supplyTotalPre);
			}
			if ((supplyTotalPost - supplyTotalPre) == 0) {
				printf ("Scenario1-test2: SUCCESS: player #%d, check if total supply count has not changed\n", p);
			} else {
				printf ("Scenario1-test2: FAILED: player #%d, check if total supply count has not changed\n", p);
				printf ("Debug Data: supplyTotalPost: %d, supplyTotalPre: %d\n", supplyTotalPost, supplyTotalPre);
				errorval--;
			}

			// Scenario1-test3: check if hand count went up by 2 (minus Smith + 3 cards)
			if ((G->handCount[p] - Gpre.handCount[p]) == 2) {
				printf ("Scenario1-test3: SUCCESS: player #%d, check if hand count went up by 2 (minus Smith + 3 cards)\n", p);
			} else {
				printf ("Scenario1-test3: FAILED: player #%d, check if hand count went up by 2 (minus Smith + 3 cards)\n", p);
				printf ("Debug Data: G->handCount[p]: %d, Gpre.handCount[p]: %d\n", G->handCount[p], Gpre.handCount[p]);
				errorval--;
			}

			// Scenario1-test4: check deck+discard count decreased 3 (only 3 cards moved to hand)
			if (((G->deckCount[p] + G->discardCount[p]) - (Gpre.deckCount[p] + Gpre.discardCount[p])) == -3) {
				printf ("Scenario1-test4: SUCCESS: player #%d, check deck+discard count decreased 3 (only 3 cards moved to hand)\n", p);
			} else {
				printf ("Scenario1-test4: FAILED: player #%d, check deck+discard count decreased 3 (only 3 cards moved to hand)\n", p);
				printf ("Debug Data: G->deckCount[p] + G->discardCount[p]): %d, (Gpre.deckCount[p] + Gpre.discardCount[p]): %d\n",
						(G->deckCount[p] + G->discardCount[p]), (Gpre.deckCount[p] + Gpre.discardCount[p]) );
				errorval--;
			}
		}
	}

	// SCENARIO 2:
	// # Smithy in each player's Hand = 0
	if (scenario == 2) {
		printf ("---- in checkSmithy Scenario 2 test loop\n");
		// loop through each player
		// loop through each player
		for (p=0; p< G->numPlayers; p++) {
			printf ("---- in checkSmmithy Scenario 2 player %d test loop\n", p);
			// Scenario2-test1: check if played card count is unchanged
			if ((G->playedCardCount - Gpre.playedCardCount) == 0) {
				printf ("Scenario2-test1: SUCCESS: player #%d, check if played card count unchanged\n", p);
			} else {
				printf ("Scenario2-test1: FAILED: player #%d, check if played card count unchanged\n", p);
				errorval--;
			}

			// Scenario2-test2: check to see if the total supply count has not changed
			int c;
			int supplyTotalPost = 0;
			int supplyTotalPre = 0;
			for (c=0; c < (treasure_map+1); c++) {
				supplyTotalPost += G->supplyCount[c];
				supplyTotalPre += Gpre.supplyCount[c];
				//printf ("supplyTotalPost: %d, supplyTotalPre:%d\n", supplyTotalPost, supplyTotalPre);
			}
			if (supplyTotalPost == supplyTotalPre) {
				printf ("Scenario2-test2: SUCCESS: player #%d, check to see if the total supply count has not changed\n", p);
			} else {
				printf ("Scenario2-test2: FAILED: player #%d, check to see if the total supply count has not changed\n", p);
				errorval--;
			}

			// Scenario2-test3: check if hand count has not changed
			if ((G->handCount[p] - Gpre.handCount[p]) == 0) {
				printf ("Scenario2-test3: SUCCESS: player #%d, check if hand count has not changed\n", p);
			} else {
				printf ("Scenario2-test3: FAILED: player #%d, check if hand count has not changed\n", p);
				errorval--;
			}

			// Scenario2-test4: check if deck count has not changed
			if ((G->deckCount[p] - Gpre.deckCount[p]) == 0) {
				printf ("Scenario2-test4: SUCCESS: player #%d, check if deck count has not changed\n", p);
			} else {
				printf ("Scenario2-test4: FAILED: player #%d, check if deck count has not changed\n", p);
				errorval--;
			}
		}
	}
	return 0;
}

int main () {
	printf ("\n\nstarting cardtest1 -- testing SMITHY function\n\n");
	// MAX_HAND = 500, MAX_DECK = 500, MAX_PLAYERS = 4

	int player, response, p;
	struct gameState G; // test game state
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	           sea_hag, smithy, treasure_map}; // replaced one of the cards with treasure_map
	int deckCt, discardCt, handCt;
	int toFlag;

	// ---- SCENARIO 1 ---------------------------------------------
	// # Players = start with 2 (may loop from 2 to 4 or MAX_PLAYER)
	// DeckCount = loop from X to Y (extreme cases 0 to MAX_DECK)
	// HandCount = loop from X to Y (extreme cases 0 to MAX_HAND)
	// DiscardCount = loop from X to Y (Where DiscardCount + DeckCount < MAX_DECK)
	// # Smithy in each player's Hand = 1

	printf ("----Starting Scenario 1 tests -----\n");
	// test for some reasonable # of players
	for (player = 2; player <= 2; player++) {	//MAX loop:	for (player = 2; player <= MAX_PLAYERS; player++)
		// initialize the standard game
		response = initializeGame (player, k, 1, &G);
		if (response < 0) { // then an error in initialize game
			printf ("cardtest 2, Scenario 1 ERROR: Failed to initialize game. Data of current game state:\n");
			printf ("Players = %d\n", player);
			//printGameState (&G);
			exit (1); // exit the program with value of 1
		}

		// USE THIS OPTION TO GENERATE REASONABLE COMBINATIONS OF DECK SIZE
		for (deckCt = 10; deckCt < 11; deckCt++) {
			for (discardCt = 5; discardCt < 6; discardCt++) {
				for (handCt = 9; handCt < 10; handCt++) {

					// set the counts for each card stack for each player
					int pCt;
					for (pCt = 0; pCt < player; pCt++) {
						G.handCount[pCt] = handCt;
						G.discardCount[pCt] = discardCt;
						G.deckCount[pCt] = deckCt;
					}

					// fill in the hand, discard, and deckCount with valid cards (systematically, not randomly)
					fillHandWithCards (&G, handCt);
					fillDiscardWithCards (&G, discardCt);
					fillDeckWithCards(&G, deckCt);

					// force each player to have only 1 Smithy
					for (p=0; p<player; p++) {
						// first remove all Smithy cards from hand
						int c;
						for (c=0; c< G.deckCount[p]; c++) {
							if (G.hand[p][c] == smithy) {
								// replace with a benign card
								G.hand[p][c] = curse;
							}
						}
					}

					// now add 1 Smmithy to each players hand
					for (p=0; p<player; p++) {
						toFlag = 2; // add card to the hand
						gainCard (smithy, &G, toFlag, p);
						// DEBUG
						//printGameState (&G);
					}

					printf ("--- loop with players: %d, deck: %d, discard: %d, hand: %d\n",
							G.numPlayers, deckCt, discardCt, handCt);
					response = checkSmithy (&G, 1); // 1 for scenario 1
					if (response == 0) {
						printf ("cardtest1-Scenario1-tests-> successfully passed tests\n");
					} else {
						printf ("cardtest1-Scenario1-tests -> FAILED to pass tests # errors: %d\n", response);
					}
				}
			}
		}
	}

	// ---- SCENARIO 2 ---------------------------------------------
	// # Players = start with 2 (may loop from 2 to 4 or MAX_PLAYER)
	// DeckCount = loop from X to Y (extreme cases 0 to MAX_DECK)
	// HandCount = loop from X to Y (extreme cases 0 to MAX_HAND)
	// DiscardCount = loop from X to Y (Where DiscardCount + DeckCount < MAX_DECK)
	// # Smithy in each player's Hand = 0

	printf ("----Starting Scenario 2 tests -----\n");
	// test for some reasonable # of players
	for (player = 2; player <= 2; player++) {	//MAX loop:	for (player = 2; player <= MAX_PLAYERS; player++)
		// initialize the standard game
		response = initializeGame (player, k, 1, &G);
		if (response < 0) { // then an error in initialize game
			printf ("cardtest 2, Scenario 1 ERROR: Failed to initialize game. Data of current game state:\n");
			printf ("Players = %d\n", player);
			//printGameState (&G);
			exit (1); // exit the program with value of 1
		}

		// USE THIS OPTION TO GENERATE REASONABLE COMBINATIONS OF DECK SIZE
		for (deckCt = 10; deckCt < 11; deckCt++) {
			for (discardCt = 5; discardCt < 6; discardCt++) {
				for (handCt = 9; handCt < 10; handCt++) {

					// set the counts for each card stack for each player
					int pCt;
					for (pCt = 0; pCt < player; pCt++) {
						G.handCount[pCt] = handCt;
						G.discardCount[pCt] = discardCt;
						G.deckCount[pCt] = deckCt;
					}

					// fill in the hand, discard, and deckCount with valid cards (systematically, not randomly)
					fillHandWithCards (&G, handCt);
					fillDiscardWithCards (&G, discardCt);
					fillDeckWithCards(&G, deckCt);

					// force each player to have at least 0 Smithy card
					for (p=0; p<player; p++) {
						// first remove all Smithy cards from hand
						int c;
						for (c=0; c< G.deckCount[p]; c++) {
							if (G.hand[p][c] == smithy) {
								// replace with a benign card
								G.hand[p][c] = curse;
							}
						}
					}

					printf ("--- loop with players: %d, deck: %d, discard: %d, hand: %d\n",
							G.numPlayers, deckCt, discardCt, handCt);
					response = checkSmithy (&G, 2); // 2 for scenario 2
					if (response == 0) {
						printf ("cardtest1-Scenario2-tests-> successfully passed tests\n");
					} else {
						printf ("cardtest1-Scenario2-tests -> FAILED to pass tests # errors: %d\n", response);
					}
				}
			}
		}
	}

	return 0;
}


/*
 			// if there was >= 3 cards in deck
			// check if deck count was decreased by 3
			if (Gpre.deckCount[p] > 2) {
				if ((G->deckCount[p] - Gpre.deckCount[p]) == 3) {
					printf ("Success player %d: deckCount decreased by 3\n", p);
				} else {
					printf ("FAILED player %d: deckCount NOT decreased by 3\n", p);
					errorval--;
				}
			}

			// if there was < 3 cards in deck
			// check if deck count = discard count - (3 - old deck count)
			if (Gpre.deckCount[p] < 3) {
				if ((G->deckCount[p] - (Gpre.discardCount[p] - (3 - Gpre.deckCount[p]))) == 0) {
					printf ("Success player %d: new deck created from discard and decreased appropriately\n", p);
				} else {
					printf ("FAILED player %d: new deck created from discard and NOT decreased appropriately\n", p);
					errorval--;
				}
			}

			// check if played card was increased by 1
			if ((G->playedCardCount - Gpre.playedCardCount) == 1) {
				printf ("Success player %d: playedCardCount was increased 1\n", p);
			} else {
				printf ("FAILED player %d: playedCardCount was NOT increased by 1\n", p);
				errorval--;
			}

			// check to see if the total supply count has not changed
			int c;
			int supplyTotalPost = 0;
			int supplyTotalPre = 0;
			for (c=0; c < (treasure_map+1); c++) {
				supplyTotalPost += G->supplyCount[c];
				supplyTotalPre += Gpre.supplyCount[c];
				//printf ("supplyTotalPost: %d, supplyTotalPre:%d\n", supplyTotalPost, supplyTotalPre);
			}
			if (supplyTotalPost == supplyTotalPre) {
				printf ("Success player %d: given no supply to draw down, no change in total supply count\n", p);
			} else {
				printf ("FAILED player %d: given no supply to draw down, change in total supply count\n", p);
				errorval--;
			}
		}

		// IF THERE WAS NO SMITHY CARD TO PLAY
		if (handPos < 0) {
			// check if handcount is the same)
			if ((G->handCount[p] - Gpre.handCount[p]) == 0) {
				printf ("Success player %d: given no Smithy handCount increased by 0\n", p);
			} else {
				printf ("FAILED player %d: given no SmithyhandCount NOT increased by 0\n", p);
				//printGameState(G);
				errorval--;
			}

			// check if deck count was decreased by 0
			if (Gpre.deckCount[p] > 2) {
				if ((G->deckCount[p] - Gpre.deckCount[p]) == 0) {
					printf ("Success player %d: given no Smithy deckCount increased by 0\n", p);
				} else {
					printf ("FAILED player %d: given no Smithy deckCount NOT increased by 0\n", p);
					errorval--;
				}
			}

			// check if played card was increased by 0
			if ((G->playedCardCount - Gpre.playedCardCount) == 0) {
				printf ("Success player %d: given no Smithy playedCardCount was increased 0\n", p);
			} else {
				printf ("FAILED player %d: given no Smithy playedCardCount was NOT increased by 0\n", p);
				errorval--;
			}

			// check to see if the total supply count has not changed
			int c;
			int supplyTotalPost = 0;
			int supplyTotalPre = 0;
			for (c=0; c < (treasure_map+1); c++) {
				supplyTotalPost += G->supplyCount[c];
				supplyTotalPre += Gpre.supplyCount[c];
				//printf ("supplyTotalPost: %d, supplyTotalPre:%d\n", supplyTotalPost, supplyTotalPre);
			}
			if (supplyTotalPost == supplyTotalPre) {
				printf ("Success player %d: given no Smithy, no change in total supply count\n", p);
			} else {
				printf ("FAILED player %d: given no Smithy, change in total supply count\n", p);
				errorval--;
			}
		}

	}
	return errorval;
}
*/






		// USE THIS OPTION TO GENERATE SOE REASONABLE COMBINATIONS OF DECK SIZE
/*
		for (deckCt = 10; deckCt < 11; deckCt++) {
			for (discardCt = 5; discardCt < 6; discardCt++) {
				for (handCt = 8; handCt < 10; handCt++) {

					// set the counts for each card stack for each player
					int pCt;
					for (pCt = 0; pCt < player; pCt++) {
						G.handCount[pCt] = handCt;
						G.discardCount[pCt] = discardCt;
						G.deckCount[pCt] = deckCt;
					}

					// fill in the hand, discard, and deckCount with valid cards (systematically, not randomly)
					fillHandWithCards (&G, handCt);
					fillDiscardWithCards (&G, discardCt);
					fillDeckWithCards(&G, deckCt);

					// each loop is a "trial"
					trial++;
					printf ("--- Trial #%d ---\n", trial);
					response = checkGainCard (&G);

					// ASSERT TO TEST IF CHECK COMPLETED
					if (!(response == 0)) {
						printf ("\nUnittest3: gainCard() did not pass our unit test\n");
// TODO CHANGE						printf ("Debug data: trial #%d, handCt = %d, discardCt = %d, deckCt = %d, players = %d, response = %d\n\n",
// TODO CHANGE								trial, handCt, discardCt, deckCt, player, response);
					} else {
						printf ("\nUnittest2: gainCard() TEST SUCCESSFULLY COMPLETED\n\n");
					}
				}
			}
		}
*/


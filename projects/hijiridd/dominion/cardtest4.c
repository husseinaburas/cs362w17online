// ***************
// * cardtest4.c
// * Desc: Unit test for village card in domion.c
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
int checkVillage (struct gameState * G, int scenario);

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
// tests for Village
// **********************
int checkVillage (struct gameState * G, int scenario) {
	int errorval = 0;
	int testresponse, controlresponse;
	int p;
	int response;
	controlresponse = 0; response = 0; // to silence unused var warning

	struct gameState Gpre, Gcontrol;
	// Create a pre and control Game state that is copy of G
	memcpy (&Gpre, G, sizeof(struct gameState));
	memcpy (&Gcontrol, G, sizeof(struct gameState));

	// loop through each player
	for (p=0; p< G->numPlayers; p++) {

		G->whoseTurn = p; // setting the turn of the player to play Treasure Map

		// find the location of village in player p's hand
		int handPos = -1; // default is that there is no village in hand
		int c;
		for (c=0; c < G->handCount[p]; c++) {
			if (G->hand[p][c] == village) { handPos = c; }
		}
		if (handPos == -1) {
			printf ("\nNOTE Player %d: did NOT find Village in player's hand\n", p);
			//printGameState (G);
		}

		// call the function to test
		int card = village;
		int choice1 = 0; // not used for village
		int choice2 = 0; // not used for village
		int choice3 = 0; // not used for village
		int bonus = 0;  // not used for village
		testresponse =  cardEffect(card, choice1, choice2, choice3, G,
									handPos, &bonus);
	}

	// SCENARIO 1: IF THERE WAS 1 VILLAGE IN HAND
	if (scenario == 1) {
		printf ("---- in checkVillage Scenario 1 test loop\n");
		// loop through each player
		for (p=0; p< G->numPlayers; p++) {
			printf ("---- in checkVillage Scenario 1 player %d test loop\n", p);

			// Scenario1-test1: check if played card is increased by 1
			if ((G->playedCardCount - Gpre.playedCardCount) == 1) {
				printf ("Scenario1-test1: SUCCESS: player #%d,  check if played card is increased by 1\n", p);
			} else {
				printf ("Scenario1-test1: FAILED: player #%d,  check if played card is increased by 1\n", p);
				printf ("G->playedCardCount: %d,  Gpre.playedCardCount: %d\n", G->playedCardCount, Gpre.playedCardCount);
				errorval--;
			}

			// Scenario1-test2: check if total supply count is unchanged
			int c;
			int supplyTotalPost = 0;
			int supplyTotalPre = 0;
			for (c=0; c < (treasure_map+1); c++) {
				supplyTotalPost += G->supplyCount[c];
				supplyTotalPre += Gpre.supplyCount[c];
				//printf ("supplyTotalPost: %d, supplyTotalPre:%d\n", supplyTotalPost, supplyTotalPre);
			}
			if ((supplyTotalPost - supplyTotalPre) == 0) {
				printf ("Scenario1-test2: SUCCESS: player #%d, check if total supply count is unchanged\n", p);
			} else {
				printf ("Scenario1-test2: FAILED: player #%d, check if total supply count is unchanged\n", p);
				printf ("supplyTotalPost: %d, supplyTotalPre: %d\n", supplyTotalPost, supplyTotalPre);
				errorval--;
			}

			// Scenario1-test3: check if hand count is unchanged (minus Village + 1 card)
			if ((G->handCount[p] - Gpre.handCount[p]) == 0) {
				printf ("Scenario1-test3: SUCCESS: player #%d, check if hand count is unchanged (minus Village + 1 card)\n", p);
			} else {
				printf ("Scenario1-test3: FAILED: player #%d, check if hand count is unchanged (minus Village + 1 card)\n", p);
				printf ("G->handCount[p]: %d, Gpre.handCount[p]: %d\n", G->handCount[p], Gpre.handCount[p]);
				errorval--;
			}

			// Scenario1-test4: check if deck count decreased by 1
			if ((G->deckCount[p] - Gpre.deckCount[p]) == -1) {
				printf ("Scenario1-test4: SUCCESS: player #%d, check if deck count decreased by 1\n", p);
			} else {
				printf ("Scenario1-test4: FAILED: player #%d, check if deck count decreased by 1\n", p);
				printf ("G->deckCount[p]: %d, Gpre.deckCount[p]: %d\n", G->deckCount[p], Gpre.deckCount[p]);
				errorval--;
			}

			// Scenario1-test5: check if numActions is now +2 * # players
			if ((G->numActions - Gpre.numActions) == 2*G->numPlayers) {
				printf ("Scenario1-test5: SUCCESS: player #%d, check if numActions is now +2 * # players\n", p);
			} else {
				printf ("Scenario1-test5: FAILED: player #%d, check if numActions is now +2 * # players\n", p);
				printf ("G->numActions: %d, Gpre.numActions: %d\n", G->numActions, Gpre.numActions);
				errorval--;
			}
		}
	}

	// SCENARIO 2: IF THERE WAS 0 VILLAGE IN HAND
		if (scenario == 2) {
			printf ("---- in checkVillage Scenario 2 test loop\n");
			// loop through each player
			for (p=0; p< G->numPlayers; p++) {
				printf ("---- in checkVillage Scenario 2 player %d test loop\n", p);

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

	// SCENARIO 3: IF THERE WAS 5 VILLAGE CARDS IN HAND
		if (scenario == 3) {
			printf ("---- in checkVillage Scenario 3 test loop\n");
			// loop through each player
			for (p=0; p< G->numPlayers; p++) {
				printf ("---- in checkVillage Scenario 3 player %d test loop\n", p);

				// Scenario3-test1: check if played card is increased by 1
				if ((G->playedCardCount - Gpre.playedCardCount) == 1) {
					printf ("Scenario3-test1: SUCCESS: player #%d,  check if played card is increased by 1\n", p);
				} else {
					printf ("Scenario3-test1: FAILED: player #%d,  check if played card is increased by 1\n", p);
					errorval--;
				}

				// Scenario3-test2: check if total supply count is unchanged
				int c;
				int supplyTotalPost = 0;
				int supplyTotalPre = 0;
				for (c=0; c < (treasure_map+1); c++) {
					supplyTotalPost += G->supplyCount[c];
					supplyTotalPre += Gpre.supplyCount[c];
					//printf ("supplyTotalPost: %d, supplyTotalPre:%d\n", supplyTotalPost, supplyTotalPre);
				}
				if ((supplyTotalPost - supplyTotalPre) == 0) {
					printf ("Scenario3-test2: SUCCESS: player #%d,  is unchanged\n", p);
				} else {
					printf ("Scenario3-test2: FAILED: player #%d,  is unchanged", p);
					printf ("supplyTotalPost: %d, supplyTotalPre: %d\n", supplyTotalPost, supplyTotalPre);
					errorval--;
				}

				// Scenario3-test3: check if hand count went down 1
				if ((G->handCount[p] - Gpre.handCount[p]) == -1) {
					printf ("Scenario3-test3: SUCCESS: player #%d, check if hand count went down 1\n", p);
				} else {
					printf ("Scenario3-test3: FAILED: player #%d, check if hand count went down 1\n", p);
					errorval--;
				}

				// Scenario3-test4: check if deck count decreased by 3
				if ((G->deckCount[p] - Gpre.deckCount[p]) == -3) {
					printf ("Scenario3-test4: SUCCESS: player #%d, check if deck count decreased by 3\n", p);
				} else {
					printf ("Scenario3-test4: FAILED: player #%d, check if deck count decreased by 3\n", p);
					errorval--;
				}

				// Scenario3-test5: check if numActions is now +2 * # players
				if ((G->numActions - Gpre.numActions) == 2*G->numPlayers) {
					printf ("Scenario3-test5: SUCCESS: player #%d, check if numActions is now +2 * # players\n", p);
				} else {
					printf ("Scenario3-test5: FAILED: player #%d, check if numActions is now +2 * # players\n", p);
					errorval--;
				}
			}
		}
	return errorval;
}

int main () {
	printf ("\n\nstarting cardtest4 -- testing VILLAGE function\n\n");
	// DEBUGGING
	// printf ("MAX_HAND = %d, MAX_DECK = %d, MAX_PLAYERS = %d\n", MAX_HAND, MAX_DECK, MAX_PLAYERS);
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
	// # of Village in each player's hand = 1

	// SCENARIO 1: setup game
	printf ("----Starting Scenario 1 tests -----\n");
	// test for some reasonable # of players
	for (player = 2; player <= 2; player++) {	//MAX loop:	for (player = 2; player <= MAX_PLAYERS; player++)
		// initialize the standard game
		response = initializeGame (player, k, 1, &G);
		if (response < 0) { // then an error in initialize game
			printf ("cardtest4, Scenario 1 ERROR: Failed to initialize game. Data of current game state:\n");
			printf ("Players = %d\n", player);
			//printGameState (&G);
			exit (1); // exit the program with value of 1
		}

		// USE THIS OPTION TO GENERATE REASONABLE COMBINATIONS OF DECK SIZE
		for (deckCt = 10; deckCt < 11; deckCt++) { // range: 0 to MAX_DECK
			for (discardCt = 5; discardCt < 6; discardCt++) {  // range: 0 to MAX_DECK
				for (handCt = 9; handCt < 10; handCt++) {  // range: 0 to MAX_HAND

					// force each player to have 1 Village in each player's hand.
					for (p=0; p<player; p++) {
						toFlag = 2; // add action card to the hand
						gainCard (village, &G, toFlag, p);
						// DEBUG
						//printGameState (&G);
					}
					response = checkVillage (&G, 1); // 1 for scenario 1
					if (response == 0) {
						printf ("cardtest4-Scenario1-tests-> successfully passed tests\n");
					} else {
						printf ("cardtest4-Scenario1-tests -> FAILED to pass tests # errors: %d\n", response);
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
	// # of Village in each player's Hand = 0

	// SCENARIO 2: setup game
	printf ("----Starting Scenario 2 tests -----\n");
	// test for some reasonable # of players
	for (player = 2; player <= 2; player++) {	//MAX loop:	for (player = 2; player <= MAX_PLAYERS; player++)
		// initialize the standard game
		response = initializeGame (player, k, 1, &G);
		if (response < 0) { // then an error in initialize game
			printf ("cardtest 4, Scenario 2 ERROR: Failed to initialize game. Data of current game state:\n");
			printf ("Players = %d\n", player);
			//printGameState (&G);
			exit (1); // exit the program with value of 1
		}

		// USE THIS OPTION TO GENERATE REASONABLE COMBINATIONS OF DECK SIZE
		for (deckCt = 10; deckCt < 11; deckCt++) { // range: 0 to MAX_DECK
			for (discardCt = 5; discardCt < 6; discardCt++) {  // range: 0 to MAX_DECK
				for (handCt = 9; handCt < 10; handCt++) {  // range: 0 to MAX_HAND

					// force each player to have 0 Village in each player's hand.
					// In this case we do nothing since there is no Village in hand for default initialization						// DEBUG
					//printGameState (&G);

					response = checkVillage (&G, 2); // 2 for scenario 2
					if (response == 0) {
						printf ("cardtest4-Scenario2-tests-> successfully passed tests\n");
					} else {
						printf ("cardtest4-Scenario2-tests -> FAILED to pass tests # errors: %d\n", response);
					}
				}
			}
		}
	}


	// ---- SCENARIO 3 ---------------------------------------------
	// # Players = start with 2 (may loop from 2 to 4 or MAX_PLAYER)
	// DeckCount = loop from X to Y (extreme cases 0 to MAX_DECK)
	// HandCount = loop from X to Y (extreme cases 0 to MAX_HAND)
	// DiscardCount = loop from X to Y (Where DiscardCount + DeckCount < MAX_DECK)
	// # of Village in each player's Hand = 5

	// SCENARIO 3: setup game
	// test for some reasonable # of players
	printf ("----Starting Scenario 3 tests -----\n");
	for (player = 2; player <= 2; player++) {	//MAX loop:	for (player = 2; player <= MAX_PLAYERS; player++)
		// initialize the standard game
		response = initializeGame (player, k, 1, &G);
		if (response < 0) { // then an error in initialize game
			printf ("cardtest4, Scenario 1 ERROR: Failed to initialize game. Data of current game state:\n");
			printf ("Players = %d\n", player);
			//printGameState (&G);
			exit (1); // exit the program with value of 1
		}

		// USE THIS OPTION TO GENERATE REASONABLE COMBINATIONS OF DECK SIZE
		for (deckCt = 10; deckCt < 11; deckCt++) { // range: 0 to MAX_DECK
			for (discardCt = 5; discardCt < 6; discardCt++) {  // range: 0 to MAX_DECK
				for (handCt = 9; handCt < 10; handCt++) {  // range: 0 to MAX_HAND

					// force each player to have 5 Village in each player's hand.
					for (p=0; p<player; p++) {
						toFlag = 2; // add action card to the hand
						gainCard (village, &G, toFlag, p);
						gainCard (village, &G, toFlag, p);
						gainCard (village, &G, toFlag, p);
						gainCard (village, &G, toFlag, p);
						gainCard (village, &G, toFlag, p);
						// DEBUG
						//printGameState (&G);
					}
					response = checkVillage (&G, 3); // 3 for scenario 3

					if (response == 0) {
						printf ("cardtest4-Scenario3-tests-> successfully passed tests\n");
					} else {
						printf ("cardtest4-Scenario3-tests -> FAILED to pass tests # errors: %d\n", response);
					}
				}
			}
		}
	}
	return 0;
}








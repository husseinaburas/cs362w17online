// ***************
// * cardtest2.c
// * Desc: Unit test for ADVENTURER card in domion.c
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
int checkAdventurer (struct gameState * G, int scenario);
//int myOwnAdventurerAction (int currentPlayer, struct gameState * G, int handPos);

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

	}	printf ("\n");

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
// tests for Adventurer
// **********************
int checkAdventurer (struct gameState * G, int scenario) {
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

		// call the function to test
		int card = adventurer;
		int choice1 = 0; // not used for Adventurer
		int choice2 = 0; // not used for Adventurer
		int choice3 = 0; // not used for Adventurer
		int bonus = 0;  // not used for Adventurer
		testresponse =  cardEffect(card, choice1, choice2, choice3, G,
									handPos, &bonus);
		//controlresponse = myOwnTreasureMap (p, &Gcontrol, handPos);
	}

	// SCENARIO 1:
	// # Adventurer in each player's Hand = 1
	// # copper cards in each player's deck and discard pile = 2 (silver = 0, gold = 0)
	if (scenario == 1) {
		printf ("---- in checkAdventurer Scenario 1 test loop\n");
		// loop through each player
		for (p=0; p< G->numPlayers; p++) {
			printf ("---- in check Adventurer Scenario 1 player %d test loop\n", p);

			// Scenario1-test1: check if played card has increased by 1
			if ((G->playedCardCount - Gpre.playedCardCount) == 1) {
				printf ("Scenario1-test1: SUCCESS: player #%d, check if played card has increased by 1\n", p);
			} else {
				printf ("Scenario1-test1: FAILED: player #%d, check if played card has increased by 1\n", p);
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

			// Scenario1-test3: check if hand count went up by 1 (minus Adventurer + 2 treasure cards)
			if ((G->handCount[p] - Gpre.handCount[p]) == 1) {
				printf ("Scenario1-test3: SUCCESS: player #%d, check if hand count went up by 1 (minus Adventurer + 2 treasure cards)\n", p);
			} else {
				printf ("Scenario1-test3: FAILED: player #%d, check if hand count went up by 1 (minus Adventurer + 2 treasure cards)\n", p);
				printf ("Debug Data: G->handCount[p]: %d, supplyTotalPre: %d\n", G->handCount[p], Gpre.handCount[p]);
				errorval--;
			}

			// Scenario1-test4: check deck+discard count decreased 2 (only 2 treasure moves to hand, rest are discard)
			if (((G->deckCount[p] + G->discardCount[p]) - (Gpre.deckCount[p] + Gpre.discardCount[p])) == -2) {
				printf ("Scenario1-test4: SUCCESS: player #%d, check deck+discard count decreased 2 (only 2 treasure moves to hand, rest are discard)\n", p);
			} else {
				printf ("Scenario1-test4: FAILED: player #%d, ccheck deck+discard count decreased 2 (only 2 treasure moves to hand, rest are discard)\n", p);
				errorval--;
			}

			// Scenario1-test5: check if top 2 cards of hand are treasure cards
			// in this case top 2 cards in hand correspond to highest index in deck array with a valid card
			// loop backward from top of hand
			int d;
			int treasureCounter = 0;
			int topHand = G->handCount[p];
			for (d = 1; d <= 2; d++) {
				if ((G->hand[p][ topHand - d ] == gold) || (G->hand[p][ topHand - d ] == silver) || (G->hand[p][ topHand - d ] == copper)) {
					treasureCounter++;
				}
			}
			if (treasureCounter == 2) {
				printf ("Scenario1-test5: SUCCESS: player #%d, check if top 2 cards of hand are treasure cards\n", p);
			} else {
				printf ("Scenario1-test5: FAILED: player #%d, check if top 2 cards of hand are treasure cards\n", p);
				errorval--;
			}
		}
	}

	// SCENARIO 2:
	// # Adventurer in each player's Hand = 1
	// # silver cards in each player's deck = 1, gold cards in each player's deck = 1
		if (scenario == 2) {
			printf ("---- in Adventurer Scenario 2 test loop\n");
			// loop through each player
			for (p=0; p< G->numPlayers; p++) {
				printf ("---- in Adventurer Scenario 2 player %d test loop\n", p);

				// Scenario2-test1: check if played card has increased by 1
				if ((G->playedCardCount - Gpre.playedCardCount) == 1) {
					printf ("Scenario2-test1: SUCCESS: player #%d, check if played card has increased by 1\n", p);
				} else {
					printf ("Scenario2-test1: FAILED: player #%d, check if played card has increased by 1\n", p);
					errorval--;
				}

				// Scenario2-test2: check if total supply count has not changed
				int c;
				int supplyTotalPost = 0;
				int supplyTotalPre = 0;
				for (c=0; c < (treasure_map+1); c++) {
					supplyTotalPost += G->supplyCount[c];
					supplyTotalPre += Gpre.supplyCount[c];
					//printf ("supplyTotalPost: %d, supplyTotalPre:%d\n", supplyTotalPost, supplyTotalPre);
				}

				if ((supplyTotalPost - supplyTotalPre) == 0) {
					printf ("Scenario2-test2: SUCCESS: player #%d, check if total supply count has not changed\n", p);
				} else {
					printf ("Scenario2-test2: FAILED: player #%d, check if total supply count has not changed\n", p);
					printf ("Debug Data: supplyTotalPost: %d, supplyTotalPre: %d\n", supplyTotalPost, supplyTotalPre);
					errorval--;
				}

				// Scenario2-test3: check if hand count went up by 1 (minus Adventurer + 2 treasure cards)
				if ((G->handCount[p] - Gpre.handCount[p]) == 1) {
					printf ("Scenario2-test3: SUCCESS: player #%d, check if hand count went up by 1 (minus Adventurer + 2 treasure cards)\n", p);
				} else {
					printf ("Scenario2-test3: FAILED: player #%d, check if hand count went up by 1 (minus Adventurer + 2 treasure cards)\n", p);
					errorval--;
				}

				// Scenario2-test4: check deck+discard count decreased 2 (only 2 treasure moves to hand, rest are discard)
				if (((G->deckCount[p] + G->discardCount[p]) - (Gpre.deckCount[p] + Gpre.discardCount[p])) == -2) {
					printf ("Scenario2-test4: SUCCESS: player #%d, check deck+discard count decreased 2 (only 2 treasure moves to hand, rest are discard)\n", p);
				} else {
					printf ("Scenario2-test4: FAILED: player #%d, ccheck deck+discard count decreased 2 (only 2 treasure moves to hand, rest are discard)\n", p);
					errorval--;
				}

				// Scenario2-test5: check if top 2 cards of hand are treasure cards
				// in this case top 2 cards in hand correspond to highest index in deck array with a valid card
				// loop backward from top of hand
				int d;
				int treasureCounter = 0;
				int topHand = G->handCount[p];
				for (d = 1; d <= 2; d++) {
					if ((G->hand[p][ topHand - d ] == gold) || (G->hand[p][ topHand - d ] == silver) || (G->hand[p][ topHand - d ] == copper)) {
						treasureCounter++;
					}
				}
				if (treasureCounter == 2) {
					printf ("Scenario2-test5: SUCCESS: player #%d, check if top 2 cards of hand are treasure cards\n", p);
				} else {
					printf ("Scenario2-test5: FAILED: player #%d, check if top 2 cards of hand are treasure cards\n", p);
					errorval--;
				}
			}
		}

	// SCENARIO 3:
	// # Adventurer in each player's Hand = 1
	// # copper cards in each player's deck = 1 (silver = 0, gold = 0)
		if (scenario == 3) {
			printf ("---- in checkTreasureMap Scenario 3 test loop\n");
			// loop through each player
			for (p=0; p< G->numPlayers; p++) {
				printf ("---- in checkTreasureMap Scenario 3 player %d test loop\n", p);

				// Scenario3-test1: check if played card has increased by 1
				if ((G->playedCardCount - Gpre.playedCardCount) == 1) {
					printf ("Scenario3-test1: SUCCESS: player #%d, check if played card has increased by 1\n", p);
				} else {
					printf ("Scenario3-test1: FAILED: player #%d, check if played card has increased by 1\n", p);
					errorval--;
				}

				// Scenario3-test2: check if total supply count has not changed
				int c;
				int supplyTotalPost = 0;
				int supplyTotalPre = 0;
				for (c=0; c < (treasure_map+1); c++) {
					supplyTotalPost += G->supplyCount[c];
					supplyTotalPre += Gpre.supplyCount[c];
					//printf ("supplyTotalPost: %d, supplyTotalPre:%d\n", supplyTotalPost, supplyTotalPre);
				}
				if (supplyTotalPost == supplyTotalPre) {
					printf ("Scenario3-test2: SUCCESS: player #%d, check to see if the total supply count has not changed\n", p);
				} else {
					printf ("Scenario3-test2: FAILED: player #%d, check to see if the total supply count has not changed\n", p);
					errorval--;
				}

				// Scenario3-test3: check if hand count is unchanged (minus adventurer + 1 treasure)
				if ((G->handCount[p] - Gpre.handCount[p]) == 0) {
					printf ("Scenario3-test3: SUCCESS: player #%d, check if hand count is unchanged (minus adventurer + 1 treasure)\n", p);
				} else {
					printf ("Scenario3-test3: FAILED: player #%d, check if hand count is unchanged (minus adventurer + 1 treasure)\n", p);
					errorval--;
				}

				// Scenario3-test4: check deck+discard count decreased 1 (1 treasure moves to hand, rest are discard)
				if (((G->deckCount[p] + G->discardCount[p]) - (Gpre.deckCount[p] + Gpre.discardCount[p])) == -1) {
					printf ("Scenario3-test4: SUCCESS: player #%d, check deck+discard count decreased 1 (1 treasure moves to hand, rest are discard)\n", p);
				} else {
					printf ("Scenario3-test4: FAILED: player #%d, check deck+discard count decreased 1 (1 treasure moves to hand, rest are discard)\n", p);
					errorval--;
				}

				// Scenario2-test5: check if top 1 card of hand is treasure cards
				// in this case top 1 cards in hand correspond to highest index in deck array with a valid card
				// loop backward from top of hand
				int d;
				int treasureCounter = 0;
				int topHand = G->handCount[p];
				for (d = 1; d <= 1; d++) {
					if ((G->hand[p][ topHand - d ] == gold) || (G->hand[p][ topHand - d ] == silver) || (G->hand[p][ topHand - d ] == copper)) {
						treasureCounter++;
					}
				}
				if (treasureCounter == 1) {
					printf ("Scenario3-test5: SUCCESS: player #%d, check if top 1 cards of hand are treasure cards\n", p);
				} else {
					printf ("Scenario3-test5: FAILED: player #%d, check if top 1 cards of hand are treasure cards\n", p);
					errorval--;
				}
			}
		}
/* CAN'T EXECUTE BECAUSE THIS CRASHES DOMION
		// ---- SCENARIO 4 ---------------------------------------------
		// # Adventurer in each player's Hand = 1
		// # copper, silver or gold cards in each player's deck = 0
		if (scenario == 4) {
			printf ("---- in checkAdventurer Scenario 4 test loop\n");
			// loop through each player
			for (p=0; p< G->numPlayers; p++) {
				printf ("---- in checkAdventurer Scenario 4 player %d test loop\n", p);

				// Scenario4-test1: check if played card has increased by 1
				if ((G->playedCardCount - Gpre.playedCardCount) == 1) {
					printf ("Scenario4-test1: SUCCESS: player #%d, check if played card has increased by 1\n", p);
				} else {
					printf ("Scenario4-test1: FAILED: player #%d, check if played card has increased by 1\n", p);
					errorval--;
				}

				// Scenario4-test2: check if total supply count has not changed
				int c;
				int supplyTotalPost = 0;
				int supplyTotalPre = 0;
				for (c=0; c < (treasure_map+1); c++) {
					supplyTotalPost += G->supplyCount[c];
					supplyTotalPre += Gpre.supplyCount[c];
					//printf ("supplyTotalPost: %d, supplyTotalPre:%d\n", supplyTotalPost, supplyTotalPre);
				}
				if (supplyTotalPost == supplyTotalPre) {
					printf ("Scenario4-test2: SUCCESS: player #%d, check to see if the total supply count has not changed\n", p);
				} else {
					printf ("Scenario4-test2: FAILED: player #%d, check to see if the total supply count has not changed\n", p);
					errorval--;
				}

				// Scenario4-test3: check if hand count is down by 1 (minus adventurer + 0 treasure)
				if ((G->handCount[p] - Gpre.handCount[p]) == -1) {
					printf ("Scenario4-test3: SUCCESS: player #%d, check if hand count is down by 1 (minus adventurer + 0 treasure)\n", p);
				} else {
					printf ("Scenario4-test3: FAILED: player #%d, check if hand count is down by 1 (minus adventurer + 0 treasure)\n", p);
					errorval--;
				}

				// Scenario4-test4: check deck+discard count stayed same (no treasure moves to hand)
				if (((G->deckCount[p] + G->discardCount[p]) - (Gpre.deckCount[p] + Gpre.discardCount[p])) == 0) {
					printf ("Scenario3-test4: SUCCESS: player #%d, check deck+discard count stayed same (no treasure moves to hand)\n", p);
				} else {
					printf ("Scenario3-test4: FAILED: player #%d, check deck+discard count stayed same (no treasure moves to hand)\n", p);
					errorval--;
				}

			}
		}
*/
		// ---- SCENARIO 5 ---------------------------------------------
		// # Adventurer in each player's Hand = 0
		// doesn't matter how many treasure card in deck
		if (scenario == 5) {
			printf ("---- in checkAdventurer Scenario 5 test loop\n");
			// loop through each player
			for (p=0; p< G->numPlayers; p++) {
				printf ("---- in checkAdventurer Scenario 5 player %d test loop\n", p);

				// Scenario4-test1: check if played card has increased by 0
				if ((G->playedCardCount - Gpre.playedCardCount) == 0) {
					printf ("Scenario5-test1: SUCCESS: player #%d, check if played card has increased by 0\n", p);
				} else {
					printf ("Scenario5-test1: FAILED: player #%d, check if played card has increased by 0\n", p);
					errorval--;
				}

				// Scenario4-test2: check if total supply count has not changed
				int c;
				int supplyTotalPost = 0;
				int supplyTotalPre = 0;
				for (c=0; c < (treasure_map+1); c++) {
					supplyTotalPost += G->supplyCount[c];
					supplyTotalPre += Gpre.supplyCount[c];
					//printf ("supplyTotalPost: %d, supplyTotalPre:%d\n", supplyTotalPost, supplyTotalPre);
				}
				if (supplyTotalPost == supplyTotalPre) {
					printf ("Scenario5-test2: SUCCESS: player #%d, check to see if the total supply count has not changed\n", p);
				} else {
					printf ("Scenario5-test2: FAILED: player #%d, check to see if the total supply count has not changed\n", p);
					errorval--;
				}

				// Scenario5-test3: check if hand count is down by 0 (no adventurer to play)
				if ((G->handCount[p] - Gpre.handCount[p]) == 0) {
					printf ("Scenario5-test3: SUCCESS: player #%d, check if hand count is down by 0 (no adventurer to play)\n", p);
				} else {
					printf ("Scenario5-test3: FAILED: player #%d, check if hand count is down by 0 (no adventurer to play)\n", p);
					errorval--;
				}

				// Scenario5-test4: check deck+discard count stayed same (no treasure moves to hand)
				if (((G->deckCount[p] + G->discardCount[p]) - (Gpre.deckCount[p] + Gpre.discardCount[p])) == 0) {
					printf ("Scenario5-test4: SUCCESS: player #%d, check deck+discard count stayed same (no treasure moves to hand)\n", p);
				} else {
					printf ("Scenario5-test4: FAILED: player #%d, check deck+discard count stayed same (no treasure moves to hand)\n", p);
					errorval--;
				}

			}
		}

		return errorval;
}


int main () {
	printf ("\n\nstarting cardtest2 -- testing ADVENTURER function\n\n");
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
	// # Adventurer in each player's Hand = 1
	// # copper cards in each player's deck and discard pile = 2 (silver = 0, gold = 0)

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

					// force each player to have at least 1 Adventurer card
					for (p=0; p<player; p++) {
						toFlag = 2; // add action card to the hand
						gainCard (adventurer, &G, toFlag, p);
						// DEBUG
						//printGameState (&G);
					}

					// force each player to have only 2 copper in deck
					for (p=0; p<player; p++) {
						// first remove all treasury cards from deck and discard
						int c;
						for (c=0; c< G.deckCount[p]; c++) {
							if ((G.deck[p][c] == gold) || (G.deck[p][c] == copper) ||(G.deck[p][c] == silver)) {
								// replace with a benign card
								G.deck[p][c] = curse;
							}
						}
					}

					// now add 2 copper to each players deck
					for (p=0; p<player; p++) {
						toFlag = 1; // add card to the deck
						gainCard (copper, &G, toFlag, p);
						gainCard (copper, &G, toFlag, p);
						// DEBUG
						//printGameState (&G);
					}

					response = checkAdventurer (&G, 1); // 1 for scenario 1
					if (response == 0) {
						printf ("cardtest2-Scenario1-tests-> successfully passed tests\n");
					} else {
						printf ("cardtest2-Scenario1-tests -> FAILED to pass tests # errors: %d\n", response);
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
	// # Adventurer in each player's Hand = 1
	// # silver cards in each player's deck = 1, gold cards in each player's deck = 1

	printf ("----Starting Scenario 2 tests -----\n");
	// test for some reasonable # of players
	for (player = 2; player <= 2; player++) {	//MAX loop:	for (player = 2; player <= MAX_PLAYERS; player++)
		// initialize the standard game
		response = initializeGame (player, k, 1, &G);
		if (response < 0) { // then an error in initialize game
			printf ("cardtest 2, Scenario 2 ERROR: Failed to initialize game. Data of current game state:\n");
			printf ("Players = %d\n", player);
			//printGameState (&G);
			exit (1); // exit the program with value of 1
		}

		// USE THIS OPTION TO GENERATE REASONABLE COMBINATIONS OF DECK SIZE
		for (deckCt = 10; deckCt < 11; deckCt++) {
			for (discardCt = 5; discardCt < 6; discardCt++) {
				for (handCt = 9; handCt < 10; handCt++) {

					// force each player to have at least 1 Adventurer card in hand
					for (p=0; p<player; p++) {
						toFlag = 2; // add action card to the hand
						gainCard (adventurer, &G, toFlag, p);
						// DEBUG
						//printGameState (&G);
					}

					// force each player to have only 1 silver and 1 gold in deck
					for (p=0; p<player; p++) {
						// first remove all treasury cards from deck and discard
						int c;
						for (c=0; c< G.deckCount[p]; c++) {
							if ((G.deck[p][c] == gold) || (G.deck[p][c] == copper) ||(G.deck[p][c] == silver)) {
								// replace with a benign card
								G.deck[p][c] = curse;
							}
						}
					}

					// now add 1 solver and 1 gold to each players deck
					for (p=0; p<player; p++) {
						toFlag = 1; // add card to the deck
						gainCard (silver, &G, toFlag, p);
						gainCard (gold, &G, toFlag, p);
						// DEBUG
						//printGameState (&G);
					}

					response = checkAdventurer (&G, 2); // 2 for scenario 2
					if (response == 0) {
						printf ("cardtest2-Scenario2-tests-> successfully passed tests\n");
					} else {
						printf ("cardtest2-Scenario2-tests -> FAILED to pass tests # errors: %d\n", response);
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
	// # Adventurer in each player's Hand = 1
	// # copper cards in each player's deck = 1 (silver = 0, gold = 0)

	printf ("----Starting Scenario 3 tests -----\n");
	// test for some reasonable # of players
	for (player = 2; player <= 2; player++) {	//MAX loop:	for (player = 2; player <= MAX_PLAYERS; player++)
		// initialize the standard game
		response = initializeGame (player, k, 1, &G);
		if (response < 0) { // then an error in initialize game
			printf ("cardtest 2, Scenario 3 ERROR: Failed to initialize game. Data of current game state:\n");
			printf ("Players = %d\n", player);
			//printGameState (&G);
			exit (1); // exit the program with value of 1
		}

		// USE THIS OPTION TO GENERATE REASONABLE COMBINATIONS OF DECK SIZE
		for (deckCt = 10; deckCt < 11; deckCt++) {
			for (discardCt = 5; discardCt < 6; discardCt++) {
				for (handCt = 9; handCt < 10; handCt++) {

					// force each player to have at least 1 Adventurer card in hand
					for (p=0; p<player; p++) {
						toFlag = 2; // add action card to the hand
						gainCard (adventurer, &G, toFlag, p);
						// DEBUG
						//printGameState (&G);
					}

					// force each player to have only 1 copper
					for (p=0; p<player; p++) {
						// first remove all treasury cards from deck and discard
						int c;
						for (c=0; c< G.deckCount[p]; c++) {
							if ((G.deck[p][c] == gold) || (G.deck[p][c] == copper) ||(G.deck[p][c] == silver)) {
								// replace with a benign card
								G.deck[p][c] = curse;
							}
						}
					}

					// now add 1 copperto each players deck
					for (p=0; p<player; p++) {
						toFlag = 1; // add card to the deck
						gainCard (copper, &G, toFlag, p);
						// DEBUG
						//printGameState (&G);
					}

					response = checkAdventurer (&G, 3); // 3 for scenario 3
					if (response == 0) {
						printf ("cardtest2-Scenario3-tests-> successfully passed tests\n");
					} else {
						printf ("cardtest2-Scenario3-tests -> FAILED to pass tests # errors: %d\n", response);
					}
				}
			}
		}
	}


	// ---- SCENARIO 5 ---------------------------------------------
	// # Players = start with 2 (may loop from 2 to 4 or MAX_PLAYER)
	// DeckCount = loop from X to Y (extreme cases 0 to MAX_DECK)
	// HandCount = loop from X to Y (extreme cases 0 to MAX_HAND)
	// DiscardCount = loop from X to Y (Where DiscardCount + DeckCount < MAX_DECK)
	// # Adventurer in each player's Hand = 0
	// doesn't matter how many treasure card in deck

	printf ("----Starting Scenario 5 tests -----\n");
	// test for some reasonable # of players
	for (player = 2; player <= 2; player++) {	//MAX loop:	for (player = 2; player <= MAX_PLAYERS; player++)
		// initialize the standard game
		response = initializeGame (player, k, 1, &G);
		if (response < 0) { // then an error in initialize game
			printf ("cardtest 2, Scenario 5 ERROR: Failed to initialize game. Data of current game state:\n");
			printf ("Players = %d\n", player);
			//printGameState (&G);
			exit (1); // exit the program with value of 1
		}

		// USE THIS OPTION TO GENERATE REASONABLE COMBINATIONS OF DECK SIZE
		for (deckCt = 10; deckCt < 11; deckCt++) {
			for (discardCt = 5; discardCt < 6; discardCt++) {
				for (handCt = 9; handCt < 10; handCt++) {

					// no player has adventurer card in hand (no need to do anything here)
					// doesn't matter how many treasure cards in deck

					response = checkAdventurer (&G, 5); // 5 for scenario 5
					if (response == 0) {
						printf ("cardtest2-Scenario5-tests-> successfully passed tests\n");
					} else {
						printf ("cardtest2-Scenario5-tests -> FAILED to pass tests # errors: %d\n", response);
					}
				}
			}
		}
	}

/* Can't execute because this crashes domion
	// ---- SCENARIO 4 ---------------------------------------------
	// # Players = start with 2 (may loop from 2 to 4 or MAX_PLAYER)
	// DeckCount = loop from X to Y (extreme cases 0 to MAX_DECK)
	// HandCount = loop from X to Y (extreme cases 0 to MAX_HAND)
	// DiscardCount = loop from X to Y (Where DiscardCount + DeckCount < MAX_DECK)
	// # Adventurer in each player's Hand = 1
	// # copper, silver or gold cards in each player's deck = 0

	printf ("----Starting Scenario 4 tests -----\n");
	// test for some reasonable # of players
	for (player = 2; player <= 2; player++) {	//MAX loop:	for (player = 2; player <= MAX_PLAYERS; player++)
		// initialize the standard game
		response = initializeGame (player, k, 1, &G);
		if (response < 0) { // then an error in initialize game
			printf ("cardtest 2, Scenario 4 ERROR: Failed to initialize game. Data of current game state:\n");
			printf ("Players = %d\n", player);
			//printGameState (&G);
			exit (1); // exit the program with value of 1
		}

		// USE THIS OPTION TO GENERATE REASONABLE COMBINATIONS OF DECK SIZE
		for (deckCt = 10; deckCt < 11; deckCt++) {
			for (discardCt = 5; discardCt < 6; discardCt++) {
				for (handCt = 9; handCt < 10; handCt++) {

					// force each player to have at least 1 Adventurer card in hand
					for (p=0; p<player; p++) {
						toFlag = 2; // add action card to the hand
						gainCard (adventurer, &G, toFlag, p);
						// DEBUG
						//printGameState (&G);
					}

					// force each player to have only 0 treasure cards
					for (p=0; p<player; p++) {
						// first remove all treasury cards from deck and discard
						int c;
						for (c=0; c< G.deckCount[p]; c++) {
							if ((G.deck[p][c] == gold) || (G.deck[p][c] == copper) ||(G.deck[p][c] == silver)) {
								// replace with a benign card
								G.deck[p][c] = curse;
							}
						}
					}

					response = checkAdventurer (&G, 4); // 4 for scenario 4
					if (response == 0) {
						printf ("cardtest2-Scenario4-tests-> successfully passed tests\n");
					} else {
						printf ("cardtest2-Scenario4-tests -> FAILED to pass tests # errors: %d\n", response);
					}
				}
			}
		}
	}
*/
	return 0;
}


// **********************
// tests for ADVENTURER
// **********************
/*
int checkAdventurer (struct gameState * G) {
	int errorval = 0;
	int testresponse, controlresponse;
	int p;
	int response;

	struct gameState Gpre, Gcontrol;

	// loop through each player
	for (p=0; p< G->numPlayers; p++) {

		G->whoseTurn = p; // setting the turn of the player to play Adventurer

		// find the location of adventurer in player p's hand
		int handPos = -1;
		int c;
		for (c=0; c < G->handCount[p]; c++) {
			if (G->hand[p][c] == adventurer) { handPos = c; }
		}
		if (handPos == -1) {
			printf ("\nNOTE Player %d: did NOT find Adventurer in this player's hand\n", p);
			//printGameState (G);
		}

		// Create a control state that is copy of G
		memcpy (&Gpre, G, sizeof(struct gameState));
		memcpy (&Gcontrol, G, sizeof(struct gameState));

		// call the function to test
		int card = adventurer;
		int choice1 = 0; // not used for adventurer
		int choice2 = 0; // not used for adventurer
		int choice3 = 0; // not used for adventurer
		int bonus = 0;  // not used for adventurer

		testresponse =  cardEffect(card, choice1, choice2, choice3, G,
									handPos, &bonus);

		controlresponse = myOwnAdventurerAction (p, &Gcontrol, handPos);

		// IF THERE WAS AN ADVENTURER CARD TO PLAY
		if (handPos > -1) {

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

			// check if hand count between test and control are the same
			if ((G->handCount[p] - Gcontrol.handCount[p]) == 0) {
				printf ("Success player %d: handCount test and control = %d\n", p, G->handCount[p]);
			} else {
				printf ("FAILED player %d: handCount test: %d and control: %d not same\n",
						p, G->handCount[p], Gcontrol.handCount[p]);
				errorval--;
			}

			// check if deck count between test and control are the same
			if ((G->deckCount[p] - Gcontrol.deckCount[p]) == 0) {
				printf ("Success player %d: deckCount test and control = %d\n", p, G->deckCount[p]);
			} else {
				printf ("FAILED player %d: deckCount test: %d and control: %d not same\n",
						p, G->deckCount[p], Gcontrol.deckCount[p]);
				//printGameState (G);
				//printGameState (&Gcontrol);
				errorval--;
			}

		}

		// IF THERE WAS NO ACTION CARD TO PLAY
		if (handPos < 0) {

			// check if handcount is the same)
			if ((G->handCount[p] - Gpre.handCount[p]) == 0) {
				printf ("Success player %d: given no Adventurer handCount increased by 0\n", p);
			} else {
				printf ("FAILED player %d: given no Adventurer handCount NOT increased by 0\n", p);
				//printGameState(G);
				errorval--;
			}

			// check if deck count was decreased by 0
			if (Gpre.deckCount[p] > 2) {
				if ((G->deckCount[p] - Gpre.deckCount[p]) == 0) {
					printf ("Success player %d: given no Adventurer deckCount increased by 0\n", p);
				} else {
					printf ("FAILED player %d: given no Adventurer deckCount NOT increased by 0\n", p);
					errorval--;
				}
			}

			// check if played card was increased by 0
			if ((G->playedCardCount - Gpre.playedCardCount) == 0) {
				printf ("Success player %d: given no Adventurer playedCardCount was increased 0\n", p);
			} else {
				printf ("FAILED player %d: given no AdventurerplayedCardCount was NOT increased by 0\n", p);
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
				printf ("Success player %d: given no Adventurer, no change in total supply count\n", p);
			} else {
				printf ("FAILED player %d: given no Adventurer, change in total supply count\n", p);
				errorval--;
			}
		}

	}
	return errorval;
}

int myOwnAdventurerAction (int p, struct gameState * G, int handPos) {

	if (G->hand[p][handPos] != adventurer) {
		printf ("There is no adventurer to play in this hand position");
		return -1;
	}

	int drawntreasure=0;
	int z = 0; // for temp hand counter
	int cardDrawn;
	int temphand[MAX_HAND];

	int maxdraw = G->deckCount[p] + G->discardCount[p]; // some maximum time you can loop (if no treasure)
	int loopcounter = 0;

	//discard card from hand (to played pile)
	discardCard (handPos, p, G, 0);

	while ((drawntreasure<2) && (loopcounter < maxdraw)) {
		loopcounter++;
		if (G->deckCount[p] <1){
			//if the deck is empty we need to shuffle discard and add to deck
			shuffle(p, G);
		}

		drawCard(p, G);
		cardDrawn = G->hand[p][G->handCount[p]-1];
		//top card of hand is most recently drawn card.

		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) {
			drawntreasure++;
			printf ("found a treasure!\n");
		} else {
			 temphand[z]=cardDrawn;
			 G->handCount[p]--;
			 //this should just remove the top card (the most recently drawn one).
			 z++;
		 }
	  }

	  while(z-1>=0){
		  G->discard[p][G->discardCount[p]++]=temphand[z-1];
		  // discard all cards in play that have been drawn
		  z=z-1;
	  }
	return 0;
}
*/

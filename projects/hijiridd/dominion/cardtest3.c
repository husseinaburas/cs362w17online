// ***************
// * cardtest3.c
// * Desc: Unit test for treasure map card in domion.c
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
int checkTreasureMap (struct gameState * G, int scenario);

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
// tests for Treasure Map
// **********************
int checkTreasureMap (struct gameState * G, int scenario) {
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

		// find the location of treasure_map in player p's hand
		int handPos = -1; // default is that there is no treasure_map in hand
		int c;
		for (c=0; c < G->handCount[p]; c++) {
			if (G->hand[p][c] == treasure_map) { handPos = c; }
		}
		if (handPos == -1) {
			printf ("NOTE Player %d: did NOT find Treasure Map in player's hand\n", p);
			//printGameState (G);
		}

		// call the function to test
		int card = treasure_map;
		int choice1 = 0; // not used for treasure_map
		int choice2 = 0; // not used for treasure_map
		int choice3 = 0; // not used for treasure_map
		int bonus = 0;  // not used for treasure_map
		testresponse =  cardEffect(card, choice1, choice2, choice3, G,
									handPos, &bonus);
		//controlresponse = myOwnTreasureMap (p, &Gcontrol, handPos);
	}

	// SCENARIO 1: IF THERE WERE 2 TREAURE MAP CARDS IN HAND
	if (scenario == 1) {
		printf ("---- in checkTreasureMap Scenario 1 test loop\n");
		// loop through each player
		for (p=0; p< G->numPlayers; p++) {
			printf ("---- in checkTreasureMap Scenario 1 player %d test loop\n", p);

			// Scenario1-test1: check if played card is unchanged (both cards go to trash)
			if ((G->playedCardCount - Gpre.playedCardCount) == 0) {
				printf ("Scenario1-test1: SUCCESS: player #%d, check if played card unchanged (both cards go to trash)\n", p);
			} else {
				printf ("Scenario1-test1: FAILED: player #%d, check if played card unchanged (both cards go to trash)\n", p);
				errorval--;
			}

			// Scenario1-test2: check if total supply count has gone down by 4 * # players
			int c;
			int supplyTotalPost = 0;
			int supplyTotalPre = 0;
			for (c=0; c < (treasure_map+1); c++) {
				supplyTotalPost += G->supplyCount[c];
				supplyTotalPre += Gpre.supplyCount[c];
				//printf ("supplyTotalPost: %d, supplyTotalPre:%d\n", supplyTotalPost, supplyTotalPre);
			}
			if ((supplyTotalPost - supplyTotalPre) == -(4 * G->numPlayers)) {
				printf ("Scenario1-test2: SUCCESS: player #%d, check if total supply count has gone down by 4 * # players\n", p);
			} else {
				printf ("Scenario1-test2: FAILED: player #%d, check if total supply count has gone down by 4 * # players\n", p);
				printf ("supplyTotalPost: %d, supplyTotalPre: %d\n", supplyTotalPost, supplyTotalPre);
				errorval--;
			}

			// Scenario1-test3: check if hand count went down by two
			if ((G->handCount[p] - Gpre.handCount[p]) == -2) {
				printf ("Scenario1-test3: SUCCESS: player #%d, check if hand count went down by two\n", p);
			} else {
				printf ("Scenario1-test3: FAILED: player #%d, check if hand count went down by two\n", p);
				errorval--;
			}

			// Scenario1-test4: check if deck count increased by 4
			if ((G->deckCount[p] - Gpre.deckCount[p]) == 4) {
				printf ("Scenario1-test4: SUCCESS: player #%d, check if deck count increased by 4\n", p);
			} else {
				printf ("Scenario1-test4: FAILED: player #%d, check if deck count increased by 4\n", p);
				errorval--;
			}

			// Scenario1-test5: check if top 4 cards of deck are gold cards
			// in this case top 4 cards in deck correspond to highest index in deck array with a valid card
			// loop backward from top of deck
			int d;
			int goldCounter = 0;
			int topDeck = G->deckCount[p];
			for (d = 1; d <= 4; d++) {
				if (G->deck[p][ topDeck - d ] == gold) {
					goldCounter++;
				}
			}
			if (goldCounter == 4) {
				printf ("Scenario1-test5: SUCCESS: player #%d, check if top 4 cards of deck are gold cards\n", p);
			} else {
				printf ("Scenario1-test5: FAILED: player #%d, check if top 4 cards of deck are gold cards\n", p);
				errorval--;
			}
		}
	}

	// SCENARIO 2: IF THERE WAS ONLY 1 TREAURE MAP CARDS IN HAND
		if (scenario == 2) {
			printf ("---- in checkTreasureMap Scenario 2 test loop\n");
			// loop through each player
			for (p=0; p< G->numPlayers; p++) {
				printf ("---- in checkTreasureMap Scenario 2 player %d test loop\n", p);
				// Scenario2-test1: check if played card count is unchanged (treasure map cards go to trash)
				if ((G->playedCardCount - Gpre.playedCardCount) == 0) {
					printf ("Scenario1-test1: SUCCESS: player #%d, check if played card count unchanged (treasure map cards go to trash)\n", p);
				} else {
					printf ("Scenario1-test1: FAILED: player #%d, check if played card count unchanged (treasure map cards go to trash)\n", p);
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

				// Scenario2-test3: check if hand count went down by 1
				if ((G->handCount[p] - Gpre.handCount[p]) == -1) {
					printf ("Scenario2-test3: SUCCESS: player #%d, check if hand count went down by 1\n", p);
				} else {
					printf ("Scenario2-test3: FAILED: player #%d, check if hand count went down by 1\n", p);
					printf ("G->handCount[%d]: %d, Gpre.handCount[%d]: %d\n", p, G->handCount[p], p, Gpre.handCount[p]);
					errorval--;
				}

				// Scenario1-test4: check if deck count increased by 0
				if ((G->deckCount[p] - Gpre.deckCount[p]) == 0) {
					printf ("Scenario2-test4: SUCCESS: player #%d, check if deck count increased by 0\n", p);
				} else {
					printf ("Scenario2-test4: FAILED: player #%d, check if deck count increased by 0\n", p);
					errorval--;
				}
			}
		}

	// SCENARIO 3: IF THERE WAS 0 TREAURE MAP CARDS IN HAND
		if (scenario == 3) {
			printf ("---- in checkTreasureMap Scenario 3 test loop\n");
			// loop through each player
			for (p=0; p< G->numPlayers; p++) {
				printf ("---- in checkTreasureMap Scenario 3 player %d test loop\n", p);
				// Scenario3-test1: check if played card count is unchanged (treasure map cards go to trash)
				if ((G->playedCardCount - Gpre.playedCardCount) == 0) {
					printf ("Scenario3-test1: SUCCESS: player #%d, check if played card count unchanged (treasure map cards go to trash)\n", p);
				} else {
					printf ("Scenario3-test1: FAILED: player #%d, check if played card count unchanged (treasure map cards go to trash)\n", p);
					errorval--;
				}

				// Scenario3-test2: check to see if the total supply count has not changed
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

				// Scenario3-test3: check if hand count has not changed
				if ((G->handCount[p] - Gpre.handCount[p]) == 0) {
					printf ("Scenario3-test3: SUCCESS: player #%d, check if hand count has not changed\n", p);
				} else {
					printf ("Scenario3-test3: FAILED: player #%d, check if hand count has not changed\n", p);
					errorval--;
				}

				// Scenario3-test4: check if deck count has not changed
				if ((G->deckCount[p] - Gpre.deckCount[p]) == 0) {
					printf ("Scenario3-test4: SUCCESS: player #%d, check if deck count has not changed\n", p);
				} else {
					printf ("Scenario3-test4: FAILED: player #%d, check if deck count has not changed\n", p);
					errorval--;
				}
			}
		}
	return errorval;
}

int main () {
	printf ("\n\nstarting cardtest3 -- testing TREASURE MAP function\n\n");
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
	// # of Treasure Maps in each player's Hand = 2

	// SCENARIO 1: setup game
	printf ("----Starting Scenario 1 tests -----\n");
	// test for some reasonable # of players
	for (player = 2; player <= 2; player++) {	//MAX loop:	for (player = 2; player <= MAX_PLAYERS; player++)
		// initialize the standard game
		response = initializeGame (player, k, 1, &G);
		if (response < 0) { // then an error in initialize game
			printf ("cardtest 3, Scenario 1 ERROR: Failed to initialize game. Data of current game state:\n");
			printf ("Players = %d\n", player);
			//printGameState (&G);
			exit (1); // exit the program with value of 1
		}

		// USE THIS OPTION TO GENERATE REASONABLE COMBINATIONS OF DECK SIZE
		for (deckCt = 10; deckCt < 11; deckCt++) {
			for (discardCt = 5; discardCt < 6; discardCt++) {
				for (handCt = 9; handCt < 10; handCt++) {

					// force each player to have 2 Treasure Maps in each player's hand.
					for (p=0; p<player; p++) {
						toFlag = 2; // add action card to the hand
						gainCard (treasure_map, &G, toFlag, p);
						gainCard (treasure_map, &G, toFlag, p);
						// DEBUG
						//printGameState (&G);
					}
					response = checkTreasureMap (&G, 1); // 1 for scenario 1
					if (response == 0) {
						printf ("cardtest3-Scenario1-tests-> successfully passed tests\n");
					} else {
						printf ("cardtest3-Scenario1-tests -> FAILED to pass tests # errors: %d\n", response);
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
	// # of Treasure Maps in each player's Hand = 1

	// SCENARIO 2: setup game
	printf ("----Starting Scenario 2 tests -----\n");
	// test for some reasonable # of players
	for (player = 2; player <= 2; player++) {	//MAX loop:	for (player = 2; player <= MAX_PLAYERS; player++)
		// initialize the standard game
		response = initializeGame (player, k, 1, &G);
		if (response < 0) { // then an error in initialize game
			printf ("cardtest 3, Scenario 1 ERROR: Failed to initialize game. Data of current game state:\n");
			printf ("Players = %d\n", player);
			//printGameState (&G);
			exit (1); // exit the program with value of 1
		}

		// USE THIS OPTION TO GENERATE REASONABLE COMBINATIONS OF DECK SIZE
		for (deckCt = 10; deckCt < 11; deckCt++) {
			for (discardCt = 5; discardCt < 6; discardCt++) {
				for (handCt = 8; handCt < 10; handCt++) {

					// force each player to have 1 Treasure Map in each player's hand.
					for (p=0; p<player; p++) {
						toFlag = 2; // add action card to the hand
						gainCard (treasure_map, &G, toFlag, p);
						// DEBUG
						//printGameState (&G);
					}
					response = checkTreasureMap (&G, 2); // 2 for scenario 2
					if (response == 0) {
						printf ("cardtest3-Scenario2-tests-> successfully passed tests\n");
					} else {
						printf ("cardtest3-Scenario2-tests -> FAILED to pass tests # errors: %d\n", response);
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
	// # of Treasure Maps in each player's Hand = 0

	// SCENARIO 3: setup game
	// test for some reasonable # of players
	printf ("----Starting Scenario 3 tests -----\n");
	for (player = 2; player <= 2; player++) {	//MAX loop:	for (player = 2; player <= MAX_PLAYERS; player++)
		// initialize the standard game
		response = initializeGame (player, k, 1, &G);
		if (response < 0) { // then an error in initialize game
			printf ("cardtest 3, Scenario 1 ERROR: Failed to initialize game. Data of current game state:\n");
			printf ("Players = %d\n", player);
			//printGameState (&G);
			exit (1); // exit the program with value of 1
		}

		// USE THIS OPTION TO GENERATE REASONABLE COMBINATIONS OF DECK SIZE
		for (deckCt = 10; deckCt < 11; deckCt++) {
			for (discardCt = 5; discardCt < 6; discardCt++) {
				for (handCt = 8; handCt < 10; handCt++) {

					// force each player to have 0 Treasure Map in each player's hand.
					// In this case we do nothing since there is no Treasure Map in hand for default initialization
					response = checkTreasureMap (&G, 3); // 3 for scenario 3

					if (response == 0) {
						printf ("cardtest3-Scenario3-tests-> successfully passed tests\n");
					} else {
						printf ("cardtest3-Scenario3-tests -> FAILED to pass tests # errors: %d\n", response);
					}
				}
			}
		}
	}
	return 0;
}

		// now loop through different sizes of deck, hand, and discard counts

		// USE THIS OPTION TO GENERATE ALL POSSIBLE COMBINATIONS OF DECK SIZE
//		for (deckCt = 0; deckCt < MAX_DECK; deckCt++) {
//			for (discardCt = 0; discardCt < MAX_DECK; discardCt++) {
//				for (handCt = 0; handCt < MAX_HAND; handCt++) {
//
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

/*
    case treasure_map:
      //search hand for another treasure_map
      index = -1;
      for (i = 0; i < state->handCount[currentPlayer]; i++)
      {
	  if (state->hand[currentPlayer][i] == treasure_map && i != handPos)
	    {
	      index = i;
	      break;
	    }
      }
      if (index > -1) {
		  //trash both treasure cards
		  discardCard(handPos, currentPlayer, state, 1);
		  discardCard(index, currentPlayer, state, 1);

		  //gain 4 Gold cards
		  for (i = 0; i < 4; i++) {
			  gainCard(gold, state, 1, currentPlayer);
		  }

		  //return success
		  return 1;
      }

      //no second treasure_map found in hand
      return -1;
    }
*/





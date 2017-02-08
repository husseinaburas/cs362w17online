// ***************
// * unittest4.c
// * Desc: Unit test for gainCard() function in domion.c
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
//int myOwnGainCard (int supplyPile, struct gameState * G, int destination, int player);
int fillHandWithCards (struct gameState * G, int handCt);
int fillDiscardWithCards (struct gameState * G, int discardCt);
int fillDeckWithCards(struct gameState * G, int deckCt);

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
// tests for gainCard()
// **********************
int checkGainCard (struct gameState * G) {
	int errorval = 0;
	int testresponse, controlresponse;
	int p;
	int response;
	testresponse = 0; controlresponse = 0; response = 0; // to quite unused var warning

	struct gameState Gpre;


	// Set supply position for each player
	int supplyPos[G->numPlayers];
	int toFlag [G->numPlayers];
	for (p=0; p<G->numPlayers; p++) {

		if (p == 0) { supplyPos[p] = 7; } // // player 1 gets card 7 (adventurer)
		if (p == 1) { supplyPos[p] = 9; } // player 2 card 9 (feast)
		if (p == 2) { supplyPos[p] = 13; } // player 3 card13 (smithy),
		if (p == 3) { supplyPos[p] = 16; } // player 4 card 16 (great hall)

		toFlag[p] = p+1; // player1 put card in discard, player 2 to deck
		if (toFlag[p] >  2) { toFlag[p] = 0; } // cant' be bigger than 2
	}

	// loop for each player
	for (p=0; p< G->numPlayers; p++) {

		// Create a control state that is copy of G
		memcpy (&Gpre, G, sizeof(struct gameState));

		// call the function to test
		testresponse = gainCard (supplyPos[p], G, toFlag[p], p);

		// compare the G (post change) with Gpre (previous version unchanged)

		// check if original supply card was zero or not used
		int supplyFlag = 1; //default that there was enough supply to draw the card
		if (Gpre.supplyCount[ supplyPos[p] ] < 1) { // if 0 or -1 for supply position, there shoud be no change
			supplyFlag = 0; // then set supplyFlag to show no card was drawn
			printf ("there was no supply pile to draw down...\n");
		}

		// IF SUPPLY COUNT WAS CHANGED
		if (supplyFlag) {

			// for the given supply card, check if the supply card is decreased by 1
			if ((G->supplyCount[ supplyPos[p] ] - Gpre.supplyCount[ supplyPos[p] ]) == -1) {
				printf ("Success player %d: target supply card #%d was reduced by 1\n", p, supplyPos[p]);
			} else {
				printf ("FAILEDplayer %d: target supply card #%d was NOT reduced by 1\n", p, supplyPos[p]);
				errorval--;
			}

			// if toFlag == 1 (deck), check if deckCount increased by 1
			if (toFlag[p] == 1) {
				if ((G->deckCount[p] - Gpre.deckCount[p]) == 1) {
					printf ("Success player %d: deckCount increased by 1\n", p);
				} else {
					printf ("FAILED player %d: deckCount NOT increased by 1\n", p);
					errorval--;
				}
			}

			// if toFlag == 2 (hand), check if handCount increased by 1
			if (toFlag[p] == 2) {
				if ((G->handCount[p] - Gpre.handCount[p]) == 1) {
					printf ("Success player %d: handCount increased by 1\n", p);
				} else {
					printf ("FAILED player %d: handCount NOT increased by 1\n", p);
					errorval--;
				}
			}

			// if toFlag == 0 (discard), check if discard count increased by 1
			if (toFlag[p] == 0) {
				if ((G->discardCount[p] - Gpre.discardCount[p]) == 1) {
					printf ("Success player %d: discardCount increased by 1\n", p);
				} else {
					printf ("FAILED player %d: discardCount NOT increased by 1\n", p);
					errorval--;
				}
			}

			// check to see if the total supply count has only gone down by one
			int c;
			int supplyTotalPost = 0;
			int supplyTotalPre = 0;
			for (c=0; c < (treasure_map+1); c++) {
				supplyTotalPost += G->supplyCount[c];
				supplyTotalPre += Gpre.supplyCount[c];
			}
			if ((supplyTotalPost - supplyTotalPre) == -1) {
				printf ("Success player %d: total supply count decreased by 1\n", p);
			} else {
				printf ("FAILED player %d: total supply count NOT decreased by 1\n", p);
				printf ("Debug data: supplyTotalPre: %d, supplyTotalPost: %d\n",
						supplyTotalPre, supplyTotalPost);
				errorval--;
			}

		} else { // if there was no supply pile to draw donw on...

			// for the given supply card, check no change to value
			if (G->supplyCount[ supplyPos[p] ] == Gpre.supplyCount[ supplyPos[p] ]) {
				printf ("Success player %d: given no supply to draw down, no change in supply card #%d value\n", p, supplyPos[p]);
			} else {
				printf ("FAILED player %d: given no supply to draw down, target supply card #%d was changed1\n", p, supplyPos[p]);
				errorval--;
			}

			// if toFlag == 1 (deck), check if deckCount is same
			if (toFlag[p] == 1) {
				if (G->deckCount[p] == Gpre.deckCount[p]) {
					printf ("Success player %d: given no supply to draw down, no change in deck count\n", p);
				} else {
					printf ("FAILED player %d: given no supply to draw down, change in deck count\n", p);
					errorval--;
				}
			}

			// if toFlag == 2 (hand), check if handCount increased by 1
			if (toFlag[p] == 2) {
				if (G->handCount[p] == Gpre.handCount[p]) {
					printf ("Success player %d: given no supply to draw down, no change in hand count\n", p);
				} else {
					printf ("FAILED player %d: given no supply to draw down, change in hand count\n", p);
					errorval--;
				}
			}

			// if toFlag == 0 (discard), check if discard count increased by 1
			if (toFlag[p] == 0) {
				if (G->discardCount[p] == Gpre.discardCount[p]) {
					printf ("Success player %d: given no supply to draw down, no change in discard count\n", p);
				} else {
					printf ("FAILED player %d: given no supply to draw down, change in discard count\n", p);
					errorval--;
				}
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
	}
	return errorval;
}

// ****************
// gainCardControl() -- we will use the output of this function to test whether
// 					our target function, gainCard(), output is valid
// Input: pointer to struct gamestate, supply pile # we are gaining a card from, player #, and
//			destination number which determines where the supply card lands
// Output: The game state is changed. returns -1 if there was an error
//
// ****************
/*
int myOwnGainCard (int supplyPile, struct gameState * G, int destination, int player) {
	// check if supply pile is empty or not used
	if ( G->supplyCount[supplyPile] < 1) {
		// if 0 or -1
		return -1;
	}

	// TODO: TEST CASE WHERE DESTINATINON IS <0 or >0
	if ((destination >= 0) && (destination <3)) {

		// destination = 0 : add to discard
		// destination = 1 : add to deck
		// destination = 2 : add to hand
		switch (destination) {
			case 0: // add to discard
				G->discard[player][G->discardCount[player]] = supplyPile;
				G->discardCount[player]++;
				break;
			case 1: // add to deck
				G->deck[player][G->deckCount[player]] = supplyPile;
				G->deckCount[player]++;
				break;
			case 2: // add to hand
				G->hand[player][G->handCount[player]] = supplyPile;
				G->handCount[player]++;
		}
		//decrease number in supply pile
		G->supplyCount[supplyPile]--;
	} else { // invalid destination out of range
		// TODO: error message!
		printf ("gainCardControl() input error, destination is <0 or >2\n");
	}
	return 0;
}
*/

int main () {
	printf ("\n\nstarting unittest4 -- testing gainCard() function\n\n");
	// DEBUGGING
	// printf ("MAX_HAND = %d, MAX_DECK = %d, MAX_PLAYERS = %d\n", MAX_HAND, MAX_DECK, MAX_PLAYERS);
	// MAX_HAND = 500, MAX_DECK = 500, MAX_PLAYERS = 4

	// -----------------
	// setup a standard game
	// -----------------
	struct gameState G; // test game state
	//struct gameState Gcontrol; // control game state (pre-test)
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	           sea_hag, tribute, smithy};

	// -------------------
	// setup the fixed unit tests  !!! WE ARE NOT DOING RANDOM TESTS!!!
	// INSTEAD we are creating fixed tests by looping through different input spaces
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
//	for (player = 2; player <= MAX_PLAYERS; player++) {
	for (player = 2; player <= 4; player++) {

		// initialize the standard game
		response = initializeGame (player, k, 1, &G);
		if (response < 0) { // then an error in initialize game
			printf ("unittest4 ERROR: Failed to initialize game. Data of current game state:\n");
			printf ("Players = %d\n", player);
			//printGameState (&G);
			exit (1); // exit the program with value of 1
		}

		// now loop through different sizes of deck, hand, and discard counts
		// Cases to consider:
		// very large and very small decks, discards and hand counts

		// USE THIS OPTION TO GENERATE ALL POSSIBLE COMBINATIONS OF DECK SIZE
//		for (deckCt = 0; deckCt < MAX_DECK; deckCt++) {
//			for (discardCt = 0; discardCt < MAX_DECK; discardCt++) {
//				for (handCt = 0; handCt < MAX_HAND; handCt++) {
//
		// USE THIS OPTION TO GENERATE SOE REASONABLE COMBINATIONS OF DECK SIZE
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
						printf ("\nUnittest4: gainCard() did not pass our unit test\n");
// TODO CHANGE						printf ("Debug data: trial #%d, handCt = %d, discardCt = %d, deckCt = %d, players = %d, response = %d\n\n",
// TODO CHANGE								trial, handCt, discardCt, deckCt, player, response);
					} else {
						printf ("\nUnittest4: gainCard() TEST SUCCESSFULLY COMPLETED\n\n");
					}
				}
			}
		}
	}
	return 0;
}

/*

 int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
{
  //Note: supplyPos is enum of choosen card

  //check if supply pile is empty (0) or card is not used in game (-1)
  if ( supplyCount(supplyPos, state) < 1 )
    {
      return -1;
    }

  //added card for [whoseTurn] current player:
  // toFlag = 0 : add to discard
  // toFlag = 1 : add to deck
  // toFlag = 2 : add to hand

  if (toFlag == 1)
    {
      state->deck[ player ][ state->deckCount[player] ] = supplyPos;
      state->deckCount[player]++;
    }
  else if (toFlag == 2)
    {
      state->hand[ player ][ state->handCount[player] ] = supplyPos;
      state->handCount[player]++;
    }
  else
    {
      state->discard[player][ state->discardCount[player] ] = supplyPos;
      state->discardCount[player]++;
    }

  //decrease number in supply pile
  state->supplyCount[supplyPos]--;

  return 0;
}



		for (p=0; p<2; p++) {

			// select a supply pile to gain from
			pileTarget = getRandIntLowHigh (0, 26);
			printf ("pileTarget = %d\n", pileTarget);

			// select a random destination
			destinationTarget = getRandIntLowHigh (0, 2);
			printf ("destinationTarget = %d\n", destinationTarget);

			// *****************
			// TODO: make a copy of testGameState!!
			// *****************

			// call control function
			int gainCardControlOutput = gainCardControl(pileTarget, &testGame, destinationTarget, p);
			// call test function
			int gainCardTestOutput = gainCard (pileTarget, &testGame, destinationTarget, p);

			int assertOut = assertTrue(gainCardControlOutput,gainCardTestOutput);

			if (assertOut == 0) {
				int i;
				// For debugging and log output
				printf ("ASSERT FAILED --> LOG GAME SUPPLY STATS ");
				for (i = 0; i < (treasure_map+1); i++) {
					printf ("supply[%d]: %d, ", i, testGame.supplyCount[i]);
				}
				printf ("\n");
			}
		}
	}
	return 0;
}
*/

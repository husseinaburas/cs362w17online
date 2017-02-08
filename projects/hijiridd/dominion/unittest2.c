// ***************
// * unittest2.c
// * Desc: Unit test for updateCoins() function in domion.c
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
int checkUpdateCoins (struct gameState * G);
int myOwnUpdateCoins (int p, struct gameState * G, int bonus);
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
		return 0;
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


int checkUpdateCoins (struct gameState * G) {
	int errorval = 0;
	int testresponse, controlresponse;
	int p;
	int response;

	// Create a control state that is copy of G
	struct gameState Gcontrol;
	memcpy (&Gcontrol, G, sizeof(struct gameState));

	// set bonus to be some positive number
	// if this were a random test, we could make this a random number
	int bonus = 15;

	// loop for each player
	for (p=0; p< G->numPlayers; p++) {

		// this allows the bonus points to be varied systematically per player
		// if the number of players are greater than 3, then this will also test
		// an edge case bonus = negative number
		bonus = bonus - 5;

		// call the function to test
		testresponse = updateCoins (p, G, bonus);

		// call the control function to compare against
		controlresponse = myOwnUpdateCoins (p, &Gcontrol, bonus);

		// compare the two results

		// first compare the test and control response in game.coin
		// Assert test and control are equal
		if (Gcontrol.coins == G->coins) {
			printf ("player %d, coin calculation successful: testresponse = controlresponse = %d\n",
					p, Gcontrol.coins);
		} else {
			printf ("FAILED coin calculation: player: %d, testresponse: %d, controlresponse %d\n",
					p, G->coins, Gcontrol.coins);
			printf ("\nPrinting game state for Gcontrol:\n");
			printGameState (&Gcontrol);
			printf ("\nPrinting game state for G (test):\n");
			printGameState (G);
			errorval--; // subtract -1 for each error encountered.
		}

		// second, compare that the the test and control game states are equal
		// we changed "coins" variable in each test and control
		// assert that G and Gcontrol are equal
		response = memcmp(&Gcontrol, G, sizeof(struct gameState));
		if (response == 0) {
			printf ("gameState compare successful: memcmp response = %d\n", response);
		} else {
			printf ("FAILED gameState compare: player: %d\n", p);
			//printf ("\nPrinting game state for Gcontrol:\n");
			//printGameState (&Gcontrol);
			//printf ("\nPrinting game state for G (test):\n");
			//printGameState (G);
			errorval--; // subtract -1 for each error encountered.
		}
	}
	return errorval;
}

// ****************
// countCoin() -- we will use the output of countCoin() to test whether
// 					our target function, updateCoins() output, is valid
// Input: player #, pointer to struct gamestate, any bonus coin to add
// output: the total amount of coins in a player's hand (copper, silver and gold) plus bonus coin
// ****************
int myOwnUpdateCoins (int p, struct gameState * G, int bonus) {
	int i;
	int copperTot = 0;
	int silverTot = 0;
	int goldTot = 0;
	int c;

	// walk through hand
	for (i = 0; i < G->handCount[p]; i++) {
		c = G->hand[p][i];
		if (c == copper) {
			copperTot++;
		} else if (c == silver) {
			silverTot++;
		} else if (c == gold) {
			goldTot++;
		}
	}

	// walk through deck
	/*for (i = 0; i < G->deckCount[p]; i++) {
		c = G->deck[p][i];
		if (c == copper) {
			copperTot++;
		} else if (c == silver) {
			silverTot++;
		} else if (c == gold) {
			goldTot++;
		} else if (c == duchy) {
			duchyTot++;
		} else if (c == province) {
			provinceTot++;
		} else if (c == gardens) {
			gardensTot++;
		}
	}
	*/
	// walk through discard
	/*for (i = 0; i < G->discardCount[p]; i++) {
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
	} */

	int coinTot = 0;
	// cooper +1 coin
	coinTot += (copperTot * 1);

	// silver +2 coin
	coinTot += (silverTot * 2);

	// gold +3 coin
	coinTot += (goldTot * 3);

	// add bonus
	coinTot += bonus;

	// update the game state
	G->coins = coinTot;
	//printf ("LOG PLAYER %d KEY COIN STATS -> copper cards: %d, silver cards: %d, gold cards: %d, bonus added: %d\n",
	//		p, copperTot, silverTot, goldTot, bonus);
	return 0;
}

// ************************
// main function
// ************************
int main () {
	printf ("\n\nstarting unittest2 -- testing updateCoins() function\n\n");
	// DEBUGGING
	// printf ("MAX_HAND = %d, MAX_DECK = %d, MAX_PLAYERS = %d\n", MAX_HAND, MAX_DECK, MAX_PLAYERS);
	// MAX_HAND = 500, MAX_DECK = 500, MAX_PLAYERS = 4

	// -----------------
	// setup a standard game
	// -----------------
	struct gameState G; // test game state
	struct gameState Gcontrol; // control game state (pre-test)
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
	for (player = 2; player <= 2; player++) {

		// initialize the standard game
		response = initializeGame (player, k, 1, &G);
		if (response < 0) { // then an error in initialize game
			printf ("unittest1 ERROR: Failed to initialize game. Data of current game state:\n");
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
		for (deckCt = 8; deckCt < 11; deckCt++) {
			for (discardCt = 0; discardCt < 6; discardCt++) {
				for (handCt = 0; handCt < 10; handCt++) {

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
					response = checkUpdateCoins (&G);

					// ASSERT TO TEST IF CHECK COMPLETED
					if (!(response == 0)) {
						printf ("\nUnittest2: updateCoins did not pass our unit test\n");
// TODO CHANGE						printf ("Debug data: trial #%d, handCt = %d, discardCt = %d, deckCt = %d, players = %d, response = %d\n\n",
// TODO CHANGE								trial, handCt, discardCt, deckCt, player, response);
					} else {
						printf ("\nUnittest2: TEST SUCCESSFULLY COMPLETED\n\n");
					}
				}
			}
		}
	}
	return 0;
}


// enum CARD {	curse = 0, estate, duchy, province, copper, silver, gold, (#7) adventurer,
//				council_room, feast, (#10) gardens, (#11) mine, remodel, (#13) smithy,
//				(#14) village, baron, great_hall, (#17) minion, steward, (#19) tribute,
//				ambassador, (#21) cutpurse, (#22) embargo, outpost, salvager, (#25) sea_hag,
//				treasure_map };
/*
 * int updateCoins(int player, struct gameState *state, int bonus)
{
  int i;

  //reset coin count
  state->coins = 0;

  //add coins for each Treasure card in player's hand
  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == copper)
	{
	  state->coins += 1;
	}
      else if (state->hand[player][i] == silver)
	{
	  state->coins += 2;
	}
      else if (state->hand[player][i] == gold)
	{
	  state->coins += 3;
	}
    }

  //add bonus
  state->coins += bonus;

  return 0;
}
 */


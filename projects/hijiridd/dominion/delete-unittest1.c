// ***************
// * unittest1.c
// * Desc: Unit test for scorFor() function in domion.c
//****************

#include "dominion.h"
#include "dominion_helpers.h"
#include "dominion_refactorwk2.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int assertTrue();
int anyRandCard ();
int getRandIntLowHigh (int low, int high);
int printGameState (struct gameState * G);

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

int printGameState (struct gameState * G) {
	printf ("numPlayers = %d\n", G->numPlayers);
	int i;
	int totalsupply = 0;;
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
	printf ("whoseTurn = %d\n", G->whoseTurn);
	printf ("phase = %d, ", G->phase);
	printf ("numActions = %d, ", G->numActions);
	printf ("coins = %d, ", G->coins);
	printf ("numBuys = %d\n", G->numBuys);
	int p, j;
	for (p=0; p<2; p++) {
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
		printf ("---------------------\n");
	}
	printf ("playedCardCount = %d, playedCards[x]: \n", G->playedCardCount);
	for (j=0; j< (G->playedCardCount); j++) {
		printf ("[%d] = %d", j, G->playedCards[j]);
	}
	printf ("\n");
	return 0;
}

int countVP (int p, struct gameState * G) {
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

	printf ("LOG PLAYER %d KEY VP STATS -> curse: %d, estate: %d, great: %d, duchy: %d, province:%d, gardens:%d, TotalCards: %d \n",
			p, curseTot, estateTot, great_hallTot, duchyTot, provinceTot, gardensTot, cTot);
	return vp;
}

int main () {
	printf ("starting unittest1 -- testing scoreFor() function\n");

	// -----------------
	// setup a standard game
	// -----------------
	struct gameState testGame;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	           sea_hag, tribute, smithy};
	// TODO: make the # of players variable
	initializeGame(2, k, 2, &testGame);

	// -----------------
	// Now change size of hands and cards randomly
	// -----------------
	//#define MAX_HAND 500 and #define MAX_DECK 500
	int largestSize = 10;

	int i;
	int players=2;
	for (i=0; i<players; i++) {
		testGame.handCount[i] = getRandIntLowHigh (0, largestSize);
	}
	// choose random size of deck
	for (i=0; i<players; i++) {
		testGame.deckCount[i] = getRandIntLowHigh (0, largestSize);
	}
	// choose random size of discard
	for (i=0; i<players; i++) {
		testGame.discardCount[i] = getRandIntLowHigh (0, largestSize);
	}

	// Loop over X# of trials
	int trials = 3;
	int trialcount = 0;
	while (trialcount < trials) {
		trialcount++;
		printf ("\n----- Trial #%d ----\n", trialcount);
		// now let's play with player 0 and 1's hand and deck
		int p=0;
		int j;

		// TODO: make max player variable
		for (p=0; p<2; p++) {
			// change player's hand
			for (j=0; j<testGame.handCount[p]; j++) {
				testGame.hand[p][j] = anyRandCard();
			}

			// change player discard
			for (j=0; j<testGame.discardCount[p]; j++) {
					testGame.discard[p][j] = anyRandCard();
			}

			// change player deck
			for (j=0; j<testGame.deckCount[p]; j++) {
					testGame.deck[p][j] = anyRandCard();
			}
		}

		// DEBUG: show state of game
		// printGameState (&testGame);

		// TODO: make max player variable
		int playerVPcontrol;
		int playerVPtest;
		for (p=0; p<2; p++) {

			// count the number of victory points
			playerVPcontrol = countVP(p, &testGame);
			//int player0vp = countVP(0, &testGame);
			//int player1vp = countVP(1, &testGame);

			// call the function and assert
			playerVPtest = scoreFor (p, &testGame);
			//int testScoreFor = scoreFor (0, &testGame);
			//printf ("player0vp = %d, testScoreFor = %d\n", player0vp, testScoreFor);

			assertTrue(playerVPcontrol, playerVPtest);

			//assertTrue(player0vp, testScoreFor);
			//testScoreFor = scoreFor (1, &testGame);
			//printf ("player1vp = %d, testScoreFor = %d\n", player1vp, testScoreFor);
			//assertTrue(player1vp, testScoreFor);
		}
	}
	return 0;
}



// enum CARD {	curse = 0, estate, duchy, province, copper, silver, gold, (#7) adventurer,
//				council_room, feast, (#10) gardens, (#11) mine, remodel, (#13) smithy,
//				(#14) village, baron, great_hall, (#17) minion, steward, (#19) tribute,
//				ambassador, (#21) cutpurse, (#22) embargo, outpost, salvager, (#25) sea_hag,
//				treasure_map };
// there are only 6 cards that count toward victory points
/*
int scoreFor (int player, struct gameState *state) {
  int i;
  int score = 0;
  //score from hand
  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == curse) { score = score - 1; };
      if (state->hand[player][i] == estate) { score = score + 1; };
      if (state->hand[player][i] == duchy) { score = score + 3; };
      if (state->hand[player][i] == province) { score = score + 6; };
      if (state->hand[player][i] == great_hall) { score = score + 1; };
      if (state->hand[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
    }

  //score from discard
  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->discard[player][i] == curse) { score = score - 1; };
      if (state->discard[player][i] == estate) { score = score + 1; };
      if (state->discard[player][i] == duchy) { score = score + 3; };
      if (state->discard[player][i] == province) { score = score + 6; };
      if (state->discard[player][i] == great_hall) { score = score + 1; };
      if (state->discard[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
    }

  //score from deck
  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->deck[player][i] == curse) { score = score - 1; };
      if (state->deck[player][i] == estate) { score = score + 1; };
      if (state->deck[player][i] == duchy) { score = score + 3; };
      if (state->deck[player][i] == province) { score = score + 6; };
      if (state->deck[player][i] == great_hall) { score = score + 1; };
      if (state->deck[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
    }

  return score;
}
*/


// -----------------
// what inputs to test
// -----------------
/*
int player = 1;
int handcount = testGame.handCount[player];
int discardCount = testGame.discardCount[player];
int deckCount = testGame.deckCount[player];
int playedCardsCount = testGame.playedCardCount; // not sure if playedcardscount is needed it's not a separate pile??
printf ("handcount = %d, discardCount = %d, deckCount = %d, playedCardsCount = %d\n",
		handcount, discardCount, deckCount, playedCardsCount);
*/






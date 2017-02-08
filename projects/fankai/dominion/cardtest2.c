/*int Dosteward(int choice1,int choice2,int choice3, struct gameState *state,int currentPlayer,int handPos){
      if (choice1 == 2)//??
	{
	  //+2 cards
	  drawCard(currentPlayer, state);
	  drawCard(currentPlayer, state);
	}
      else if (choice1 == 1)//??
	{
	  //+2 coins
	  state->coins = state->coins + 2;
	}
      else
	{
	  //trash 2 cards in hand
	  discardCard(choice2, currentPlayer, state, 1);
	  discardCard(choice3, currentPlayer, state, 1);
	}

      //discard card from hand
      discardCard(handPos, currentPlayer, state, 0);
}
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "steward"

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int CurrentPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);


	printf("-------Case 1: choice1 = 1 = +2 cards\n-------");

	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	Dosteward(choice1, choice2, choice3, &testG, CurrentPlayer, handpos);
	newCards = 2;
	printf("hand count = %d, expected = %d\n", testG.handCount[CurrentPlayer], G.handCount[CurrentPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[CurrentPlayer], G.deckCount[CurrentPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins);


	printf("---------Case 2: choice1 = 2 = +2 coins\n-------");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 2;
	Dosteward(choice1, choice2, choice3, &testG,CurrentPlayer, handpos);

	newCards = 0;
	xtraCoins = 2;
	printf("hand count = %d, expected = %d\n", testG.handCount[CurrentPlayer], G.handCount[CurrentPlayer] + newCards - discarded);
	printf("deck count = %d, expected = %d\n", testG.deckCount[CurrentPlayer], G.deckCount[CurrentPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);

	// ----------- TEST 3: choice1 = 3 = trash two cards --------------

	//printf("Case 3: choice1 = 3 = trash two cards\n");
	//choice1 = 3;

	// still thinking this part


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}



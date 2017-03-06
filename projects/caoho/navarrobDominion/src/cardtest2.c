#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {

	printf("****** Testing Method <playSmithy  ;>******\n");

	int k[10] = { adventurer, gardens, feast, village, minion, mine, steward,
			sea_hag, tribute, smithy };
	int seed = 44;
	int playerIndex = 0;
	int temphand[MAX_HAND];
	int playerNum = 2;

	struct gameState *state1 = newGame();
	initializeGame(playerNum, k, seed, state1);
	state1->handCount[playerIndex] = 5;
	state1->hand[playerIndex][0] = feast;
	state1->hand[playerIndex][1] = adventurer;
	state1->hand[playerIndex][2] = smithy;
	state1->hand[playerIndex][3] = tribute;
	state1->hand[playerIndex][4] = gardens;
	state1->deckCount[playerIndex] = 5;
	state1->deck[playerIndex][0] = estate;
	state1->deck[playerIndex][1] = silver;
	state1->deck[playerIndex][2] = great_hall;
	state1->deck[playerIndex][3] = copper;
	state1->deck[playerIndex][4] = duchy;
	state1->discardCount[playerIndex] = 0;

	struct gameState *state2 = newGame();
	initializeGame(playerNum, k, seed, state2);
	state2->handCount[playerIndex] = 5;
	state2->hand[playerIndex][0] = feast;
	state2->hand[playerIndex][1] = adventurer;
	state2->hand[playerIndex][2] = smithy;
	state2->hand[playerIndex][3] = tribute;
	state2->hand[playerIndex][4] = gardens;
	state2->deckCount[playerIndex] = 5;
	state2->deck[playerIndex][0] = copper;
	state2->deck[playerIndex][1] = silver;
	state2->deck[playerIndex][2] = great_hall;
	state2->deck[playerIndex][3] = duchy;
	state2->deck[playerIndex][4] = copper;
	state2->discardCount[playerIndex] = 0;

	struct gameState *state3 = newGame();
	initializeGame(playerNum, k, seed, state3);
	state3->handCount[playerIndex] = 5;
	state3->hand[playerIndex][0] = feast;
	state3->hand[playerIndex][1] = adventurer;
	state3->hand[playerIndex][2] = smithy;
	state3->hand[playerIndex][3] = tribute;
	state3->hand[playerIndex][4] = gardens;
	state3->deckCount[playerIndex] = 0;
	state3->discardCount[playerIndex] = 5;
	state3->discard[playerIndex][0] = copper;
	state3->discard[playerIndex][1] = silver;
	state3->discard[playerIndex][2] = great_hall;
	state3->discard[playerIndex][3] = duchy;
	state3->discard[playerIndex][4] = copper;

	struct gameState *state4 = newGame();
	initializeGame(playerNum, k, seed, state4);
	state4->handCount[playerIndex] = 5;
	state4->hand[playerIndex][0] = feast;
	state4->hand[playerIndex][1] = adventurer;
	state4->hand[playerIndex][2] = smithy;
	state4->hand[playerIndex][3] = tribute;
	state4->hand[playerIndex][4] = gardens;
	state4->deckCount[playerIndex] = 0;
	state4->discardCount[playerIndex] = 0;
	state4->discard[playerIndex][0] = copper;
	state4->discard[playerIndex][1] = silver;
	state4->discard[playerIndex][2] = great_hall;
	state4->discard[playerIndex][3] = duchy;
	state4->discard[playerIndex][4] = copper;

	struct gameState *state5 = newGame();
	initializeGame(playerNum, k, seed, state5);
	state5->handCount[playerIndex] = 5;
	state5->hand[playerIndex][0] = feast;
	state5->hand[playerIndex][1] = adventurer;
	state5->hand[playerIndex][2] = smithy;
	state5->hand[playerIndex][3] = tribute;
	state5->hand[playerIndex][4] = gardens;
	state5->deckCount[playerIndex] = 0;
	state5->discardCount[playerIndex] = 0;
	state5->discard[playerIndex][0] = estate;
	state5->discard[playerIndex][1] = silver;
	state5->discard[playerIndex][2] = great_hall;
	state5->discard[playerIndex][3] = copper;
	state5->discard[playerIndex][4] = duchy;

	playSmithy(state1, 1);
	assertMsg("Testing drawing 2 cards", 7, state1->handCount[playerIndex]);
	playSmithy(state2, 1);
	assertMsg("Testing draws no cards when no treasure cards in deck", 7,state2->handCount[playerIndex]);
	playSmithy(state3, 1);
	assertMsg("Testing draws 2 cards from discard", 0,state3->handCount[playerIndex]);
	playSmithy(state4, 1);
	assertMsg("Testing draws 2 cards from discard", 1, state4->discardCount[playerIndex]);


	printf("****** FInished ******\n");

	return 0;
}

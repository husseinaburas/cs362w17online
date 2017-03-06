/* unittest1.c

	for testing the shuffle function

*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
 
int main() {
	

	struct gameState* testGame = newGame();

	int testcards[10];
	int i;
	for (i=0;i<10;i++){

		testcards[i] = i+1;
	}

	initializeGame(2, testcards, 5, testGame);

	int testhand[MAX_HAND];
	for (i=0; i< testGame->deckCount[1]; i++)
	{
		testhand[i] = testGame->deck[1][i];

	}
	
	for (i=0; i< testGame->deckCount[1]; i++)
	{
		discardCard(i, 1, testGame, 0);
	}
	shuffle(1, testGame);

	if (testhand == testGame->deck[1]){
		printf("shuffle test failed\n");
	}
	else printf("shuffle test passed\n");
}

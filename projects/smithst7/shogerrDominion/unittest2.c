/* unittest2.c

	for testing the drawcard function

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

	int testdeck[MAX_HAND];
	for (i=0; i< testGame->deckCount[1]; i++)
	{
		testdeck[i] = testGame->deck[1][i];

	}
	
	drawCard(1, testGame);

	if (testdeck!= testGame->deck[1])
	{	printf("draw test pass\n");	}
	else printf ("draw test fail\n");	

}

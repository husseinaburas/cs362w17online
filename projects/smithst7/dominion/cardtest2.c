/* cardtest2.c

	for testing the adventurer card

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

	drawCard(1, testGame);
	adventurer_func(1, testGame);

	if (testGame->handCount[1] == 2)
	{	printf ("adventurer test pass\n");	}
	else printf ("adventurer test failed\n");
}

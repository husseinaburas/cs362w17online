/* cardtest1.c

	for testing the smithy card

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
	smithy_func(1, testGame, 0);

	if (testGame->handCount[1] == 3) {
		printf ("smithy test pass\n");	}
	else printf ("smithy test failed\n");
}

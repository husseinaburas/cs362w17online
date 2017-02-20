/* unittest4.c

	for testing the isgameover function

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

	testGame->supplyCount[province] = 0;

	if (isGameOver(testGame) == 1)
	{	printf("isgameover test pass");	}
	else printf("isgameover test fail");

}

/* cardtest3.c

	for testing the sea_hag card

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

	
	testGame->whoseTurn = 1;
	drawCard(1, testGame);
	cardEffect(sea_hag,0,0,0, testGame, 0, 0); 
	if (scoreFor(0, testGame) == 2) //origninal 3 estates, minus one for curse
	{	printf ("sea_hag test pass\n");	}
	else printf ("sea_hag test failed\n");
}

/* cardtest4.c 
	for testing the council_room card

*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "dominion.c"
#include "rngs.c"  

int main() {
	

	struct gameState* testGame = newGame();

	int testcards[10];
	int i;
	for (i=0;i<10;i++){

		testcards[i] = i+1;
	}

	initializeGame(2, testcards, 5, testGame);

	drawCard(1, testGame);
	testGame->whoseTurn = 1;
	testGame->numBuys = 0;
	card_effect_council_room(1, testGame, 0);
	if (testGame->handCount[1] == 4 && testGame->numBuys == 1)
	{	printf ("council_room test pass\n");	}
	else printf ("council_room test failed\n");
}

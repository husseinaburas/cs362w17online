//Unit Test 1
#include "dominion.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>

//test that scoreFor works correctly, will return 0 if all was well and -1 if something fails
int testscoreFor() {

	int numPlayers = 2;

	printf ("TESTING scoreFor function!\n\n");
	int success = 1;
	// Create gamestate
    struct gameState G;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    int r = rand();
    initializeGame(numPlayers, k, r, &G);

    int currentPlayer = whoseTurn(&G);
    int nextPlayer = currentPlayer+1;

    printf ("Cards in hand for player %d: %d\n", currentPlayer+1, G.handCount[currentPlayer]);
    printf ("Cards in hand for player %d: %d\n", nextPlayer+1, G.handCount[nextPlayer]);

    printf ("Cards in discard pile for player %d: %d\n", currentPlayer+1, G.discardCount[currentPlayer]);
    printf ("Cards in discard pile for player %d: %d\n", nextPlayer+1, G.discardCount[nextPlayer]);

    printf ("Cards in deck for player %d: %d\n", currentPlayer+1, G.deckCount[currentPlayer]);
    printf ("Cards in deck for player %d: %d\n", nextPlayer+1, G.deckCount[nextPlayer]);

    printf("Score should be equal at the start of the game,\nas each player has 3 Estate Cards for a total of 3 VPs\n");

    int score = scoreFor(currentPlayer, &G);
    int score2 = scoreFor (nextPlayer, &G);
    if (score == score2) {
    	printf ("Player %d's score is %d. - PASS\n", currentPlayer+1, score);
		printf ("Player %d's score is %d. - PASS\n", nextPlayer+1, score2);
	}
	else {
		printf ("Player %d's score is %d. - FAIL (should be 3)\n", currentPlayer+1, score);
		printf ("Player %d's score is %d. - FAIL (should be 3)\n", nextPlayer+1, score2);
		success = 0;
	}

	endTurn(&G);

	printf("Ending turn. Score will be recalculated and it\nshould still be the same as no new cards have been drawn.\n");

	currentPlayer = whoseTurn(&G);
	if (numPlayers == 2) {
		nextPlayer = currentPlayer - 1;
	}
	else {
		nextPlayer = currentPlayer + 1;
	}

	score = scoreFor(currentPlayer, &G);
	score2 = scoreFor(nextPlayer, &G);
	if (score == score2) {
    	printf ("Player %d's score is %d. - PASS\n", currentPlayer+1, score);
		printf ("Player %d's score is %d. - PASS\n", nextPlayer+1, score2);
	}
	else {
		printf ("Player %d's score is %d. - FAIL (should be 3)\n", currentPlayer+1, score);
		printf ("Player %d's score is %d. - FAIL (should be 3)\n", nextPlayer+1, score2);
		success = 0;
	}

    if (success == 1) {
    	return 0;
    }
    else {
    	return 1;
    }
}

int main() {
	int x = testscoreFor();
	if (x == 0) {
		printf("testscoreFor passes.\n\n");
	}
	else {
		printf("testscoreFor fails miserably.\n\n");
	}
	return 0;
}
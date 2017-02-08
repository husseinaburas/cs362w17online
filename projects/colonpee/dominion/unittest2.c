//Unit Test 2
#include "dominion.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>

//test that endTurn works correctly, will return 0 if all was well and -1 if something fails
int testEndTurn() {
	printf ("TESTING endTurn function!\n\n");
	int success = 1;
	// Create gamestate
    struct gameState G;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    int r = rand();
    initializeGame(2, k, r, &G);

    int currentPlayer = whoseTurn(&G);
    int nextPlayer = currentPlayer+1;

    printf ("Player %d has %d cards in hand.\n", currentPlayer+1, G.handCount[currentPlayer]);

    endTurn (&G);

    printf ("After endTurn, it should be player %d's turn\n", nextPlayer+1);

    currentPlayer = whoseTurn(&G);

    if (currentPlayer == nextPlayer) {
    	printf ("Current Player is player %d. - PASS\n", currentPlayer+1);
    }
    else {
    	printf("Current player is player %d. - FAIL\n", currentPlayer+1);
    	success = 0;
    }

    printf ("After endTurn player %d should have 0 cards in hand, 5 in discard \nand player %d should have 5 cards in hand, 0 in discard.\n", currentPlayer, currentPlayer+1);

    if (G.handCount[currentPlayer-1] == 0) {
    	printf ("Player %d has %d cards in hand. - PASS\n", currentPlayer, G.handCount[currentPlayer-1]);
    }
    else {
    	printf ("Player %d has %d cards in hand. - FAIL (should be 0)\n", currentPlayer, G.handCount[currentPlayer-1]);
    	success = 0;
    }

    if (G.deckCount[currentPlayer-1] == 5) {
        printf ("Player %d has %d cards in deck. - PASS\n", currentPlayer, G.deckCount[currentPlayer-1]);
    }
    else {
        printf ("Player %d has %d cards in deck. - FAIL (should be 5)\n", currentPlayer, G.deckCount[currentPlayer-1]);
        success = 0;
    }

    if (G.discardCount[currentPlayer-1] == 5) {
        printf ("Player %d has %d cards in discard. - PASS\n", currentPlayer, G.discardCount[currentPlayer-1]);
    }
    else {
        printf ("Player %d has %d cards in discard. - FAIL (should be 5)\n", currentPlayer, G.discardCount[currentPlayer-1]);
        success = 0;
    }
    
    if (G.handCount[currentPlayer] == 5 && G.discardCount[currentPlayer] == 0) {
    	printf ("Player %d has %d cards in hand. - PASS\n", currentPlayer+1, G.handCount[currentPlayer]);
	}
	else {
		printf ("Player %d has %d cards in hand. - FAIL (should be 5)\n", currentPlayer+1, G.handCount[currentPlayer]);
		success = 0;
	}

    if (G.deckCount[currentPlayer] == 5) {
        printf ("Player %d has %d cards in deck. - PASS\n", currentPlayer+1, G.deckCount[currentPlayer]);
    }
    else {
        printf ("Player %d has %d cards in deck. - FAIL (should be 5)\n", currentPlayer+1, G.deckCount[currentPlayer]);
        success = 0;
    }

    if (G.discardCount[currentPlayer] == 0) {
        printf ("Player %d has %d cards in discard. - PASS\n", currentPlayer+1, G.discardCount[currentPlayer]);
    }
    else {
        printf ("Player %d has %d cards in discard. - FAIL (should be 0)\n", currentPlayer+1, G.discardCount[currentPlayer]);
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
    int x = testEndTurn();
    if (x == 0) {
		printf("endTurn passes.\n\n");
	}
	else {
		printf("endTurn fails miserably.\n\n");
	}
	return 0;
}
//Card Test 1
#include "dominion.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>

int testSmithy() {
	printf ("TESTING Smithy card!\n\n");
	int success = 1;
	// Create gamestate
    struct gameState G;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    int r = rand();
    initializeGame(2, k, r, &G);

    int currentPlayer = whoseTurn(&G);

    printf ("Playing smithy for player %d. Should add 3 cards to his hand from the deck\n", currentPlayer+1);

	printf ("Cards in hand for player %d, before playing smithy: %d\n", currentPlayer+1, G.handCount[currentPlayer]);

	printf ("Cards in discard pile for player %d, before playing smithy: %d\n", currentPlayer+1, G.discardCount[currentPlayer]);

	printf ("Cards in deck for player %d, before playing smithy: %d\n", currentPlayer+1, G.deckCount[currentPlayer]);

    printf("Getting one free smithy for player %d\n", currentPlayer+1);

   	gainCard (13, &G, 2, currentPlayer);

   	//Verify if it added smithy
   	if (G.hand[currentPlayer][G.handCount[currentPlayer]-1] != 13) {
   		printf ("Drawed a card that is not smithy.\n");
   		success = 0;
   	}
   	

   	//Verify that playCard runs successfully
   	if (playCard(G.handCount[currentPlayer]-1, -1, -1, -1, &G) != 0) {
   		success = 0;
   		printf("Some error ocurred with playCard.\n");
   	}

   	printf ("After playing smithy, player %d should have + 3 cards in hand \nbecause smithy was added for free.\n", currentPlayer+1);

   	if (G.playedCardCount == 1) {
   		printf ("Played cards: %d - PASS\n", G.playedCardCount);
   	}

   	else {
   		printf ("Played cards: %d - FAIL (should be 1)\n", G.playedCardCount);
   		success = 0;
   	}

   	if (G.handCount[currentPlayer] == 8) {
   		printf ("Cards in hand for player %d: %d - PASS\n", currentPlayer+1, G.handCount[currentPlayer]);
   	}

   	else {
   		printf ("Cards in hand for player %d: %d - FAIL (should be 8)\n", currentPlayer+1, G.handCount[currentPlayer]);
		success = 0;
   	}

   	if (G.deckCount[currentPlayer] == 2) {
   		printf ("Cards in deck for player %d: %d - PASS\n", currentPlayer+1, G.deckCount[currentPlayer]);
   	}

   	else {
   		printf ("Cards in deck for player %d: %d - FAIL (should be 2)\n", currentPlayer+1, G.deckCount[currentPlayer]);
   		success = 0;
   	}

   	endTurn(&G);
   	printf ("After endTurn, discard pile should be 11 because smithy was gained for free\n");
   	if (G.discardCount[currentPlayer] == 11) {
   		printf ("Cards in discard pile for player %d: %d - PASS\n", currentPlayer+1, G.discardCount[currentPlayer]);
   	}

   	else {
   		printf ("Cards in discard pile for player %d: %d - FAIL (should be 11)\n", currentPlayer+1, G.discardCount[currentPlayer]);
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
	int x = testSmithy();
	if (x == 0) {
		printf("testSmithy passes.\n\n");
	}
	else {
		printf("testSmithy fails miserably.\n\n");
	}
    return 0;
}
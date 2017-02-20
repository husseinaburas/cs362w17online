//Card Test 3
#include "dominion.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>

int testVillage() {
	printf ("TESTING Village card!\n\n");
	int success = 1;
	// Create gamestate
    struct gameState G;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    int r = rand();
    initializeGame(2, k, r, &G);

    int currentPlayer = whoseTurn(&G);

    printf ("Playing Village for player %d. Should add 1 card to his hand from the deck and 2 actions\n", currentPlayer+1);
    printf ("Number of actions for player %d, before playing Village: %d\n", currentPlayer+1, G.numActions);
	printf ("Cards in hand for player %d, before playing Village: %d\n", currentPlayer+1, G.handCount[currentPlayer]);
	printf ("Cards in discard pile for player %d, before playing Village: %d\n", currentPlayer+1, G.discardCount[currentPlayer]);
	printf ("Cards in deck for player %d, before playing Village: %d\n", currentPlayer+1, G.deckCount[currentPlayer]);
    printf ("Getting one free Village for player %d\n", currentPlayer+1);

   	gainCard (14, &G, 2, currentPlayer);

   	//Verify if it added smithy
   	if (G.hand[currentPlayer][G.handCount[currentPlayer]-1] != 14) {
   		printf ("Drawed a card that is not Village.\n");
   		success = 0;
   	}
   	//Verify that playCard runs successfully
   	if (playCard(G.handCount[currentPlayer]-1, -1, -1, -1, &G) != 0) {
   		success = 0;
   		printf("Some error ocurred with playCard.\n");
   	}

   	printf ("After playing Village, player %d should have + 1 card in hand \nand 2 more actions.\n", currentPlayer+1);

   	if (G.numActions == 2) {
   		printf ("Number of actions for player %d: %d - PASS\n", currentPlayer+1, G.numActions);
   	}

   	else {
   		printf ("Number of actions for player %d: %d - FAIL (should be 2)\n", currentPlayer+1, G.numActions);
   		success = 0;
   	}

   	if (G.playedCardCount == 1) {
   		printf ("Played cards: %d - PASS\n", G.playedCardCount);
   	}

   	else {
   		printf ("Played cards: %d - FAIL (should be 1)\n", G.playedCardCount);
   		success = 0;
   	}

   	if (G.handCount[currentPlayer] == 6) {
   		printf ("Cards in hand for player %d: %d - PASS\n", currentPlayer+1, G.handCount[currentPlayer]);		
   	}

   	else {
   		printf ("Cards in hand for player %d: %d - FAIL (should be 6)\n", currentPlayer+1, G.handCount[currentPlayer]);
		success = 0;
   	}

   	if (G.deckCount[currentPlayer] == 4) {
   		printf ("Cards in deck for player %d: %d - PASS\n", currentPlayer+1, G.deckCount[currentPlayer]);
   	}

   	else {
   		printf ("Cards in deck for player %d: %d - FAIL (should be 4)\n", currentPlayer+1, G.deckCount[currentPlayer]);
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
	int x = testVillage();
	if (x == 0) {
		printf("testVillage passes.\n\n");
	}
	else {
		printf("testVillage fails miserably.\n\n");
	}
    return 0;
}
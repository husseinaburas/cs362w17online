//Card Test 2
#include "dominion.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>

int testAdventurer() {
	printf ("TESTING Adventurer card!\n\n");
	int success = 1;
	// Create gamestate
    struct gameState G;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    int r = rand();
    initializeGame(2, k, r, &G);

    int currentPlayer = whoseTurn(&G);

    printf ("Playing adventurer for player %d. Should add 2 treasure cards\nto his hand from the deck and discard the other revealed cards\n", currentPlayer+1);
    printf ("Coins available for player %d, before playing Adventurer: %d\n", currentPlayer+1, G.coins);

    int coinsBefore = G.coins;

	printf ("Cards in hand for player %d, before playing Adventurer: %d\n", currentPlayer+1, G.handCount[currentPlayer]);
	printf ("Cards in discard pile for player %d, before playing Adventurer: %d\n", currentPlayer+1, G.discardCount[currentPlayer]);
	printf ("Cards in deck for player %d, before playing Adventurer: %d\n", currentPlayer+1, G.deckCount[currentPlayer]);
    printf("Getting one free Adventurer for player %d\n", currentPlayer+1);

   	gainCard (7, &G, 2, currentPlayer);

   	//Verify if it added Adventurer
   	if (G.hand[currentPlayer][G.handCount[currentPlayer]-1] != 7) {
   		printf ("Drawed a card that is not Adventurer.\n");
   		success = 0;
   	}
   	

   	//Verify that playCard runs successfully
   	if (playCard(G.handCount[currentPlayer]-1, -1, -1, -1, &G) != 0) {
   		success = 0;
   		printf("Some error ocurred with playCard.\n");
   	}

   	printf ("After playing Adventurer, player %d should have + 2 treasure cards\nin hand because Adventurer was added for free and\nplayed card should be set to 1.\n", currentPlayer+1);

   	if (G.coins == (coinsBefore+2)) {
   		printf ("Coins available for player %d: %d - PASS\n", currentPlayer+1, G.coins);
   	}
   	else {
   		printf ("Coins available for player %d: %d - FAIL (should be %d)\n", currentPlayer+1, G.coins, coinsBefore+2);
   		success = 0;
   	}

   	if (G.playedCardCount == 1) {
   		printf ("Played cards: %d - PASS\n", G.playedCardCount);
   	}

   	else {
   		printf ("Played cards: %d - FAIL (should be 1)\n", G.playedCardCount);
   		success = 0;
   	}

   	if (G.handCount[currentPlayer] == 7){
   		printf ("Cards in hand for player %d: %d - PASS\n", currentPlayer+1, G.handCount[currentPlayer]);
   	}

   	else {
   		printf ("Cards in hand for player %d: %d - FAIL (should be 7)\n", currentPlayer+1, G.handCount[currentPlayer]);
		success = 0;
   	}

   	if (G.deckCount[currentPlayer] == 3) {
   		printf ("Cards in deck for player %d: %d - PASS\n", currentPlayer+1, G.deckCount[currentPlayer]);
   	}
   	else {
   		printf ("Cards in deck for player %d: %d - FAIL (should be 3)\n", currentPlayer+1, G.deckCount[currentPlayer]);
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
	int x = testAdventurer();
	if (x == 0) {
		printf("testAdventurer passes.\n\n");
	}
	else {
		printf("testAdventurer fails miserably.\n\n");
	}
    return 0;
}
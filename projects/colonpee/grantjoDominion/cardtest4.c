//Card Test 4
#include "dominion.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>

int testGardens() {
	printf ("TESTING Gardens card!\n\n");
	int success = 1;
	// Create gamestate
    struct gameState G;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    int r = rand();
    initializeGame(2, k, r, &G);

    int currentPlayer = whoseTurn(&G);

    printf ("Playing Gardens card for player %d. Should be worth 1 VP per 10 cards\nshould add 1 VP to total VPs\n", currentPlayer+1);

    printf ("Player %d score before having a Gardens: %d\n", currentPlayer+1, scoreFor(currentPlayer, &G));

    printf("Getting one free Gardens card for player %d\n", currentPlayer+1);

   	gainCard (10, &G, 2, currentPlayer);

   	//Verify if it added Gardens
   	if (G.hand[currentPlayer][G.handCount[currentPlayer]-1] != 10) {
   		printf ("Drawed a card that is not Gardens.\n");
   		success = 0;
   	}

   	printf ("After having a Gardens, player %d \nshould have + 1 VP for each 10 cards.\n", currentPlayer+1);

   	if (G.handCount[currentPlayer] == 6){
   		printf ("Cards in hand for player %d: %d - PASS\n", currentPlayer+1, G.handCount[currentPlayer]);
   	}

   	else {
   		printf ("Cards in hand for player %d: %d - FAIL (should be 7)\n", currentPlayer+1, G.handCount[currentPlayer]);
		success = 0;
   	}

   	if (G.deckCount[currentPlayer] == 5) {
   		printf ("Cards in deck for player %d: %d - PASS\n", currentPlayer+1, G.deckCount[currentPlayer]);
   	}
   	else {
   		printf ("Cards in deck for player %d: %d - FAIL (should be 5)\n", currentPlayer+1, G.deckCount[currentPlayer]);
   		success = 0;
   	}

   	if (scoreFor(currentPlayer, &G) == 4) {
   	    printf ("Player %d score: %d - PASS\n", currentPlayer+1, scoreFor(currentPlayer, &G));
   	}
   	else {
   		printf ("Player %d score: %d - FAIL (should be 4)\n", currentPlayer+1, scoreFor(currentPlayer, &G));
   		success = 0;
   	}

   	printf("Adding 3 Estates and 7 Duchys to player %d's hand, should then have +25 VPs \nsince 3 Estates and 7 Duchys are added and player has a Gardens\n", currentPlayer+1);

   	for (int i = 0; i < 3; i++) {
   		gainCard(1, &G, 2, currentPlayer);
   	}

   	for (int i = 0; i < 7; i++) {
   		gainCard(2, &G, 2, currentPlayer);
   	}

   	if (G.handCount[currentPlayer] == 16){
   		printf ("Cards in hand for player %d: %d - PASS\n", currentPlayer+1, G.handCount[currentPlayer]);
   	}

   	else {
   		printf ("Cards in hand for player %d: %d - FAIL (should be 7)\n", currentPlayer+1, G.handCount[currentPlayer]);
		success = 0;
   	}

   	if (scoreFor(currentPlayer, &G) == 29) {
   	    printf ("Player %d score: %d - PASS\n", currentPlayer+1, scoreFor(currentPlayer, &G));
   	}
   	else {
   		printf ("Player %d score: %d - FAIL (should be 29)\n", currentPlayer+1, scoreFor(currentPlayer, &G));
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
	int x = testGardens();
	if (x == 0) {
		printf("testGardens passes.\n\n");
	}
	else {
		printf("testGardens fails miserably.\n\n");
	}
    return 0;
}
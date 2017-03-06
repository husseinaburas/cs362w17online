/* 
 * Name: Thomas Adamcewicz
 * Due Date: 3/5/17
 * Function: playSmithy(struct gameState *state, int handPos)
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


 //assertTrue function in place of assert
 void assertTrue(int val) {
	if (val){
		printf("TEST PASSED\n");
	}
	else{
		printf("TEST FAILED\n");
	}
}


int main() {

    printf("\n**** playSmithy() TESTING BEGINNING ****\n");

	int i;
	int tFlag = 0;
    int seed = 1000;
    int numPlayers = 2;
    int p1 = 0;
    int p2 = 1;
    int cards[10] = {adventurer, council_room, feast, gardens, mine,
                     remodel, outpost, village, baron, great_hall};
    struct gameState G;
    //int maxHandCount = 5;
    int initialSupplyCount[treasure_map + 1];

    //start game
    initializeGame(numPlayers, cards, seed, &G);
    int initDeckSizeP1 = G.deckCount[p1];
    int initDiscardSizeP1 = G.discardCount[p1];
    int initDeckSizeP2 = G.deckCount[p2];
    int initDiscardSizeP2 = G.discardCount[p2];
    int initHandSizeP2 = G.handCount[p2];

    //TEST-1: Test playSmithy() after game initialized
    printf("TEST-1\n **GAME INITIALIZED CALLING playSmithy() AND CHECKING CHANGED VARS**\n");
    G.hand[p1][0] = smithy;
    int initHandSizeP1 = G.handCount[p1];
    //int initLastCard = G.hand[p1][G.handCount[p1]-1];
    playSmithy(&G, 0);
    printf("Check p1 handSize is == initial hand size of p1 + 2: ");
    assertTrue(G.handCount[p1] == initHandSizeP1 + 2);
    printf("Check value of p1 hand at current handCount is == -1 (discard): ");
    assertTrue(G.hand[p1][G.handCount[p1]] == -1);
    printf("Check smithy is not in p1 hand: ");
    int smithyFound = 0;
    for (i = 0; i < G.handCount[p1]; i++) {
        if (G.hand[p1][i] == smithy) smithyFound++;
    }
    assertTrue(smithyFound == 0);
    printf("Check deckCount is equal to initial deckCount - 3 for p1: ");
    assertTrue(G.deckCount[p1] == initDeckSizeP1 - 3);

    //TEST-2: Check deck/discard which shouldn't have changed
    printf("TEST-2\n **AFTER SMITHY PLAYED, CHECK VARS THAT SHOULDN'T BE EFFECTED**\n");
    printf("Check discardCount is equal to initial discardCount for p1: ");
    assertTrue(G.discardCount[p1] == initDiscardSizeP1);
    printf("Check p2 Deck/Hand/Discard counts are same as initial values: ");
    assertTrue(G.discardCount[p2] == initDiscardSizeP2 && G.deckCount[p2] == initDeckSizeP2 && G.handCount[p2] == initHandSizeP2);

    printf("\n**** playSmithy() TESTING COMPLETE ****\n");

    return 0;

}

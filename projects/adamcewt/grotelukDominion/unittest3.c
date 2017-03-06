/* 
 * Name: Thomas Adamcewicz
 * Due Date: 2/7/17
 * Function: fullDeckCount(int player, int card, struct gameState *state)
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

    printf("\n**** fullDeckCount() TESTING BEGINNING ****\n");

	int i;
	int tFlag = 0;
    int seed = 1000;
    int numPlayers = 2;
    int p1 = 0;
    int p2 = 1;
    int cards[10] = {adventurer, council_room, feast, gardens, mine,
                     remodel, smithy, village, baron, great_hall};
    struct gameState G;
    //int maxHandCount = 5;
    int initialSupplyCount[treasure_map + 1];

    //start game
    initializeGame(numPlayers, cards, seed, &G);

    //TEST-1: Test fullDeckCounts return of copper in p1's deck/hand/discard after init
    printf("TEST-1\n **GAME INITIALIZED CHECKING fullDeckCount of copper vs manual count**\n");
    int count = 0;

    for (i = 0; i < G.deckCount[p1]; i++)
    {
        if (G.deck[p1][i] == copper) count++;
    }

    for (i = 0; i < G.handCount[p1]; i++)
    {
        if (G.hand[p1][i] == copper) count++;
    }

    for (i = 0; i < G.discardCount[p1]; i++)
    {
        if (G.discard[p1][i] == copper) count++;
    }
    //printf("%d\n", fullDeckCount(p1, copper, &G));
    printf("Checking fullDeckCount == manual count of copper card of p1: ");
    assertTrue(fullDeckCount(p1, copper, &G) == count);

    count = 0;

    for (i = 0; i < G.deckCount[p2]; i++)
    {
        if (G.deck[p2][i] == copper) count++;
    }

    for (i = 0; i < G.handCount[p2]; i++)
    {
        if (G.hand[p2][i] == copper) count++;
    }

    for (i = 0; i < G.discardCount[p2]; i++)
    {
        if (G.discard[p2][i] == copper) count++;
    }
    printf("Checking fullDeckCount == manual count of copper card of p2: ");
    assertTrue(fullDeckCount(p2, copper, &G) == count);

    //TEST-2 Check cards not in game/cards players don't start with fullDeckCount == 0
    printf("TEST-2\n **CHECKING CARDS THAT SHOULDN'T BE IN HAND/DECK/DISCARD == 0**\n");
    printf("Checking p1 and p2 fullDeckCount of provinces == 0: ");
    assertTrue(fullDeckCount(p1, province, &G) == 0 && fullDeckCount(p2, province, &G) == 0);
    printf("Checking p1 and p2 fullDeckCount of treasure_map (not in game) == 0: ");
    assertTrue(fullDeckCount(p1, treasure_map, &G) == 0 && fullDeckCount(p2, treasure_map, &G) == 0);


    printf("TEST-3\n **MANUALLY ADD PROVINCE TO DECK/HAND/DISCARD AND CHECK fullDeckCount VALUE**\n");
    G.deck[p1][G.deckCount[p1] -1] = province;
    G.deck[p2][G.deckCount[p2] -1] = province;
    printf("Added province to deck, checking p1 fullDeckCount of provinces == 1: ");
    assertTrue(fullDeckCount(p1, province, &G) == 1);
    printf("Added province to deck, checking p2 fullDeckCount of provinces == 1: ");
    assertTrue(fullDeckCount(p2, province, &G) == 1);
    G.hand[p1][G.handCount[p1] -1] = province;
    G.hand[p2][G.handCount[p2]] = province;
    G.handCount[p2]++;
    printf("Added province to hand, checking p1 fullDeckCount of provinces == 2: ");
    assertTrue(fullDeckCount(p1, province, &G) == 2);
    printf("Added province to hand, checking p2 fullDeckCount of provinces == 2: ");
    assertTrue(fullDeckCount(p2, province, &G) == 2);
    G.discard[p1][G.discardCount[p1]] = province;
    G.discard[p2][G.discardCount[p2]] = province;
    G.discardCount[p1]++;
    G.discardCount[p2]++;
    printf("Added province to discard, checking p1 fullDeckCount of provinces == 3: ");
    assertTrue(fullDeckCount(p1, province, &G) == 3);
    printf("Added province to discard, checking p2 fullDeckCount of provinces == 3: ");
    assertTrue(fullDeckCount(p2, province, &G) == 3);
    
    printf("\n**** fullDeckCount() TESTING COMPLETE ****\n");

    return 0;
}
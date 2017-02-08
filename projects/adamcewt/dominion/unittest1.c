/* 
 * Name: Thomas Adamcewicz
 * Due Date: 2/7/17
 * Function: gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
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

	printf("\n**** gainCard() TESTING BEGINNING ****\n");
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

    //initialize InitialsupplyCount
    for(i = 0; i < treasure_map + 1; i++) {
    	initialSupplyCount[i] = G.supplyCount[i];
    }

	//TEST-1: Check initial player hand/deck/discard counts, add card to all piles on each player and check again
	printf("TEST-1\n **CHECKING INITIAL HAND/DECK/DISCARD COUNTS**\n");
	printf("Checking both p1 hand == 5 and p2 hand size == 0: ");
	assertTrue(G.handCount[p1] == 5 && G.handCount[p2] == 0);
	printf("Checking both p1 deck size == 5 and p2 deck size == 10: ");
	assertTrue(G.deckCount[p1] == 5 && G.deckCount[p2] == 10);
	printf("CHecking both p1 and p2 discard size == 0: ");
	assertTrue(G.discardCount[p1] == 0 && G.discardCount[p2] == 0);

	printf("**ADDING CARD TO P1 DISCARD**\n");
    gainCard(smithy, &G, 0, p1);
    printf("Checking both p1 hand == 5 and p2 hand size == 0: ");
	assertTrue(G.handCount[p1] == 5 && G.handCount[p2] == 0);
	printf("Checking both p1 deck size == 5 and p2 deck size == 10: ");
	assertTrue(G.deckCount[p1] == 5 && G.deckCount[p2] == 10);
	printf("CHecking both p1  discard size == 1 and p2 discard size == 0: ");
	assertTrue(G.discardCount[p1] == 1 && G.discardCount[p2] == 0);

	printf("**ADDING CARD TO P2 DISCARD**\n");
    gainCard(smithy, &G, 0, p2);
    printf("Checking both p1 hand == 5 and p2 hand size == 0: ");
	assertTrue(G.handCount[p1] == 5 && G.handCount[p2] == 0);
	printf("Checking both p1 deck size == 5 and p2 deck size == 10: ");
	assertTrue(G.deckCount[p1] == 5 && G.deckCount[p2] == 10);
	printf("CHecking both p1  discard size == 1 and p2 discard size == 1: ");
	assertTrue(G.discardCount[p1] == 1 && G.discardCount[p2] == 1);

	printf("**ADDING CARD TO P1 DECK**\n");
    gainCard(smithy, &G, 1, p1);
    printf("Checking both p1 hand == 5 and p2 hand size == 0: ");
	assertTrue(G.handCount[p1] == 5 && G.handCount[p2] == 0);
	printf("Checking both p1 deck size == 6 and p2 deck size == 10: ");
	assertTrue(G.deckCount[p1] == 6 && G.deckCount[p2] == 10);
	printf("CHecking both p1  discard size == 1 and p2 discard size == 1: ");
	assertTrue(G.discardCount[p1] == 1 && G.discardCount[p2] == 1);

	printf("**ADDING CARD TO P2 DECK**\n");
    gainCard(smithy, &G, 1, p2);
    printf("Checking both p1 hand == 5 and p2 hand size == 0: ");
	assertTrue(G.handCount[p1] == 5 && G.handCount[p2] == 0);
	printf("Checking both p1 deck size == 6 and p2 deck size == 11: ");
	assertTrue(G.deckCount[p1] == 6 && G.deckCount[p2] == 11);
	printf("CHecking both p1  discard size == 1 and p2 discard size == 1: ");
	assertTrue(G.discardCount[p1] == 1 && G.discardCount[p2] == 1);

	printf("**ADDING CARD TO P1 HAND**\n");
    gainCard(smithy, &G, 2, p1);
    printf("Checking both p1 hand == 6 and p2 hand size == 0: ");
	assertTrue(G.handCount[p1] == 6 && G.handCount[p2] == 0);
	printf("Checking both p1 deck size == 6 and p2 deck size == 11: ");
	assertTrue(G.deckCount[p1] == 6 && G.deckCount[p2] == 11);
	printf("CHecking both p1  discard size == 1 and p2 discard size == 1: ");
	assertTrue(G.discardCount[p1] == 1 && G.discardCount[p2] == 1);

	printf("**ADDING CARD TO P2 HAND**\n");
    gainCard(smithy, &G, 2, p2);
    printf("Checking both p1 hand == 6 and p2 hand size == 1: ");
	assertTrue(G.handCount[p1] == 6 && G.handCount[p2] == 1);
	printf("Checking both p1 deck size == 6 and p2 deck size == 11: ");
	assertTrue(G.deckCount[p1] == 6 && G.deckCount[p2] == 11);
	printf("CHecking both p1  discard size == 1 and p2 discard size == 1: ");
	assertTrue(G.discardCount[p1] == 1 && G.discardCount[p2] == 1);

	//TEST-2 MAKE SURE supplyCount was decremented correctly
	printf("\nTEST-2\n **CHECKING INITIAL supplyCount VS CURRENT supplyCount**\n");
	printf("Check all cards except smithy are same as initial supplyCount: ");
	int supplyTestFlag = 0;
	for(i = 0; i < treasure_map + 1; i++) {
		if (i != smithy) {
    		if (initialSupplyCount[i] != G.supplyCount[i]){
    			supplyTestFlag = 1;
    			break;
    		}
    	}
    }
	assertTrue(supplyTestFlag == 0);
	printf("Checking smithy supplyCount is 6 less than original supplyCount: ");
	assertTrue(G.supplyCount[smithy] == initialSupplyCount[smithy] - 6);

	//TEST-3 MAKE SURE card with 0 supplyCount IS NOT ADDED TO ANY PILE
	//printf("%d", G.supplyCount[smithy]);
	printf("\nTEST-3\n **CHECKING CARD IS NOT ADDED TO ANY PILE WHEN SUPPLY IS 0**\n");
	G.supplyCount[smithy] = 0;
	printf("**ADDING CARD TO P1 DISCARD**\n");
    gainCard(smithy, &G, 0, p1);
    printf("Checking both p1 hand == 6 and p2 hand size == 1: ");
	assertTrue(G.handCount[p1] == 6 && G.handCount[p2] == 1);
	printf("Checking both p1 deck size == 6 and p2 deck size == 11: ");
	assertTrue(G.deckCount[p1] == 6 && G.deckCount[p2] == 11);
	printf("CHecking both p1  discard size == 1 and p2 discard size == 1: ");
	assertTrue(G.discardCount[p1] == 1 && G.discardCount[p2] == 1);

	printf("**ADDING CARD TO P2 DISCARD**\n");
    gainCard(smithy, &G, 0, p2);
    printf("Checking both p1 hand == 6 and p2 hand size == 1: ");
	assertTrue(G.handCount[p1] == 6 && G.handCount[p2] == 1);
	printf("Checking both p1 deck size == 6 and p2 deck size == 11: ");
	assertTrue(G.deckCount[p1] == 6 && G.deckCount[p2] == 11);
	printf("CHecking both p1  discard size == 1 and p2 discard size == 1: ");
	assertTrue(G.discardCount[p1] == 1 && G.discardCount[p2] == 1);

	printf("**ADDING CARD TO P1 DECK**\n");
    gainCard(smithy, &G, 1, p1);
    printf("Checking both p1 hand == 6 and p2 hand size == 1: ");
	assertTrue(G.handCount[p1] == 6 && G.handCount[p2] == 1);
	printf("Checking both p1 deck size == 6 and p2 deck size == 11: ");
	assertTrue(G.deckCount[p1] == 6 && G.deckCount[p2] == 11);
	printf("CHecking both p1  discard size == 1 and p2 discard size == 1: ");
	assertTrue(G.discardCount[p1] == 1 && G.discardCount[p2] == 1);

	printf("**ADDING CARD TO P2 DECK**\n");
    gainCard(smithy, &G, 1, p2);
    printf("Checking both p1 hand == 6 and p2 hand size == 1: ");
	assertTrue(G.handCount[p1] == 6 && G.handCount[p2] == 1);
	printf("Checking both p1 deck size == 6 and p2 deck size == 11: ");
	assertTrue(G.deckCount[p1] == 6 && G.deckCount[p2] == 11);
	printf("CHecking both p1  discard size == 1 and p2 discard size == 1: ");
	assertTrue(G.discardCount[p1] == 1 && G.discardCount[p2] == 1);

	printf("**ADDING CARD TO P1 HAND**\n");
    gainCard(smithy, &G, 2, p1);
    printf("Checking both p1 hand == 6 and p2 hand size == 1: ");
	assertTrue(G.handCount[p1] == 6 && G.handCount[p2] == 1);
	printf("Checking both p1 deck size == 6 and p2 deck size == 11: ");
	assertTrue(G.deckCount[p1] == 6 && G.deckCount[p2] == 11);
	printf("CHecking both p1  discard size == 1 and p2 discard size == 1: ");
	assertTrue(G.discardCount[p1] == 1 && G.discardCount[p2] == 1);

	printf("**ADDING CARD TO P2 HAND**\n");
    gainCard(smithy, &G, 2, p2);
    printf("Checking both p1 hand == 6 and p2 hand size == 1: ");
	assertTrue(G.handCount[p1] == 6 && G.handCount[p2] == 1);
	printf("Checking both p1 deck size == 6 and p2 deck size == 11: ");
	assertTrue(G.deckCount[p1] == 6 && G.deckCount[p2] == 11);
	printf("CHecking both p1  discard size == 1 and p2 discard size == 1: ");
	assertTrue(G.discardCount[p1] == 1 && G.discardCount[p2] == 1);
	//printf("%d", G.supplyCount[smithy]);

	printf("\nTEST-4\n **CHECKING TOP CARD IN DECK, HAND AND DISCARD IS SMITHY**\n");
	printf("Checking both p1 and p2 hand last card is smithy: ");
	assertTrue(G.hand[p1][G.handCount[p1] -1] == smithy && G.hand[p2][G.handCount[p2] -1] == smithy);	
	printf("Checking both p1 and p2 deck last card is smithy: ");
	assertTrue(G.deck[p1][G.deckCount[p1] -1] == smithy && G.deck[p2][G.deckCount[p2] -1] == smithy);
	printf("Checking both p1 and p2 discard last card is smithy: ");
	assertTrue(G.discard[p1][G.discardCount[p1] -1] == smithy && G.discard[p2][G.discardCount[p2] -1] == smithy);

	printf("\n**** gainCard() TESTING COMPLETE ****\n");

    return 0;
}
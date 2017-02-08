/* 
 * Name: Thomas Adamcewicz
 * Due Date: 2/7/17
 * Function: playAdventurer(int currentPlayer, struct gameState *state, int cardDrawn, int drawntreasure, int z, int temphand[MAX_HAND])
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

    printf("\n**** playAdventurer() TESTING BEGINNING ****\n");

	int i;
	int tFlag = 0;
    int seed = 1000;
    int numPlayers = 2;
    int p1 = 0;
    int p2 = 1;
    int cards[10] = {outpost, council_room, feast, gardens, mine,
                     remodel, smithy, village, baron, great_hall};
    int z = 0;
    int tempHand[MAX_HAND];
    int cardDrawn;
    struct gameState G;
    //int maxHandCount = 5;
    int initialSupplyCount[treasure_map + 1];

    //start game
    initializeGame(numPlayers, cards, seed, &G);
    int initDeckSizeP1 = G.deckCount[p1];
    int initDiscardSizeP1 = G.discardCount[p1];
    int initDeckSizeP2 = G.deckCount[p2];
    int initDiscardSizeP2 = G.discardCount[p2];
    int initHandSizeP1 = G.handCount[p1];
    int initHandSizeP2 = G.handCount[p2];
    int drawntreasure = 0;
    int initHandTreasure = 0;

    //add adventurer to first position in p1 hand
    G.hand[p1][0] = adventurer;


    //get initial treasure in hand for p1
    for (i = 0; i < G.handCount[p1]; i++) {
        if (G.hand[p1][i] == copper) initHandTreasure++;
        if (G.hand[p1][i] == silver) initHandTreasure++;
        if (G.hand[p1][i] == gold) initHandTreasure++;
    }


    playAdventurer(p1, &G, cardDrawn, drawntreasure, z, tempHand);
    //TEST-1: Test playAventurer() after game initialized
    printf("TEST-1\n **GAME INITIALIZED CALLING playAdventurer() WITH P1 AND CHECKING CHANGED VARS**\n");
    printf("Check drawntreasure == 0: ");
    assertTrue(drawntreasure == 0);
    printf("Check p1 discardCount > initial discardCount: ");
    assertTrue(G.discardCount[p1] > initDiscardSizeP1);
    printf("Check p1 handCount < initial handCount: ");
    assertTrue(G.handCount[p1] > initHandSizeP1);
    int currHandTreasure = 0;
    for (i = 0; i < G.handCount[p1]; i++) {
        if (G.hand[p1][i] == copper) currHandTreasure++;
        if (G.hand[p1][i] == silver) currHandTreasure++;
        if (G.hand[p1][i] == gold) currHandTreasure++;
    }
    printf("Check p1 initial hand treasure + 2 == current hand treasure for p1: ");
    assertTrue(initHandTreasure + 2 == currHandTreasure);
    printf("Check nothing in p2 Deck/Hand/Discard changed: ");
    assertTrue(initDeckSizeP2 == G.deckCount[p2] && initHandSizeP2 == G.handCount[p2] && initDiscardSizeP2 == G.discardCount[p2]);
    printf("Check adventurer was discarded from p1 hand: ");
    int adventurerFound = 0;
    for (i = 0; i < G.handCount[p1]; i++) {
        if (G.hand[p1][i] == adventurer) adventurerFound++;
    }
    assertTrue(adventurerFound == 0);
     printf("Check cards in discard hand are in kingdom Cards (due to bug introduced): ");
    assertTrue(G.discard[p1][G.discardCount[p1] - 1] >= 0 ||  G.discard[p1][G.discardCount[p1] - 1] <= treasure_map);

    endTurn(&G);
    initDeckSizeP2 = G.deckCount[p2];
    initDiscardSizeP2 = G.discardCount[p2];
    initHandSizeP2 = G.handCount[p2];
    G.hand[p2][0] = adventurer;
    //TEST-2: End P1 turn remove all but 1 treasure cards and playAdventurer()
    printf("TEST-2\n **END P1 TURN, REMOVE ALL BUT 1 TREASURE FROM P2 AND playAdenturer()**\n");
    int initHandTreasureP2 = 0;
    for (i = 0; i < G.handCount[p2]; i++) {
        if (G.hand[p2][i] == copper) initHandTreasureP2++;
        if (G.hand[p2][i] == silver) initHandTreasureP2++;
        if (G.hand[p2][i] == gold) initHandTreasureP2++;
    }
    for (i = 0; i < G.deckCount[p2]; i++) {
        if (G.deck[p2][i] == copper) G.deck[p2][i] = smithy;
        if (G.deck[p2][i] == silver) G.deck[p2][i] = smithy;
        if (G.deck[p2][i] == gold) G.deck[p2][i] = smithy;
    }
    G.deck[p2][0] = copper;
    playAdventurer(p2, &G, cardDrawn, drawntreasure, z, tempHand);
    printf("Check drawntreasure == 0: ");
    assertTrue(drawntreasure == 0);
    printf("Check p2 discardCount > initial discardCount: ");
    assertTrue(G.discardCount[p2] > initDiscardSizeP2);
    printf("Check p2 handCount < initial handCount: ");
    assertTrue(G.handCount[p2] > initHandSizeP2);
    int currHandTreasureP2 = 0;
    for (i = 0; i < G.handCount[p2]; i++) {
        if (G.hand[p2][i] == copper) currHandTreasureP2++;
        if (G.hand[p2][i] == silver) currHandTreasureP2++;
        if (G.hand[p2][i] == gold) currHandTreasureP2++;
    }
    printf("Check p2 initial hand treasure + 1 == current hand treasure for p2: ");
    assertTrue(initHandTreasureP2 + 1 == currHandTreasureP2);
    printf("Check adventurer was discarded from p2 hand: ");
    adventurerFound = 0;
    for (i = 0; i < G.handCount[p2]; i++) {
        if (G.hand[p2][i] == adventurer) adventurerFound++;
    }
    assertTrue(adventurerFound == 0);

    endTurn(&G);
    initDeckSizeP1 = G.deckCount[p1];
    initDiscardSizeP1 = G.discardCount[p1];
    initHandSizeP1 = G.handCount[p1];
    G.hand[p1][0] = adventurer;
    //TEST-3: End P2 turn remove all treasure cards and playAdventurer()
    printf("TEST-3\n **END P2 TURN, REMOVE ALL TREASURE FROM P1 DECK AND playAdenturer()**\n");
    initHandTreasure = 0;
    for (i = 0; i < G.handCount[p1]; i++) {
        if (G.hand[p1][i] == copper) initHandTreasure++;
        if (G.hand[p1][i] == silver) initHandTreasure++;
        if (G.hand[p1][i] == gold) initHandTreasure++;
    }
    for (i = 0; i < G.deckCount[p1]; i++) {
        if (G.deck[p1][i] == copper) G.deck[p1][i] = smithy;
        if (G.deck[p1][i] == silver) G.deck[p1][i] = smithy;
        if (G.deck[p1][i] == gold) G.deck[p1][i] = smithy;
    }
    playAdventurer(p1, &G, cardDrawn, drawntreasure, z, tempHand);
    printf("Check drawntreasure == 0: ");
    assertTrue(drawntreasure == 0);
    printf("Check p1 discardCount > initial discardCount: ");
    assertTrue(G.discardCount[p1] > initDiscardSizeP1);
    printf("Check p1 handCount == initial handCount (no treasure added): ");
    assertTrue(G.handCount[p1] == initHandSizeP1);
    currHandTreasure = 0;
    for (i = 0; i < G.handCount[p1]; i++) {
        if (G.hand[p1][i] == copper) currHandTreasure++;
        if (G.hand[p1][i] == silver) currHandTreasure++;
        if (G.hand[p1][i] == gold) currHandTreasure++;
    }
    printf("Check p1 initial hand treasure == current hand treasure for p1: ");
    assertTrue(initHandTreasure == currHandTreasure);
    printf("Check adventurer was discarded from p1 hand: ");
    adventurerFound = 0;
    for (i = 0; i < G.handCount[p1]; i++) {
        if (G.hand[p1][i] == adventurer) adventurerFound++;
    }
    assertTrue(adventurerFound == 0);

    printf("\n**** playAdventurer() TESTING COMPLETE ****\n");

    return 0;

}
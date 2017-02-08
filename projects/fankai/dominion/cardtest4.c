/*int Doadventurer(int drawntreasure,struct gameState *state,int currentPlayer,int cardDrawn, int *temphand, int z){
   while(drawntreasure<3){
        if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
            shuffle(currentPlayer, state);
        }
        drawCard(currentPlayer, state);
        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]];//??top card of hand is most recently drawn card.
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
            drawntreasure++;
        else{
            temphand[z]=cardDrawn;
            state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
            z++;
        }
    }
    while(z-1>=0){
        state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
        z=z-1;
    }
    return 0;
}
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventure"

int main() {
    int drawntreasure = 0;
    int cardDrawn =0;
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    int z=0;
    int i;
    int temphand[MAX_HAND];
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);


	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.deck[0][0] = copper;
	testG.deck[0][1] = copper;
    testG.deck[0][2] = silver;
	testG.deck[0][3] = village;
	testG.deck[0][4] = village;
    testG.hand[0][0] = adventurer;
	printf("Test adventure draw 2 treasure cards\n");
    Doadventurer(drawntreasure,&testG, currentPlayer, cardDrawn,temphand,z);
    printf("Expected: %d, Result: %d\n", G.handCount[currentPlayer] + 2, testG.handCount[currentPlayer]);
   // int treasureCount = 0;
 	//for ( z = 0; z < testG.handCount[0]; z++) {

		//if (testG.hand[0][z]==gold || testG.hand[0][z]==silver || testG.hand[0][z]==copper)
	//		treasureCount++;
	//}
    printf("Test adventure if discard 2 village cards\n");
    printf("Expected: %d ,Result discard count:%d\n ",G.discardCount[0]+2,testG.discardCount[0] );
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}



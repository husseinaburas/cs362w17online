#include "dominion.h"
#include "dominion_helpers.h"
#include "stdio.h"
#include "stdlib.h"
#include "rngs.h"

int testPlaySmithy();

int main(){

    int x = testPlaySmithy();

    if(x == 0){
        return 0;
    }else{
        printf("Error during testPlaySmithy() testing");
        exit(200);
    }
}

int testPlaySmithy() {
    struct gameState G;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
    int numPlayers = 2;
    int player = 0;
    int seed = 1000;
    int i = 0;

    initializeGame(numPlayers, k, seed, &G);

    G.hand[player][0] = smithy;
    int handPos = 0;
    printf("testPlaySmithy() started: player 1 hand count = %d, smithy pos at %d "
    "number of cards played %d\n", G.handCount[player], 0, G.playedCardCount);
    playSmithy(&G, handPos);
    if((G.hand[player][0] != smithy) && (G.handCount[player] == 7) && (G.playedCardCount == 1) &&
            G.playedCards[0] == smithy){
        printf("testPlaySmithy() finished: player 1 hand count = %d, smithy card removed, "
               "number of cards played %d -- Test Passed \n", G.handCount[player], G.playedCardCount);
    }else{
        printf("testPlaySmithy() finished: player 1 hand count = %d, "
                       "number of cards played %d -- Test Failed \n", G.handCount[player], G.playedCardCount);
    }

    return 0;
}
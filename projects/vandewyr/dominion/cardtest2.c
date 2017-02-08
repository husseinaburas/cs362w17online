#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rngs.h"

int testPlayAdventurer();

int main(){

    int x = testPlayAdventurer();

    if(x == 0){
        return 0;
    }else{
        printf("Error during testPlayAdventurer() testing");
        exit(200);
    }
}

int testPlayAdventurer() {
    struct gameState G;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
    int numPlayers = 2;
    int player = 0;
    int seed = 1000;
    int i = 0;
    int numOfTreasure = 0;
    int newTreasure = 0;
    int tempHand[5];
    int sameArrayFlag = 0;

    initializeGame(numPlayers, k, seed, &G);

    for(i = 0; i < G.handCount[player]; i++){
        if((G.hand[player][i] == copper) || (G.hand[player][i] == silver) ||
                (G.hand[player][i] == gold)){
            numOfTreasure += 1;
        }
    }
    //current hand
    memcpy(tempHand, G.hand[player], 20);
    printf("testPlayAdventurer() started: hand count = %d, treasure cards = %d"
    " \n", G.handCount[player], numOfTreasure);
    playAdventurer(&G);

    for(i = 0; i < G.handCount[player]; i++){
        if((G.hand[player][i] == copper) || (G.hand[player][i] == silver) ||
           (G.hand[player][i] == gold)){
            newTreasure += 1;
        }
    }

    for(i = 0; i < sizeof(tempHand)/sizeof(int); i++){
        if(tempHand[i] == G.hand[player][i]){
            sameArrayFlag += 1;
        }else{
            break;
        }
    }

    if((newTreasure == numOfTreasure+2) && (G.handCount[player] == 7) &&
            (sameArrayFlag == 5)){
        printf("testPlayAdventurer() finished: hand count = %d, treasure cards = %d "
          "originally drawn cards remain -- Test Passed \n", G.handCount[player], newTreasure);
    }else{
        printf("testPlayAdventurer() finished: hand count = %d, treasure cards = %d "
          "original cards may not be the same -- Test Failed \n", G.handCount[player], newTreasure);
    }

    return 0;
}

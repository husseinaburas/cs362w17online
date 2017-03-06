#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "string.h"

int remodelAssert(int val);

int main(){
    srand((unsigned) time(0));

    int i = 1;
    int timesRan = 0;
    int seed = 0;
    int numPlayers = 2;
    int failures = 0;
    int passes = 0;

    while(i == 1){
        seed = rand()+1 % 10000;
        int x;
        int y;

        //G will be used to store pre-state
        struct gameState G;

        int k[10] = {adventurer, gardens, embargo, village, minion, mine, remodel,
                     sea_hag, tribute, smithy};
        int player = rand() % 2;

        initializeGame(numPlayers, k, seed, &G);

        //randomize cards in hand
        //set handCount to 5 for testing
        for(x = 0; x < numPlayers; x++){
            for(y = 0; y < 5; y++){
                G.hand[x][y] = rand() % 27;
            }
            G.handCount[x] = 5;
        }

        //ensure random player has turn
        G.whoseTurn = player;

        //enable shuffle function to be reached.
        int empty = rand()%2;
        if(empty == 0){
            G.deckCount[player] = 0;
            //Add to discard pile for shuffling
            for(y = 0; y < 100; y++){
                G.discard[player][y] = rand() % 27;
                G.discardCount[player]+=1;
            }
        }

        //testState will be checked against G for errors
        struct gameState testState;
        memcpy(&testState, &G, sizeof(struct gameState));

        //run function with remodel card seeded to enable correct case for testing
        playAdventurer(&testState);

        //If deckCount is same for both then function failed to shuffle
        if(remodelAssert(testState.deckCount[player] == G.deckCount[player]) == 1){
            failures++;
        }else{
            passes++;
        }

        //with two extra treasure cards handCount should be 7
        if(remodelAssert(testState.handCount[player] == 7) == 0){
            failures++;
        }else{
            passes++;
        }

        //numActions should be zero as Adventurer is an action card
        if(remodelAssert(testState.numActions == 0) == 0){
            failures++;
        }else{
            passes++;
        }

        //check the last cards for treasure
        if((remodelAssert(testState.hand[player][5] != copper || testState.hand[player][5] != silver ||
                                 testState.hand[player][5] != gold  && testState.hand[player][6] != copper ||
                                 testState.hand[player][6] != silver) || testState.hand[player][6] != gold)){
            failures++;
        }else{
            passes++;
        }

        timesRan++;
        if(timesRan == 1000){
            i = 0;
        }
    }

    printf("Finished running randomtestadventurer: %d passes, %d failures\n", passes, failures);
    return 0;
}

int remodelAssert(int val){
    if(val == 1){
        return 1;
    }else{
        return 0;
    }
}

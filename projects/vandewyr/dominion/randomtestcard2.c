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
        int nextPlayer = 0;
        if(player == 0){
            nextPlayer = 1;
        }

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

        //randomize council_room card in hand
        int location = rand() % 5;
        G.hand[player][location] = council_room;

        //testState will be checked against G for errors
        struct gameState testState;
        memcpy(&testState, &G, sizeof(struct gameState));

        //location is the handPos of council_room
        playCouncil_Room(&testState, location);

        //4 cards drawn with council_room discarded = 8 cards in hand
        if(remodelAssert(testState.handCount[player] == 8) == 0){
            failures++;
        }else{
            passes++;
        }

        //test for other player drawing card
        if(remodelAssert(testState.handCount[nextPlayer] == G.handCount[nextPlayer]+1) == 0){
            failures++;
        }else{
            passes++;
        }

        //council_room gives +1 Buy attribute
        if(remodelAssert(testState.numBuys == 2) == 0){
            failures++;
        }else{
            passes++;
        }

        timesRan++;
        if(timesRan == 1000){
            i = 0;
        }
    }

    printf("Finished running randomtestcard2: %d passes, %d failures\n", passes, failures);
    return 0;
}

int remodelAssert(int val){
    if(val == 1){
        return 1;
    }else{
        return 0;
    }
}


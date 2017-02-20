#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "string.h"

int remodelAssert(int val);

int main() {
    srand((unsigned) time(0));

    int i = 1;
    int timesRan = 0;
    int seed = 0;
    int numPlayers = 0;
    int failures = 0;
    int passes = 0;

    while(i == 1){
        seed = rand()+1 % 10000;
        numPlayers = 2;
        int x;
        int y;

        //G will be used to store pre-state
        struct gameState G;

        int k[10] = {adventurer, gardens, embargo, village, minion, mine, remodel,
                     sea_hag, tribute, smithy};
        int player = rand() % 2;

        initializeGame(numPlayers, k, seed, &G);

        for(x = 0; x < numPlayers; x++){
            for(y = 0; y < 5; y++){
                G.hand[x][y] = rand() % 27;
            }
        }

        //make random location to place remodel card
        int cardLocation = rand() % 5;
        //place remodel in player's hand
        G.hand[player][cardLocation] = remodel;
        //select random card location to select card to remove
        int choice1 = cardLocation;
        while(choice1 == cardLocation){
            choice1 = rand() % 5;
        }
        //choice2 is desired card to buy
        int choice2 = rand() % 27;
        //choice3 not used in test
        int choice3 = rand() % 27;

        //testState will be checked against G for errors
        struct gameState testState;
        memcpy(&testState, &G, sizeof(struct gameState));

        //run function with remodel card seeded to enable correct case for testing
        cardEffect(remodel, choice1, choice2, choice3, &testState, cardLocation, 0);

        //Test that the remodel card has been removed from the players hand
        //Test that choice2 was in hand at end
        //Test for correct amount of cads in hand
        if(remodelAssert(testState.hand[player][cardLocation] != 12) == 0){
            failures++;
        }else{
            passes++;
        }

        if(remodelAssert(testState.hand[player][0] != remodel &&
                    testState.hand[player][1] != remodel && testState.hand[player][2] != remodel &&
                    testState.hand[player][3] != remodel)){
            failures++;
        }else {
            passes++;
        }

        if(remodelAssert(testState.handCount[player] == 4) == 0){
            failures++;
        }else{
            passes++;
        }


        timesRan++;
        if(timesRan == 1000){
            i = 0;
        }
    }

    printf("Finished running randomtestcard1: %d passes, %d failures\n", passes, failures);
    return 0;
}

int remodelAssert(int val){
    if(val == 1){
        return 1;
    }else{
        return 0;
    }
}
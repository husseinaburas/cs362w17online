#include "dominion.h"
#include "dominion_helpers.h"
#include "stdio.h"
#include "stdlib.h"
#include "rngs.h"

int testGreatHall();

int main(){

    int x = testGreatHall();

    if(x == 0){
        return 0;
    }else{
        printf("Error during testPlaySmithy() testing");
        exit(200);
    }
}

int testGreatHall() {
    struct gameState G;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
    int numPlayers = 2;
    int player = 0;
    int seed = 1000;
    int i = 0;

    initializeGame(numPlayers, k, seed, &G);

    int card = great_hall;
    G.hand[player][0] = great_hall;
    int handPos = 0;
    int *bonus = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int oldNumActions = G.numActions;

    printf("testGreatHall() started: hand count = %d, number of actions = %d, great_hall at position 0 \n",
    G.handCount[player], G.numActions);
    cardEffect(card, choice1, choice2, choice3, &G, handPos, bonus);
    int newNumActions = G.numActions;
    if((G.hand[player][0] != great_hall) && (G.handCount[player] == 5) &&
            (newNumActions = oldNumActions + 1)){
        printf("testGreatHall() finished: hand count = %d, number of actions = %d, great_hall discarded"
               " -- Test Passed \n", G.handCount[player], G.numActions);
    }else{
        printf("testGreatHall() finished: hand count = %d, number of actions = %d, great_hall whereabouts unknown"
              " -- Test Failed \n", G.handCount[player], G.numActions);
    }


    return 0;

}

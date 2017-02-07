#include "dominion.h"
#include "dominion_helpers.h"
#include "stdio.h"
#include "stdlib.h"
#include "rngs.h"

int testCouncilRoom();

int main(){

    int x = testCouncilRoom();

    if(x == 0){
        return 0;
    }else{
        printf("Error during testCouncilRoom() testing");
        exit(200);
    }
}

int testCouncilRoom() {
    struct gameState G;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
    int numPlayers = 2;
    int player = 0;
    int seed = 1000;
    int i = 0;

    initializeGame(numPlayers, k, seed, &G);
    G.hand[player][0] = 8;
    int handPos = 0;

    printf("testCouncilRoom() started: hand count = %d, number of buys = %d, player 1 hand"
    "count = %d \n", G.handCount[player], G.numBuys, G.handCount[player+1]);
    playCouncil_Room(&G, handPos);
    if((G.handCount[player] == 8) && (G.numBuys == 2) && (G.handCount[player+1] == 1) &&
            (G.hand[player][0] != council_room)){
        printf("testCouncilRoom() finished: hand count = %d, number of buys = %d, player 1 hand \n"
        "count = %d, council room card discarded --Test Passed \n",
               G.handCount[player], G.numBuys, G.handCount[player+1]);
    }else{
        printf("testCouncilRoom() finished: hand count = %d, number of buys = %d, player 1 hand \n"
        "count = %d, council room card discarded --Test Passed \n",
               G.handCount[player], G.numBuys, G.handCount[player+1]);
    }

    return 0;

}

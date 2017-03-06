#include "dominion.h"
#include "dominion_helpers.h"
#include "stdio.h"
#include "stdlib.h"
#include "rngs.h"

int testGainCard();

int main(){

    int x = testGainCard();

    if(x == 0){
        return 0;
    }else{
        printf("Error during testGainCard() testing");
        exit(200);
    }
}

int testGainCard() {
    struct gameState G;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
    int numPlayers = 2;
    int player = 0;
    int seed = 1000;
    //Adventurer Card
    int supplyPos = 7;
    initializeGame(numPlayers, k, seed, &G);

    //2 = add to hand
    int toFlag = 2;
    int oldHandCount = G.handCount[player];
    int oldSupplyCount = G.supplyCount[supplyPos];
    printf("testGainCard() test: attempt to add adventurer to hand ");
    gainCard(supplyPos, &G, toFlag, player);
    //check if 6th card in hand is now adventurer, oldHandCount should be less
    //and oldSupplyCount should be greater
    if((G.hand[player][5] == 7) && (oldHandCount < G.handCount[player]) &&
            (oldSupplyCount > G.supplyCount[supplyPos])){
        printf(" -- Test Passed \n");
    }else if((G.hand[player][5] != 7) || (oldHandCount >= G.handCount[player]) ||
            (oldSupplyCount <= G.supplyCount[supplyPos])) {
        printf(" -- Test Failed \n");
    }

    //1 = add to deck
    toFlag = 1;
    //Minion Card
    supplyPos = 17;
    oldSupplyCount = G.supplyCount[supplyPos];
    int oldDeckCount = G.deckCount[player];
    printf("testGainCard() test: attempt to add minion to deck ");
    //toFlag is set to 1, testing for card being inserted into deck
    gainCard(supplyPos, &G, toFlag, player);
    if((G.deck[player][G.deckCount[player]-1] == 17) && (oldDeckCount < G.deckCount[player]) &&
            (oldSupplyCount > G.supplyCount[supplyPos])){
        printf(" -- Test Passed \n");
    }else if((G.deck[player][G.deckCount[player]-1] != 17) || (oldDeckCount >= G.deckCount[player]) ||
            (oldSupplyCount <= G.supplyCount[supplyPos])) {
        printf(" -- Test Failed \n");
    }

    //0 = add to discard
    toFlag = 0;
    //Smithy Card
    supplyPos = 13;
    oldSupplyCount = G.supplyCount[supplyPos];
    int oldDiscardCount = G.discardCount[player];
    printf("testGainCard() test: attempt to add smithy to discard ");
    //toFlag set to 0, testing for card being discarded
    gainCard(supplyPos, &G, toFlag, player);
    if((G.discard[player][G.discardCount[player]-1] == 13) && (oldDiscardCount < G.discardCount[player]) &&
       (oldSupplyCount > G.supplyCount[supplyPos])){
        printf(" -- Test Passed \n");
    }else if((G.discard[player][G.discardCount[player]-1] != 13) || (oldDiscardCount >= G.discardCount[player]) ||
             (oldSupplyCount <= G.supplyCount[supplyPos])) {
        printf(" -- Test Failed \n");
    }



    return 0;
}
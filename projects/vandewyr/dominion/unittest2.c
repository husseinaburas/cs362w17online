#include "dominion.h"
#include "dominion_helpers.h"
#include "stdio.h"
#include "stdlib.h"
#include "rngs.h"

int testBuyCard();

int main(){

    int x = testBuyCard();

    if(x == 0){
        return 0;
    }else{
        printf("Error during testBuyCard() testing");
        exit(200);
    }
}

int testBuyCard(){
    struct gameState G;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
    int numPlayers = 2;
    int player = 0;
    int seed = 1000;
    int supplyPos;
    initializeGame(numPlayers, k, seed, &G);

    supplyPos = 1;
    //Testing for normal functionality, perfect world scenario
    printf("testBuyCard() test: coins = %d, estate cost = %d (buy allowed)", G.coins, 2);
    buyCard(supplyPos, &G);
    if(G.hand[player][5] == 1){
        printf("-- Test Passed \n");
    }else if(G.hand[player][5] != 1){
        printf("-- Test Failed \n");
    }

    supplyPos = 3;
    //numBuys needs to be greater than 0
    G.numBuys = 1;
    //Testing for buying card with not enough coins
    printf("testBuyCard() test: coins = %d, province cost = %d (buy not allowed)", G.coins, 8);
    int returnValue = buyCard(supplyPos, &G);
    if(returnValue == -1){
        printf("-- Test Passed \n");
    }else if(returnValue != -1){
        printf("-- Test Failed \n");
    }

    supplyPos = 11;
    G.coins = 5;
    //numBuys needs to be greater than 0
    G.numBuys = 1;
    //Set mine cards to 0, should not be purchasable
    G.supplyCount[11] = 0;
    //Test to buy card that is no longer in the supply
    printf("testBuyCard() test: coins = %d, mine supply = %d (buy not allowed)", G.coins, G.supplyCount[11]);
    returnValue = buyCard(supplyPos, &G);
    if(returnValue == -1){
        printf("-- Test Passed \n");
    }else if(returnValue != -1){
        printf("-- Test Failed \n");
    }


    return 0;
}
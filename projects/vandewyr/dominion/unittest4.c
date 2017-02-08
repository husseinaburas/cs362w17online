#include "dominion.h"
#include "dominion_helpers.h"
#include "stdio.h"
#include "stdlib.h"
#include "rngs.h"

int testIsGameOver();

int main(){

    int x = testIsGameOver();

    if(x == 0){
        return 0;
    }else{
        printf("Error during testIsGameOver() testing");
        exit(200);
    }
}

int testIsGameOver() {
    struct gameState G;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
    int numPlayers = 2;
    int player = 0;
    int seed = 1000;
    int i = 0;

    initializeGame(numPlayers, k, seed, &G);

    //Test checks if game is over when all province cards remain and no supply stacks
    //have been depleted
    printf("isGameOver() test: test with province cards at %d and supplies full ", G.supplyCount[province]);
    int over = isGameOver(&G);
    if(over == 0){
        printf("-- Test Passed \n");
    }else if(over == -1){
        printf("-- Test Failed \n");
    }

    //Test checks if game is over when all province cards depleted but all supply stacks remain
    G.supplyCount[province] = 0;
    printf("isGameOver() test: test with province cards at %d and supplies full ", G.supplyCount[province]);
    over = isGameOver(&G);
    if(over == 1){
        printf("-- Test Passed \n");
    }else if(over == 0){
        printf("-- Test Failed \n");
    }

    //Test checks if game is over when all province cards remain but 3 supply stacks
    //have been depleted
    G.supplyCount[province] = 8;
    G.supplyCount[4] = 0;
    G.supplyCount[5] = 0;
    G.supplyCount[6] = 0;
    printf("isGameOver() test: test with province cards at %d and 3 supply stacks depleted ",
           G.supplyCount[province]);
    over = isGameOver(&G);
    if(over == 1){
        printf("-- Test Passed \n");
    }else if(over == 0){
        printf("-- Test Failed \n");
    }

    return 0;
}



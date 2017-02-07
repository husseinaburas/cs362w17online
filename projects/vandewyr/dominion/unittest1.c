#include "dominion.h"
#include "dominion_helpers.h"
#include "stdio.h"
#include "stdlib.h"
#include "rngs.h"

int testUpdateCoins();

int main(){

    int x = testUpdateCoins();

    if(x == 0){
        return 0;
    }else{
        printf("Error during testUpdateCoins() testing");
        exit(200);
    }
}

int testUpdateCoins(){
    struct gameState G;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
    int numPlayers = 2;
    int player = 0;
    int bonus = 0;
    int seed = 1000;
    int i = 0;
    int handCount;
    initializeGame(numPlayers, k, seed, &G);
    G.coins = 0;

    for (i = 0; i < G.handCount[player]; i++){
        G.hand[player][i] = 1;
    }

    //Test for when no treasure cards are held
    printf("updateCoins() test: Zero treasure cards, expect 0,  returned ");
    updateCoins(player, &G, bonus);
    if(G.coins == 0){
        printf("%d -- Test Passed\n", G.coins);
    }else if(G.coins != 0){
        printf("%d -- Test Failed\n", G.coins);
    }

    G.coins = 0;
    for (i = 0; i < G.handCount[player]; i++){
        G.hand[player][i] = 4;
    }

    //Test for when all cards are treasure cards
    printf("updateCoins() test: 5 copper cards, expect 5,  returned ");
    updateCoins(player, &G, bonus);
    if(G.coins == 5){
        printf("%d -- Test Passed\n", G.coins);
    }else if(G.coins != 5){
        printf("%d -- Test Failed\n", G.coins);
    }

    G.coins = 0;
    bonus = 2;
    for (i = 0; i < G.handCount[player]; i++){
        if(i < 2)
            G.hand[player][i] = 4;
        else if(i < 4)
            G.hand[player][i] = 5;
        else if(i == 4){
            G.hand[player][i] = 1;
        }
    }

    //Test for bonus plus 4 treasure cards and 1 estate card
    printf("updateCoins() test: 2 copper, 2 silver, bonus+2 -- expect 8,  returned ");
    updateCoins(player, &G, bonus);
    if(G.coins == 8){
        printf("%d -- Test Passed\n", G.coins);
    }else{
        printf("%d -- Test Failed\n", G.coins);
    }


    return 0;
}
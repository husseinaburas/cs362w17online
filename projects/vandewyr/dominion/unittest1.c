#include "dominion.h"
#include "dominion_helpers.h"
#include "stdio.h"
#include "stdlib.h"
#include "rngs.h"


/**int numPlayers; //number of players
int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
int embargoTokens[treasure_map+1];
int outpostPlayed;
int outpostTurn;
int whoseTurn;
int phase;
int numActions; ///Starts at 1 each turn
int coins; /// Use as you see
int numBuys; /// Starts at 1 each turn
int hand[MAX_PLAYERS][MAX_HAND];
int handCount[MAX_PLAYERS];
int deck[MAX_PLAYERS][MAX_DECK];
int deckCount[MAX_PLAYERS];
int discard[MAX_PLAYERS][MAX_DECK];
int discardCount[MAX_PLAYERS];
int playedCards[MAX_DECK];
int playedCardCount;
**/

int testUpdateCoins();

int main(){

    int x = testUpdateCoins();

    if(x == 0){
        return 0;
    }else{
        printf("Error during updateCoins() testing");
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
            G.hand[player][i] = 6;
        }
    }

    printf("updateCoins() test: 2 copper, 2 silver, 1 gold, 2 bonus -- expect 11,  returned ");
    updateCoins(player, &G, bonus);
    if(G.coins == 11){
        printf("%d -- Test Passed\n", G.coins);
    }else if(G.coins != 11){
        printf("%d -- Test Failed\n", G.coins);
    }


    return 0;
}
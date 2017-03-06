/* -----------------------------------------------------------------------
 *
 *          unittest1.c
 *          Unit Testing playCard()
 * 
 *      
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

 #define TESTFUNCTION "playCard()"

 void failedTest() {
    printf("!!!! FAILED TEST !!!!\n");
 }

int main() {
    // Some initialization variables
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0;
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    int k[10] = {adventurer, embargo, great_hall, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    
    struct gameState G, testG;

    // Initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);


    printf("---------------------- Testing card: %s ----------------------\n", TESTFUNCTION);

    printf("----Test 1: Try to play card after action phase is over ----\n");
    G.phase = 1;    // Phase changes after a card is bought signifying the end of the action phase
    printf("game state expected to be unchanged after an unsuccessful attempt to buy a card after action phase is over\n");
    if(playCard(handpos, choice1, choice2, choice3, &G)  != -1)
        failedTest();

    printf("----Test 2: Try to play card when player does not have actions available ----\n");
    G.numActions = 0;
    printf("game state expected to be unchanged after an unsuccessful attempt to buy a card when no actions are available\n");
    if(playCard(handpos, choice1, choice2, choice3, &G)  != -1)
        failedTest();

    printf("----Test 3: Try to play card that is not an action card ----\n");
    G.phase = 0;
    G.numActions = 1;
    G.hand[currentPlayer][handpos] = copper;
    printf("game state expected to be unchanged after trying to play a card that is not an action card\n");
    if(playCard(handpos, choice1, choice2, choice3, &G)  != -1)
        failedTest();


    printf("----Test 4: Try to play card that is not in the game ----\n");
    G.phase = 0;
    G.numActions = 1;
    G.hand[currentPlayer][handpos] = outpost;
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("game state expected to be unchanged after trying to play a card that is not in the current game\n");
    if(playCard(handpos, choice1, choice2, choice3, &G)  != -1)
        failedTest();

    playCard(handpos, choice1, choice2, choice3, &G);
    printf("current numActions = %d, expected %d\n", G.numActions, testG.numActions - 1);
    if(G.numActions != testG.numActions - 1)
        failedTest();

    
    printf("----Test 5: Try to play card that is in the current game with no coin bonus----\n");
    G.numActions = 1;
    G.hand[currentPlayer][handpos] = sea_hag;
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("current coins = %d, expected %d\n", G.coins, testG.coins);          // Check to make sure coins are equal prior to playCard called
    if(G.coins != testG.coins)
        failedTest();
    playCard(handpos, choice1, choice2, choice3, &G);
    printf("current numActions = %d, expected %d\n", G.numActions, testG.numActions - 1);
    if(G.numActions != testG.numActions -1)
        failedTest();

    printf("current coins = %d, expected %d\n", G.coins, testG.coins);          // Test failing. Bug somewhere, though not tracing it immediately
    if(G.coins != testG.coins)
        failedTest();


    printf("----Test 6: Try to play card that is in the current game with a coin bonus----\n");
    G.numActions = 1;
    G.hand[currentPlayer][handpos] = embargo;
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("current coins = %d, expected %d\n", G.coins, testG.coins);          // Check to make sure coins are equal prior to playCard called
    if(G.coins != testG.coins)
        failedTest();
    playCard(handpos, choice1, choice2, choice3, &G);
    printf("current numActions = %d, expected %d\n", G.numActions, testG.numActions - 1);
    if(G.numActions != testG.numActions -1)
        failedTest();

    printf("current coins = %d, expected %d\n", G.coins, testG.coins);          // Test failing. Bug somewhere, though not tracing it immediately
    if(G.coins != testG.coins)
        failedTest();


    printf("----Test 7: Try to play card that is in the current game which increases numActions----\n");
    G.numActions = 1;
    G.hand[currentPlayer][handpos] = great_hall;
    memcpy(&testG, &G, sizeof(struct gameState));

    if (playCard(handpos, choice1, choice2, choice3, &G) == -1)             //Included to make sure playCard was not returning -1
        failedTest();

    playCard(handpos, choice1, choice2, choice3, &G);
    printf("current numActions = %d, expected %d\n", G.numActions, testG.numActions);
    if(G.numActions != testG.numActions)
        failedTest();



    printf("------------ Testing complete for: %s -----------------------\n", TESTFUNCTION);
    return 0;
}

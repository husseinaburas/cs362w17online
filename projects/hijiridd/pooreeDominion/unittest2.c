/* -----------------------------------------------------------------------
 *
 *          unittest1.c
 *          Unit Testing gainCard()
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

 #define TESTFUNCTION "gainCard()"

 void failedTest() {
    printf("!!!! FAILED TEST !!!!\n");
 }

int main() {
    // Some initialization variables
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    
    struct gameState G, testG;

    // Initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);


    printf("---------------------- Testing card: %s ----------------------\n", TESTFUNCTION);

    printf("----Test 1: Try to gain a card not in play ----\n");

    // copy the game state to a test case 
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("game state expected to be unchanged after an unsuccessful attempt to gain a card\n");
    if(gainCard(salvager, &G, 0, currentPlayer) != -1)
        failedTest();

    printf("----Test 2: Gain a card with flag=1 ----\n");
    //Actual card gained not relevant, no card effects being called, any card in play and flag=1
    gainCard(adventurer, &G, 1, currentPlayer);
    printf("current player card deck count = %d, expected %d\n", G.deckCount[currentPlayer], testG.deckCount[currentPlayer] + 1);
    if(G.deckCount[currentPlayer] != testG.deckCount[currentPlayer] + 1)
        failedTest();

    printf("last card of deck = %d, expected adventurer (7)\n", G.deck[currentPlayer][G.deckCount[currentPlayer]-1]);
    if(G.deck[currentPlayer][G.deckCount[currentPlayer]-1] != adventurer)
        failedTest();

    printf("current supply count = %d, expected %d\n", G.supplyCount[adventurer], testG.supplyCount[adventurer] - 1);
    if(G.supplyCount[adventurer] != testG.supplyCount[adventurer] - 1)
        failedTest();

    printf("----Test 2: Gain a card with flag=2 ----\n"); 
    gainCard(mine, &G, 2, currentPlayer);
    printf("current player card hand count = %d, expected %d\n", G.handCount[currentPlayer], testG.handCount[currentPlayer] + 1);
    if(G.handCount[currentPlayer] != testG.handCount[currentPlayer] + 1)
        failedTest();

    printf("last card of hand = %d, expected mine (11)\n", G.hand[currentPlayer][G.handCount[currentPlayer]-1]);
    if(G.hand[currentPlayer][G.handCount[currentPlayer]-1] != mine)
        failedTest();

    printf("current supply count = %d, expected %d\n", G.supplyCount[mine], testG.supplyCount[mine] - 1);
    if(G.supplyCount[mine] != testG.supplyCount[mine] - 1)
        failedTest();

    printf("----Test 3: Gain a card with flag=0 ----\n"); 
    gainCard(minion, &G, 0, currentPlayer);
    printf("current player card discard count = %d, expected %d\n", G.discardCount[currentPlayer], testG.discardCount[currentPlayer] + 1);
    if(G.discardCount[currentPlayer] != testG.discardCount[currentPlayer] + 1)
        failedTest();

    printf("last card of hand = %d, expected minion (17)\n", G.discard[currentPlayer][G.discardCount[currentPlayer]-1]);
    if(G.discard[currentPlayer][G.discardCount[currentPlayer]-1] != minion)
        failedTest();

    printf("current supply count = %d, expected %d\n", G.supplyCount[minion], testG.supplyCount[minion] - 1);
    if(G.supplyCount[minion] != testG.supplyCount[minion] - 1)
        failedTest();

    printf("----Test 4: No change to other player's decks should have occurred with current player's gain----\n"); 
    printf("other player card deck count = %d, expected %d\n", G.deckCount[currentPlayer + 1], testG.deckCount[currentPlayer + 1]);
    if(G.deckCount[currentPlayer + 1] != testG.deckCount[currentPlayer + 1])
        failedTest();

    printf("other player card hand count = %d, expected %d\n", G.handCount[currentPlayer + 1], testG.handCount[currentPlayer + 1]);
    if(G.handCount[currentPlayer + 1] != testG.handCount[currentPlayer + 1])
        failedTest();

    printf("other player card discard count = %d, expected %d\n", G.discardCount[currentPlayer + 1], testG.discardCount[currentPlayer + 1]);
    if(G.discardCount[currentPlayer + 1] != testG.discardCount[currentPlayer])
        failedTest();


    printf("------------ Testing complete for: %s -----------------------\n", TESTFUNCTION);
    return 0;
}

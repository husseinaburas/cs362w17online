/* -----------------------------------------------------------------------
 *  Method buyCard
 *  --------------
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "asserttrue.h"
#include "rngs.h"


// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
#define CARDORFUNCTIONTOTEST "buyCard"


int main() {
    
    /****************************** Main Setup ******************************/
    
    int constantSeedForRandomSeed = 1;
    int numPlayer = 2;
    struct gameState NewGameStateStruct, OldVersionOfGameStruct, resetVersionOfGameStruct;
    
    memset(&NewGameStateStruct, 23, sizeof(struct gameState));      // clear the game state
    memset(&OldVersionOfGameStruct, 23, sizeof(struct gameState));  // clear the old game state (used to compare before after effect of method call)
    memset(&resetVersionOfGameStruct, 23, sizeof(struct gameState));  // clear the old game state (used to compare before after effect of method call)
    
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    
    // initialize a game state and player cards
    initializeGame(numPlayer, k, constantSeedForRandomSeed, &NewGameStateStruct);
    //memcpy(&NewGameStateStruct, &OldVersionOfGameStruct, sizeof(struct gameState)); // copy game state to have before - after comparision
    resetVersionOfGameStruct = NewGameStateStruct;
    
    printf("----------------- Testing: %s ----------------\n", CARDORFUNCTIONTOTEST);
    
    // Did Any Test Fail Variable
    int atLeast1TestFailed = 0;
    
    
    //Invariable Conditions for all Tests
    int enumOfCardBeingBought = estate;
    int indexCurrentPlayer = 0;
    
    
    
    // ----------- TEST 1: Test no more buys left --------------
    //Invariable Conditions for this Test
    NewGameStateStruct.numBuys = 0;
    NewGameStateStruct.supplyCount[estate] = 3;
    NewGameStateStruct.coins = 2;
    
    printf("--- TEST 1: Test no more buys left\n");
    // copy the game state to compare (before + expected) with after
    OldVersionOfGameStruct = NewGameStateStruct;
    
    /**** Call Func ****/
    int resultBuyCard = buyCard(enumOfCardBeingBought, &NewGameStateStruct);
    
    asserttrue(resultBuyCard == -1, &atLeast1TestFailed);
    
    // copy the game state to compare (before + expected) with after
    OldVersionOfGameStruct = NewGameStateStruct;
    printf("Buy Success Status = %d, expected = %d\n", buyCard(enumOfCardBeingBought, &NewGameStateStruct), -1);
    
    /**** Assert Results ****/
    asserttrue(buyCard(enumOfCardBeingBought, &NewGameStateStruct) == -1, &atLeast1TestFailed);
    
    printf("Coin Count = %d, expected = %d\n", NewGameStateStruct.coins, OldVersionOfGameStruct.coins);
    asserttrue(NewGameStateStruct.coins == OldVersionOfGameStruct.coins, &atLeast1TestFailed);
    
    printf("num Buys Count = %d, expected = %d\n", NewGameStateStruct.numBuys, OldVersionOfGameStruct.numBuys);
    asserttrue(NewGameStateStruct.numBuys == OldVersionOfGameStruct.numBuys, &atLeast1TestFailed);
    
    printf("handCount Count = %d, expected = %d\n", NewGameStateStruct.handCount[indexCurrentPlayer], OldVersionOfGameStruct.handCount[indexCurrentPlayer]);
    asserttrue(NewGameStateStruct.handCount[indexCurrentPlayer] == OldVersionOfGameStruct.handCount[indexCurrentPlayer], &atLeast1TestFailed);
    
    printf("supply Count = %d, expected = %d\n", NewGameStateStruct.supplyCount[estate], OldVersionOfGameStruct.supplyCount[estate]);
    asserttrue(NewGameStateStruct.supplyCount[estate] == OldVersionOfGameStruct.supplyCount[estate], &atLeast1TestFailed);
    
    /**** End Assert Results ****/
    
    
    // ----------- TEST 2: Test no more estate card left --------------
    //Invariable Conditions for this Test
    NewGameStateStruct = resetVersionOfGameStruct;
    NewGameStateStruct.numBuys = 2;
    NewGameStateStruct.supplyCount[estate] = 0;
    NewGameStateStruct.coins = 2;
    
    printf("--- TEST 2: Test no more estate card left\n");
    /**** Call Func ****/
    OldVersionOfGameStruct = NewGameStateStruct;
    resultBuyCard = buyCard(enumOfCardBeingBought, &NewGameStateStruct);
    asserttrue(resultBuyCard == -1, &atLeast1TestFailed);
    
    // copy the game state to compare (before + expected) with after
    
    printf("Buy Success Status = %d, expected = %d\n", resultBuyCard, -1);
    
    /**** Assert Results ****/
    asserttrue(resultBuyCard == -1, &atLeast1TestFailed);
    
    printf("Coin Count = %d, expected = %d\n", NewGameStateStruct.coins, OldVersionOfGameStruct.coins);
    asserttrue(NewGameStateStruct.coins == OldVersionOfGameStruct.coins, &atLeast1TestFailed);
    
    printf("num Buys Count = %d, expected = %d\n", NewGameStateStruct.numBuys, OldVersionOfGameStruct.numBuys);
    asserttrue(NewGameStateStruct.numBuys == OldVersionOfGameStruct.numBuys, &atLeast1TestFailed);
    
    printf("handCount Count = %d, expected = %d\n", NewGameStateStruct.handCount[indexCurrentPlayer], OldVersionOfGameStruct.handCount[indexCurrentPlayer]);
    asserttrue(NewGameStateStruct.handCount[indexCurrentPlayer] == OldVersionOfGameStruct.handCount[indexCurrentPlayer], &atLeast1TestFailed);
    
    printf("supply Count = %d, expected = %d\n", NewGameStateStruct.supplyCount[estate], OldVersionOfGameStruct.supplyCount[estate]);
    asserttrue(NewGameStateStruct.supplyCount[estate] == OldVersionOfGameStruct.supplyCount[estate], &atLeast1TestFailed);
    
    /**** End Assert Results ****/
    
    
    // ----------- TEST 3: Test not enough coins for Estate buy --------------
    //Invariable Conditions for this Test
    NewGameStateStruct = OldVersionOfGameStruct;
    NewGameStateStruct.numBuys = 2;
    NewGameStateStruct.supplyCount[estate] = 3;
    NewGameStateStruct.coins = 1;
    
    printf("--- TEST 3: Test not enough coins for Estate buy\n");
    // copy the game state to compare (before + expected) with after
    NewGameStateStruct = OldVersionOfGameStruct ;
    
    /**** Call Func ****/
    resultBuyCard = buyCard(enumOfCardBeingBought, &NewGameStateStruct);
    asserttrue(resultBuyCard == -1, &atLeast1TestFailed);
    
    // copy the game state to compare (before + expected) with after
    OldVersionOfGameStruct = NewGameStateStruct;
    printf("Buy Success Status = %d, expected = %d\n", resultBuyCard, -1);
    
    /**** Assert Results ****/
    asserttrue(buyCard(enumOfCardBeingBought, &NewGameStateStruct) == -1, &atLeast1TestFailed);
    
    printf("Coin Count = %d, expected = %d\n", NewGameStateStruct.coins, OldVersionOfGameStruct.coins);
    asserttrue(NewGameStateStruct.coins == OldVersionOfGameStruct.coins, &atLeast1TestFailed);
    
    printf("num Buys Count = %d, expected = %d\n", NewGameStateStruct.numBuys, OldVersionOfGameStruct.numBuys);
    asserttrue(NewGameStateStruct.numBuys == OldVersionOfGameStruct.numBuys, &atLeast1TestFailed);
    
    printf("handCount Count = %d, expected = %d\n", NewGameStateStruct.handCount[indexCurrentPlayer], OldVersionOfGameStruct.handCount[indexCurrentPlayer]);
    asserttrue(NewGameStateStruct.handCount[indexCurrentPlayer] == OldVersionOfGameStruct.handCount[indexCurrentPlayer], &atLeast1TestFailed);
    
    printf("supply Count = %d, expected = %d\n", NewGameStateStruct.supplyCount[estate], OldVersionOfGameStruct.supplyCount[estate]);
    asserttrue(NewGameStateStruct.supplyCount[estate] == OldVersionOfGameStruct.supplyCount[estate], &atLeast1TestFailed);
    
    /**** End Assert Results ****/
    
    
    // ----------- TEST 4: Test Sufficient Conditions to Buy Estate --------------
    //Invariable Conditions for this Test
    NewGameStateStruct = OldVersionOfGameStruct;
    NewGameStateStruct.numBuys = 1;
    NewGameStateStruct.supplyCount[estate] = 2;
    NewGameStateStruct.coins = 2;
    
    
    printf("--- TEST 4: Test Sufficient Conditions to Buy Estate\n");
    /**** Call Func ****/
    
    
    // copy the game state to compare (before + expected) with after
    OldVersionOfGameStruct = NewGameStateStruct;
    NewGameStateStruct.numBuys = 1;
    NewGameStateStruct.supplyCount[estate] = 2;
    NewGameStateStruct.coins = 2;
    
    resultBuyCard = buyCard(enumOfCardBeingBought, &NewGameStateStruct);
    printf("Buy Success Status = %d, expected = %d\n", resultBuyCard, 0);
    
    /**** Assert Results ****/
    
    asserttrue(resultBuyCard == 0 , &atLeast1TestFailed);
    
    printf("Coin Count = %d, expected = %d\n", NewGameStateStruct.coins, OldVersionOfGameStruct.coins - (getCost(estate)));
    asserttrue(NewGameStateStruct.coins == OldVersionOfGameStruct.coins - (getCost(estate)), &atLeast1TestFailed);
    
    printf("num Buys Count = %d, expected = %d\n", NewGameStateStruct.numBuys, OldVersionOfGameStruct.numBuys - 1);
    asserttrue(NewGameStateStruct.numBuys == OldVersionOfGameStruct.numBuys -1, &atLeast1TestFailed);
    
    printf("handCount Count = %d, expected = %d\n", NewGameStateStruct.handCount[indexCurrentPlayer], OldVersionOfGameStruct.handCount[indexCurrentPlayer] + 1);
    asserttrue(NewGameStateStruct.handCount[indexCurrentPlayer] == OldVersionOfGameStruct.handCount[indexCurrentPlayer] + 1, &atLeast1TestFailed);
    
    printf("supply Count = %d, expected = %d\n", NewGameStateStruct.supplyCount[estate], OldVersionOfGameStruct.supplyCount[estate] -1);
    asserttrue(NewGameStateStruct.supplyCount[estate] == OldVersionOfGameStruct.supplyCount[estate] - 1, &atLeast1TestFailed);
    
    /**** End Assert Results ****/
    
    
    
    
    
    
    if (atLeast1TestFailed == 0) {
        printf("All TESTS PASSED...\n");
    }else{
        printf("All TESTS DID NOT PASS X...\n");
    }
    return 0;
}

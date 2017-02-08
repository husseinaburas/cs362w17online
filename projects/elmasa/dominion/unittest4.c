/* -----------------------------------------------------------------------
 *  Method fullDeckCount
 *  --------------------
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
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
#define CARDORFUNCTIONTOTEST "fullDeckCount"
#define GAMEISOVER 1

int main() {

    /****************************** Main Setup ******************************/

    int constantSeedForRandomSeed = 1;
    int numPlayer = 2;
    struct gameState NewGameStateStruct, OldVersionOfGameStruct;

    memset(&NewGameStateStruct, 23, sizeof(struct gameState));      // clear the game state
    memset(&OldVersionOfGameStruct, 23, sizeof(struct gameState));  // clear the old game state (used to compare before after effect of method call)

    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards
    initializeGame(numPlayer, k, constantSeedForRandomSeed, &NewGameStateStruct);
    //memcpy(&NewGameStateStruct, &OldVersionOfGameStruct, sizeof(struct gameState)); // copy game state to have before - after comparision


    printf("----------------- Testing: %s ----------------\n", CARDORFUNCTIONTOTEST);

    // Did Any Test Fail Variable
    int atLeast1TestFailed = 0;


    //Invariable Conditions for all Tests
    int fillDeckAmount = 4;


    // ----------- TEST 1: Test count of copper in entire deck --------------
    //Invariable Conditions for this Test
    int indexCurrentPlayer = 0;

    printf("TEST 1: Test count of copper in entire deck \n");
    // copy the game state to compare (before + expected) with after
    OldVersionOfGameStruct = NewGameStateStruct;

    /**** Call Func ****/
    printf("Filling All Deck With All Copper, 0 Estate\n");

    memset(NewGameStateStruct.deck, 0, sizeof(int)*MAX_DECK); // Reset deck
    NewGameStateStruct.deckCount[indexCurrentPlayer] = fillDeckAmount;
    for (int i = 0; i < fillDeckAmount; i++) {
        NewGameStateStruct.deck[indexCurrentPlayer][i] = copper;
    }
    memset(NewGameStateStruct.hand, 0, sizeof(int)*MAX_HAND); // Reset deck
    NewGameStateStruct.handCount[indexCurrentPlayer] = fillDeckAmount;
    for (int i = 0; i < fillDeckAmount; i++) {
        NewGameStateStruct.hand[indexCurrentPlayer][i] = copper;
    }
    memset(NewGameStateStruct.discard, 0, sizeof(int)*MAX_DECK); // Reset deck
    NewGameStateStruct.discardCount[indexCurrentPlayer] = fillDeckAmount;
    for (int i = 0; i < fillDeckAmount; i++) {
        NewGameStateStruct.discard[indexCurrentPlayer][i] = copper;
    }


    // copy the game state to compare (before + expected) with after
    OldVersionOfGameStruct = NewGameStateStruct;
    printf("Copper Count = %d, expected = %d\n", fullDeckCount(indexCurrentPlayer, copper, &NewGameStateStruct), fillDeckAmount*3);

    /**** Assert Results ****/
    asserttrue(fullDeckCount(indexCurrentPlayer, copper, &NewGameStateStruct) == fillDeckAmount*3, &atLeast1TestFailed);

    printf("Estate Count = %d, expected = %d\n", fullDeckCount(indexCurrentPlayer, estate, &NewGameStateStruct), fillDeckAmount*0);
    asserttrue(fullDeckCount(indexCurrentPlayer, estate, &NewGameStateStruct) == fillDeckAmount*0, &atLeast1TestFailed);

    /**** End Assert Results ****/






    // ----------- TEST 2: Test count of half copper, half estate in entire deck --------------
    //Invariable Conditions for this Test

    printf("TEST 2: Test count of half copper, half estate in entire deck \n");
    // copy the game state to compare (before + expected) with after
    OldVersionOfGameStruct = NewGameStateStruct;

    /**** Call Func ****/
    printf("Filling All Deck With 6 Copper, 6 Estate\n");

    memset(NewGameStateStruct.deck, 0, sizeof(int)*MAX_DECK); // Reset deck
    NewGameStateStruct.deckCount[indexCurrentPlayer] = fillDeckAmount;
    for (int i = 0; i < fillDeckAmount; i++) {
        if (i % 2 == 0) {
            NewGameStateStruct.deck[indexCurrentPlayer][i] = estate;
        } else {
            NewGameStateStruct.deck[indexCurrentPlayer][i] = copper;
        }
    }
    memset(NewGameStateStruct.hand, 0, sizeof(int)*MAX_HAND); // Reset deck
    NewGameStateStruct.handCount[indexCurrentPlayer] = fillDeckAmount;
    for (int i = 0; i < fillDeckAmount; i++) {
        if (i % 2 == 0) {
            NewGameStateStruct.hand[indexCurrentPlayer][i] = estate;
        } else {
            NewGameStateStruct.hand[indexCurrentPlayer][i] = copper;
        }    }
    memset(NewGameStateStruct.discard, 0, sizeof(int)*MAX_DECK); // Reset deck
    NewGameStateStruct.discardCount[indexCurrentPlayer] = fillDeckAmount;
    for (int i = 0; i < fillDeckAmount; i++) {
        if (i % 2 == 0) {
            NewGameStateStruct.discard[indexCurrentPlayer][i] = estate;
        } else {
            NewGameStateStruct.discard[indexCurrentPlayer][i] = copper;
        }    }


    // copy the game state to compare (before + expected) with after
    OldVersionOfGameStruct = NewGameStateStruct;
    printf("Copper Count = %d, expected = %d\n", fullDeckCount(indexCurrentPlayer, copper, &NewGameStateStruct), (fillDeckAmount*3)/2);

    /**** Assert Results ****/
    asserttrue(fullDeckCount(indexCurrentPlayer, copper, &NewGameStateStruct) == (fillDeckAmount*3)/2, &atLeast1TestFailed);

    printf("Estate Count = %d, expected = %d\n", fullDeckCount(indexCurrentPlayer, estate, &NewGameStateStruct), (fillDeckAmount*3)/2);
    asserttrue(fullDeckCount(indexCurrentPlayer, estate, &NewGameStateStruct) == (fillDeckAmount*3)/2, &atLeast1TestFailed);

    /**** End Assert Results ****/
    
    
    // ----------- TEST 3: Test count of 2/3 copper only in discard & hand, 1/3 estate only in deck --------------
    //Invariable Conditions for this Test
    
    printf("TEST 3: Test count of 2/3 copper only in discard & hand, 1/3 estate only in deck \n");
    // copy the game state to compare (before + expected) with after
    OldVersionOfGameStruct = NewGameStateStruct;
    
    /**** Call Func ****/
    printf("Filling All Deck With 8 Copper only in discard & hand, 4 Estate only in deck\n");
    
    memset(NewGameStateStruct.deck, 0, sizeof(int)*MAX_DECK); // Reset deck
    NewGameStateStruct.deckCount[indexCurrentPlayer] = fillDeckAmount;
    for (int i = 0; i < fillDeckAmount; i++) {
        NewGameStateStruct.deck[indexCurrentPlayer][i] = estate;
    }
    memset(NewGameStateStruct.hand, 0, sizeof(int)*MAX_HAND); // Reset deck
    NewGameStateStruct.handCount[indexCurrentPlayer] = fillDeckAmount;
    for (int i = 0; i < fillDeckAmount; i++) {
        NewGameStateStruct.hand[indexCurrentPlayer][i] = copper;
    }
    memset(NewGameStateStruct.discard, 0, sizeof(int)*MAX_DECK); // Reset deck
    NewGameStateStruct.discardCount[indexCurrentPlayer] = fillDeckAmount;
    for (int i = 0; i < fillDeckAmount; i++) {
        NewGameStateStruct.discard[indexCurrentPlayer][i] = copper;
    }
    
    // copy the game state to compare (before + expected) with after
    OldVersionOfGameStruct = NewGameStateStruct;
    printf("Copper Count = %d, expected = %d\n", fullDeckCount(indexCurrentPlayer, copper, &NewGameStateStruct), (fillDeckAmount*2));
    
    /**** Assert Results ****/
    asserttrue(fullDeckCount(indexCurrentPlayer, copper, &NewGameStateStruct) == (fillDeckAmount*2), &atLeast1TestFailed);
    
    printf("Estate Count = %d, expected = %d\n", fullDeckCount(indexCurrentPlayer, estate, &NewGameStateStruct), (fillDeckAmount));
    asserttrue(fullDeckCount(indexCurrentPlayer, estate, &NewGameStateStruct) == (fillDeckAmount*1), &atLeast1TestFailed);
    
    /**** End Assert Results ****/




    if (atLeast1TestFailed == 0) {
        printf("All TESTS PASSED...\n");
    }else{
        printf("All TESTS DID NOT PASS X...\n");
    }
    return 0;
}

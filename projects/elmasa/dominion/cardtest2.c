/* -----------------------------------------------------------------------
 *  Card Village
 *  ------------
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
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
#define CARDORFUNCTIONTOTEST "Village"

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


    printf("----------------- Testing Card: %s ----------------\n", CARDORFUNCTIONTOTEST);

    // Did Any Test Fail Variable
    int atLeast1TestFailed = 0;


    //Invariable Conditions for all Tests
    int expectedNumCardDrawn = 1;
    int expectedNumCardDiscarded = 1;
    int indexOfCardBeingPlayed = 0;
    int expectedNumActionsIncrease = 2;

    // ----------- TEST 1: Test playVillage when deckCount is undepleted --------------
    //Invariable Conditions for this Test
    int indexCurrentPlayer = 0;

    printf("TEST 1: Test playVillage when deckCount is undepleted \n");
    // copy the game state to compare (before + expected) with after
    OldVersionOfGameStruct = NewGameStateStruct;

    /**** Call Func ****/
    printf("Testing Successful Return of 0 for calling Method\n");
    asserttrue(playVillage(&NewGameStateStruct, indexOfCardBeingPlayed) == 0, &atLeast1TestFailed);
    /**** End Call Func ****/
    /**** Assert Results ****/
    printf("hand count = %d, expected = %d\n", NewGameStateStruct.handCount[indexCurrentPlayer], OldVersionOfGameStruct.handCount[indexCurrentPlayer] + expectedNumCardDrawn - expectedNumCardDiscarded);
    asserttrue(NewGameStateStruct.handCount[indexCurrentPlayer] == OldVersionOfGameStruct.handCount[indexCurrentPlayer] + expectedNumCardDrawn - expectedNumCardDiscarded, &atLeast1TestFailed);

    printf("discard count = %d, expected = %d\n", NewGameStateStruct.discardCount[indexCurrentPlayer], OldVersionOfGameStruct.discardCount[indexCurrentPlayer] + expectedNumCardDiscarded);
    asserttrue(NewGameStateStruct.discardCount[indexCurrentPlayer] == OldVersionOfGameStruct.discardCount[indexCurrentPlayer] +  expectedNumCardDiscarded, &atLeast1TestFailed);

    printf("numActions count = %d, expected = %d\n", NewGameStateStruct.numActions, OldVersionOfGameStruct.numActions + expectedNumActionsIncrease);
    asserttrue(NewGameStateStruct.numActions == OldVersionOfGameStruct.numActions +  expectedNumActionsIncrease, &atLeast1TestFailed);
    /**** End Assert Results ****/




    // ----------- TEST 2: Test playVillage when deckCount is depleted --------------
    //Invariable Conditions for this Test
     indexCurrentPlayer = 0;
    NewGameStateStruct.deckCount[indexCurrentPlayer] = 0;

    printf("TEST 2: Test playVillage when deckCount is depleted \n");
    // copy the game state to compare (before + expected) with after
    OldVersionOfGameStruct = NewGameStateStruct;
    
    /**** Call Func ****/
    printf("Testing Successful Return of 0 for calling Method\n");
    asserttrue(playVillage(&NewGameStateStruct, indexOfCardBeingPlayed) == 0, &atLeast1TestFailed);
    /**** End Call Func ****/
    /**** Assert Results ****/
    printf("hand count = %d, expected = %d\n", NewGameStateStruct.handCount[indexCurrentPlayer], OldVersionOfGameStruct.handCount[indexCurrentPlayer] + expectedNumCardDrawn - expectedNumCardDiscarded);
    asserttrue(NewGameStateStruct.handCount[indexCurrentPlayer] == OldVersionOfGameStruct.handCount[indexCurrentPlayer] + expectedNumCardDrawn - expectedNumCardDiscarded, &atLeast1TestFailed);
    
    printf("discard count = %d, expected = %d\n", NewGameStateStruct.discardCount[indexCurrentPlayer], OldVersionOfGameStruct.discardCount[indexCurrentPlayer] + expectedNumCardDiscarded);
    asserttrue(NewGameStateStruct.discardCount[indexCurrentPlayer] == OldVersionOfGameStruct.discardCount[indexCurrentPlayer] +  expectedNumCardDiscarded, &atLeast1TestFailed);
    
    printf("numActions count = %d, expected = %d\n", NewGameStateStruct.numActions, OldVersionOfGameStruct.numActions + expectedNumActionsIncrease);
    asserttrue(NewGameStateStruct.numActions == OldVersionOfGameStruct.numActions +  expectedNumActionsIncrease, &atLeast1TestFailed);
    /**** End Assert Results ****/





    if (atLeast1TestFailed == 0) {
        printf("All TESTS PASSED...\n");
    }else{
        printf("All TESTS DID NOT PASS X...\n");
    }
    return 0;
}

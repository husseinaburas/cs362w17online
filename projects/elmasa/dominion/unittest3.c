/* -----------------------------------------------------------------------
 *  Method isGameOver
 *  -----------------
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
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
#define CARDORFUNCTIONTOTEST "isGameOver"
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

    // ----------- TEST 1: Test isGameOver with No Depleted Pile --------------
    //Invariable Conditions for this Test
    
    printf("TEST 1: Test isGameOver with No Depleted Pile \n");
    // copy the game state to compare (before + expected) with after
    OldVersionOfGameStruct = NewGameStateStruct;
    
    /**** Call Func ****/
    printf("Depleting Province Pile, Should make game over\n");
    // copy the game state to compare (before + expected) with after
    OldVersionOfGameStruct = NewGameStateStruct;
    int isGameOverResult = isGameOver(&NewGameStateStruct);
    printf("is Game Over? = %d, expected = %d\n", isGameOverResult, !GAMEISOVER);
    
    /**** Assert Results ****/
    asserttrue(isGameOverResult == !GAMEISOVER, &atLeast1TestFailed);
    
    printf("Province Supply Count = %d, expected = %d\n", NewGameStateStruct.supplyCount[province], OldVersionOfGameStruct.supplyCount[province]);
    asserttrue(NewGameStateStruct.supplyCount[province] == OldVersionOfGameStruct.supplyCount[province], &atLeast1TestFailed);
    
    printf("Card Index 0 Supply Count = %d, expected = %d\n", NewGameStateStruct.supplyCount[k[0]], OldVersionOfGameStruct.supplyCount[k[0]]);
    asserttrue(NewGameStateStruct.supplyCount[k[0]] == OldVersionOfGameStruct.supplyCount[k[0]], &atLeast1TestFailed);
    
    printf("Card Index 1 Supply Count = %d, expected = %d\n", NewGameStateStruct.supplyCount[k[1]], OldVersionOfGameStruct.supplyCount[k[1]]);
    asserttrue(NewGameStateStruct.supplyCount[k[1]] == OldVersionOfGameStruct.supplyCount[k[1]], &atLeast1TestFailed);
    
    printf("Card Index 9 Supply Count = %d, expected = %d\n", NewGameStateStruct.supplyCount[k[9]], OldVersionOfGameStruct.supplyCount[k[9]]);
    asserttrue(NewGameStateStruct.supplyCount[k[9]] == OldVersionOfGameStruct.supplyCount[k[9]], &atLeast1TestFailed);
    /**** End Assert Results ****/

    
    
    
    
    
    
    
    // ----------- TEST 2: Test isGameOver with Depleted Province Pile --------------
    //Invariable Conditions for this Test

    printf("TEST 2: Test isGameOver with Depleted Province Pile \n");
    // copy the game state to compare (before + expected) with after
    NewGameStateStruct = OldVersionOfGameStruct;

    /**** Call Func ****/
    printf("Depleting Province Pile, Should make game over\n");
    NewGameStateStruct.supplyCount[province] = 0;
    // copy the game state to compare (before + expected) with after
    OldVersionOfGameStruct = NewGameStateStruct;
    isGameOverResult = isGameOver(&NewGameStateStruct);
    printf("is Game Over? = %d, expected = %d\n", isGameOverResult, GAMEISOVER);

    /**** Assert Results ****/
    asserttrue(isGameOver(&NewGameStateStruct) == GAMEISOVER, &atLeast1TestFailed);

    printf("Province Supply Count = %d, expected = %d\n", NewGameStateStruct.supplyCount[province], OldVersionOfGameStruct.supplyCount[province]);
    asserttrue(NewGameStateStruct.supplyCount[province] == OldVersionOfGameStruct.supplyCount[province], &atLeast1TestFailed);
    
    printf("Card Index 0 Supply Count = %d, expected = %d\n", NewGameStateStruct.supplyCount[k[0]], OldVersionOfGameStruct.supplyCount[k[0]]);
    asserttrue(NewGameStateStruct.supplyCount[k[0]] == OldVersionOfGameStruct.supplyCount[k[0]], &atLeast1TestFailed);
    
    printf("Card Index 1 Supply Count = %d, expected = %d\n", NewGameStateStruct.supplyCount[k[1]], OldVersionOfGameStruct.supplyCount[k[1]]);
    asserttrue(NewGameStateStruct.supplyCount[k[1]] == OldVersionOfGameStruct.supplyCount[k[1]], &atLeast1TestFailed);
    
    printf("Card Index 9 Supply Count = %d, expected = %d\n", NewGameStateStruct.supplyCount[k[9]], OldVersionOfGameStruct.supplyCount[k[9]]);
    asserttrue(NewGameStateStruct.supplyCount[k[9]] == OldVersionOfGameStruct.supplyCount[k[9]], &atLeast1TestFailed);

    /**** End Assert Results ****/

    
    
    
    
    
    
    
    
    
    // ----------- TEST 3: Test isGameOver with Boundry Card Piles 0, 1, and 9 --------------
    //Invariable Conditions for this Test

    printf("TEST 2: Test isGameOver with Boundry Card Piles 0, 1, and 9\n");
    // copy the game state to compare (before + expected) with after
    NewGameStateStruct = OldVersionOfGameStruct;

    /**** Call Func ****/
    printf("Depleting 3 OTHER Piles, Should make game over\n");
    NewGameStateStruct.supplyCount[province] = 4;
    NewGameStateStruct.supplyCount[k[0]] = 0;
    NewGameStateStruct.supplyCount[k[1]] = 0;
    NewGameStateStruct.supplyCount[k[9]] = 0;

    // copy the game state to compare (before + expected) with after
    OldVersionOfGameStruct = NewGameStateStruct;
    isGameOverResult =isGameOver(&NewGameStateStruct);
    printf("is Game Over? = %d, expected = %d\n", isGameOverResult, GAMEISOVER);

    /**** Assert Results ****/
    asserttrue(isGameOverResult == GAMEISOVER, &atLeast1TestFailed);

    printf("Province Supply Count = %d, expected = %d\n", NewGameStateStruct.supplyCount[province], OldVersionOfGameStruct.supplyCount[province]);
    asserttrue(NewGameStateStruct.supplyCount[province] == OldVersionOfGameStruct.supplyCount[province], &atLeast1TestFailed);

    printf("Card Index 0 Supply Count = %d, expected = %d\n", NewGameStateStruct.supplyCount[k[0]], OldVersionOfGameStruct.supplyCount[k[0]]);
    asserttrue(NewGameStateStruct.supplyCount[k[0]] == OldVersionOfGameStruct.supplyCount[k[0]], &atLeast1TestFailed);

    printf("Card Index 1 Supply Count = %d, expected = %d\n", NewGameStateStruct.supplyCount[k[1]], OldVersionOfGameStruct.supplyCount[k[1]]);
    asserttrue(NewGameStateStruct.supplyCount[k[1]] == OldVersionOfGameStruct.supplyCount[k[1]], &atLeast1TestFailed);

    printf("Card Index 9 Supply Count = %d, expected = %d\n", NewGameStateStruct.supplyCount[k[9]], OldVersionOfGameStruct.supplyCount[k[9]]);
    asserttrue(NewGameStateStruct.supplyCount[k[9]] == OldVersionOfGameStruct.supplyCount[k[9]], &atLeast1TestFailed);

    /**** End Assert Results ****/






    if (atLeast1TestFailed == 0) {
        printf("All TESTS PASSED...\n");
    }else{
        printf("All TESTS DID NOT PASS X...\n");
    }
    return 0;
}

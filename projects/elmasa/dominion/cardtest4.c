/* -----------------------------------------------------------------------
 *  Card Adventurer
 *  ---------------
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
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
#define CARDORFUNCTIONTOTEST "Adventurer"

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
    int expectedNumCardAddedToHand = 2;

    // ----------- TEST 1: Test playAdventurer with Treasure Cards --------------
    //Invariable Conditions for this Test
    int indexCurrentPlayer = 0;

    printf("TEST 1: Test playAdventurer with Treasure Cards\n");
    // copy the game state to compare (before + expected) with after
    OldVersionOfGameStruct = NewGameStateStruct;


    // Capture number of Cards in Deck before first 2 Treasure Cards (will be discarded)
    int countTreasureCards = 0;
    int countCardsRevealedBefore2TreasureCardsRevealed = 0;

    for (int i = 0; i < NewGameStateStruct.deckCount[indexCurrentPlayer]; i++) {
        if (NewGameStateStruct.deck[indexCurrentPlayer][i] == copper || NewGameStateStruct.deck[indexCurrentPlayer][i] == silver || NewGameStateStruct.deck[indexCurrentPlayer][i] == gold ) {
            countTreasureCards++;
            if (countTreasureCards >= 2) {
                break;      // Break out of loop once found 2 Treasure cards
            }

        } else {
            countCardsRevealedBefore2TreasureCardsRevealed++;
        }
    }

    // Afterward: • deckCount -= countCardsRevealedBefore2TreasureCardsRevealed
    // Afterward: • discardCount += countCardsRevealedBefore2TreasureCardsRevealed
    // Afterward: • handCount += 2

    /**** Call Func ****/
    printf("Testing Successful Return of 0 for calling Method\n");
    int resultPlayAdventurer = playAdventurer(&NewGameStateStruct);
    asserttrue(resultPlayAdventurer == 0, &atLeast1TestFailed);
    /**** End Call Func ****/
    /**** Assert Results ****/
    printf("hand count = %d, expected = %d\n", NewGameStateStruct.handCount[indexCurrentPlayer], OldVersionOfGameStruct.handCount[indexCurrentPlayer] + expectedNumCardAddedToHand);
    asserttrue(NewGameStateStruct.handCount[indexCurrentPlayer] == OldVersionOfGameStruct.handCount[indexCurrentPlayer] + expectedNumCardAddedToHand, &atLeast1TestFailed);

    printf("discard count = %d, expected = %d\n", NewGameStateStruct.discardCount[indexCurrentPlayer], OldVersionOfGameStruct.discardCount[indexCurrentPlayer] + countCardsRevealedBefore2TreasureCardsRevealed);
    asserttrue(NewGameStateStruct.discardCount[indexCurrentPlayer] == OldVersionOfGameStruct.discardCount[indexCurrentPlayer] - countCardsRevealedBefore2TreasureCardsRevealed, &atLeast1TestFailed);

    printf("deck count = %d, expected = %d\n", NewGameStateStruct.deckCount[indexCurrentPlayer], OldVersionOfGameStruct.deckCount[indexCurrentPlayer] + countCardsRevealedBefore2TreasureCardsRevealed);
    asserttrue(NewGameStateStruct.deckCount[indexCurrentPlayer] == OldVersionOfGameStruct.deckCount[indexCurrentPlayer] -  countCardsRevealedBefore2TreasureCardsRevealed, &atLeast1TestFailed);
    /**** End Assert Results ****/


    // ----------- TEST 2: Test playAdventurer with No Treasure Cards in Deck --------------
    //Invariable Conditions for this Test
    indexCurrentPlayer = 0;
    
    printf("TEST 2: Test playAdventurer with No Treasure Cards in Deck \n");
    // copy the game state to compare (before + expected) with after
    NewGameStateStruct = OldVersionOfGameStruct;
    
    
    // Capture number of Cards in Deck before first 2 Treasure Cards (will be discarded)
    countTreasureCards = 0;
    countCardsRevealedBefore2TreasureCardsRevealed = 0;
    
    
    for (int i = 0; i < MAX_HAND; i++)
    {
        NewGameStateStruct.deck[indexCurrentPlayer][i] = estate;
    }
    
    for (int i = 0; i < NewGameStateStruct.deckCount[indexCurrentPlayer]; i++) {
        if (NewGameStateStruct.deck[indexCurrentPlayer][i] == copper || NewGameStateStruct.deck[indexCurrentPlayer][i] == silver || NewGameStateStruct.deck[indexCurrentPlayer][i] == gold ) {
            countTreasureCards++;
            if (countTreasureCards >= 2) {
                break;      // Break out of loop once found 2 Treasure cards
            }
            
        } else {
            countCardsRevealedBefore2TreasureCardsRevealed++;
        }
    }
    
    // Afterward: • deckCount -= countCardsRevealedBefore2TreasureCardsRevealed
    // Afterward: • discardCount += countCardsRevealedBefore2TreasureCardsRevealed
    // Afterward: • handCount += 2
    
    /**** Call Func ****/
    printf("Testing Successful Return of 0 for calling Method\n");
    resultPlayAdventurer = playAdventurer(&NewGameStateStruct);
    asserttrue(resultPlayAdventurer == 0, &atLeast1TestFailed);
    /**** End Call Func ****/
    /**** Assert Results ****/
    printf("hand count = %d, expected = %d\n", NewGameStateStruct.handCount[indexCurrentPlayer], OldVersionOfGameStruct.handCount[indexCurrentPlayer] + expectedNumCardAddedToHand);
    asserttrue(NewGameStateStruct.handCount[indexCurrentPlayer] == OldVersionOfGameStruct.handCount[indexCurrentPlayer] + expectedNumCardAddedToHand, &atLeast1TestFailed);
    
    printf("discard count = %d, expected = %d\n", NewGameStateStruct.discardCount[indexCurrentPlayer], OldVersionOfGameStruct.discardCount[indexCurrentPlayer] + countCardsRevealedBefore2TreasureCardsRevealed);
    asserttrue(NewGameStateStruct.discardCount[indexCurrentPlayer] == OldVersionOfGameStruct.discardCount[indexCurrentPlayer] - countCardsRevealedBefore2TreasureCardsRevealed, &atLeast1TestFailed);
    
    printf("deck count = %d, expected = %d\n", NewGameStateStruct.deckCount[indexCurrentPlayer], OldVersionOfGameStruct.deckCount[indexCurrentPlayer] + countCardsRevealedBefore2TreasureCardsRevealed);
    asserttrue(NewGameStateStruct.deckCount[indexCurrentPlayer] == OldVersionOfGameStruct.deckCount[indexCurrentPlayer] -  countCardsRevealedBefore2TreasureCardsRevealed, &atLeast1TestFailed);
    /**** End Assert Results ****/



    if (atLeast1TestFailed == 0) {
        printf("All TESTS PASSED...\n");
    }else{
        printf("All TESTS DID NOT PASS X...\n");
    }
    return 0;
}

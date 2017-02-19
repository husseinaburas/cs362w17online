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
#include <stdlib.h>     // needed for srand and rand
#include "asserttrue.h"
#include "rngs.h"


// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
#define CARDORFUNCTIONTOTEST "Village"

int main(int argc, char** argv) {
    
    
    int passedSeed = atoi(argv[1]); // first char is '/'
    srand(passedSeed); // seed the random number generator with the passed int that is passed from the command line when running the program
    
    /****************************** Main Setup ******************************/
    struct gameState NewGameStateStruct, OldVersionOfGameStruct;
    
    memset(&NewGameStateStruct, 23, sizeof(struct gameState));      // clear the game state
    memset(&OldVersionOfGameStruct, 23, sizeof(struct gameState));  // clear the old game state (used to compare before after effect of method call)
    
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    
    
    
    printf("----------------- Testing Card: %s ----------------\n", CARDORFUNCTIONTOTEST);
    
    // Did Any Test Fail Variable
    int atLeast1TestFailed = 0;
    
    
    //Invariable Conditions for all Tests
    int expectedNumCardDrawn = 1;
    int expectedNumCardDiscarded = 1;
    int indexOfCardBeingPlayed = 0;
    int expectedNumActionsIncrease = 2;
    int indexCurrentPlayer = 0;
    
    int numRandomTestRuns = 5000;                           // Number of Random Tests to Run
    
    for (int i = 0; i < numRandomTestRuns; i++)
    {
        
        //Randomized Variable Conditions
        int numPlayer = 2 + (rand()%2);
        
        
        memset(&NewGameStateStruct, 23, sizeof(struct gameState));      // clear the game state
        memset(&OldVersionOfGameStruct, 23, sizeof(struct gameState));  // clear the old game state (used to compare before after effect of method call)
        
        // initialize a game state and player cards
        initializeGame(numPlayer, k, passedSeed, &NewGameStateStruct);
        //memcpy(&NewGameStateStruct, &OldVersionOfGameStruct, sizeof(struct gameState)); // copy game state to have before - after comparision
        
        
        
        NewGameStateStruct.hand[indexCurrentPlayer][0] = village; //set the first card in player's hand to village to guarantee he has village to use
        
        
        int currentHandCount = 1+(rand()%4); // choose a random number of cards in current hand from 1 to 5
        // Discard the difference between the former handcount (5) and the randomized handcount
        for (int currentCardInHand=5; currentCardInHand > currentHandCount; currentCardInHand--) {
            NewGameStateStruct.discard[indexCurrentPlayer][NewGameStateStruct.discardCount[indexCurrentPlayer]] = NewGameStateStruct.hand[indexCurrentPlayer][currentCardInHand];       // copy the current card in hand to discard pile
            NewGameStateStruct.discardCount[indexCurrentPlayer]++;                  // increment discard count
            NewGameStateStruct.hand[indexCurrentPlayer][currentCardInHand] = -1;    // reset the removed card position to -1
            NewGameStateStruct.handCount[indexCurrentPlayer] -= 1;                  // decrement hand count
        }
        
        if (rand()%5 == 0) {                                                        // Fill all cards in Deck with non Treasure cards 20% of the time
            for (int i = 0; i < MAX_HAND; i++)
            {
                NewGameStateStruct.deck[indexCurrentPlayer][i] = estate;
            }
        }
        
        // ----------- TEST 1: Test playVillage when deckCount is undepleted --------------
        
        
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
        
    }
    
    
    
    if (atLeast1TestFailed == 0) {
        printf("All TESTS PASSED...\n");
    }else{
        printf("All TESTS DID NOT PASS X...\n");
    }
    return 0;
}

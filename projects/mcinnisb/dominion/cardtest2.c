#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "test_help.h"

#define MAX_HAND 500

/*unit test for adventurer card implementation
 *preconditions: handCount[player] = H
 *postconditions: handCount[player] = H + 2
 */
void testAdventurerCard(int *temphand, int cardDrawn, int currentPlayer, struct gameState *state)
{
    if (assertIsValid("test adventurer card", currentPlayer, state))
    {
        int handCt = state->handCount[currentPlayer];
        adventurerCard(temphand, cardDrawn, currentPlayer, state);
        assertIsEqual("test adventurer card: hand", handCt + 2, state->handCount[currentPlayer]);
    }
}

int main()
{
    int temphand[MAX_HAND];
    int cardDrawn;
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    printf ("Testing adventurer card: \n");

    initializeGame(2, k, 2, &G);
    testAdventurerCard(temphand, cardDrawn, 1, &G);
    return 0;
} 

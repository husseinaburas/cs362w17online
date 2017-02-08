#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "test_help.h"

/*unit test for smithy card implementation
 *preconditions: handCount[player} = H;
		deckCount[player] = D
 *postconditions: handCount[player] = H + 2 (draw 3, discard 1);
		deckCount[player] = D + 3
*/
void testSmithyCard(int currentPlayer, int handPos, struct gameState *state)
{
    if (assertIsValid("test smithy card", currentPlayer, state))
    {
    	int handCt = state->handCount[currentPlayer];
    	int deckCt = state->deckCount[currentPlayer];
	smithyCard(currentPlayer, handPos, state);
	assertIsEqual("test smithy card: hand", handCt + 2, state->handCount[currentPlayer]);
	assertIsEqual("test smithy card: deck", deckCt - 3, state->deckCount[currentPlayer]);
    }
}

int main()
{
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    printf ("Testing smithy card: \n");

    initializeGame(2, k, 2, &G);
    testSmithyCard(1, 0, &G);
    return 0;
}

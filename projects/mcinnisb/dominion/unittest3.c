#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "test_help.h"

/*unit test for function: discardCard()
preconditions: 	playedCardCount = P;
		handCount[currentPlayer] = C
postconditions:	playedCardCount = P + 1 (if trashFlag < 1);
		handCount[currentPlayer] = C - 1
*/
void testDiscardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
{
    if (assertIsValid("test discardCard", currentPlayer, state))
    {
    	int playedCt = state->playedCardCount;
    	int handCt = state->handCount[currentPlayer];
    	discardCard(handPos, currentPlayer, state, trashFlag);
        if (trashFlag >= 1)
	    assertIsEqual("test discardCard: trash", playedCt, state->playedCardCount);
	else
	    assertIsEqual("test discardCard: not trash", playedCt + 1, state->playedCardCount);
	assertIsEqual("test discardCard: handCt", handCt - 1, state->handCount[currentPlayer]);
    }
}

int main()
{
    printf("Testing discardCard().\n");
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    initializeGame(2, k, 2, &G);
    testDiscardCard(0, 0, &G, 0);
    testDiscardCard(1, 0, &G, 1);
    return 0;
}

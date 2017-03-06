#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "test_help.h"

/*unit test for mine card implementation
 * preconditions: numActions = N;
 * 		 playedCardCount = P;
 * 		 coins = C
 * postconditions:numActions = N + 1;
 * 		playedCardCount = P + 1;
 * 		coins = C + 2 (if choice1) 
 */
void testMinionCard(int choice1, int choice2, int currentPlayer, int handPos, struct gameState *state)
{
    state->whoseTurn = currentPlayer;
    if (assertIsValid("test minion card: player", currentPlayer, state))
    {
	int numActCt = state->numActions;
	int coins = state->coins;
	cardEffect(minion, choice1, choice2, 0, state, handPos, 0);
	assertIsEqual("test minion card: numActions", numActCt + 1, state->numActions);
	if (choice1)
	    assertIsEqual("test minion card: coins", coins + 2, state->coins);
    }
}

int main()
{
    int i;
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
    printf("Testing minion card\n");
    initializeGame(2, k, 2, &G);
    testMinionCard(1, 0, 0, 0, &G);
    testMinionCard(1, 1, 0, 0, &G); 
    return 0;
}

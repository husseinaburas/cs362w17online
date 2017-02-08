#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "test_help.h"


//helper function for testUpdateCoins
int countTreasure(int player, struct gameState *state)
{
    int coinCount = 0, i;
    for (i = 0; i < state->handCount[player]; i++)
    {
	if (state->hand[player][i] == copper)
	    coinCount += 1;
	else if (state->hand[player][i] == silver)
	    coinCount += 2;
	else if (state->hand[player][i] == gold)
	    coinCount += 3;
    }
    return coinCount;
}


/*unit test for function: updateCoins()
preconditions: coins = C
postconditions: coins = C + newCoins + bonus
*/
void testUpdateCoins(int player, struct gameState *state, int bonus)
{
    //first check that player index valid
    if (assertIsValid("testIndex", player, state))
    {
        int coinCount = countTreasure(player, state);
        updateCoins(player, state, bonus);
	if (bonus)
            assertIsEqual("test updateCoins: coins", state->coins, coinCount + bonus);
	else
	    assertIsEqual("test updateCoins: coins", state->coins, coinCount);
    }
}

int main()
{
    printf("Testing updateCoins().\n");
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    initializeGame(2, k, 2, &G);

    testUpdateCoins(1, &G, 0);
    testUpdateCoins(1, &G, 1);

    return 0;
}

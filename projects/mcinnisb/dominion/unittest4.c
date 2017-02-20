#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "test_help.h"

/*unit test for function: drawCard()
 *preconditions: deckCount[player] = D;
 *		handCount[player] = H
 *postconditions: deckCount[player] = D - 1;
 *		handCount[player] = H + 1 
 */
void testDrawCard(int player, struct gameState *state){
    if (assertIsValid("test drawCard", player, state))
    {
    	int deckCt = state->deckCount[player];
	int handCt = state->handCount[player];
	int result = drawCard(player, state);
	if (result >= 0)
	{
	    assertIsEqual("test drawCard: deck", deckCt - 1, state->deckCount[player]);
	    assertIsEqual("test drawCard: hand", handCt + 1, state->handCount[player]);
        }
	else
	    printf("deckCount = 0.\n");
    }
}

int main()
{
    int i, deckSize;
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    printf ("testing drawCard():\n");

    initializeGame(2, k, 2, &G);
    //get deck size of player 1
    deckSize = G.deckCount[1];
    for (i = 0; i <= deckSize; i++)
    {
        testDrawCard(1, &G);
    }
    return 0;
}

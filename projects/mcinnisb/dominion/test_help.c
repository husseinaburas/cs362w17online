#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "test_help.h"

void assertIsEqual(char *msg, int a, int b) //change to use void pointers
{
    if (a == b)
	printf("TEST CASE %s PASSED.\n", msg);
    else
	printf("TEST CASE %s FAILED.\n", msg);
}

int assertIsValid(char *msg, int player, struct gameState *state)
{
    if (player >= state->numPlayers)
    {
	printf("TEST CASE %s FAILED: Invalid Index.\n", msg);
	return 0;
    }
    else
    {
	printf("TEST CASE %s PASSED.\n", msg);
	return 1;
    }
}

void testCounts(int player, struct gameState *state, int handCtpre, int deckCtpre, int playedCtpre, int handCt, int deckCt, int playedCt)
{
    if (assertIsValid("test card count", player, state))
    {
	assertIsEqual("testing hand count", (handCtpre + handCt), state->handCount[player]);
    	assertIsEqual("testing deck count", (deckCtpre + deckCt), state->deckCount[player]);
    	assertIsEqual("testing played card count", (playedCtpre + playedCt), state->playedCardCount);
	printf("Current player: %d, hand count after: %d (expected %d), deck count after: %d (expected %d), played card count after: %d (expected %d).\n", player, state->handCount[player], (handCtpre + handCt), state->deckCount[player], (deckCtpre + deckCt), state->playedCardCount, (playedCtpre + playedCt));
    }
}

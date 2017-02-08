#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "test_help.h"

/*unit test for function: gainCard()
preconditions: deckCount[player] = C; 
		handCount[player] = H;
		supplyCount[supplyPos] = S;
		discardCount[player] = D
postconditions: deckCount[player] = C + 1 (if toFlag == 1); 
		handCount[player] = H + 1;
		supplyCOunt[supplyPos] = S + 1 (if toFlag == 2);
		discardCount[player] = D + 1 (if toFlag != 2 || 1)
*/
void testGainCard(struct gameState *state, int player){
    if (assertIsValid("testValid", player, state))
    {
	int deckCt = state->deckCount[player];
	int handCt = state->handCount[player];
	int discardCt = state->discardCount[player];
	int supplyCt = state->supplyCount[curse];
	
	gainCard(curse, state, 0, player); //gain curse card to discard
	assertIsEqual("test gainCard: discard", discardCt+1, state->discardCount[player]); 
	
	gainCard(curse, state, 1, player); //gain curse card to deck
	assertIsEqual("test gainCard: deck", deckCt+1, state->deckCount[player]);
	
	gainCard(curse, state, 2, player); //gain curse card to hand
	assertIsEqual("test gainCard: hand", handCt+1, state->handCount[player]);

	assertIsEqual("test discard: supplyCount", supplyCt - 3, state->supplyCount[curse]);
    }
}

int main()
{
    printf("Testing gainCard().\n");
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    initializeGame(2, k, 2, &G);
    testGainCard(&G, 1);
    return 0;
}

#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "test_help.h"

/*unit test for baron card implementation
 * preconditions: numBuys = N;
 * postconditions: numBuys = N + 1;
 */
void testBaronCard(int currentPlayer, int choice1, int estateFlag, struct gameState *state)
{
    if(assertIsValid("test baron card", currentPlayer, state))
    {
    	int numbuysCt = state->numBuys;
	int handCt = state->handCount[currentPlayer];
	int coinCt = state->coins;
	int estateSupplyCount = supplyCount(estate, state);
    	playBaron(currentPlayer, state, choice1);
	assertIsEqual("test baron card: numBuys", numbuysCt + 1, state->numBuys);
    	if (choice1 > 0)
	{
	    if (estateFlag == 1)
	    {
    	        assertIsEqual("test baron card: handCount", handCt - 1, state->handCount[currentPlayer]);
            	assertIsEqual("test baron card: coins", coinCt + 4, state->coins);
	    }
	    else //estateFlag==0
	    {
		if (estateSupplyCount)
		{
		    assertIsEqual("test baron card: supplyCount[estate]", estateSupplyCount - 1, supplyCount(estate, state));
		}
	    }
	}
	else //choice1==0
	{
	    assertIsEqual("test baron card: supplyCount[estate]", estateSupplyCount - 1, supplyCount(estate, state));
        }
    }
}

int main()
{
    int i, estateFlag=0;
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    printf ("Testing baron card:\n");

    initializeGame(2, k, 2, &G);
    G.handCount[0] = G.handCount[1] = 3;
    //search for estate card
    for (i=0; i < G.handCount[0]; i++)
    {
	G.hand[0][i] = estate;
	G.hand[1][i] = estate;
	/*if (G.hand[0][i] == estate)
	{
	    estateFlag = 1;
	    break;  
	}*/
    }
    /*testBaronCard(1, 0, estateFlag, &G);
    for (i=0; i < G.handCount[0]; i++)
    {
	if (G.hand[0][i] == estate)
	{
	    estateFlag = 1;
	    break;  
	}
    }*/
    testBaronCard(0, 1, 1/*stateFlag*/, &G); 
    testBaronCard(1, 1, 1, &G); 
    return 0;
}

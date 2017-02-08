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
	int estateSupplyCount = supplyCount(estate, state);
	printf("Estate supply count before: %d\n", estateSupplyCount);
    	baronCard(currentPlayer, choice1, state);
	assertIsEqual("test baron card: numBuys", numbuysCt + 1, state->numBuys);
    	if (choice1 > 0)
	{
	    if (estateFlag == 1)
    	        assertIsEqual("test baron card: handCount", handCt - 1, state->handCount[currentPlayer]);
            else //estateFlag==0
	    {
		if (estateSupplyCount)
		{
		    printf("Estate supply count after: %d\n", supplyCount(estate, state));
		    assertIsEqual("test baron card: supplyCount[estate]", estateSupplyCount - 1, supplyCount(estate, state));
		}
	    }
	}
	else //choice1==0
	{
	    printf("Estate supply count after: %d\n", supplyCount(estate, state));
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
    //search for estate card
    for (i=0; i < G.handCount[0]; i++)
    {
	if (G.hand[0][i] == estate)
	{
	    estateFlag = 1;
	    break;  
	}
    }
    testBaronCard(1, 0, estateFlag, &G);
    for (i=0; i < G.handCount[0]; i++)
    {
	if (G.hand[0][i] == estate)
	{
	    estateFlag = 1;
	    break;  
	}
    }
    testBaronCard(1, 1, estateFlag, &G); 
    testBaronCard(1, 1, 0, &G); 
    return 0;
}

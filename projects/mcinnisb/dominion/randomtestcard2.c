#include "dominion.h"
#include "dominion_helpers.h"
#include "test_help.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

//random tester for baron card
/****************************************************************
 * unit test for baron card					*
 ***************************************************************/
void testBaronCard(int currentPlayer, int choice1, int estateFlag, struct gameState *state)
{
    if(assertIsValid("test baron card", currentPlayer, state))
    {
    	printf("Player: %d, choice: %d, ", currentPlayer, choice1);
	int numbuysCt = state->numBuys;
	int handCt = state->handCount[currentPlayer];
	int estateSupplyCount = supplyCount(estate, state);
	int coinAmt = state->coins;
	int discardCt = state->discardCount[currentPlayer];
	printf("estate supply count before: %d, hand ct: %d, coins: %d\n", estateSupplyCount, handCt, coinAmt);
    	baronCard(currentPlayer, choice1, state);
	assertIsEqual("test baron card: numBuys", numbuysCt + 1, state->numBuys);
    	if (choice1 > 0)
	{
	    if (estateFlag == 1)
	    {
    	        assertIsEqual("test baron card: handCount", handCt - 1, state->handCount[currentPlayer]);
            	assertIsEqual("test baron card: coins", coinAmt + 4, state->coins);
	    }
	    else //estateFlag==0
	    {
		if (estateSupplyCount)
		{
		    printf("Estate supply count after: %d\n", supplyCount(estate, state));
		    assertIsEqual("test baron card: supplyCount[estate]", estateSupplyCount - 1, supplyCount(estate, state));
		    assertIsEqual("test baron card: discardCount", discardCt + 1, state->discardCount[currentPlayer]);
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

int main(int argc, char** argv)
{
    srand(atoi(argv[1]));
    int i ,j, player, choice, estateFlag;
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    printf("Starting Baron card random test.\n");
    initializeGame(MAX_PLAYERS, k, atoi(argv[1]), &G);
    //initialize each player to have handCount = MAX_HAND
    //and deckCount = MAX_DECK
    for (i = 0; i < G.numPlayers; i++)
    {
	G.handCount[i] = MAX_HAND;
	G.deckCount[i] = MAX_DECK;
	for (j = 0; j < MAX_HAND; j++)
	{
	    G.hand[i][j] = smithy;
	}
    }
    struct timeval start, end;
    float total;
    gettimeofday(&start, 0);
    for (i = 0; i < 1000; i++)
    {
	if (i ==500)
	    G.supplyCount[province] == 0; 	//trigger isGameOver
	estateFlag = 0;
	printf("\nTEST CASE %d:", i);
	//choose random player
	player = rand()%MAX_PLAYERS;
	//choose random choice 1 or 0
	choice = rand()%2;
	for (j = 0; j < G.handCount[player]; j++)
	{
	    if (G.hand[player][j] == estate)
	    {
		estateFlag = 1;
	    }
	}
	testBaronCard(player, choice, estateFlag, &G);
	//add estate card to hand every 5th test case
	if (G.handCount[player] > 0 && i%5 == 0)
	{
	    G.hand[player][G.handCount[player]-1] = estate;
	}
    }
    gettimeofday(&end, 0);
    //for http://stackoverflow.com/questions/10192903/time-in-milliseconds
    total = (end.tv_sec - start.tv_sec) * 1000.0f + (end.tv_usec - start.tv_usec)/1000.0f;
    printf("Total time: %f ms.\n", total);
    return 0;
}


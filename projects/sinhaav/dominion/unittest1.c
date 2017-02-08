/* unit test for  updateCoins() */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

void assertTrue(int firstValue, int secondValue, char* message);

int main()
{
	struct gameState *myState = newGame();
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	initializeGame(2, k, 2, myState);
	
	//player 0
	int i = 0;
	int copperCount = 0;
	for (i = 0; i<myState->handCount[0]; i++)
	{
		if(myState->hand[0][i] == 4) copperCount++;
		
	}
	int result = updateCoins(0, myState, 0); 
	assertTrue(result, 0, "coins updated for player 0, no error from updateCoins().");
	assertTrue(myState->coins, copperCount,"update coins for player 0, correct number count.");
	initializeGame(2, k, 2, myState);
	
	//player 1
	i = 0;
	copperCount = 0;
	for (i = 0; i < myState->handCount[1]; i++)
	{
		if(myState->hand[1][i] == 4) copperCount++;
	}
	result = updateCoins(1, myState, 0);
	assertTrue(result, 0, "coins updated for player 1, no error from updateCoins().");
	assertTrue(myState->coins, copperCount,"update coins for player 1, correct number count.");
	initializeGame(2, k, 2, myState);
	
	//Player -1
	result = updateCoins(1, myState, 0);
	assertTrue(result, -1, "coins updated for player 1, no error from updateCoins().");
	initializeGame(2, k, 2, myState);
	
	//Player 4
	result = updateCoins(4, myState, 0);
	assertTrue(result, -1, "coins updated for player 1, no error from updateCoins().");
	initializeGame(2, k, 2, myState);
	
	/*testing bonus parameter of updateCoins()*/
	
	//bonus = 1
	i = 0;
	copperCount = 0;
	for ( i = 0; i < myState->handCount[0]; i++)
	{
		if(myState->hand[0][i] == 4) copperCount++;
	}
	result = updateCoins(0, myState, 1);
	assertTrue(result, 0, "Updated coins with bonus = 1. No error given by updateCoins().");
	assertTrue(myState->coins, copperCount+1, "coins updated with bonus 1, treasure count +1 bonus");
	initializeGame(2, k, 2, myState);
	
	//bonus = -1
	i = 0;
	copperCount = 0;
	for (i = 0; i < myState->handCount[0]; i++)
	{
		if(myState->hand[0][i] == 4) copperCount++;
	}
	result = updateCoins(0, myState, -1);
	assertTrue(result, 0, "Updated coins with bonus = -1. No error given by updateCoins().");
	assertTrue(myState->coins, copperCount,"coins updated with bonus 1,no change should happen if bonus is less than 0.");
	initializeGame(2, k, 2, myState);
	
	//bonus = 99999
	i = 0;
	copperCount = 0;
	for (i = 0; i < myState->handCount[0]; i++)
	{
		if(myState->hand[0][i] == 4) copperCount++;	
	}
	result = updateCoins(0, myState, 99999);
	assertTrue(result, -1, "Updated coins with bonus = 9999. No error given by updateCoins().");
	assertTrue(myState->coins, copperCount, "Coins update with a bonus = 9999, no change should happen if bonus is greater than sum of all the treasure.");
	initializeGame(2, k , 2, myState);
	
	/*Testing the state parameter of updateCoins() */
	
	//hand count for player =0. updateCoins() yields 0.
	myState->hand[0][0] = -1;
	myState->hand[0][1] = -1;
	myState->hand[0][2] = -1;
	myState->hand[0][3] = -1;
	myState->hand[0][4] = -1;
	myState->handCount[0] = 0;
	result = updateCoins(0, myState, 0);
	assertTrue(result, 0, "Coins updated with no cards in hand, this is not an error from updateCoins().");
	assertTrue(myState->coins, 0, "update coins with no cards in hand thus coins = 0.");
	initializeGame(2, k, 2, myState);
	
	//Player has cards just not treasure cards.
	myState->hand[0][0] = estate;
	myState->hand[0][1] = estate;
	myState->hand[0][2] = estate;
	myState->hand[0][3] = estate;
	myState->hand[0][4] = estate;
	result = updateCoins(0, myState, 0);
	assertTrue(result, 0, "Coins updated with no treasure cards, no error from updateCoins().");
	assertTrue(myState->coins, 0, "update coins with no treasure cards meaning coins = 0.");
	initializeGame(2, k , 2, myState);
	
	//player has 3 gold which equals 9.
	myState->hand[0][0] = gold;
	myState->hand[0][1] = gold;
	myState->hand[0][2] = gold;
	myState->hand[0][3] = estate;
	myState->hand[0][4] = estate;
	result = updateCoins(0, myState, 0);
	assertTrue(result, 0, "Coins updated with 3 gold cards, no error from updateCoins().");
	assertTrue(myState->coins, 9, "update coins with 3 gold cards meaning coins = 9.");
	initializeGame(2, k , 2, myState); 
	
	//player has 2 silver which equals 4
	myState->hand[0][0] = silver;
	myState->hand[0][1] = estate;
	myState->hand[0][2] = silver;
	myState->hand[0][3] = estate;
	myState->hand[0][4] = estate;
	result = updateCoins(0, myState, 0);
	assertTrue(result, 0, "Coins updated with 2 silver cards, no error from updateCoins().");
	assertTrue(myState->coins, 4, "update coins with 2 silver cards meaning coins = 4.");
	initializeGame(2, k , 2, myState); 
	
	//player has 3 copper which equals 3
	myState->hand[0][0] = copper;
	myState->hand[0][1] = copper;
	myState->hand[0][2] = copper;
	myState->hand[0][3] = estate;
	myState->hand[0][4] = estate;
	result = updateCoins(0, myState, 0);
	assertTrue(result, 0, "Coins updated with 3 copper cards, no error from updateCoins().");
	assertTrue(myState->coins, 3, "update coins with 3 copper cards meaning coins = 3.");
	initializeGame(2, k , 2, myState); 	
	
	
	//player has 1 gold, 1 silver, 1 copper and 1 bonus which equals 7
	myState->hand[0][0] = gold;
	myState->hand[0][1] = silver;
	myState->hand[0][2] = copper;
	myState->hand[0][3] = estate;
	myState->hand[0][4] = estate;
	result = updateCoins(0, myState, 1);
	assertTrue(result, 0, "Coins updated with 1 gold, 1 silver, 1 copper, and 1 bonus card, no error from updateCoins().");
	assertTrue(myState->coins, 7, "update coins with 1 gold, 1 silver, 1 copper, and 1 bonus card meaning coins = 7.");
	initializeGame(2, k , 2, myState); 	
	
	return 0;
	
}

/*assert function to keep program from crashing while also keeping the program updated with info */

void assertTrue(int firstValue, int secondValue, char* message)
{
	if(firstValue == secondValue)
	{
		printf("Test passed: %s\n", message);
	}
	else
	{
		printf("Test failed: %s Correct Value: %i; Expected Value: %i\n", message, firstValue, secondValue);	
	}

}
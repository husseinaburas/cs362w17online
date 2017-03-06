//Unit test for updateCoins() method in dominion.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int customAssert(int condition, char *errorMsg)
{
	if (condition)
	{
		return 0;
	}
	else
	{
		printf("Error: %s\n", errorMsg);
		return 1;	
	}
}


int main()
{
	int numBugs = 0;	//Stores total number of bugs encountered by unit test
	struct gameState G;
	struct gameState copy;
	int bonus;
	int returnValue;


	printf ("\n----------Starting Unit Test 1----------\n");

	//Testing for two players 
	G.numPlayers = 2;

	//Player 1 will have 1 treasure card - copper
	//Player 2 is just a dummy hand used to see if updateCoins() unexpectedly changes/uses any cards in it
	G.handCount[0] = 2;
	G.hand[0][0] = copper;
	G.hand[0][1] = adventurer;

	G.handCount[1] = 4;
	G.hand[1][0] = copper;
	G.hand[1][1] = silver;
	G.hand[1][2] = gold;
	G.hand[1][3] = adventurer;


	//Make copy prior to calling function
	memcpy(&copy, &G, sizeof(struct gameState));	
	
	//Call updateCoins() for player 0
	bonus = 0;
	returnValue = updateCoins(0, &G, bonus);

	numBugs += customAssert( (returnValue == 0), "Call to updateCoins() failed." );

	//Testing if any members in the struct were incorrectly changed
	//Only coins should be changed by updateCoins(), so that was updated to the latest value
	//Also, other player's cards should not be modified
	copy.coins = G.coins;
	returnValue = memcmp(&copy, &G, sizeof(struct gameState));
	
	numBugs += customAssert( (returnValue == 0), "Member in struct gameState incorrectly modified. Only coins should be changed by updateCoins()." );

	//Check if copper card was applied correctly (expected value is 1 coin)
	//Also, updateCoins() should not use treasure cards from player 2's hand 
	numBugs += customAssert( (G.coins == 1), "Copper was not added correctly." );


	//Call updateCoins() for player 0 again, with bonus = 1
	bonus = 1;
	returnValue = updateCoins(0, &G, bonus);

	numBugs += customAssert( (G.coins == 2), "Bonus was not applied correctly." );


	//Test if silver cards are applied correctly (expected value is 2 coins)	
	G.hand[0][0] = silver;
	bonus = 0;
	returnValue = updateCoins(0, &G, bonus);

	numBugs += customAssert( (G.coins == 2), "Silver was not added correctly." );


	//Test if gold cards are applied correctly (expected value is 3 coins)	
	G.hand[0][0] = gold;
	bonus = 0;
	returnValue = updateCoins(0, &G, bonus);

	numBugs += customAssert( (G.coins == 3), "Gold was not added correctly." );


	//Test if two treasure cards are added correctly (expected value is 4 coins)	
	G.handCount[0] = 3;
	G.hand[0][0] = copper;
	G.hand[0][2] = gold;
	bonus = 0;
	returnValue = updateCoins(0, &G, bonus);

	numBugs += customAssert( (G.coins == 4), "Multiple treasure cards not added correctly." );



	if(numBugs)
	{
		printf("\nUnit Test 1 - Total bugs: %d\n", numBugs);
	}	
	else
	{
		printf("\nUnit Test 1 - All tests for updateCoins() successful\n");
	}

	printf("\n----------End of Unit Test 1----------\n");

	return 0;
}

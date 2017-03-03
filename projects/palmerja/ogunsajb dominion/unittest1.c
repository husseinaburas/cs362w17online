#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>


//unit test 1 tests existance of Copper, Silver and Gold Coins 
int main (int argc, char** argv)	{
	struct gameState G;
	G.coins = 0;
	
	printf("\n** Unit test 1: Coins **\n");
	
	printf("\nCopper Test:\n");
	G.hand[0][0] = copper;
	G.hand[0][1] = copper;
	G.hand[0][2] = copper;
	G.hand[0][3] = copper;
	G.hand[0][4] = copper;
	G.hand[0][5] = copper;
	G.hand[0][6] = copper;
	G.hand[0][7] = copper;
	G.hand[0][8] = copper;
	G.hand[0][9] = copper;
	updateCoins(0,&G, 0);
	printf("\nWe should have 10 copper coins: %d\n", G.coins);
	if(G.coins == 10)
		printf("Test Passed\n");
	else
		printf("Test Failed\n");
	
	printf("\nSilver Test:\n");
	G.hand[0][0] = silver;
	G.hand[0][1] = silver;
	G.hand[0][2] = silver;
	G.hand[0][3] = silver;
	G.hand[0][4] = silver;
	G.hand[0][5] = silver;
	G.hand[0][6] = silver;
	G.hand[0][7] = silver;
	G.hand[0][8] = silver;
	G.hand[0][9] = silver;
	updateCoins(0,&G, 0);
	printf("We should have 10 silver coins: %d\n", G.coins);
	if(G.coins == 20)
		printf("Test Passed\n");
	else
		printf("Test Failed\n");
	
	printf("\nGold Test:\n");
	G.hand[0][0] = gold;
	G.hand[0][1] = gold;
	G.hand[0][2] = gold;
	G.hand[0][3] = gold;
	G.hand[0][4] = gold;
	G.hand[0][5] = gold;
	G.hand[0][6] = gold;
	G.hand[0][7] = gold;
	G.hand[0][8] = gold;
	G.hand[0][9] = gold;
	updateCoins(0,&G, 0);
	printf("We should have 10 gold coins: %d\n", G.coins);
	if(G.coins == 30)
		printf("Test Passed\n");
	else
		printf("Test Failed\n");
	
	printf("\nTest for zero existing Coin:\n");
	G.hand[0][0] = adventurer;
	G.hand[0][1] = adventurer;
	G.hand[0][2] = adventurer;
	G.hand[0][3] = adventurer;
	G.hand[0][4] = adventurer;
	G.hand[0][5] = adventurer;
	G.hand[0][6] = adventurer;
	G.hand[0][7] = adventurer;
	G.hand[0][8] = adventurer;
	G.hand[0][9] = adventurer;
	updateCoins(0,&G, 0);
	printf("We should have zero existing Coins: %d\n", G.coins);
	if(G.coins == 0)
		printf("Test Passed");
	else
		printf("Test Failed");
	
	printf("\n** End of Unit Test 1: Coins **\n");

	return 0;
}
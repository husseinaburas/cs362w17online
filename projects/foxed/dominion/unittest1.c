/************************
** Author: Eddie C. Fox
** Date: February 7, 2017
** Description: Unit testing for function.
************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>


int asserttrue(int left, int right)
{
	if (left == right)
	{
		printf("Test PASSED\n");
	}

	else
	{
		printf("Test FAILED\n");
	}
}

int main()
{

	printf("-------- UNIT TEST 1 ----------\n");
	printf("Testing getCost() function.\n");
	printf("Test can be found at unittest1.c\n");

	// Names and costs taken from the hard coded values in dominon.c
	int names[] = { curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, mine, remodel, smithy, village,
		baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map };

	int correctCosts[] = { 0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4 };
	int functionDeterminedCosts[27];

	int i;

	for (i = 0; i < 27; i++)
	{
		functionDeterminedCosts[i] = getCost(names[i]);

		printf("Testing the cost of card # %d, as defined by getCost()\n", names[i]);
		asserttrue(functionDeterminedCosts[i], correctCosts[i]);
	}

	printf("Testing of getCost() is finished.\n");

	return 0;
}
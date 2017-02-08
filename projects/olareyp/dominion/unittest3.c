/* -----------------------------------------------------------------------
 * File: unittest3.c
 * Function: getCost()
 * Author: Patrick OLarey
 * Date: 2/2/2017
 * Course/Assignment: CS362-400 / Assignment 3
 *
 * Source(s): Preprocessor #if/#endif statements for "noisy" tests sourced from instructor-provided
 *				testUpdateCoins.c
 *
 * Makefile
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */


// required #includes
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"	// for card costs defined in interface.h
#include <string.h>
#include <stdio.h>
#include <assert.h>


// set HALTING_TEST to 0 to remove halting asserts
#define HALTING_TEST 0
// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0


// max values
#define MAX_CARDNUMBER 26


// card costs from http://wiki.dominionstrategy.com/index.php/List_of_cards
#define COPPER_COST_WEB 0
#define SILVER_COST_WEB 3
#define GOLD_COST_WEB 6
#define ESTATE_COST_WEB 2
#define DUCHY_COST_WEB 5
#define PROVINCE_COST_WEB 8
#define CURSE_COST_WEB 0
#define ADVENTURER_COST_WEB 6
#define COUNCIL_ROOM_COST_WEB 5
#define FEAST_COST_WEB 4
#define GARDEN_COST_WEB 4
#define MINE_COST_WEB 5
#define MONEYLENDER_COST_WEB 4
#define REMODEL_COST_WEB 4
#define SMITHY_COST_WEB 4
#define VILLAGE_COST_WEB 3
#define WOODCUTTER_COST_WEB 3
#define BARON_COST_WEB 4
#define GREAT_HALL_COST_WEB 3
#define MINION_COST_WEB 5
#define SHANTY_TOWN_COST_WEB 3
#define STEWARD_COST_WEB 3
#define TRIBUTE_COST_WEB 5
#define WISHING_WELL_COST_WEB 3
#define AMBASSADOR_COST_WEB 3
#define CUTPURSE_COST_WEB 4
#define EMBARGO_COST_WEB 2
#define OUTPOST_COST_WEB 5
#define SALVAGER_COST_WEB 4
#define SEA_HAG_COST_WEB 4
#define TREASURE_MAP_COST_WEB 4


//Unit test for: getCost()
int main() {

	// 1 = failures, 0 = no failures
	int failFlag = 0;

	// initializeGame() arguments
	int seed = 999;
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	int player = 2;
	struct gameState state;

	// clear gamestate and initialize new gamestate
	memset(&state, 23, sizeof(struct gameState));		//clear gamestate
	initializeGame(player, k, seed, &state);			//initialize new gamestate

	int cardNumber;
	int cardCostWeb;
	int cardCostInterface;
	int invalidCardCost = -1;

	// compares costs of each card returned by getCost() to costs of the cards from http://wiki.dominionstrategy.com/index.php/List_of_cards
	for (cardNumber = 0; cardNumber <= 26; cardNumber++)
	{
		if (cardNumber == curse)
			cardCostWeb = CURSE_COST_WEB;
		else if (cardNumber == estate)
			cardCostWeb = ESTATE_COST_WEB;
		else if (cardNumber == duchy)
			cardCostWeb = DUCHY_COST_WEB;
		else if (cardNumber == province)
			cardCostWeb = PROVINCE_COST_WEB;
		else if (cardNumber == copper)
			cardCostWeb = COPPER_COST_WEB;
		else if (cardNumber == silver)
			cardCostWeb = SILVER_COST_WEB;
		else if (cardNumber == gold)
			cardCostWeb = GOLD_COST_WEB;
		else if (cardNumber == adventurer)
			cardCostWeb = ADVENTURER_COST_WEB;
		else if (cardNumber == council_room)
			cardCostWeb = COUNCIL_ROOM_COST_WEB;
		else if (cardNumber == feast)
			cardCostWeb = FEAST_COST_WEB;
		else if (cardNumber == gardens)
			cardCostWeb = GARDEN_COST_WEB;
		else if (cardNumber == mine)
			cardCostWeb = MINE_COST_WEB;
		else if (cardNumber == remodel)
			cardCostWeb = REMODEL_COST_WEB;
		else if (cardNumber == smithy)
			cardCostWeb = SMITHY_COST_WEB;
		else if (cardNumber == village)
			cardCostWeb = VILLAGE_COST_WEB;
		else if (cardNumber == baron)
			cardCostWeb = BARON_COST_WEB;
		else if (cardNumber == great_hall)
			cardCostWeb = GREAT_HALL_COST_WEB;
		else if (cardNumber == minion)
			cardCostWeb = MINION_COST_WEB;
		else if (cardNumber == steward)
			cardCostWeb = STEWARD_COST_WEB;
		else if (cardNumber == tribute)
			cardCostWeb = TRIBUTE_COST_WEB;
		else if (cardNumber == ambassador)
			cardCostWeb = AMBASSADOR_COST_WEB;
		else if (cardNumber == cutpurse)
			cardCostWeb = CUTPURSE_COST_WEB;
		else if (cardNumber == embargo)
			cardCostWeb = EMBARGO_COST_WEB;
		else if (cardNumber == outpost)
			cardCostWeb = OUTPOST_COST_WEB;
		else if (cardNumber == salvager)
			cardCostWeb = SALVAGER_COST_WEB;
		else if (cardNumber == sea_hag)
			cardCostWeb = SEA_HAG_COST_WEB;
		else if (cardNumber == treasure_map)
			cardCostWeb = TREASURE_MAP_COST_WEB;

#if (NOISY_TEST == 1)
		printf("getCost() cost = %d, expected cost (web) = %d\n", getCost(cardNumber), cardCostWeb);
#endif
#if (HALTING_TEST == 1)
		assert(getCost(cardNumber) == cardCostWeb);
#endif

		if (getCost(cardNumber) != cardCostWeb)
			failFlag = 1;
	
	}
	// compares costs of each card returned by getCost() to costs of the cards interface.h
	for (cardNumber = 0; cardNumber <= 26; cardNumber++)
	{
		if (cardNumber == curse)
			cardCostInterface = CURSE_COST;
		else if (cardNumber == estate)
			cardCostInterface = ESTATE_COST;
		else if (cardNumber == duchy)
			cardCostInterface = DUCHY_COST;
		else if (cardNumber == province)
			cardCostInterface = PROVINCE_COST;
		else if (cardNumber == copper)
			cardCostInterface = COPPER_COST;
		else if (cardNumber == silver)
			cardCostInterface = SILVER_COST;
		else if (cardNumber == gold)
			cardCostInterface = GOLD_COST;
		else if (cardNumber == adventurer)
			cardCostInterface = ADVENTURER_COST;
		else if (cardNumber == council_room)
			cardCostInterface = COUNCIL_ROOM_COST;
		else if (cardNumber == feast)
			cardCostInterface = FEAST_COST;
		else if (cardNumber == gardens)
			cardCostInterface = GARDEN_COST;
		else if (cardNumber == mine)
			cardCostInterface = MINE_COST;
		else if (cardNumber == remodel)
			cardCostInterface = REMODEL_COST;
		else if (cardNumber == smithy)
			cardCostInterface = SMITHY_COST;
		else if (cardNumber == village)
			cardCostInterface = VILLAGE_COST;
		else if (cardNumber == baron)
			cardCostInterface = BARON_COST;
		else if (cardNumber == great_hall)
			cardCostInterface = GREAT_HALL_COST;
		else if (cardNumber == minion)
			cardCostInterface = MINION_COST;
		else if (cardNumber == steward)
			cardCostInterface = STEWARD_COST;
		else if (cardNumber == tribute)
			cardCostInterface = TRIBUTE_COST;
		else if (cardNumber == ambassador)
			cardCostInterface = AMBASSADOR_COST;
		else if (cardNumber == cutpurse)
			cardCostInterface = CUTPURSE_COST;
		else if (cardNumber == embargo)
			cardCostInterface = EMBARGO_COST;
		else if (cardNumber == outpost)
			cardCostInterface = OUTPOST_COST;
		else if (cardNumber == salvager)
			cardCostInterface = SALVAGER_COST;
		else if (cardNumber == sea_hag)
			cardCostInterface = SEA_HAG_COST;
		else if (cardNumber == treasure_map)
			cardCostInterface = TREASURE_MAP_COST;

#if (NOISY_TEST == 1)
		printf("getCost() cost = %d, expected cost (interface.h) = %d\n", getCost(cardNumber), cardCostInterface);
#endif
#if (HALTING_TEST == 1)
		assert(getCost(cardNumber) == cardCostInterface);
#endif

		if (getCost(cardNumber) != cardCostInterface)
			failFlag = 1;
	
	}


	// test where an invalid card number (-1) is passed to getCost.
	cardNumber = -1;
	#if (NOISY_TEST == 1)
	printf("getCost() cost = %d, expected cost (for invalid card number) = %d\n", getCost(cardNumber), invalidCardCost);
#endif
#if (HALTING_TEST == 1)
	assert(getCost(cardNumber) == invalidCardCost);
#endif

	if (getCost(cardNumber) != invalidCardCost)
		failFlag = 1;


	// test where an invalid card number (27) is passed to getCost.
	cardNumber = 27;
#if (NOISY_TEST == 1)
	printf("getCost() cost = %d, expected cost (for invalid card number) = %d\n", getCost(cardNumber), invalidCardCost);
#endif
#if (HALTING_TEST == 1)
	assert(getCost(cardNumber) == invalidCardCost);
#endif

	if (getCost(cardNumber) != invalidCardCost)
		failFlag = 1;


	// print error if the failFlag was tripped, otherwise, print tests passed
	if (failFlag == 1)
		printf("unittest3 (GETCOST) - TESTS FAILED\n");
	else
		printf("unittest3 (GETCOST) - ALL TESTS PASSED\n");

	return 0;
}

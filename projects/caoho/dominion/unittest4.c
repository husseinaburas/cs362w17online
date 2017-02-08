#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

/**
 * int handCard(int handNum, struct gameState *state);
 	 enum value of indexed card in player's hand
 **/
int main () {

	printf("****** Testing Method <int buyCard(int supplyPos, struct gameState *state);>******\n");

	int rSeed = rand();
	int kValues[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int numPlayers = 2;
	struct gameState state;
	struct gameState copyState;

    initializeGame(numPlayers, kValues, rSeed, &state);

    memcpy(&copyState, &state, sizeof(struct gameState));
    int purchaseCard;
    int totalCost;

    /*=====================================================================================================*/

	printf("Condition 1: BuyNum >1, Coin > Cost, CardSupply > BuyNum");
    int curTurn = state.whoseTurn;

    state.numBuys = 2;
    state.coins = 10;
	purchaseCard = council_room;
	totalCost = 5;


	int preDiscardNum = state.discardCount[curTurn];
	int preSupplyNum = state.supplyCount[purchaseCard];
	int preBuyNum = state.numBuys;
	int preCoinNum = state.coins;

	buyCard(purchaseCard, &state);

	assertMsg("Testing number of cards", preDiscardNum + 1, state.discardCount[curTurn]);
	assertMsg("Testing adding cards", purchaseCard, state.discard[curTurn][state.discardCount[curTurn] - 1]);
	assertMsg("Testing supply card number",preSupplyNum - 1, state.supplyCount[purchaseCard]);
	assertMsg("Testing number of buying", preBuyNum - 1, state.numBuys);
	assertMsg("Testing number of coin cost", preCoinNum - totalCost, state.coins);

	memcpy(&state, &copyState, sizeof(struct gameState));

	printf("Condition 2: BuyNum == 1, Coin > Cost, CardSupply > BuyNum");

    state.numBuys = 1;
    state.coins = 10;
	purchaseCard = council_room;
	totalCost = 5;

	buyCard(purchaseCard, &state);

	assertMsg("Testing number of cards", preDiscardNum + 1, state.discardCount[curTurn]);
	assertMsg("Testing adding cards", purchaseCard, state.discard[curTurn][state.discardCount[curTurn] - 1]);
	assertMsg("Testing supply card number",preSupplyNum - 1, state.supplyCount[purchaseCard]);
	assertMsg("Testing number of buying", preBuyNum - 1, state.numBuys);
	assertMsg("Testing number of coin cost", preCoinNum - totalCost, state.coins);

	memcpy(&state, &copyState, sizeof(struct gameState));

	printf("Condition 3: BuyNum == 0, Coin > Cost, CardSupply > BuyNum");

    state.numBuys = 0;
    state.coins = 10;
	purchaseCard = council_room;
	totalCost = 5;

	buyCard(purchaseCard, &state);

	assertMsg("Testing number of cards", preDiscardNum, state.discardCount[curTurn]);
	assertMsg("Testing supply card number",preSupplyNum , state.supplyCount[purchaseCard]);
	assertMsg("Testing number of buying", preBuyNum, state.numBuys);
	assertMsg("Testing number of coin cost", preCoinNum, state.coins);

	memcpy(&state, &copyState, sizeof(struct gameState));

	printf("Condition 4: BuyNum == 1, Coin < Cost, CardSupply > BuyNum");

    state.numBuys = 1;
    state.coins = 4;
	purchaseCard = council_room;
	totalCost = 5;

	buyCard(purchaseCard, &state);

	assertMsg("Testing number of cards", preDiscardNum, state.discardCount[curTurn]);
	assertMsg("Testing supply card number",preSupplyNum , state.supplyCount[purchaseCard]);
	assertMsg("Testing number of buying", preBuyNum, state.numBuys);
	assertMsg("Testing number of coin cost", preCoinNum, state.coins);

	memcpy(&state, &copyState, sizeof(struct gameState));

	printf("Condition 5: BuyNum == 1, Coin > Cost, CardSupply ==0");

	curTurn = state.whoseTurn;
    state.numBuys = 1;
    state.coins = 5;
	purchaseCard = council_room;
	totalCost = 5;
	state.supplyCount[purchaseCard] = 0;

	buyCard(purchaseCard, &state);

	assertMsg("Testing number of cards", preDiscardNum, state.discardCount[curTurn]);
	assertMsg("Testing supply card number",preSupplyNum, state.supplyCount[purchaseCard]);
	assertMsg("Testing number of buying", preBuyNum, state.numBuys);
	assertMsg("Testing number of coin cost", preCoinNum, state.coins);

	memcpy(&state, &copyState, sizeof(struct gameState));

	printf("Condition 6: BuyNum == 1, Coin > Cost, CardSupply == 1");

	curTurn = state.whoseTurn;
	state.numBuys = 1;
	state.coins = 4;
	purchaseCard = cutpurse;
	totalCost = 4;
	state.supplyCount[purchaseCard] = 1;

	buyCard(purchaseCard, &state);

	assertMsg("Testing number of cards", preDiscardNum + 1, state.discardCount[curTurn]);
	assertMsg("Testing adding cards", purchaseCard, state.discard[curTurn][state.discardCount[curTurn] - 1]);
	assertMsg("Testing supply card number",preSupplyNum - 1, state.supplyCount[purchaseCard]);
	assertMsg("Testing number of buying", preBuyNum - 1, state.numBuys);
	assertMsg("Testing number of coin cost", preCoinNum - totalCost, state.coins);

	printf("****** FInished ******\n");
	return 0;
}

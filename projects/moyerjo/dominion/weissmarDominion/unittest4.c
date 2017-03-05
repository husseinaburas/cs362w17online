#include "dominion.h"
#include "dominion_helpers.h"
#include "testing_helpers.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

//testing scoreFor

int main(int argc, char** argv) {
	int i = 0, totalTests = 0;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	int numPlayers = 2, seed = 500, curPlayer = 0;
	int numFailed = 0;
	struct gameState pre, post, temp;


	initializeGame(numPlayers, k, seed, &pre);
	printf("=============================================\n");
	printf("Beginning testing of scoreFor function:\n");
	printf("=============================================\n\n");
	temp.handCount[curPlayer] = 5;
	for (i = 0; i < temp.handCount[curPlayer]; i++) {
		temp.hand[curPlayer][i] = adventurer;
	}
	temp.deckCount[curPlayer] = 5;
	for (i = 0; i < temp.deckCount[curPlayer]; i++) {
		temp.deck[curPlayer][i] = adventurer;
	}
	temp.discardCount[curPlayer] = 5;
	for (i = 0; i < temp.discardCount[curPlayer]; i++) {
		temp.discard[curPlayer][i] = adventurer;
	}

	pre = post = temp;

	printf("Testing score with no scoring cards:\n");
	if (scoreFor(curPlayer, &post) == 0) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing current player game state did not change:\n");

	if (compareGameState(curPlayer, &pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing second player game state remained same:\n");
	if (compareGameState(curPlayer + 1, &pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing supply remained the same:\n");
	if (supplyUnchanged(&pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	pre = temp;
	pre.hand[curPlayer][2] = estate;
	pre.discard[curPlayer][2] = estate;
	pre.deck[curPlayer][2] = estate;
	post = pre;

	printf("Testing estate and scoring cards centered in array:\n");
	if (scoreFor(curPlayer, &post) == 3) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing current player game state did not change:\n");

	if (compareGameState(curPlayer, &pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing second player game state remained same:\n");
	if (compareGameState(curPlayer + 1, &pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing supply remained the same:\n");
	if (supplyUnchanged(&pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	pre = temp;
	pre.hand[curPlayer][0] = estate;
	pre.discard[curPlayer][0] = estate;
	pre.deck[curPlayer][0] = estate;
	post = pre;

	printf("Testing estate and scoring cards at beginning of array:\n");
	if (scoreFor(curPlayer, &post) == 3) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing current player game state did not change:\n");

	if (compareGameState(curPlayer, &pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing second player game state remained same:\n");
	if (compareGameState(curPlayer + 1, &pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing supply remained the same:\n");
	if (supplyUnchanged(&pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	pre = temp;
	pre.hand[curPlayer][4] = estate;
	pre.discard[curPlayer][4] = estate;
	pre.deck[curPlayer][4] = estate;
	post = pre;

	printf("Testing estate and scoring cards at end of array:\n");
	if (scoreFor(curPlayer, &post) == 3) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing current player game state did not change:\n");

	if (compareGameState(curPlayer, &pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing second player game state remained same:\n");
	if (compareGameState(curPlayer + 1, &pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing supply remained the same:\n");
	if (supplyUnchanged(&pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	pre = temp;
	pre.hand[curPlayer][2] = curse;
	pre.discard[curPlayer][2] = curse;
	pre.deck[curPlayer][2] = curse;
	post = pre;

	printf("Testing curse:\n");
	if (scoreFor(curPlayer, &post) == -3) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing current player game state did not change:\n");

	if (compareGameState(curPlayer, &pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing second player game state remained same:\n");
	if (compareGameState(curPlayer + 1, &pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing supply remained the same:\n");
	if (supplyUnchanged(&pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	pre = temp;
	pre.hand[curPlayer][2] = duchy;
	pre.discard[curPlayer][2] = duchy;
	pre.deck[curPlayer][2] = duchy;
	post = pre;

	printf("Testing duchy:\n");
	if (scoreFor(curPlayer, &post) == 9) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing current player game state did not change:\n");

	if (compareGameState(curPlayer, &pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing second player game state remained same:\n");
	if (compareGameState(curPlayer + 1, &pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing supply remained the same:\n");
	if (supplyUnchanged(&pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	pre = temp;
	pre.hand[curPlayer][2] = province;
	pre.discard[curPlayer][2] = province;
	pre.deck[curPlayer][2] = province;
	post = pre;

	printf("Testing province:\n");
	if (scoreFor(curPlayer, &post) == 18) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing current player game state did not change:\n");

	if (compareGameState(curPlayer, &pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing second player game state remained same:\n");
	if (compareGameState(curPlayer + 1, &pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing supply remained the same:\n");
	if (supplyUnchanged(&pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	pre = temp;
	pre.hand[curPlayer][2] = great_hall;
	pre.discard[curPlayer][2] = great_hall;
	pre.deck[curPlayer][2] = great_hall;
	post = pre;

	printf("Testing great hall:\n");
	if (scoreFor(curPlayer, &post) == 3) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing current player game state did not change:\n");

	if (compareGameState(curPlayer, &pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing second player game state remained same:\n");
	if (compareGameState(curPlayer + 1, &pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing supply remained the same:\n");
	if (supplyUnchanged(&pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	pre = temp;
	pre.hand[curPlayer][2] = gardens;
	pre.discard[curPlayer][2] = gardens;
	pre.deck[curPlayer][2] = gardens;
	post = pre;

	printf("Testing gardens - round down to one each (15 total cards):\n");
	if (scoreFor(curPlayer, &post) == 3) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing current player game state did not change:\n");

	if (compareGameState(curPlayer, &pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing second player game state remained same:\n");
	if (compareGameState(curPlayer + 1, &pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing supply remained the same:\n");
	if (supplyUnchanged(&pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	pre = temp;
	pre.deck[curPlayer][2] = gardens;
	pre.deckCount[curPlayer] = 0;
	post = pre;

	printf("Testing gardens - exactly divisible by 10, no rounding (10 total cards):\n");
	if (scoreFor(curPlayer, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing current player game state did not change:\n");

	if (compareGameState(curPlayer, &pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing second player game state remained same:\n");
	if (compareGameState(curPlayer + 1, &pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing supply remained the same:\n");
	if (supplyUnchanged(&pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	pre = temp;
	pre.deck[curPlayer][2] = gardens;
	pre.deckCount[curPlayer] = 0;
	pre.discardCount[curPlayer] = 4;
	post = pre;

	printf("Testing gardens - fewer than 10 cards (9 total cards):\n");
	if (scoreFor(curPlayer, &post) == 0) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing current player game state did not change:\n");

	if (compareGameState(curPlayer, &pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing second player game state remained same:\n");
	if (compareGameState(curPlayer + 1, &pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("Testing supply remained the same:\n");
	if (supplyUnchanged(&pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	printf("%d/%d tests failed\n\n", numFailed, totalTests);

	return 0;
}
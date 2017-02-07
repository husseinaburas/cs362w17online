#include "dominion.h"
#include "dominion_helpers.h"
#include "testing_helpers.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

//testing Great Hall


int main(int argc, char** argv) {
	int i = 0, totalTests = 0;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	int numPlayers = 2, handPos = 0, seed = 500, curPlayer = 0;
	int numFailed = 0;
	struct gameState pre, post, temp;


	initializeGame(numPlayers, k, seed, &pre);
	for (i = 0; i < 5; i++) {
		pre.hand[curPlayer][i] = great_hall;
	}
	pre.handCount[curPlayer] = 5;
	for (i = 0; i < 5; i++) {
		pre.deck[curPlayer][i] = great_hall;
	}
	pre.deckCount[curPlayer] = 5;
	for (i = 0; i < 5; i++) {
		pre.discard[curPlayer][i] = great_hall;
	}
	pre.discardCount[curPlayer] = 5;
	temp = post = pre; //hmm, are we using C90 or higher?

	printf("=============================================\n");
	printf("Beginning testing of GREAT HALL card:\n");
	printf("=============================================\n\n");

	greatHallPlay(curPlayer, handPos, &post);

	printf("Testing 1 card was drawn w/ cards in deck/discard:\n");
	if (pre.handCount[curPlayer] != post.handCount[curPlayer]) {
		printf("Test Failed\n");
		numFailed++;
	}
	else {
		printf("Test Passed\n");
	}
	totalTests++;

	printf("Testing number of actions was increased:\n");
	if (pre.numActions + 1 != post.numActions) {
		printf("Test Failed\n");
		numFailed++;
	}
	else {
		printf("Test Passed\n");
	}
	totalTests++;

	printf("Testing first player card total remained same:\n");
	if (cardNumbersConstant(curPlayer, &pre, &post) == 1) {
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
	pre.deckCount[curPlayer] = 0;
	post = pre;

	greatHallPlay(curPlayer, handPos, &post);

	printf("Testing 1 card was drawn with no cards in deck:\n");
	if (pre.handCount[curPlayer] != post.handCount[curPlayer]) {
		printf("Test Failed\n");
		numFailed++;
	}
	else {
		printf("Test Passed\n");
	}
	totalTests++;

	printf("Testing number of actions was increased:\n");
	if (pre.numActions + 1 != post.numActions) {
		printf("Test Failed\n");
		numFailed++;
	}
	else {
		printf("Test Passed\n");
	}
	totalTests++;

	printf("Testing first player card total remained same:\n");
	if (cardNumbersConstant(curPlayer, &pre, &post) == 1) {
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
	pre.deckCount[curPlayer] = 0;
	pre.discardCount[curPlayer] = 0;
	post = pre;

	greatHallPlay(curPlayer, handPos, &post);

	printf("Testing no card was drawn with no cards in deck/discard:\n");
	if (pre.handCount[curPlayer] - 1 != post.handCount[curPlayer]) {
		printf("Test Failed\n");
		numFailed++;
	}
	else {
		printf("Test Passed\n");
	}
	totalTests++;

	printf("Testing number of actions was increased:\n");
	if (pre.numActions + 1 != post.numActions) {
		printf("Test Failed\n");
		numFailed++;
	}
	else {
		printf("Test Passed\n");
	}
	totalTests++;

	printf("Testing first player card total remained same:\n");
	if (cardNumbersConstant(curPlayer, &pre, &post) == 1) {
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

	printf("%d/%d Tests Failed\n\n", numFailed, totalTests);



	return 0;
}
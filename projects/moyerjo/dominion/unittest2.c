#include "dominion.h"
#include "dominion_helpers.h"
#include "testing_helpers.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

//testing updateCoins

int main(int argc, char** argv) {
	int i = 0, totalTests = 0;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	int numPlayers = 2, seed = 500, curPlayer = 0;
	int numFailed = 0;
	struct gameState pre, post, temp;


	initializeGame(numPlayers, k, seed, &pre);

	printf("=============================================\n");
	printf("Beginning testing of updateCoins function:\n");
	printf("=============================================\n\n");
	

	pre.handCount[curPlayer] = 5;
	for (i = 0; i < pre.handCount[curPlayer]; i++) {
		pre.hand[curPlayer][i] = adventurer;
	}
	temp = post = pre;


	printf("Testing on hand with no treasure, no bonus:\n");
	updateCoins(curPlayer, &post, 0);
	if (post.coins == 0) {
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

	pre = post = temp;

	printf("Testing on hand with no treasure, negative bonus:\n");
	updateCoins(curPlayer, &post, -1);
	if (post.coins == -1) {
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


	pre = post = temp;
	
	printf("Testing on hand with no treasure, positive bonus:\n");
	updateCoins(curPlayer, &post, 5);
	if (post.coins == 5) {
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


	temp.hand[curPlayer][0] = copper;
	temp.hand[curPlayer][1] = silver;
	temp.hand[curPlayer][2] = adventurer;
	temp.hand[curPlayer][3] = village;
	temp.hand[curPlayer][4] = gold;

	pre = post = temp;

	printf("Testing on hand with some treasure, positive bonus:\n");
	updateCoins(curPlayer, &post, 5);
	if (post.coins == 11) {
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


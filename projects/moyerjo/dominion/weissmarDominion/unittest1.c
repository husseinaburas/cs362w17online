
#include "dominion.h"
#include "dominion_helpers.h"
#include "testing_helpers.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

//testing isGameOver


int main(int argc, char** argv) {
	int totalTests = 0;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	int numPlayers = 2, seed = 500, curPlayer = 0;
	int numFailed = 0;
	struct gameState pre, post, temp;


	initializeGame(numPlayers, k, seed, &pre);
	
	printf("=============================================\n");
	printf("Beginning testing of isGameOver function:\n");
	printf("=============================================\n\n");

	temp = post = pre;

	printf("Testing Initial Game State Does Not End Game:\n");

	if (isGameOver(&post) == 0) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	pre = temp;

	printf("Testing 0 Provinces Ends Game:\n");
	pre.supplyCount[province] = 0;

	post = pre;

	if (isGameOver(&post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	pre = temp;

	printf("Testing 1 Provinces Does Not End Game (All other supply present):\n");
		pre.supplyCount[province] = 1;

		post = pre;

	if (isGameOver(&post) == 0) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	pre = temp;

	printf("Testing three empty piles (including min):\n");
	pre.supplyCount[0] = 0;
	pre.supplyCount[6] = 0;
	pre.supplyCount[7] = 0;

	post = pre;

	if (isGameOver(&post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		numFailed++;
	}
	totalTests++;

	pre = temp;

	printf("Testing three empty piles (including max)\n");
	pre.supplyCount[6] = 0;
	pre.supplyCount[7] = 0;
	pre.supplyCount[26] = 0;

	post = pre;

	if (isGameOver(&post) == 1) {
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

	printf("Testing two empty piles\n");
	pre.supplyCount[6] = 0;
	pre.supplyCount[7] = 0;

	post = pre;

	if (isGameOver(&post) == 0) {
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

	printf("Testing four empty piles\n");
	pre.supplyCount[6] = 0;
	pre.supplyCount[7] = 0;
	pre.supplyCount[8] = 0;
	pre.supplyCount[9] = 0;

	post = pre;

	if (isGameOver(&post) == 1) {
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


	printf("%d/%d Tests Failed\n\n", numFailed, totalTests);


	return 0;
}




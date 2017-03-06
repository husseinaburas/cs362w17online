#include "dominion.h"
#include "dominion_helpers.h"
#include "testing_helpers.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

//testing fullDeckCount


int main(int argc, char** argv) {
	int i = 0, totalTests = 0;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	int numPlayers = 2, seed = 500, curPlayer = 0;
	int numFailed = 0;
	struct gameState pre, post, temp;


	initializeGame(numPlayers, k, seed, &pre);

	printf("=============================================\n");
	printf("Beginning testing of fullDeckCount function:\n");
	printf("=============================================\n\n");
	
	temp.handCount[curPlayer] = 5;
	for (i = 0; i < temp.handCount[curPlayer]; i++) {
		temp.hand[curPlayer][i] = great_hall;
	}
	temp.deckCount[curPlayer] = 5;
	for (i = 0; i < temp.deckCount[curPlayer]; i++) {
		temp.deck[curPlayer][i] = great_hall;
	}
	temp.discardCount[curPlayer] = 5;
	for (i = 0; i < temp.discardCount[curPlayer]; i++) {
		temp.discard[curPlayer][i] = great_hall;
	}

	pre = post = temp;

	printf("Testing count of misc. card present in all locations:\n");
	if (fullDeckCount(curPlayer, great_hall, &post) == 15) {
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

	printf("Testing card not present (3):\n");
	if (fullDeckCount(curPlayer, 3, &post) == 0) {
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


	pre.hand[curPlayer][0] = gold;
	pre.discard[curPlayer][0] = gold;
	pre.deck[curPlayer][0] = gold;

	post = pre;


	printf("Testing locations at the beginning of hand/deck/discard are being found:\n");
	if (fullDeckCount(curPlayer, gold, &post) == 3) {
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
	pre.hand[curPlayer][4] = gold;
	pre.discard[curPlayer][4] = gold;
	pre.deck[curPlayer][4] = gold;

	post = pre;


	printf("Testing locations at the end of hand/deck/discard are being found:\n");
	if (fullDeckCount(curPlayer, gold, &post) == 3) {
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


	printf("Testing locations with enum 0 (curse) are being found:\n");
	if (fullDeckCount(curPlayer, curse, &post) == 3) {
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
	pre.hand[curPlayer][2] = treasure_map;
	pre.discard[curPlayer][2] = treasure_map;
	pre.deck[curPlayer][2] = treasure_map;

	post = pre;


	printf("Testing locations with enum 26 (treasure_map) are being found:\n");
	if (fullDeckCount(curPlayer, treasure_map, &post) == 3) {
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
	
	printf("Testing locations with enum below bounds finds nothing:\n");
	if (fullDeckCount(curPlayer, -1, &post) == 0) {
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


	printf("Testing locations above enum bounds finds nothing:\n");
	if (fullDeckCount(curPlayer, 54, &post) == 0) {
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
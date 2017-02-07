#include "dominion.h"
#include "dominion_helpers.h"
#include "testing_helpers.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

//testing Smithy

int main(int argc, char** argv) {
	int i = 0, totalTests = 0;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	int numPlayers = 2, handPos = 0, seed = 500, curPlayer = 0;
	int numFailed = 0;
	struct gameState pre, post, temp;
	

	initializeGame(numPlayers, k, seed, &pre);
	for (i = 0; i < 5; i++) {
		pre.hand[curPlayer][i] = smithy;
	}
	pre.handCount[curPlayer] = 5;
	for (i = 0; i < 5; i++) {
		pre.deck[curPlayer][i] = smithy;
	}
	pre.deckCount[curPlayer] = 5;
	for (i = 0; i < 5; i++) {
		pre.discard[curPlayer][i] = smithy;
	}
	pre.discardCount[curPlayer] = 5;
	temp = post = pre; //hmm, are we using C90 or higher?
	
	printf("=============================================\n");
	printf("Beginning testing of SMITHY card:\n");
	printf("=============================================\n\n");
	smithyPlay(curPlayer, handPos, &post);

	printf("Testing hand count increase:\n"); //should be net gain of two cards
		if (pre.handCount[curPlayer] + 2 != post.handCount[curPlayer]) {
			numFailed++;
			printf("Test failed\n");

		}
		else {
			printf("Test passed\n");
		}
		totalTests++;

		printf("Testing cards drawn from deck:\n");
			if (pre.deckCount[curPlayer] - 3 != post.deckCount[curPlayer]) {
				printf("Test failed\n");
				numFailed++;
			}
			else {
				printf("Test passed\n");
			}
			totalTests++;

			printf("Testing first player card total remained same w/ 3+ cards:\n");
			if (cardNumbersConstant(curPlayer, &pre, &post) == 1) {
				printf("Test Passed\n");
			}
			else {
				printf("Test Failed\n");
				numFailed++;
			}
			totalTests++;

			printf("Testing second player game state remained same w/ 3+ cards:\n");
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

			printf("Testing drawing with fewer than 3 cards (2) - cards in discard:\n");
			pre = temp;
			pre.deckCount[curPlayer] = 2;
			post = pre;
			smithyPlay(curPlayer, handPos, &post);
			if (pre.handCount[curPlayer] + 2 != post.handCount[curPlayer]) {
				printf("Test failed\n");
				numFailed++;
			}
			else {
				printf("Test passed\n");
			}
			totalTests++;

			printf("Testing first player card total remained same w/ 2 cards, cards in discard:\n");
			if (cardNumbersConstant(curPlayer, &pre, &post) == 1) {
				printf("Test Passed\n");
			}
			else {
				printf("Test Failed\n");
				numFailed++;
			}
			totalTests++;

			printf("Testing second player game state remained same w/ 2 cards, cards in discard:\n");
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

			printf("Testing drawing with fewer than 3 cards (0), cards in discard:\n");
			pre = temp;
			pre.deckCount[curPlayer] = 0;
			post = pre;
			smithyPlay(curPlayer, handPos, &post);
			if (pre.handCount[curPlayer] + 2 != post.handCount[curPlayer]) {
				printf("Test failed\n");
				numFailed++;
			}
			else {
				printf("Test passed\n");
			}
			totalTests++;

			printf("Testing first player card total remained same w/ 0 cards, cards in discard:\n");
			if (cardNumbersConstant(curPlayer, &pre, &post) == 1) {
				printf("Test Passed\n");
			}
			else {
				printf("Test Failed\n");
				numFailed++;
			}
			totalTests++;

			printf("Testing second player game state remained same w/ 0 cards, cards in discard:\n");
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

			printf("Testing drawing with fewer than 3 cards in deck/discard (0):\n");
			pre = temp;
			pre.deckCount[curPlayer] = 0;
			pre.discardCount[curPlayer] = 0;
			post = pre;
			smithyPlay(curPlayer, handPos, &post);
			if (pre.handCount[curPlayer] != post.handCount[curPlayer] - 1) {
				printf("Test failed\n");
				numFailed++;
			}
			else {
				printf("Test passed\n");
			}
			totalTests++;

			printf("Testing first player card total remained same with fewer than 3 cards in deck/discard (0):\n");
			if (cardNumbersConstant(curPlayer, &pre, &post) == 1) {
				printf("Test Passed\n");
			}
			else {
				printf("Test Failed\n");
				numFailed++;
			}
			totalTests++;

			printf("Testing second player game state remained same with fewer than 3 cards in deck/discard (0):\n");
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

			printf("Testing drawing with fewer than with fewer than 3 cards in deck/discard (2):\n");
			pre = temp;
			pre.deckCount[curPlayer] = 0;
			post = pre;
			smithyPlay(curPlayer, handPos, &post);
			if (pre.handCount[curPlayer] + 1 != post.handCount[curPlayer]) {
				printf("Test failed\n");
				numFailed++;
			}
			else {
				printf("Test passed\n");
			}
			totalTests++;

			printf("Testing first player card total remained same with fewer than 3 cards in deck/discard (2):\n");
			if (cardNumbersConstant(curPlayer, &pre, &post) == 1) {
				printf("Test Passed\n");
			}
			else {
				printf("Test Failed\n");
				numFailed++;
			}
			totalTests++;

			printf("Testing second player game state remained same with fewer than 3 cards in deck/discard (2):\n");
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

			printf("\n%d/%d tests failed.\n\n", numFailed, totalTests);

	return 0;
}


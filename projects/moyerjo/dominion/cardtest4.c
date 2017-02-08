#include "dominion.h"
#include "dominion_helpers.h"
#include "testing_helpers.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

//testing Treasure Map



int main(int argc, char** argv) {
	int i = 0, totalTests = 0, preCardTotal = 0, postCardTotal = 0;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	int numPlayers = 2, handPos = 0, seed = 500, curPlayer = 0;
	int failed = 0, numFailed = 0;
	struct gameState pre, post, temp;


	initializeGame(numPlayers, k, seed, &pre);
	for (i = 0; i < 5; i++) {
		pre.hand[curPlayer][i] = treasure_map;
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
	printf("Beginning testing of Treasure Map card:\n");
	printf("=============================================\n\n");
	treasureMapPlay(curPlayer, handPos, &post);

	printf("Testing more than two treasure maps in hand:\n");

	printf("Testing deck size four larger:\n"); //net hand increase of 2
	if (pre.deckCount[curPlayer] + 4 != post.deckCount[curPlayer]) {
		printf("Test Failed\n");
		failed = 1;
		numFailed++;
	}
	else {
		printf("Test Passed\n");
	}
	totalTests++;

	printf("Testing four gold cards added to deck:\n");
	failed = 0;
	for (i = pre.deckCount[curPlayer] - 4; i < post.deckCount[curPlayer] && failed != 1; i++) {
		if (post.deck[curPlayer][i] != gold) {
			printf("Test Failed\n");
			failed = 1;
			numFailed++;
		}
		else {
			printf("Test Passed\n");
		}
	}
	if (failed == 0) {
		printf("Test Passed\n");
	}
		totalTests++;

	printf("Testing total cards in current players state increased by 2:\n");
	preCardTotal = pre.deckCount[curPlayer] + pre.discardCount[curPlayer] + pre.handCount[curPlayer] + pre.playedCardCount;
	postCardTotal = post.deckCount[curPlayer] + post.discardCount[curPlayer] + post.handCount[curPlayer] + post.playedCardCount;
	if (preCardTotal + 2 == postCardTotal) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		failed = 1;
		numFailed++;
	}
	totalTests++;

	printf("Testing second player game state remained same:\n");
	if (compareGameState(curPlayer + 1, &pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		failed = 1;
		numFailed++;
	}
	totalTests++;

	printf("Testing supply remained the same:\n");
	if (treasureMapSupplyUnchanged(&pre, &post) == 1) {
		printf("Test Passed\n");
	}
	else {
		printf("Test Failed\n");
		failed = 1;
		numFailed++;
	}
	totalTests++;

	pre = temp;
	//set two treasure map cards in hand
	for (i = 2; i < 5; i++) {
		pre.hand[curPlayer][i] = great_hall;
	}

	post = pre;

	treasureMapPlay(curPlayer, handPos, &post);

	printf("Testing two treasure maps in hand:\n");

	printf("Testing deck size four larger");
		if (pre.deckCount[curPlayer] + 4 != post.deckCount[curPlayer]) {
			printf("Test Failed\n");
			failed = 1;
			numFailed++;
		}
		else {
			printf("Test Passed\n");
		}
		totalTests++;

		printf("Testing four gold cards added to deck:\n");
		failed = 0;
		for (i = pre.deckCount[curPlayer] - 4; i < post.deckCount[curPlayer] && failed != 1; i++) {
			if (post.deck[curPlayer][i] != gold) {
				printf("Test Failed\n");
				failed = 1;
				numFailed++;
			}
		}
		if (failed == 0) {
			printf("Test Passed\n");
		}
			totalTests++;

			printf("Testing total cards in current players state increased by 2:\n");
			preCardTotal = pre.deckCount[curPlayer] + pre.discardCount[curPlayer] + pre.handCount[curPlayer] + pre.playedCardCount;
			postCardTotal = post.deckCount[curPlayer] + post.discardCount[curPlayer] + post.handCount[curPlayer] + post.playedCardCount;
			if (preCardTotal + 2 == postCardTotal) {
				printf("Test Passed\n");
			}
			else {
				printf("Test Failed\n");
				failed = 1;
				numFailed++;
			}
			totalTests++;

			printf("Testing second player game state remained same:\n");
			if (compareGameState(curPlayer + 1, &pre, &post) == 1) {
				printf("Test Passed\n");
			}
			else {
				printf("Test Failed\n");
				failed = 1;
				numFailed++;
			}
			totalTests++;

			printf("Testing supply remained the same:\n");
			if (treasureMapSupplyUnchanged(&pre, &post) == 1) {
				printf("Test Passed\n");
			}
			else {
				printf("Test Failed\n");
				failed = 1;
				numFailed++;
			}
			totalTests++;

			pre = temp;
			//set one treasure card in hand
			for (i = 1; i < 5; i++) {
				pre.hand[curPlayer][i] = great_hall;
			}

			post = pre;

			treasureMapPlay(curPlayer, handPos, &post);

			printf("Testing one treasure maps in hand:\n");

			printf("Testing deck size remains the same:\n");
				if (pre.deckCount[curPlayer] != post.deckCount[curPlayer]) {
					printf("Test Failed\n");
					failed = 1;
					numFailed++;
				}
				else {
					printf("Test Passed\n");
				}
				totalTests++;

				printf("Testing no treasuremap cards in hand:\n");
				failed = 0;
				for (i = 0; i < post.handCount[curPlayer]; i++) {
					if (post.hand[curPlayer][i] == treasure_map) {
						printf("Test Failed\n");
						failed = 1;
						numFailed++;
					}
				}
				if(failed == 0) {
						printf("Test Passed\n");
					}
					totalTests++;

					printf("Testing total cards in current player's state decreased by 1:\n");
					preCardTotal = pre.deckCount[curPlayer] + pre.discardCount[curPlayer] + pre.handCount[curPlayer] + pre.playedCardCount;
					postCardTotal = post.deckCount[curPlayer] + post.discardCount[curPlayer] + post.handCount[curPlayer] + post.playedCardCount;
					if (preCardTotal == postCardTotal + 1) {
						printf("Test Passed\n");
					}
					else {
						printf("Test Failed\n");
						failed = 1;
						numFailed++;
					}
					totalTests++;

					printf("Testing second player game state remained same:\n");
					if (compareGameState(curPlayer + 1, &pre, &post) == 1) {
						printf("Test Passed\n");
					}
					else {
						printf("Test Failed\n");
						failed = 1;
						numFailed++;
					}
					totalTests++;

					printf("Testing supply remained the same:\n");
					if (treasureMapSupplyUnchanged(&pre, &post) == 1) {
						printf("Test Passed\n");
					}
					else {
						printf("Test Failed\n");
						failed = 1;
						numFailed++;
					}
					totalTests++;

					printf("%d/%d Tests Failed\n\n", numFailed, totalTests);


	return 0;
}
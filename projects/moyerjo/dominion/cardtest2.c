#include "dominion.h"
#include "dominion_helpers.h"
#include "testing_helpers.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

//Testing adventurer


int main(int argc, char** argv) {
	int i = 0, totalTests = 0;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	int numPlayers = 2, handPos = 0, seed = 500, curPlayer = 0;
	int numFailed = 0;
	struct gameState pre, post, temp;

	initializeGame(numPlayers, k, seed, &pre);
	pre.deckCount[curPlayer] = 5;
	pre.hand[curPlayer][handPos] = adventurer;
	for (i = 0; i < pre.deckCount[curPlayer]; i++) {
		pre.deck[curPlayer][i] = copper;
	}

	pre.deck[curPlayer][handPos] = adventurer;
	temp = post = pre; //hmm, are we using C90 or higher?
	printf("=============================================\n");
	printf("Beginning testing of Adventurer card:\n");
	printf("=============================================\n\n");

	adventurerPlay(curPlayer, handPos, &post);
	//TESTING COPPER
	printf("Testing 2 cards were drawn for copper:\n");
		if (pre.handCount[curPlayer] + 1 != post.handCount[curPlayer]) {
			printf("Test Failed\n");
			numFailed++;
		}
		else {
			printf("Test Passed\n");
		}
		totalTests++;

		printf("Testing 2 cards drawn were copper:\n");
			if (post.hand[curPlayer][post.handCount[curPlayer] - 1] != copper || post.hand[curPlayer][post.handCount[curPlayer] - 2] != copper) {
				printf("Test Failed\n");
				numFailed++;
			}
			else {
				printf("Test Passed\n");
			}
			totalTests++;
			//printf("%d %d\n", post.hand[curPlayer][post.handCount[curPlayer] - 1], post.hand[curPlayer][post.handCount[curPlayer] - 2]);

			printf("Testing first player card total remained same w/ copper:\n");
			if (cardNumbersConstant(curPlayer, &pre, &post) == 1) {
				printf("Test Passed\n");
			}
			else {
				printf("Test Failed\n");
				numFailed++;
			}
			totalTests++;

			printf("Testing second player game state remained same w/ copper:\n");
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

			//TESTING SILVER
			pre = temp;

			

			for (i = 0; i < pre.deckCount[curPlayer]; i++) {
				pre.deck[curPlayer][i] = silver;
			}
			totalTests++;

			post = pre;

			adventurerPlay(curPlayer, handPos, &post);

			printf("Testing 2 cards were drawn for silver:\n"); 
				if (pre.handCount[curPlayer] + 1 != post.handCount[curPlayer]) {
					printf("Test Failed\n");
					numFailed++;
				}
				else {
					printf("Test Passed\n");
				}
				totalTests++;

				printf("Testing 2 cards drawn were silver:\n");
					if (post.hand[curPlayer][post.handCount[curPlayer] - 1] != silver || post.hand[curPlayer][post.handCount[curPlayer] - 2] != silver) {
						//printf("%d %d\n", post.hand[curPlayer][post.handCount[curPlayer] - 1], post.hand[curPlayer][post.handCount[curPlayer] - 2]);
						printf("Test Failed\n");
						numFailed++;
					}
					else {
						printf("Test Passed\n");
					}
					totalTests++;

					printf("Testing first player card total remained same w/ silver:\n");
					if (cardNumbersConstant(curPlayer, &pre, &post) == 1) {
						printf("Test Passed\n");
					}
					else {
						printf("Test Failed\n");
						numFailed++;
					}
					totalTests++;

					printf("Testing second player game state remained same w/ silver:\n");
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

					//TESTING GOLD
					pre = temp;

					

					for (i = 0; i < pre.deckCount[curPlayer]; i++) {
						pre.deck[curPlayer][i] = gold;
					}

					post = pre;

					adventurerPlay(curPlayer, handPos, &post);

					printf("Testing 2 cards were drawn for gold:\n");
						if (pre.handCount[curPlayer] + 1 != post.handCount[curPlayer]) {
							printf("Test Failed\n");
							numFailed++;
						}
						else {
							printf("Test Passed\n");
						}
						totalTests++;

						printf("Testing 2 cards drawn were gold:\n");
							if (post.hand[curPlayer][post.handCount[curPlayer] - 1] != gold || post.hand[curPlayer][post.handCount[curPlayer] - 2] != gold) {
								printf("Test Failed\n");
								numFailed++;
							}
							else {
								printf("Test Passed\n");
							}
							totalTests++;
							//printf("%d %d\n", post.hand[curPlayer][post.handCount[curPlayer] - 1], post.hand[curPlayer][post.handCount[curPlayer] - 2]);

							printf("Testing first player card total remained same w/ gold:\n");
							if (cardNumbersConstant(curPlayer, &pre, &post) == 1) {
								printf("Test Passed\n");
							}
							else {
								printf("Test Failed\n");
								numFailed++;
							}
							totalTests++;

							printf("Testing second player game state remained same w/ gold:\n");
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


							printf("Testing drawing with no coins in deck, but coins in discard:\n");
							pre = temp;

							for (i = 0; i < pre.deckCount[curPlayer]; i++) {
								pre.deck[curPlayer][i] = smithy;
							}
							pre.discardCount[curPlayer] = 5;
							for (i = 0; i < pre.discardCount[curPlayer]; i++) {
								pre.discard[curPlayer][i] = copper;
							}
							totalTests++;

							post = pre;
							adventurerPlay(curPlayer, handPos, &post);
							printf("Testing correct cards in discard:\n");
							if (post.discardCount[curPlayer] != 5) {
								printf("Test Failed - s/b five cards in discard\n");
								numFailed++;
							}
							else {
								printf("Test Passed\n");
							}
							totalTests++;
							
							printf("Testing correct number of cards drawn\n");
							if (pre.handCount[curPlayer] + 1 != post.handCount[curPlayer]) {
								printf("Test Failed - did not draw correct number of cards\n");
							}
							else {
								printf("Test Passed\n");
							}
							totalTests++;

							printf("Testing correct number of cards in deck:\n");
							if(pre.deckCount[curPlayer] != post.deckCount[curPlayer] - 2){
								printf("Test Failed - incorrect number of cards in deck\n");
							}
							else {
								printf("Test Passed\n");
							}
							totalTests++;

							printf("Testing first player card total remained same w/ shuffle of discard cards:\n");
							if (cardNumbersConstant(curPlayer, &pre, &post) == 1) {
								printf("Test Passed\n");
							}
							else {
								printf("Test Failed\n");
								numFailed++;
							}
							totalTests++;

							printf("Testing second player game state remained same w/ shuffle of discard:\n");
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

							printf("Testing drawing with one in deck, and one in discard:\n");
							pre = temp;



							for (i = 0; i < pre.deckCount[curPlayer]; i++) {
								pre.deck[curPlayer][i] = smithy;
							}
							pre.discardCount[curPlayer] = 5;
							for (i = 0; i < pre.discardCount[curPlayer]; i++) {
								pre.discard[curPlayer][i] = smithy;
							}
							pre.deck[curPlayer][0] = silver;
							pre.discard[curPlayer][0] = gold;

							post = pre;

							adventurerPlay(curPlayer, handPos, &post);

							printf("Testing there are enough cards in discard:\n");
							if (post.discardCount[curPlayer >= 4]) {
								printf("Test Failed - s/b at least 4 cards in discard\n");
								numFailed++;
							}
							else {
								printf("Test Passed\n");
							}
							totalTests++;

							printf("Testing correct number of cards drawn:\n");
							if (pre.handCount[curPlayer] + 1 != post.handCount[curPlayer]) {
								printf("Test Failed - did not draw correct number of cards\n");
							}
							else {
								printf("Test Passed\n");
							}
							totalTests++;

							printf("Testing correct  number of cards in deck:\n");
							if (post.deckCount[curPlayer] <= 4) {
								printf("Test Failed - incorrect number of cards in deck\n");
							}
							else {
								printf("Test Passed\n");
							}
							totalTests++;

							printf("Testing first player card total remained same w/ treasure split:\n");
							if (cardNumbersConstant(curPlayer, &pre, &post) == 1) {
								printf("Test Passed\n");
							}
							else {
								printf("Test Failed\n");
								numFailed++;
							}
							totalTests++;

							printf("Testing second player game state remained same w/ treasure split:\n");
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

							printf("Testing drawing with one in deck only:\n");
							pre = temp;



							for (i = 0; i < pre.deckCount[curPlayer]; i++) {
								pre.deck[curPlayer][i] = smithy;
							}
							pre.discardCount[curPlayer] = 5;
							for (i = 0; i < pre.discardCount[curPlayer]; i++) {
								pre.discard[curPlayer][i] = smithy;
							}
							pre.deck[curPlayer][0] = silver;

							post = pre;

							adventurerPlay(curPlayer, handPos, &post);

							printf("Testing there are enough cards in discard pile:\n");
							if (post.discardCount[curPlayer == 9]) {
								printf("Test Failed - s/b 9 cards in discard\n");
								numFailed++;
							}
							else {
								printf("Test Passed\n");
							}
							totalTests++;

							printf("Test correct number of cards drawn:\n");
							if (pre.handCount[curPlayer] + 0 != post.handCount[curPlayer]) {
								printf("Test Failed - did not draw correct number of cards\n");
							}
							else {
								printf("Test Passed\n");
							}
							totalTests++;

							printf("Testing correct number of cards in deck:\n");
							if (post.deckCount[curPlayer] != 0) {
								printf("Test Failed - incorrect number of cards in deck\n");
							}
							else {
								printf("Test Passed\n");
							}
							totalTests++;

							printf("Testing first player card total remained same w/ only 1 treasure:\n");
							if (cardNumbersConstant(curPlayer, &pre, &post) == 1) {
								printf("Test Passed\n");
							}
							else {
								printf("Test Failed\n");
								numFailed++;
							}
							totalTests++;

							printf("Testing second player game state remained same w/ only 1 treasure:\n");
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

							printf("Testing drawing with no treasure in deck:\n");
							pre = temp;


							pre.deckCount[curPlayer] = 5;
							for (i = 0; i < pre.deckCount[curPlayer]; i++) {
								pre.deck[curPlayer][i] = smithy;
							}
							pre.discardCount[curPlayer] = 5;
							for (i = 0; i < pre.discardCount[curPlayer]; i++) {
								pre.discard[curPlayer][i] = smithy;
							}

							post = pre;

							adventurerPlay(curPlayer, handPos, &post);

							if (post.discardCount[curPlayer == 10]) {
								printf("Test Failed - s/b 10 cards in discard\n");
								numFailed++;
							}
							else {
								printf("Test Passed\n");
							}
							totalTests++;
							
							printf("Test correct number of cards drawn:\n");
							if (pre.handCount[curPlayer] - 1 != post.handCount[curPlayer]) {
								printf("Test Failed - did not draw correct number of cards (0)\n");
							}
							else {
								printf("Test Passed\n");
							}
							totalTests++;

							printf("Testing correct number of cards in deck:\n");
							if (post.deckCount[curPlayer] != 0) {
								printf("Test Failed - incorrect number of cards in deck\n");
							}
							else {
								printf("Test Passed\n");
							}
							totalTests++;

							printf("Testing first player card total remained same w/ only 1 treasure:\n");
							if (cardNumbersConstant(curPlayer, &pre, &post) == 1) {
								printf("Test Passed\n");
							}
							else {
								printf("Test Failed\n");
								numFailed++;
							}
							totalTests++;

							printf("Testing second player game state remained same w/ only 1 treasure:\n");
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


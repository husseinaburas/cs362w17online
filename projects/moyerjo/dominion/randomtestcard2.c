#include "dominion.h"
#include "dominion_helpers.h"
#include "testing_helpers.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

//Testing Great Hall

#define greatHallMaxTests 1000

int main(int argc, char** argv) {
	//printf("TEST\n");
	int failedCount = 0;
	int totalTests = 0;
	int i, j;
	//struct gameState pre, post;
	int curPlayer, handPos;
	//printf("TEST\n");

	srand(time(NULL));
	for (i = 0; i < greatHallMaxTests; i++) {
		printf("TEST: FOR LOOP BEGIN NEW TEST\n");
		struct gameState pre, post;
		randomSetup(&pre);
		curPlayer = pre.whoseTurn;
		if (pre.handCount[curPlayer] != 0) {
			handPos = rand() % pre.handCount[curPlayer];
		}
		else {
			handPos = 0;
		}
		printf("TEST: HANDPOS SET\n");
		pre.hand[curPlayer][handPos] = great_hall;
		post = pre;
		printf("TEST: JUST BEFORE ADVENTUREPLAY\n");
		greatHallPlay(curPlayer, handPos, &post);
		printf("TEST: GREAT HALL PLAYED\n");
		if (supplyUnchanged(&pre, &post) == 0) {
			printf("Test Failed: Supply Unexpectedly Changed\n");
			failedCount++;
			totalTests++;
		}

		for (j = 0; j < pre.numPlayers; j++) {
			if (j == curPlayer) {
				//total card totals unchanged for current player
				if (cardNumbersConstant(j, &pre, &post) == 0) {
					printf("Test Failed: Current player's overall deck count unexpectedly changed.\n");
					failedCount++;
					totalTests++;
				}
				else {
					//test that correct number of cards were drawn from the correct places
					if (pre.deckCount[curPlayer] >= 1) {
						if (pre.deck[curPlayer][pre.deckCount[curPlayer] - 1] != post.hand[curPlayer][pre.handCount[curPlayer]]) {
							printf("Test Failed: With at least 1 card in deck, incorrect card drawn\n");
							failedCount++;
							totalTests++;
						}

						if (pre.handCount[curPlayer] != post.handCount[curPlayer]) {
							printf("Test Failed: Incorrect number of cards drawn or removed from hand when cards in deck.\n");
						}
						//>=1 cards in discard
						else if (pre.discardCount[curPlayer] >= 1) {
							if (pre.handCount[curPlayer] != post.handCount[curPlayer]) {
								printf("Test Failed: Incorrect number of cards drawn or removed from hand when cards in discard.\n");
							}
						}
						//0 cards in deck/discard
						else {
							if (pre.handCount[curPlayer] - 1 != post.handCount[curPlayer]) {
								printf("Test Failed: Incorrect number of cards drawn or removed from hand when cards in discard.\n");
							}
						}
					}
				}

				if (pre.numActions + 1 != post.numActions) {
					printf("Test Failed: No action was added for the Great Hall\n");
				}

			}
			else
				if (compareGameState(j, &pre, &post) == 0) {
					printf("Test Failed: player %d's gameState unexpectedly changed\n", j + 1);
					failedCount++;
					totalTests++;
				}
			
		}

	}


	printf("%d/%d Tests Failed\n", failedCount, totalTests);



	return 0;

}
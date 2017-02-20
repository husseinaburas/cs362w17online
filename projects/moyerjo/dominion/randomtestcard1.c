#include "dominion.h"
#include "dominion_helpers.h"
#include "testing_helpers.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

//Testing smithy

#define smithyMaxTests 1000

int main(int argc, char** argv) {

	int failedCount = 0;
	int totalTests = 0;
	int i, j, k, l;

	int curPlayer, handPos, numCardsInDeck;

	printf("=====================================================\n");
	printf("TESTING SMITHY\n");
	printf("=====================================================\n\n");

	srand(time(NULL));
	for (i = 0; i < smithyMaxTests; i++) {
		struct gameState pre, post;
		randomSetup(&pre);
		curPlayer = pre.whoseTurn;
		if (pre.handCount[curPlayer] != 0) {
			handPos = rand() % pre.handCount[curPlayer];
		}
		else {
			handPos = 0;
		}
		pre.hand[curPlayer][handPos] = smithy;
		post = pre;

		smithyPlay(curPlayer, handPos, &post);

		if (supplyUnchanged(&pre, &post) == 0) {
			printf("Test Failed: Supply Unexpectedly Changed\n");
			failedCount++;
			
		}
		totalTests++;

		if (supplyUnchanged(&pre, &post) == 0) {
			printf("Test Failed: Supply Unexpectedly Changed\n");
			failedCount++;

		}
		totalTests++;

		for (j = 0; j < pre.numPlayers; j++) {
			if (j == curPlayer) {
				//total card totals unchanged for current player
				if (cardNumbersConstant(j, &pre, &post) == 0) {
					printf("Test Failed: Current player's overall deck count unexpectedly changed.\n");
					failedCount++;
					
				}
				else {
					//test that correct number of cards were drawn
					if (pre.deckCount[curPlayer] >= 3) {
						numCardsInDeck = 3;
					}
					else {
						numCardsInDeck = pre.deckCount[curPlayer];
						printf("Fewer than 3 cards in deck/discard\n");
					}
					l = numCardsInDeck; //offset for beginning of hand
					for (k = 1; k <= numCardsInDeck; k++) {
						if (pre.deck[curPlayer][pre.deckCount[curPlayer] - k] != post.hand[curPlayer][post.handCount[curPlayer] - l]) {
							//printf("Positions: hand: %d deck: %d cardsinhand: %d\n", k * -1, l * -1, numCardsInDeck);
							printf("Test Failed: Card %d from deck is not accurately placed or not correctly drawn\n", k);
							failedCount++;
							
						}
						
						l--;
					}
					totalTests++;
					if (pre.deckCount[curPlayer] + pre.discardCount[curPlayer] < 3) {
						if (pre.deckCount[curPlayer] + pre.discardCount[curPlayer] - 1 != post.handCount[curPlayer]) {
							printf("Test Failed: Incorrect number of cards drawn with less than 3 in deck + discard\n");
							failedCount++;
							
						}
						totalTests++;
					}
					else {
						if (pre.handCount[curPlayer] + 2 != post.handCount[curPlayer]) {
							printf("Test Failed: Incorrect number of cards drawn with three or more cards\n");
							failedCount++;
							
						}
						totalTests++;
					}
				}
			}
			else {
				if (compareGameState(j, &pre, &post) == 0) {
					printf("Test Failed: player %d's gameState unexpectedly changed\n", j + 1);
					failedCount++;
					
				}
				totalTests++;
			}
		}

	}

	printf("=====================================================\n");
	printf("%d/%d Tests Failed\n", failedCount, totalTests);
	printf("=====================================================\n\n");


	return 0;

}
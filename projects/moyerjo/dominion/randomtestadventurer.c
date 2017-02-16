#include "dominion.h"
#include "dominion_helpers.h"
#include "testing_helpers.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

//Testing adventurer

#define advMaxTests 10

int main(int argc, char** argv) {
	//printf("TEST\n");
	int failedCount = 0;
	int totalTests = 0;
	int i, j;
	//struct gameState pre, post;
	int curPlayer, handPos;
	//printf("TEST\n");

	srand(time(NULL));
	for (i = 0; i < advMaxTests; i++) {
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
		pre.hand[curPlayer][handPos] = adventurer;
		post = pre;
		printf("TEST: JUST BEFORE ADVENTUREPLAY\n");
		adventurerPlay(curPlayer, handPos, &post);
		printf("TEST: ADVENTURE PLAYED\n");
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
					//test that correct coins were drawn
					if (validateAdventurerDraw(curPlayer, &pre, &post) == 0) {
						printf("Test Failed - Incorrectly drawing treasure\n");
						failedCount++;
						totalTests+=5;
					}
				}
				
			}
			else {
				if (compareGameState(j, &pre, &post) == 0) {
					printf("Test Failed: player %d's gameState unexpectedly changed\n", j + 1);
					failedCount++;
					totalTests++;
				}
			}
		}

		
		

		
	}







	printf("%d/%d Tests Failed\n", failedCount, totalTests);



	return 0;

}
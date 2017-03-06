//This unit test is for the smithy card

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define DEBUG_MESSAGES 1

int main(){
	int seed = 1000;
	int numPlayer = 2;
	int pos = 0;
	int i = 0;
	int a = 0;
	int handSize = 1;
	int maxHand = 10;
	int testHand[maxHand];
	struct gameState game;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	for(i = 0; i < maxHand; i++){
		testHand[i] = smithy;
	}
	for(i = 0; i < numPlayer; i++){
		for(handSize = 1; handSize < maxHand; handSize++){
			for(pos = 0; pos < handSize; pos++){
		#if (DEBUG_MESSAGES == 1)
				printf("Smithycard(): Testing for player: %d with hand size of %d and smithy position %d\n", i, handSize, pos);
		#endif
				memset(&game, 23, sizeof(struct gameState));
				a = initializeGame(numPlayer, k, seed, &game);
				game.handCount[i] = handSize;
				memcpy(game.hand[i], testHand, sizeof(int) * handSize);
				int playedCount = game.playedCardCount;
				
				smithyx(&game, i, pos);
				if(game.handCount[i] != handSize + 2){
					printf("Smithycard(): TEST FAILED: Did not draw 3 cards\n");
				}
				
				if(game.hand[i][pos] == smithy){
					printf("Smithycard(): TEST FAILED: Did not remove smithy card\n");
				}
				
				if(game.playedCardCount != playedCount + 1){
					printf("Smithycard(): TEST FAILED: Did not add to played pile\n");
				}
			}
		}
	}
	printf("Smithycard(): ALL TESTS PASSED\n");
	return 0;
}
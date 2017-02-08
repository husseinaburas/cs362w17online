//This unit test is for the council room card

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
	int currentBuys;
	int testHand[5] = {adventurer, gardens, treasure_map, copper, council_room};
	struct gameState game;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	for(i = 0; i < numPlayer; i++){
#if (DEBUG_MESSAGES == 1)
		printf("Councilroomcard(): Testing for player: %d\n", i);
#endif
		memset(&game, 23, sizeof(struct gameState));
		a = initializeGame(numPlayer, k, seed, &game);
		for(a = 0; a < numPlayer; a++){
			game.handCount[a] = 5;
			memcpy(game.hand[a], testHand, sizeof(int) * 5);
		}
		currentBuys = game.numBuys;
		councilroomcard(4, i, &game);
		
		if(game.handCount[i] != 8){
			printf("Councilroomcard(): TEST ERROR: Unexpected amount of cards in card player's hand.\n");
			return 0;
		}
		
		if(game.numBuys != currentBuys + 1){
			printf("Councilroomcard(): TEST ERROR: Number of buys was not incremented.\n");
			return 0;
		}
		
		for(a = 0; a < numPlayer; a++){
			if(a != i){
				if(game.handCount[a] != 6){
					printf("Councilroomcard(): TEST ERROR: Unexpected amount of cards in other player's hands.\n");
					return 0;
				}
			}
		}
	}
	printf("Councilroomcard(): ALL TESTS PASSED.\n");
	return 0;
}
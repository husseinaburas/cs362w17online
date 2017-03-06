//this tests isGameOver()

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
	int i = 0;
	int a = 0;
	int over;
	struct gameState game;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	printf("TESTING isGameOver(): \n");
	for(i = 0; i < numPlayer; i++){
#if (DEBUG_MESSAGES == 1)
		printf("isGameOver(): Testing for player: %d\n", i);
#endif
		memset(&game, 23, sizeof(struct gameState));
		a = initializeGame(numPlayer, k, seed, &game);
		over = isGameOver(&game);
		
#if (DEBUG_MESSAGES == 1)
		printf("isGameOver(): Game initialized, nothing changed\n");
#endif
		
		if(over == 1){
			printf("isGameOver(): TEST FAILED: Game is over but it should not be\n");
			return 0;
		}

		game.supplyCount[province] = 0; 
		over = isGameOver(&game);
		
#if (DEBUG_MESSAGES == 1)
		printf("isGameOver(): Province supply set to 0\n");
#endif
		
		if(over == 0){
			printf("isGameOver(): TEST FAILED: Game is not over but it should be.\n");
			return 0;
		}

		game.supplyCount[province] = 1; 
		game.supplyCount[estate] = 0; 
		game.supplyCount[duchy] = 0;
		game.supplyCount[copper] = 1;
		game.supplyCount[silver] = 1;
		game.supplyCount[gold] = 1;
		game.supplyCount[adventurer] = 1;
		game.supplyCount[council_room] = 1;
		game.supplyCount[feast] = 1;
		game.supplyCount[gardens] = 1;
		game.supplyCount[mine] = 1;
		game.supplyCount[remodel] = 1;
		game.supplyCount[smithy] = 1;
		game.supplyCount[village] = 1;
		game.supplyCount[baron] = 1;
		game.supplyCount[great_hall] = 1;
		game.supplyCount[minion] = 1;
		game.supplyCount[steward] = 1;
		game.supplyCount[tribute] = 1;
		game.supplyCount[ambassador] = 1;
		game.supplyCount[embargo] = 1;
		game.supplyCount[outpost] = 1;
		game.supplyCount[salvager] = 1;
		game.supplyCount[sea_hag] = 1;
		game.supplyCount[treasure_map] = 1;
		
		
		over = isGameOver(&game);
		
#if (DEBUG_MESSAGES == 1)
		printf("isGameOver(): Province is 1, there are only two empty supplies\n");
#endif
		
		if(over == 1){
			printf("isGameOver(): TEST FAILED: Game is over but it should not be\n");
			return 0;
		}

		
		game.supplyCount[copper] = 0;
		
		over = isGameOver(&game);

#if (DEBUG_MESSAGES == 1)
		printf("isGameOver(): There are three empty supplies\n");
#endif
		
		
		if(over == 0){
			printf("isGameOver(): TEST FAILED: Game is not over but it should be.\n");
		}
		
		
	}
	printf("isGameOver(): ALL TESTS PASSED!\n");
	return 0;
}
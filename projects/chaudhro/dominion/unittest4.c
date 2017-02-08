//this tests supplyCount()

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
	printf("TESTING supplyCount(): \n");
	for(i = 0; i < numPlayer; i++){
#if (DEBUG_MESSAGES == 1)
		printf("supplyCount(): Testing for player: %d\n", i);
#endif
		memset(&game, 23, sizeof(struct gameState));
		a = initializeGame(numPlayer, k, seed, &game);
		
		game.supplyCount[province] = 1; 
		game.supplyCount[estate] = 2; 
		game.supplyCount[duchy] = 3;
		game.supplyCount[copper] = 4;
		game.supplyCount[silver] = 5;
		game.supplyCount[gold] = 6;
		game.supplyCount[adventurer] = 7;
		game.supplyCount[council_room] = 8;
		game.supplyCount[feast] = 1;
		game.supplyCount[gardens] = 2;
		game.supplyCount[mine] = 3;
		game.supplyCount[remodel] = 4;
		game.supplyCount[smithy] = 5;
		game.supplyCount[village] = 6;
		game.supplyCount[baron] = 7;
		game.supplyCount[great_hall] = 8;
		game.supplyCount[minion] = 1;
		game.supplyCount[steward] = 2;
		game.supplyCount[tribute] = 3;
		game.supplyCount[ambassador] = 4;
		game.supplyCount[embargo] = 5;
		game.supplyCount[outpost] = 6;
		game.supplyCount[salvager] = 7;
		game.supplyCount[sea_hag] = 8;
		game.supplyCount[treasure_map] = 1;
		
		if(supplyCount(province, &game) != 1){
			printf("supplyCount(): TEST FAILED: province count not correct\n");
			return 0;
		}
		
		if(supplyCount(estate, &game) != 2){
			printf("supplyCount(): TEST FAILED: estate count not correct\n");
			return 0;
		}
		
		if(supplyCount(duchy, &game) != 3){
			printf("supplyCount(): TEST FAILED: duchy count not correct\n");
			return 0;
		}
		
		if(supplyCount(copper, &game) != 4){
			printf("supplyCount(): TEST FAILED: copper count not correct\n");
			return 0;
		}
		
		if(supplyCount(silver, &game) != 5){
			printf("supplyCount(): TEST FAILED: silver count not correct\n");
			return 0;
		}
		
		if(supplyCount(gold, &game) != 6){
			printf("supplyCount(): TEST FAILED: gold count not correct\n");
			return 0;
		}
		
		if(supplyCount(adventurer, &game) != 7){
			printf("supplyCount(): TEST FAILED: adventurer count not correct\n");
			return 0;
		}
		
		if(supplyCount(council_room, &game) != 8){
			printf("supplyCount(): TEST FAILED: council_room count not correct\n");
			return 0;
		}
		
		if(supplyCount(feast, &game) != 1){
			printf("supplyCount(): TEST FAILED: feast count not correct\n");
			return 0;
		}
		
		if(supplyCount(gardens, &game) != 2){
			printf("supplyCount(): TEST FAILED: gardens count not correct\n");
			return 0;
		}
		
		if(supplyCount(mine, &game) != 3){
			printf("supplyCount(): TEST FAILED: mine count not correct\n");
			return 0;
		}
		
		if(supplyCount(remodel, &game) != 4){
			printf("supplyCount(): TEST FAILED: remodel count not correct\n");
			return 0;
		}
		
		if(supplyCount(smithy, &game) != 5){
			printf("supplyCount(): TEST FAILED: smithy count not correct\n");
			return 0;
		}
		
		if(supplyCount(village, &game) != 6){
			printf("supplyCount(): TEST FAILED: village count not correct\n");
			return 0;
		}
		
		if(supplyCount(baron, &game) != 7){
			printf("supplyCount(): TEST FAILED: baron count not correct\n");
			return 0;
		}
		
		if(supplyCount(great_hall, &game) != 8){
			printf("supplyCount(): TEST FAILED: great_hall count not correct\n");
			return 0;
		}
		
		if(supplyCount(minion, &game) != 1){
			printf("supplyCount(): TEST FAILED: minion count not correct\n");
			return 0;
		}
		
		if(supplyCount(steward, &game) != 2){
			printf("supplyCount(): TEST FAILED: steward count not correct\n");
			return 0;
		}
		
		if(supplyCount(tribute, &game) != 3){
			printf("supplyCount(): TEST FAILED: tribute count not correct\n");
			return 0;
		}
		
		if(supplyCount(ambassador, &game) != 4){
			printf("supplyCount(): TEST FAILED: ambassador count not correct\n");
			return 0;
		}
		
		if(supplyCount(embargo, &game) != 5){
			printf("supplyCount(): TEST FAILED: embargo count not correct\n");
			return 0;
		}
		
		if(supplyCount(outpost, &game) != 6){
			printf("supplyCount(): TEST FAILED: outpost count not correct\n");
			return 0;
		}
		
		
		if(supplyCount(salvager, &game) != 7){
			printf("supplyCount(): TEST FAILED: salvager count not correct\n");
			return 0;
		}
		
		
		if(supplyCount(sea_hag, &game) != 8){
			printf("supplyCount(): TEST FAILED: sea_hag count not correct\n");
			return 0;
		}
		
		
		if(supplyCount(treasure_map, &game) != 1){
			printf("supplyCount(): TEST FAILED: treasure_map count not correct\n");
			return 0;
		}
	}
	printf("supplyCount(): ALL TEST CASES PASSED!\n");
	return 0;
}
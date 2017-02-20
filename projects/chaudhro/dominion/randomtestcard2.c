//This random test is for the smithy card

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define DEBUG_MESSAGES 1

void assertTrue(int input){
	if(input){
		printf("smithy: TEST PASSSED.\n");
	}else{
		printf("smithy: TEST FAILED.\n");
	}
}

int main(int argc, char ** argv[]){
	
	int seed = 100;
	
	if(argc == 2){
		seed = atoi(argv[1]);
	}else{
		printf("Invalid number of command line arguments.\n");
	}
	
	
	srand((time(NULL)));
	
	int pos = 0;
	int i = 0;
	int loops = 0;
	int a = 0;
	struct gameState game;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	
	
	
	for(loops = 0; loops < 3; loops++){
		

		int handSize = rand() % (MAX_HAND - 1) + 1;
		int numPlayer = rand() % (MAX_PLAYERS - 1) + 1;
		int handPos = -1;
		int testHand[handSize];

		for(i = 0; i < handSize; i++){
			testHand[i] = rand() % 27;
			if(testHand[i] == smithy){
				handPos = i;
			}
		}

		if(handPos == -1){
			continue;
		}
		
		for(i = 0; i < numPlayer; i++){
#if (DEBUG_MESSAGES == 1)
			printf("Smithycard(): Testing for player: %d with hand size of %d and smithy position %d\n", i, handSize, handPos);
#endif
			memset(&game, 23, sizeof(struct gameState));
			a = initializeGame(numPlayer, k, seed, &game);
			game.handCount[i] = handSize;
			memcpy(game.hand[i], testHand, sizeof(int) * handSize);
			smithycard(pos, i, &game);
			printf("Testing for proper handSize: \n");
			assertTrue(game.handCount[i] == handSize + 2);
			printf("Testing for proper discard: \n");
			assertTrue(game.hand[i][pos] != smithy);
		}
	}

	return 0;
}
//This random test is for the adventurer card

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define DEBUG_MESSAGES 1

void assertTrue(int input){
	if(input){
		printf("adventurer: TEST PASSSED.\n");
	}else{
		printf("adventurer: TEST FAILED.\n");
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
	
	
	
	for(loops = 0; loops < 1; loops++){
		
		int deckSize = rand() % (MAX_DECK - 1) + 1;
		int handSize = rand() % (MAX_HAND - 1) + 1;
		int numPlayer = rand() % (MAX_PLAYERS - 1) + 1;
		
		int testDeck[deckSize];
		int testHand[handSize];
		
		// int numTreasures = 0;
		
		// for(i = 0; i < deckSize; i++){
			// testDeck[i] = rand() % 27;
			// if(testDeck[i] == 4 || testDeck[i] == 5 || testDeck[i] == 6){
				// numTreasures++;
			// }
		// }
		
		// if(numTreasures < 2){
			// continue;
		// }
		
		// for(i = 0; i < handSize; i++){
			// testHand[i] = rand() % 27;
		// }
		
		// testHand[handSize] = adventurer;
		
		for(i = 0; i < numPlayer; i++){
#if (DEBUG_MESSAGES == 1)
			printf("Adventurercard(): Random testing for player: %d\n", i);
#endif
			memset(&game, 23, sizeof(struct gameState));
			a = initializeGame(numPlayer, k, seed, &game);
			/* game.deckCount[i] = deckSize;
			memcpy(game.deck[i], testDeck, sizeof(int) * deckSize); */
			/* game.handCount[i] = handSize;
			memcpy(game.hand[i], testHand, sizeof(int) * handSize); */
			adventurercard(i, &game);
			
			assertTrue(game.discardCount[i] == 3);
			assertTrue(game.handCount[i] == handSize + 1);
		}
	}

	return 0;
}
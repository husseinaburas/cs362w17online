//This random test is for the council room card

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define DEBUG_MESSAGES 1

void assertTrue(int input){
	if(input){
		printf("council room: TEST PASSSED.\n");
	}else{
		printf("council room: TEST FAILED.\n");
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
	
	
	printf("STARTING TESTS FOR COUNCIL CARD.\n");
	for(loops = 0; loops < 1000; loops++){

		int deckSize = rand() % (MAX_DECK - 10) + 10;
		int handSize = rand() % (MAX_HAND - 1) + 1;
		int numPlayer = rand() % (MAX_PLAYERS - 1) + 1;
		int handPos = -1;
		int testDeck[deckSize];
		int testHand[handSize];

		for(i = 0; i < deckSize; i++){
			testDeck[i] = rand() % 27;
		}

		for(i = 0; i < handSize; i++){
			testHand[i] = rand() % 27;
			if(testHand[i] == 8){
				handPos = i;
			}
		}

		if(handPos == -1){
			continue;
		}
		
		for(i = 0; i < numPlayer; i++){
#if (DEBUG_MESSAGES == 1)
			printf("Councilroomcard(): Testing for player: %d\n", i);
#endif
			memset(&game, 23, sizeof(struct gameState));
			a = initializeGame(numPlayer, k, seed, &game);
			game.numPlayers = numPlayer;
			for(a = 0; a < numPlayer; a++){
				game.handCount[a] = handSize;
				memcpy(game.hand[a], testHand, sizeof(int) * handSize);
				game.deckCount[a] = deckSize;
				memcpy(game.deck[a], testDeck, sizeof(int) * deckSize);
			}
			int currentBuys = game.numBuys;
			printf("handpos: %d i: %d deckSize: %d handSize: %d\n", handPos, i, deckSize, handSize);
			councilroomcard(handPos, i, &game);
			
			printf("Testing for proper player handsize: \n");
			assertTrue(game.handCount[i] == handSize + 3);
			printf("Testing for proper buys: \n");
			assertTrue(game.numBuys == currentBuys + 1);
			
			printf("Testing for proper handsize for other players: \n");
			for(a = 0; a < numPlayer; a++){
				if(a != i){
					assertTrue(game.handCount[a] == handSize + 1);
				}
			}
		}
	}

	return 0;
}
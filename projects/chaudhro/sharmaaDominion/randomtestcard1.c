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
	
	SelectStream(2);
	PutSeed(seed);
	
	printf("STARTING TESTS FOR COUNCIL CARD.\n");
	for(loops = 0; loops < 10000; loops++){
		
		
		
		int deckSize = rand() % (MAX_DECK - 10) + 10;
		int handSize = rand() % (MAX_HAND - 1) + 1;
		int discardSize =  rand() % (MAX_DECK - 1) + 1;
		int numPlayer = rand() % (MAX_PLAYERS - 1) + 1;
		int handPos = rand() % handSize;
	/* 	int testDeck[deckSize];
		int testHand[handSize]; */

		/* for(i = 0; i < deckSize; i++){
			testDeck[i] = rand() % 27;
		} */

		// for(i = 0; i < handSize; i++){
			// if(testHand[i] == 8){
				// handPos = i;
			// }
		// }

		// if(handPos == -1){
			// continue;
		// }


		memset(&game, 23, sizeof(struct gameState));
		a = initializeGame(numPlayer, k, seed, &game);
		
		for(i = 0; i < sizeof(struct gameState); i++){
			((char*)&game)[i] = floor(Random()* 256);
		}
		
		game.numPlayers = numPlayer;
		game.playedCardCount = rand() % (MAX_DECK - 1) + 1;
		for(a = 0; a < numPlayer; a++){
			game.handCount[a] = handSize;
			game.deckCount[a] = deckSize;
			game.discardCount[a] = discardSize;
			
		}
		int currentBuys = game.numBuys;
		council_roomx(&game, numPlayer-1, handPos);
		
		printf("\nTesting for proper player handsize: \n");
		assertTrue(game.handCount[numPlayer-1] == handSize + 3);
		printf("\nTesting for proper buys: \n");
		assertTrue(game.numBuys == currentBuys + 1);
		
		printf("\nTesting for proper handsize for other players: \n");
		for(a = 0; a < numPlayer; a++){
			if(a != numPlayer - 1){
				printf("Player %d: \n", a);
				assertTrue(game.handCount[a] == handSize + 1);
			}
		}
	}

	return 0;
}
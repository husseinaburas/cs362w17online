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
	
	
	
	for(loops = 0; loops < 10000; loops++){
		
		int deckSize = rand() % MAX_DECK;
		int handSize = rand() % (MAX_HAND - 1) + 1;
		int discardSize =  rand() % (MAX_DECK - 1) + 1;
		int numPlayer = rand() % (MAX_PLAYERS - 1) + 1;
		int handPos = rand() % handSize;
		int testDeck[deckSize];
		int check = 0, i1 = 0, i2 = 0;
		
		memset(&game, 23, sizeof(struct gameState));
		a = initializeGame(numPlayer, k, seed, &game);
		
		for(i = 0; i < sizeof(struct gameState); i++){
			((char*)&game)[i] = floor(Random()* 256);
		}
		
		for(i = 0; i < deckSize; i++){
			testDeck[i] = rand() % 27;
			if(testDeck[i] == copper || testDeck[i] == silver || testDeck[i] == gold){
				check++;
				i2 = i1;
				i1 = i;
				
			}
		}
		
		if(check < 2){
			continue;
		}
	
#if (DEBUG_MESSAGES == 1)
		printf("Adventurercard(): Random testing\n");
#endif
		game.handCount[numPlayer-1] = handSize;
		game.deckCount[numPlayer-1] = deckSize;
		game.discardCount[numPlayer-1] = discardSize;
		game.numPlayers = numPlayer;
		game.playedCardCount = rand() % (MAX_DECK - 1) + 1;
		
		//game.deckCount[i] = deckSize;
		memcpy(game.deck[numPlayer-1], testDeck, sizeof(int) * deckSize); 
		/* game.handCount[i] = handSize;
		memcpy(game.hand[i], testHand, sizeof(int) * handSize); */
		int* test;
		adventurerx(&game, numPlayer-1, test, 0);
		
		printf("TESTING FOR CORRECT AMOUNT OF CARDS IN DISCARD.\n");
		assertTrue(game.discardCount[numPlayer-1] == discardSize + deckSize - i2 - 2);
		printf("TESTING FOR CORRECT AMOUNT OF CARDS IN HAND.\n");
		assertTrue(game.handCount[numPlayer-1] == handSize + 1);
	
	}

	return 0;
}
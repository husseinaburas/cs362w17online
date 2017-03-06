#include "dominion.h"
#include "rngs.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#define TESTCARD "Village"
#define NOISY_TEST 0 


void assertTrue(int val){
    if(val) printf("TEST SUCCESSFUL\n");
    else printf("TEST FAILED.\n");
    return;
}

int main(int argc, char *argv[]){
	printf(" ---------------- Random Test on Village ------------------\n");
	struct gameState game_before, game_after;
	int numplayers;
	int handPos = 0, c1 =0, c2 = 0, c3 = 0;
	int i, j;
	int k[10] = {feast, gardens, mine, remodel, smithy, adventurer, council_room, village, great_hall, baron};
	
	int seed;
	if(argc == 2){
		seed = atoi(argv[1]); 
	}
	else{
		srand(time(NULL));
		seed = rand();
		printf("%d\n",seed);
	}
	srand(seed);
	
	
	
	for(i = 0; i < 1000; i++){ //run 1000 tests
		numplayers = rand()%5; //up to 4 players can play
		initializeGame(numplayers, k, seed, &game_before);
		memcpy(&game_after, &game_before, sizeof(struct gameState));
		game_before.numActions = game_before.numActions + 2;
		cardEffect(village, c1, c2, c3, &game_after, handPos, 0);
		
		printf("Test that actions have increased by 2");
		assertTrue(game_before.numActions == game_after.numActions);
		printf("Test cards in hand are eqaul: ");
		assertTrue(game_after.handCount[0] == game_before.handCount[0]); //make sure number of cards in hand is equal
		printf("Test cards in deck are eqaul: ");
		assertTrue(game_after.deckCount[0] == game_before.deckCount[0] - 1);// make sure number of cards in deck is equal
		
		for(j = 1; j < numplayers; j++){
			
			printf("Test all players cards in deck are equal: ");
			assertTrue(game_after.deckCount[i] == game_before.deckCount[i]);
			
			printf("Test all players cards in hand are equal: ");
			assertTrue(game_after.handCount[i] == game_before.handCount[i]);
			
			printf("Test all players cards in discard are equal: ");
			assertTrue(game_after.discardCount[i] == game_before.discardCount[i]);
		}
	}
	
	return 0;	
}
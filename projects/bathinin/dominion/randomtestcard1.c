/* Name: Nipun Bathini
   Assignment: 4
   
   village random test

   
   
   I used village for one of my card unit tests.
   */
#include "dominion.h"
#include "rngs.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#define TESTCARD "Village"
#define NOISY_TEST 0 // to remove prints, learned from professor example


void assertTest(int val);

int main(int argc, char *argv[]){
	printf(" -----Random Test for Village -----\n");
	int i, j;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	
	int seed;
	if(argc == 2){
		seed = atoi(argv[1]); //seet from command line
	}else{
		printf("\n Random seed is being generated: ");
		srand(time(NULL));
		seed = rand();
		printf("%d\n",seed);
	}
	srand(seed);
	
	struct gameState G, Gtwo;
	int numPlayer;
	int handPos = 0, c1 =0, c2 = 0, c3 = 0;
	
	
	for(i = 0; i < 1000; i++){
		numPlayer = rand()%5; //up to 4 players
		initializeGame(numPlayer, k, seed, &G);
		memcpy(&Gtwo, &G, sizeof(struct gameState));
		G.numActions = G.numActions + 2;
		cardEffect(village, c1, c2, c3, &Gtwo, handPos, 0);
		
		printf("Test that numActions increased: ");
		assertTest(Gtwo.numActions == G.numActions);
		
		printf("Test cards in hand count are eqaul: ");
		assertTest(Gtwo.handCount[0] == G.handCount[0]); //make sure number of cards in hand is equal
		printf("Test cards in deck are eqaul: ");
		assertTest(Gtwo.deckCount[0] == G.deckCount[0] - 1);// make sure number of cards in deck is equal
		
		for(j = 1; j < numPlayer; j++){
			printf("Test all players cards in hand are equal: ");
			assertTest(Gtwo.handCount[j] == G.handCount[j]);
			
			printf("Test all players cards in deck are equal: ");
			assertTest(Gtwo.deckCount[j] == G.deckCount[j]);
			
			printf("Test all players cards in discard are equal: ");
			assertTest(Gtwo.discardCount[j] == G.discardCount[j]);
		}
	}
	
	return 0;	
}


void assertTest(int val){
	if(val == 0){
		printf("FAIL\n");
	}else{
		printf("PASS\n");
	}
}
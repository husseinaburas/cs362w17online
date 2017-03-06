/* Name: Nipun Bathini
   Assignment: 4
   
   steward random test
   */
#include "dominion.h"
#include "rngs.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include<stdbool.h>
#define TESTCARD "smithy"
//#define NOISY_TEST 0 // to remove prints, learned from professor example


void assertTest(int val);

int main(int argc, char *argv[]){
	printf(" -----Random Test for smithy -----\n");
	//int i;
	//int seed = rand();
	
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
	
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	struct gameState G, Gtwo;
	int numPlayer = 0;
	int i;
	int c1 =0, c2 = 0, c3 = 0;
	int handPos = 0;
	int player;
	int handCount;
	int handInc, deckDec, discInc;
	
	for(i = 0; i < 1000; i++){
		numPlayer = (rand() % 3) + 2; //randomly picks the numbers of players
		initializeGame(numPlayer, k, seed, &G);
		player = rand() % numPlayer;
		G.whoseTurn = player;
		
		handCount = G.handCount[player];
		if(handCount < 1){
			handPos = 0;
		}else{
			handPos = rand() % handCount; //randomly generate hand positon
		}
		G.hand[player][handPos] = smithy; //makes sure that the player has smithy in their hand
		printf("\n Test is smithy in hand: ");
		assertTest(G.hand[player][handPos] == smithy);
		
		G.deckCount[player] = rand() % (MAX_DECK + 1);
		
		memcpy(&Gtwo, &G, sizeof(struct gameState));
		
		cardEffect(smithy, c1, c2,c3, &G, handPos, 0);
		
		handInc = G.handCount[player] - Gtwo.handCount[player];
		printf("Testing handCount increase by 2: ");
		assertTest(handInc == 2);
		
		deckDec = G.deckCount[player] - Gtwo.deckCount[player];
		printf("Testing deckCount decreased by 3: ");
		assertTest(deckDec == -3);
		
		discInc = G.discardCount[player] - Gtwo.discardCount[player];
		printf("Testing discardCount increase by 1: ");
		assertTest(discInc == 1);
		
		printf("Test that smithy was removed from hand: ");
		assertTest(G.hand[player][handPos] != smithy);
		
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


		
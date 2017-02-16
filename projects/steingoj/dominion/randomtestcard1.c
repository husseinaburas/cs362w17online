#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h> //for rand
#include <time.h> //for time
#include <assert.h>
#include "rngs.h"
#include "asserttrue.h" //Custom assert macro
#include "math.h" //For floor

#define DEBUG 0
#define NOISY_TEST 1

int checkSmithy(int p, struct gameState *post){
	int deckCount = post->deckCount[p];
	int discardCount = post->discardCount[p];
	int handCount = post->handCount[p];	
	int r, a, b;


	post->whoseTurn = p;

	r = playSmithy(post, p);	

	//printf("discardCount: %d\n", discardCount);
	//printf("deckCount: %d\n", deckCount);
	//printf("handCount: %d\n", handCount);


	//printf("deckCount before: %d\n", deckCount);
	//printf("deckCount after: %d\n", post->deckCount[p]);



	/*******************************************************
	//Test that checks if deckCount decremented by 3 
	*******************************************************/
	a = deckCount;
	b = post->deckCount[p];
	assertTrue(a-3==b,"deckCount did not decrement properly\n");

	/*****************************************************
	//Test if discardCount is incremented by 1
	****************************************************/
	a = discardCount;
	b = post->discardCount[p];
	assertTrue(a+1==b, "discardCount did not increment\n");
	
	/***************************************************
	//Test if handCount increases by 2 
	***************************************************/
	a = handCount;
	b = post->handCount[p];
	assertTrue(a+2==b, "handCount did not increase\n");

	return 0;

}


int main(int argc, char* argv[]) {

	int i, n, r, p, deckCount, discardCount, handCount, rando;

	int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

	struct gameState G;

	printf ("Testing smithy.\n");

	printf ("RANDOM TESTS.\n");

	if(argc != 2){
		printf("You only need one argument to run this program\n\n");
	}

	SelectStream(2);
	PutSeed(argv[1]);
	//srand(time(argv[1]));


	//TO DO: Increase n for more random testing
	for (n = 0; n < 10; n++) {
		p = floor(Random() * 2);
	
		//random handCount
		G.handCount[p] = floor(Random() * MAX_DECK);
	
		//random deckCount
		G.deckCount[p] = floor(Random() * MAX_DECK);
	
		//random discardCount 
		G.discardCount[p] = floor(Random() * MAX_DECK);
			
		checkSmithy(p, &G);
  	}
	return 0;

}


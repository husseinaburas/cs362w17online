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

int checkVillage(int p, struct gameState *post){
	int numActions = post->numActions;
	int handCount = post->handCount[p];	
	int r, a, b;


	post->whoseTurn = p;
printf("INSIDE THE THING\n");

	//p is the handposition
	r = playVillage(post, p);	


	/****************************************
	//Test to see if numActions increased
	****************************************/
	
	a = numActions;
	b = post->numActions;
	assertTrue(a+2==b, "numActions didn't increase properly");

	//printf("Pre: %d\n", a);
	//printf("Post: %d\n", b);


	/****************************************
	//Test to see if handCount decreased
	****************************************/

	a = handCount;
	b = post->handCount[p];
	assertTrue(a==b, "handCount didn't decrease/increase properly"); 

	return 0;
}


int main(int argc, char* argv[]) {

	int i, n, r, p, deckCount, discardCount, handCount, rando;

	int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

	struct gameState G;

	printf ("Testing village.\n");

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
		G.numActions = floor(Random() * MAX_DECK);
						
		checkVillage(p, &G);
  	}
	return 0;

}


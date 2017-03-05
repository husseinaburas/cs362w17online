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
	int handCount = post->handCount[0];	
	int r, a, b;


	//post->whoseTurn = 0;

	//p is the handposition
	r = cardEffect(village, 0, 0, 0, post, p, 0);	//TEST CHANGE


	/****************************************
	//Test to see if numActions increased
	****************************************/
	
	a = numActions;
	b = post->numActions;
	assertTrue(a+2==b, "numActions didn't increase properly");

	
	/****************************************
	//Test to see if handCount decreased
	****************************************/

	a = handCount;
	b = post->handCount[0];
	assertTrue(a==b, "handCount changed"); 
	return 0;
}


int main(int argc, char* argv[]) {

	int n, p;

	int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

	struct gameState G;

	printf ("Testing village.\n");

	printf ("RANDOM TESTS.\n");

	//Set random seed
	srand(time(NULL));


	//TO DO: Increase n for more random testing
	for (n = 0; n < 10; n++) {
		initializeGame(2, k, 1, &G);
		
		G.deckCount[0] = floor(Random() * MAX_DECK);
		G.handCount[0] = floor(Random() * MAX_DECK);
		
		//Random position of card
		p = floor(Random() * G.handCount[0]);

		G.whoseTurn = 0;
	
		//random discardCount 
		G.discardCount[0] = floor(Random() * MAX_DECK);
		G.numActions = floor(Random() * MAX_DECK);
						
		checkVillage(p, &G);
  	}
	return 0;

}


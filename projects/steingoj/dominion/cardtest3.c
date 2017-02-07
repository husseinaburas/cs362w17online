#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "asserttrue.h" //Custom assert macro


#define DEBUG 0
#define NOISY_TEST 1


int main () {
	printf("Starting card test 3\n");
	printf("Subject: playVillage\n");
		
	int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

	int a, b;
	
	struct gameState pre;
	struct gameState post;

	initializeGame(2, k, 1, &pre);

	memcpy (&pre, &post, sizeof(struct gameState));

	post.deckCount[0] = 3; //Set deckCount so drawCard draws
	pre.deckCount[0] = 3;
	post.hand[0][0] = village;
	post.whoseTurn = 0;
	playVillage(&post, 0);


	/****************************************
	//Test to see if numActions increased
	****************************************/
	
	a = pre.numActions;
	b = post.numActions;
	assertTrue(a+2==b, "numActions didn't increase properly");

	//printf("Pre: %d\n", a);
	//printf("Post: %d\n", b);


	/****************************************
	//Test to see if handCount decreased
	****************************************/

	a = pre.handCount[0];
	b = post.handCount[0];
	assertTrue(a==b, "handCount didn't decrease/increase properly"); 

	//printf("Pre: %d\n", a);
	//printf("Post: %d\n", b);


	printf("\n\n");	

	return 0;
}

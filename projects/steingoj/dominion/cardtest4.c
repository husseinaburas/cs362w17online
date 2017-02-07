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
	printf("Starting card test 4\n");
	printf("Subject: playCouncil_Room\n");
		
	int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

	int a, b;
	
	struct gameState pre;
	struct gameState post;

	initializeGame(2, k, 1, &pre);

	memcpy (&pre, &post, sizeof(struct gameState));

	/***********************************************
	//Test to see if 4 cards were added
	***********************************************/
	post.deckCount[0] = 10;
	pre.deckCount[0] = 10;
	post.deckCount[1] = 10; //So drawCard works properly
	pre.deckCount[1] = 10; 
	post.whoseTurn = 0;
	post.numPlayers = 2;
	playCouncil_Room(&post, 0);	
	a = pre.handCount[0];
	b = post.handCount[0];

	//3 because the original card is discarded
	assertTrue(a+3==b, "cards were not added properly"); 



	/***********************************************
	//See if numBuys increased by 1
	***********************************************/
	a = pre.numBuys;
	b = post.numBuys;
	assertTrue(a+1==b, "numBuys not incremented");

	/**********************************************
	//Other players draw a card
	************************************************/
	a = pre.handCount[1];
	b = post.handCount[1];
	assertTrue(a+1==b, "Other player didn't get a card");

	//printf("Pre: %d\n", a);
	//printf("Post: %d\n", b);

	printf("\n\n");	

	return 0;
}

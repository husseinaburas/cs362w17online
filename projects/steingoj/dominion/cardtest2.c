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
	printf("Starting card test 2\n");
	printf("Subject: adventurer\n");
		
	int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

	int a, b;
	
	struct gameState pre;
	struct gameState post;

	initializeGame(2, k, 1, &pre);

	memcpy (&pre, &post, sizeof(struct gameState));

	/*************************************
	//Test adventurer with all copper
	*************************************/
	
	pre.whoseTurn = 0;

	post.deck[0][0] = copper;
	post.deck[0][1] = copper;
	post.deck[0][2] = copper;
	post.deck[0][3] = copper;
	
	pre.handCount[0] = 1;
	pre.deckCount[0] = 4;
	post.handCount[0] = 1;
	post.deckCount[0] = 4;
	
	playAdventurer(&post);
	
	a = pre.handCount[0];
	b = post.handCount[0];

	assertTrue(a+2==b, "Hand count did not increase properly for copper");

	/***********************************
	//Test adventurer with all silver
	***********************************/	
	memcpy (&pre, &post, sizeof(struct gameState));

	pre.whoseTurn = 0;

	post.deck[0][0] = silver;
	post.deck[0][1] = silver;
	post.deck[0][2] = silver;
	post.deck[0][3] = silver;
	
	pre.handCount[0] = 1;
	pre.deckCount[0] = 4;
	post.handCount[0] = 1;
	post.deckCount[0] = 4;
	
	playAdventurer(&post);
	
	a = pre.handCount[0];
	b = post.handCount[0];

	assertTrue(a+2==b, "Hand count did not increase properly for silver");

	/***********************************
	//Test adventurer with all gold
	***********************************/	
	memcpy (&pre, &post, sizeof(struct gameState));

	pre.whoseTurn = 0;

	post.deck[0][0] = gold;
	post.deck[0][1] = gold;
	post.deck[0][2] = gold;
	post.deck[0][3] = gold;
	
	pre.handCount[0] = 1;
	pre.deckCount[0] = 6;
	post.handCount[0] = 1;
	post.deckCount[0] = 6;
	
	playAdventurer(&post);
	
	a = pre.handCount[0];
	b = post.handCount[0];

	assertTrue(a+2==b, "Hand count did not increase properly for gold");



	/****************************************
	//Test that cards not taken are discarded
	*******************************************/
	memcpy (&pre, &post, sizeof(struct gameState));
	
	post.deck[0][0] = smithy;
	post.deck[0][1] = smithy;
	post.deck[0][2] = copper;
	post.deck[0][3] = copper;
	post.deck[0][4] = smithy;
	post.deck[0][5] = smithy;

	
	pre.handCount[0] = 1;	
	pre.deckCount[0] = 6;
	post.handCount[0] = 1;
	post.deckCount[0] = 6;

	playAdventurer(&post);

	a = pre.discardCount[0];
	b = post.discardCount[0];
	
	//printf("Pre: %d\n", a);	
	//printf("Post: %d\n", b);
	assertTrue(a+2==b, "Cards not discarded properly");

	printf("\n\n");	

	return 0;
}

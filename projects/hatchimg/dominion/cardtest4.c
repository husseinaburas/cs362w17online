//this is the unit test for play_outpost

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stlib.h>
#include "rngs.h"

int passFlag = 0;

void asserttrue(int a, int b, int testcase){
	
	if(a == b)
		printf("TEST PASSED.\n");
	else
		printf("TEST FAILED. ");
		passFlag++;
		
		switch(testcase){
			
			case 1:
				printf("Outpost flag was not set\n");
				break;

			case 2:
				printf("");
				break;

			case 3:
				printf("Other aspect(s) of gamestate were changed besides outpostPlayed flag\n");
				break;

			case 4:
				printf("Call returned successfully with bad/nonexistent input\n");
				break;
				
		}
	
}

int test_play_outpost(struct gameState *post, int handPos){
	
	//copy current gamestate into pre
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));
	
	//test that outpost flag was set
	int x;
	if((post->outpostPlayed != pre.outpostPlayed) && post->outpostPlayed == 1)
		x = 0;
	else
		x = 1;
	
	asserttrue(0, x, 1);
	
	//test that card was removed from hand and discarded
	
	int y;
	if((post->handCount[post->whoseTurn] == (pre.handCount[post->whoseTurn] - 1)) && (post->discardCount[post->whoseTurn] == (pre.discardCount[post->whoseTurn] + 1)))
		y = 0;
	else
		y = 1;
	
	asserttrue(0, y, 2);
	
	//reset the flag and compare gamestates to test if anything else was changed (which it shouldn't be). This will check on other players' hands/decks/discards,
	//victory and kingdom card piles, etc.
	int z;
	post->outpostPlayed = pre.outpostPlayed;
	z = memcmp(&pre, post, sizeof(struct gameState));
	asserttrue(0, z, 3);
	
	//test with bad input (nonexistent handPos)
	int q;
	q = play_outpost(post, -100);
	if(q == 0)
		q = 1;
	else
		q = 0;
	
	asserttrue(0, q, 4);
	
	
	if(passFlag == 0)
		printf("ALL TESTS PASSED SUCCESSFULLY\n");
	
	return 0;
	
}

int main(){
	
	struct gameState G;

	int numPlayers = 4;
	
	int k[10] = {adventurer, embargo, village, minion, outpost, cutpurse, great_hall, tribute, smithy, council_room};
	int seed = 1000;
	
	initializeGame(numPlayers, k, seed, &G);

	G.whoseTurn = 1;
	
	//set everyone's deck, discard, and handcounts to 20, 10, and 5, respectively
	int i;
	for(i = 0; i < G.numPlayers; i++){
		G.deckCount[i] = 20;
		G.discardCount[i] = 10;
		G.handCount[i] = 5;

	}
	
	int handPos = 3;
	G.hand[G.whoseTurn][3] = outpost;
	
	test_play_outpost(&G, handPos);
	
	return 0;
}
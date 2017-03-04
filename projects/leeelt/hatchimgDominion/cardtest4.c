//this is the unit test for play_outpost

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

int passFlag = 0;

void asserttrue(int a, int b, int testcase){
	
	if(a == b)
		printf("TEST PASS\n");
	else{
		printf("TEST FAILED. ");
		passFlag++;
		
		switch(testcase){
			
			case 1:
				printf("Outpost flag was not set\n");
				break;

			case 2:
				printf("Card was not removed from hand and/or discarded\n");
				break;

			case 3:
				printf("Deck/hand/discard of other player(s) affected by call\n");
				break;
				
			case 4:
				printf("Victory card pile was altered \n");
				break;

			case 5:
				printf("Call returned successfully with bad/nonexistent input\n");
				break;
				
		}
	}
	
}

int test_play_outpost(struct gameState *post, int handPos){
	
	printf("Beginning Card Test 4...\n");
	//copy current gamestate into pre
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));
	
	play_outpost(post, handPos);
	//test that outpost flag was set
	int x;
	if((post->outpostPlayed != pre.outpostPlayed) && post->outpostPlayed == 1)
		x = 0;
	else
		x = 1;
	
	asserttrue(0, x, 1);
	
	//test that card was removed from hand and discarded
	
	int y;
	if((post->handCount[post->whoseTurn] == (pre.handCount[pre.whoseTurn] - 1)) && (post->playedCardCount == (pre.playedCardCount + 1)))
		y = 0;
	else
		y = 1;
	
	asserttrue(0, y, 2);
	
	//test that other players' decks/hands/discard counts are not affected by function call
	
	int otherPlayersFlag = 0;
	int i;
	
	for(i = 0; i < post->numPlayers; i++){
		if(i == post->whoseTurn){}
			
		else
			if(post->deckCount[i] != pre.deckCount[i])
				otherPlayersFlag++;
			else if(post->handCount[i] != pre.handCount[i])
				otherPlayersFlag++;
			else if(post->discardCount[i] != pre.discardCount[i])
				otherPlayersFlag++;
	}
	
	asserttrue(0, otherPlayersFlag, 3);
	
	//Test that victory card pile is unchanged
	int n;
	if(post->supplyCount[estate] != pre.supplyCount[estate])
		n = 1;
	else if(post->supplyCount[duchy] != pre.supplyCount[duchy])
		n = 1;
	else if(post->supplyCount[province] != pre.supplyCount[province])
		n = 1;
	else
		n = 0;
	asserttrue(0, n, 4);
	
	//test with bad input (nonexistent handPos)
	int q;
	q = play_outpost(post, -100);
	if(q == 0)
		q = 1;
	else
		q = 0;
	
	asserttrue(0, q, 5);
	
	
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
	G.outpostPlayed = 0;
	
	test_play_outpost(&G, handPos);
	
	return 0;
}
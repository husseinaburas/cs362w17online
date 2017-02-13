//this is the unit test for play_adventurer

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int passFlag = 0;

void asserttrue(int a, int b, int testcase){
	
	if(a == b)
		printf("TEST PASSED.\n");
	
	else{
		printf("TEST FAILED. ");
		passFlag++;
		switch(testcase){
				
				case 1:
					printf("Player did not receive exactly two treasure cards\n");
					break;
				
				case 2:
					printf("Player's hand did not increase by exactly two\n");
					break;
					
				case 3:
					printf("Incorrect number of cards taken from deck and/or added to hand/discard pile\n");
					break;
					
				case 4:
					printf("Other player's deck/hand/discard pile was affected\n");
					break;
					
				case 5:
					printf("Victory card pile was affected\n");
					break;
		}
		
	}
}

int test_play_adventurer(struct gameState* post){
	
	printf("Beginning Card Test 3...\n");
	//copy current gamestate into pre
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));
	int player = post->whoseTurn;
	
	//test that player received two treasure cards
	play_adventurer(post);
	int x;
	if((post->hand[player][post->handCount[player] - 1] == (copper || silver || gold)) && (post->hand[player][post->handCount[player] - 2] == (copper || silver || gold)))
		x = 0;
	else
		x = 1;
	
	asserttrue(0, x, 1);
	
	//test that player only has two more cards in hand than before card was played (i.e. that all non-treasure cards drawn were discarded)
	int y;
	if(post->handCount[player] - pre.handCount[player] == 2)
		y = 0;
	else
		y = 1;
	
	asserttrue(0, y, 2);
	
	//test that there are as many more cards in the hand and discard pile as there are fewer cards in the deck
	int handNum;
	int discardNum;
	int totalNum;
	handNum = (post->handCount[player] - pre.handCount[player]);
	discardNum = (post->discardCount[player] - pre.discardCount[player]);
	totalNum = handNum + discardNum;
	int t;
	if((pre.deckCount[player] - post->deckCount[player]) == totalNum)
		t = 0;
	else
		t = 1;
	
	asserttrue(0, t, 3);
	
	//test that other players' deck/hand/discard counts are unchanged
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
	
	asserttrue(0, otherPlayersFlag, 4);
	
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
	asserttrue(0, n, 5);
	
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
	int player = G.whoseTurn;
	
	int i;
	for(i = 0; i < G.numPlayers; i++){
		G.deckCount[i] = 20;
		G.discardCount[i] = 10;
		G.handCount[i] = 5;

	}
	
	G.handCount[player] = 5;
	G.deckCount[player] = 10;
	G.discardCount[player] = 4;
	
	test_play_adventurer(&G);
	
	return 0;
}
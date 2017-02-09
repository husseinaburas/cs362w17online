//this is the unit test for play_great_hall

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
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
				printf("Player did not receive exactly one card\n");
				break;
				
			case 2:
				printf("New card was not drawn and/or added to hand. NOTE: May not be failure if great hall was last card in hand and drawn card was also great hall\n");
				break;			
			
			case 3:
				printf("Number of actions was not increased by exactly one\n");
				break;
				
			case 4:
				printf("Incorrect number of cards were drawn from the deck\n");
				break;
				
			case 5:
				printf("Great Hall card was not discarded and/or was not added to discard pile\n");
				break;
				
			case 6:
				printf("Hand count of other player(s) was affected\n");
				break;
				
			case 7:
				printf("Victory card pile was affected\n");
				break;
				
			case 8:
				printf("Kingdom card pile was affected\n");
				break;
				
			case 9:
				printf("Function returned successfully despite bad/nonexistent input\n");
				break;
			
		}
		
	}
	
}

int test_play_great_hall(struct gameState* post, int handPos){
	
	//copy over current gamestate to pre
	struct gameState pre;
	memcpy(&pre, post, sizeof struct(gameState));
	int player = post->whoseTurn;
	
	//test that player has same number of cards in hand after call (received one, discarded one)
	play_great_hall(post, handPos);
	int x;
	if(post->handCount[player] == pre.handCount[player])
		x = 0;
	else
		x = 1;
	
	asserttrue(0, x, 1);
	
	//test that new card is in hand (i.e. that something happened despite the matching hand sizes. NOTE: It is is possible the drawn card is the same)
	int p;
	if(post->hand[player][handCount - 1] == pre.hand[player][handCount - 1])
		p = 1;
	else
		p = 0;
	
	asserttrue(0, p, 2);
		
	
	//test that numActions is increased by one
	int u;
	if(post->numActions == (pre.numActions + 1))
		u = 0;
	else
		u = 1;
	
	asserttrue(0, u, 3);
	
	//test that deck has one fewer card
	
	int r;
	r = (pre.deckCount[player] - post->deckCount[player]);
	asserttrue(1, r, 4);
	
	//test that card was discarded/discard pile has one more card in it
	int y;
	if((post->playedCards[state->playedCardCount] == great_hall) && (post->playedCardCount == (pre.playedCardCount + 1)))
		y = 0;
	else
		y = 1;
	
	asserttrue(0, y, 5);
	
	//test that no other players' handcounts were affected
	int handCountFlag = 0;
	int i;
	for(i = 0; i < post->numPlayers; i++){
		if(i == 1)
		
		else{
			if(post->handCount[i] == pre.handCount[i])
			
			else
				handCountFlag++;
		}
		
	}
	
	asserttrue(0, handCountFlag, 6);
	
	//Test that after call, victory and kingdom card piles are unchanged
	int n;
	if(post->supplyCount[estate] != pre.supplyCount[estate])
		n = 1;
	else if(post->supplyCount[duchy] != pre.supplyCount[duchy])
		n = 1;
	else if(post->supplyCount[province] != pre.supplyCount[province])
		n = 1;
	else
		n = 0;
	asserttrue(0, n, 7);
	
	int m;
	int z = 0;
	for (m = 0; m < 10; m++){
		if(post->kingdomCards[m] != pre.kingdomCards[m])
			z++;
		else
		
	}
	asserttrue(0, z, 8);
	
	//test using bad input
	int q;
	q = play_great_hall(post, -100);
	assert(1, 1, 9);
	
	if(passFlag == 0)
		printf("ALL TESTS PASSED.\n");
	
	return 0;
}

int main(){
	
	struct gameState G;
	
	int numPlayers = 4;
	int k[10] = {adventurer, embargo, village, minion, outpost, cutpurse, great_hall, tribute, smithy, council_room};
	int seed = 1000;
	
	
	initializeGame(numPlayers, k, seed, &G);
	G.whoseTurn = 1;
	G.numActions = 1;
	int currentPlayer = G.whoseTurn;
	int deckSize = 20;
	G.handCount[currentPlayer] = 5;
	G.handCount[0] = 4;
	G.handCount[2] = 4;
	G.handCount[3] = 4;
	G.playedCardCount = 3;
	G.playedCard[0] = cutpurse;
	G.playedCard[1] = cutpurse;
	G.playedCard[2] = cutpurse;
	
	G.hand[currentPlayer][2] = great_hall;
	int handPos = 2;
	
	int j;
	for(j = 0; j < G.numPlayers; j++){
		G.deckCount[j] = deckSize;
	}
	
	test_play_great_hall(&G, handPos);
	
	
	return 0;
}
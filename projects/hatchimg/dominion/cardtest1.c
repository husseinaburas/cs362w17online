//this is the unit test for play_smithy

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

int passFlag = 0;

void asserttrue(int a, int b, int testcase){
	
	if(a == b)
		printf("TEST PASS.");
	
	else{
		printf("TEST FAIL. ");
		passFlag++;
		switch(testcase){
		
				
			case 1:
				printf("Player did not receive correct number of cards.\n");
				break;
				
			case 2:
				printf("Deck does not have three fewer cards\n");
				break;
				
			case 3:
				printf("Smithy card was notsuccessfully added to the discard pile\n");
				break;
			
			case 4:
				printf("Other player(s) handcount was affected\n");
				break;
				
			case 5:
				printf("Victory card pile was affected\n");
				break;
				
			case 6:
				printf("Kingdom card pile was affected\n");
				break;
			
			case 7:
				printf("Function returned successfully with bad input of nonexistent handPos\n");
				break;
			
		}
		
	}
	
}

int testPlay_smithy(struct gameState* post, int handPos){
	
	//copy current gamestate into pre, get current player
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));
	int player = post->whoseTurn;
	
	//test that player has two more cards in hand (drew three, but discarded one to play smithy)
	play_smithy(post, handPos);
	int x;
	x = (post->handCount[player] - pre.handCount[player]);
	asserttrue(2, x, 1);
	
	//test that deck has three fewer cards
	int u;
	u = (pre.deckCount[player] - post->deckCount[player]);
	asserttrue(3, u, 2);
	
	//test that smithy card was added to discard pile and that discard pile has more card in it
	int y;
	if((post->playedCards[state->playedCardCount] == smithy) && (post->playedCardCount == (pre.playedCardCount + 1)))
		y = 0;
	else
		y = 1;
	
	asserttrue(0, y, 3);
			
	//test that other players' handcounts were not affected
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
	
	asserttrue(0, handCountFlag, 4);
	
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
	asserttrue(0, n, 5);
	
	int m;
	int z = 0;
	for (m = 0; m < 10; m++){
		if(post->kingdomCards[m] != pre.kingdomCards[m])
			z++;
		else
		
	}
	asserttrue(0, z, 6);
	
	//test with bad input
	int q;
	q = play_smithy(post, -100);
	assert(1, 1, 7);
	
	if(passFlag == 0)
		printf("ALL TESTS PASSED.\n");
	
	return 0;
}

int main(){
	
	//have player with smithy in hand at position handPos
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
	
	G.hand[currentPlayer][2] = smithy;
	int handPos = 2;
	
	int j;
	for(j = 0; j < G.numPlayers; j++){
		G.deckCount[j] = deckSize;
	}
	test_play_great_hall(&G, handPos);
	
	return 0;
	
}
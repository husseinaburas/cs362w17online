//this is the unit test for scorefor()
	
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "rngs.h"

int passFlag = 0;

void asserttrue(int a, int b, int testcase){
	
	if(a == b)
		printf("TEST PASS\n");
	else{
		printf("TEST FAIL. ");
		passFlag++;
		switch(testcase):
			
			case 1:
				printf("Call returned a value other than 0 for a nonexistent player\n");
				break;
				
			case 2:
				printf("Call did not return correct score\n");
				break;
				
			case 3:
				printf("Score was not reset at start of scoreFor function, resulted in incorrect total\n");
				break;
				
			case 4:
				printf("Function did not return correct total when score was negative\n");
				break;
			
			case 5:
				printf("Gamestate was changed by the call\n");
				break;
		
	}
	
}

int testScoreFor(int player, struct gameState* post){
	
	//Copy current gamestate into pre
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

	//test with faulty/nonexistent input for player
	int x;
	x = scoreFor(-100, post);
	asserttrue(0, x, 1);
	
	//basic test to make sure score is correct under normal conditions
	int y;
	y = scoreFor(player, post);
	asserttrue(19, y, 2);
	
	//try with score set > 0 beforehand to make sure it's being reset in function
	int z;
	post->score = 10;
	z = scoreFor(player, post);
	asserttrue(19, z, 3);
	post->score = pre.score;
	
	//test with negative score by populating player's hand, discard, and deck with all curse cards
	
	int i;
	for(i = 0; i < post->handCount[player]; i++){
		post->hand[player][i] = curse;
	}
	
	for(i = 0; i < post->discardCount[player]; i++){
		post->discard[player][i] = curse;
	}
	
	for(i = 0; i < post->deckCount[player]; i++){
		post->deck[player][i] = curse;
	}
	
	int u;
	u = scoreFor(player, post);
	asserttrue (-19, u, 4);
	
	//restore original hand/discard/deck cards
	for(i = 0; i < post->handCount[player]; i++){
		post->hand[player][i] = estate;
	}
	
	for(i = 0; i < post->discardCount[player]; i++){
		post->discard[player][i] = estate;
	}
	
	for(i = 0; i < post->deckCount[player]; i++){
		post->deck[player][i] = estate;
	}
	
	//test that gamestate is identical post call. This test checks for all changes
	//Among other things, it checks that players' decks/hands/discards were not affected
	//and test that victory/kingdom card piles not affected
	
	scoreFor(player, post);
	int q;
	q = memcmp(&pre, post, sizeof(struct gameState));
	asserttrue(0, q, 5);
	
	
	if(passFlag == 0)
		printf("ALL TESTS SUCCESSFUL");
	
	return 0;
}

int main(){
	
	struct gameState G;
	
	int k[10] = {adventurer, embargo, village, minion, outpost, cutpurse, great_hall, tribute, smithy, council_room};
	int seed = 1000;
	int numPlayers = 4;
	
	
	initializeGame(numPlayers, k, seed, &G);
	
	G.whoseTurn = 1;
	int player = G.whoseTurn;
	G.score = 0;
	
	//player will have five cards in hand, 10 in deck, four in discard. All estate, so score should be 19 barring changes in test function
	G.handCount[player] = 5;
	G.deckCount[player] = 10;
	G.discardCount[player] = 4;
	
	int i;
	for(i = 0; i < G.handCount[player]; i++){
		G.hand[player][i] = estate;
	}
	
	for(i = 0; i < G.discardCount[player]; i++){
		G.discard[player][i] = estate;
	}
	
	for(i = 0; i < G.deckCount[player]; i++){
		G.deck[player][i] = estate;
	}
	
	testScoreFor(player, &G);
	return 0;
}


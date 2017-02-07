//This is the unit test for shuffle()

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int passFlag = 0;

void asserttrue(int a, int b, int testCase){

	if(a == b){

		printf("TEST PASS\n");
	}
	else{
		printf("TEST FAIL. ");
		passFlag++;
		switch(testCase){
			case 1:
				printf("Deck size was changed or did not shuffle\n");
				break;
			case 2:
				printf("Shuffle returned successfully despite bad deckcount\n");
				break;
			case 3:
				printf("One or more of the other players' decks were affected by shuffle\n");
				break;
			case 4:
				printf("Shuffle returned successfully with bad input\n");
				break;
		}
	}


}
int checkShuffle(int player, struct gameState *post){

	//Save current gamestate in pre
	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));


	//test that deck is same size and actually shuffled, function worked as intended
	shuffle(player, post);
	int diffFlag = 0;
	if(post->deckCount[player] == pre.deckCount[player]){
		int i;
		for(i = 0; i < post->deckCount[player]; i++){
			if(post->deck[player][i] != pre.deck[player][i])
				diffFlag++;

		}
	}
	else
		diffFlag++;

	asserttrue(1, diffFlag, 1);

	//test return with bad deckcount
	int x;
	post->deckCount[player] = 0;
	x = shuffle(player, post);
	asserttrue(-1, x, 2);
	post->deckCount[player] = pre.deckCount[player];

	//test that other player decks are the same (count, order) post shuffle
	shuffle(player, post);
	int i;
	int j;
	int deckFlag = 0;
	for(i = 0; i < post->numPlayers; i++){
		if(post->deckCount[i] != pre.deckCount[i])
			deckFlag++;
		for(j=0; j < post->deckCount[i]; j++){
			if(post->deck[i][j] != pre.deck[i][j])
				deckFlag++;

		}

	}
	asserttrue(0, deckFlag, 3);

	//test shuffling with bad input values
	int badInput = 0;
	badInput = shuffle(-100, post);
	asserttrue(-1, badInput, 4);

	if(passFlag == 0)
		printf("ALL TESTS SUCCESSFUL\n");
	
	return 0;
}

int main(){

	struct gameState G;
	G.numPlayers = 4;
	G.whoseTurn = 1;
	int deckSize = 20;

	int i;
	int j;

//initialize four players' decks, each of size 20 with four different types of cards in them

	for(i = 0; i < G.numPlayers; i++){
		G.deckCount[i] = deckSize;
		for(j = 0; j < 5; j++){ 
			G.deck[i][j] = smithy;
		}
		for(j = 5; j < 10; j++){ 
			G.deck[i][j] = adventurer;
		}
		for(j = 10; j < 15; j++){ 
			G.deck[i][j] = estate;
		}
		for(j = 15; j < 20; j++){ 
			G.deck[i][j] = copper;
		}

	}

	checkShuffle(G.whoseTurn, &G);

	return 0;
}

//this is the unit test for buycard()

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int passFlag = 0;

int asserttrue(int a, int b, int testCase){

	if(a == b)
		printf("TEST PASS.\n");
	else{
		printf("TEST FAIL. ");
		passFlag++;
		switch(testCase){
			case 1:
				printf("buyCard returned successfully with nonexistent card index\n");
				break;
			case 2:
				printf("Call failed with bad input, but gamestate was altered\n");
				break;
			case 3:
				printf("buyCard did not return -1 with 0 buys\n");
				break;
			case 4:
				printf("buyCard did not return -1 with 0 of card type remaining\n");
				break;
			case 5:
				printf("buyCard did not return -1 when try to buy card that was too expensive\n");
				break;
			case 6:
				printf("Player does not have one more card after buy\n");
				break;
			case 7:
				printf("Player did not have correct number of coins deducted after buy\n");
				break;
			case 8:
				printf("Player did not have correct card added to discard\n");
				break;
			case 9:
				printf("Incorrect number of buys left after call\n");
				break;
			case 10:
				printf("Discard count of player who just bought card did not increase by one\n");
				break;
			case 11:
				printf("Discard count changed for player other than the one who bought card\n");
				break;
			case 12:
				printf("Incorrect number of supply remaining post call\n");
				break;
			case 13:
				printf("Victory card pile was affected\n");
				break;
			case 14:
				printf("Kingdom card pile was affected\n");
				break;

		}
	}

	return 0;
}

int checkBuyCard(int supplyPos, struct gameState *post){

	//Save current gamestate in pre
	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));
	
	//get player turn
	int player = post->whoseTurn;
	
	//Test call with bad input
	int r;
	r=buyCard(-100, post);
	
	asserttrue(-1, r, 1);
	//ensure that gamestate was unchanged in event of failed call
	if(r != 0){
		int u;
		u=memcmp(&pre, post, sizeof(struct gameState));
		asserttrue(0, u, 2);
	}
			
	//Test buying with no buys
	post->numBuys = 0;
	int x;
	x = buyCard(supplyPos, post);
	asserttrue(-1, x, 3);
	//reset numBuys before performing next test
	post->numBuys = pre.numBuys;


	//Test buying with no supply left
	post->supplyCount[supplyPos] = 0;
	int y;
	y = buyCard(supplyPos, post);
	asserttrue(-1, y, 4);
	//reset supply total before performing next test
	post->supplyCount[supplyPos] = pre.supplyCount[supplyPos];


	//Test buying a card that's too expensive (smithy)
	post->coins = 3;
	int q;
	q = buyCard(supplyPos, post);
	asserttrue(-1, q, 5);
	//set coins so next call will pass
	post->coins = 5;

	//Standard call that should return correctly so we can test results
	buyCard(supplyPos, post);


	//Test that after call, player has one more card, 4 fewer coins (since we're buying a smithy card), card in discard, and correct # of buys
	asserttrue((pre.discardCount[player]+1), post->discardCount[player], 6);
	asserttrue(1, post->coins, 7);
	asserttrue(post->discard[player][post->discardCount[player]], supplyPos, 8);
	asserttrue(post->numBuys, (pre.numBuys-1), 9);


	//Test that after call, all other player discard numbers are the same
	int i;
	for(i = 0; i < pre.numPlayers; i++){
		if(i == post->whoseTurn)
			asserttrue((pre.discardCount[i]+1), post->discardCount[i], 10);
		else{
			asserttrue(pre.discardCount[i], post->discardCount[i], 11);
		}
	}

	//Test that after call, supply count of card bought is one fewer

	asserttrue(post->supplyCount[supplyPos], (pre.supplyCount[supplyPos] - 1), 12);
	
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
	asserttrue(0, n, 13);
	
	int m;
	int z = 0;
	for (m = 0; m < 10; m++){
		if(post->kingdomCards[m] != pre.kingdomCards[m])
			z++;
		else
		
	}
	asserttrue(0, z, 14);

	if(passFlag == 0)
		printf("ALL TESTS OK \n");
	
	return 0;

}

int main(){
	

	struct gameState G;

	int numPlayers = 4;
	
	int k[10] = {adventurer, embargo, village, minion, outpost, cutpurse, great_hall, tribute, smithy, council_room};
	int seed = 1000;
	
	initializeGame(numPlayers, k, seed, &G);

	G.supplyCount[smithy] = 5;
	G.coins = 5;
	G.numBuys = 1;
	G.whoseTurn = 1;
	
	//set everyone's deck, discard, and handcounts to 20, 10, and 5, respectively
	int i;
	for(i = 0; i < G.numPlayers; i++){
		G.deckCount[i] = 20;
		G.discardCount[i] = 10;
		G.handCount[i] = 5;

	}
	checkBuyCard(smithy, &G);
	return 0;
}

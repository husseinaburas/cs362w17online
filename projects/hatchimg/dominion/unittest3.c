//this is the unit test for updatecoins()

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int passFlag = 0;

void asserttrue(int a, int b, int testcase){
	
	if(a == b)
		printf("TEST PASS");
	
	else{
		printf("TEST FAIL. ");
		passFlag++;
			switch(testcase){
		
				case 1:
					printf("Call did not fail with bad input\n");
					break;
				
				case 2:
					printf("Call did not update coins properly when coin total started at zero\n");
					break;
					
				case 3:
					printf("Call did not update coins properly when coin total started at greater than zero\n");
					break;
				
				case 4:
					printf("Call did not update coins properly when there was a bonus\n");
					break;
				
				case 5:
					printf("Player had no coins in hand, but gamestate was still changed\n");
					break;
				
				case 6:
					printf("Coins did not update properly with all copper in hand\n");
					break;
				
				case 7:
					printf("Coins did not update properly with all silver in hand\n");					
					break;
					
				case 8:
					printf("Coins did not update properly with all gold in hand\n");
					break;

				case 9:
					printf("Coins did not update properly with copper and silver in hand\n");					
					break;
					
				case 10:
					printf("Coins did not update properly with silver and gold in hand\n");					
					break;
					
				case 11:
					printf("Coins did not update properly with copper and gold in hand\n");					
					break;
				
				case 12:
					printf("Call changed some other aspect of gamestate besides coins\n");
					break;
		
		}
	
	}
}

int testUpdateCoins(int player, struct gameState* post, int bonus){
	
	//Save current gamestate in pre
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));
	
	//Test with bad input (nonexistent player, impossible bonus)
	int x;
	x = updateCoins(-1, post, -1);
	asserttrue(-1, x, 1);
	
	//Test with coins at 0 and at greater than zero, check that they were updated correctly
	post->coins = 0;
	updateCoins(player, post, 0);
	asserttrue((pre.coins + 6), post->coins, 2);
	
	post->coins = pre.coins;
	post->coins = 1;
	updateCoins(player, post, 0);
	asserttrue((pre.coins + 7), post->coins, 3);
	
	//Reset coin value, test successful call with bonus (calls without bonus were just perfomed)
	post->coins = pre.coins;
	updateCoins(player, post, 5);
	asserttrue((pre.coins + 11), post->coins, 4);
	
	//Test with no treasure in hand (make sure that after call, nothing about gamestate has changed since coins should be unaffected)
	post->coins = pre.coins;
	
	int i;
	for(i = 0; i < post->handCount[player]; i++){
		
			post->hand[player][i] = smithy;
	}
	
	updateCoins(player, post, 0);
	
	for(i = 0; i < post->handCount[player]; i++){
		
			post->hand[player][i] = pre.hand[player][i];
	}
	
	int q;
	q = memcmp(&pre, post, sizeof(struct gameState));
	asserttrue(0, q, 5);
	
	//Test with mixes of copper, silver, gold (all of one, combinations of two; mix of all three has been tested previously)
	post->hand[player][0] = copper;
	post->hand[player][1] = copper;
	post->hand[player][2] = copper;
	
	updateCoins(player, post, 0);
	asserttrue((pre.coins)+3, post->coins, 6);
	post->coins = pre.coins;
	
	post->hand[player][0] = silver;
	post->hand[player][1] = silver;
	post->hand[player][2] = silver;
	
	updateCoins(player, post, 0);
	asserttrue((pre.coins)+6, post->coins, 7);
	post->coins = pre.coins;
	
	post->hand[player][0] = gold;
	post->hand[player][1] = gold;
	post->hand[player][2] = gold;
	
	updateCoins(player, post, 0);
	asserttrue((pre.coins)+9, post->coins, 8);
	post->coins = pre.coins;
	
	post->hand[player][0] = copper;
	post->hand[player][1] = silver;
	post->hand[player][2] = silver;
	
	updateCoins(player, post, 0);
	asserttrue((pre.coins)+5, post->coins, 9);
	post->coins = pre.coins;
	
	post->hand[player][0] = gold;
	post->hand[player][1] = silver;
	post->hand[player][2] = silver;
	
	updateCoins(player, post, 0);
	asserttrue((pre.coins)+7, post->coins, 10);
	post->coins = pre.coins;
	
	post->hand[player][0] = copper;
	post->hand[player][1] = gold;
	post->hand[player][2] = gold;
	
	updateCoins(player, post, 0);
	asserttrue((pre.coins)+7, post->coins, 11);
	post->coins = pre.coins;
	
	post->hand[player][0] = pre.hand[player][0];
	post->hand[player][1] = pre.hand[player][0];
	post->hand[player][2] = pre.hand[player][0];
	
	//Check no other aspect of gamestate affected after by changing coins back to old amount and then comparing gamestates
	//This covers the check for changes in victory and kingdom card piles
	
	updateCoins(player, post, 0);
	post->coins = pre.coins;
	int y;
	y = memcmp(&pre, post, sizeof(struct gameState));
	asserttrue(0, y, 12);
	
	if(passFlag == 0)
		printf("ALL TESTS SUCCESSFUL\n");
	
	return 0;
}

int main(){
	
	struct gameState G;
	int numPlayers = 4;
	
	
	
	int k[10] = {adventurer, embargo, village, minion, outpost, cutpurse, great_hall, tribute, smithy, council_room};
	int seed = 1000;
	
	initializeGame(numPlayers, k, seed, &G);
	G.coins = 0;
	G.whoseTurn = 1;
	int player = G.whoseTurn;
	G.handCount[player] = 3;
	G.hand[player][0] = copper;
	G.hand[player][1] = silver;
	G.hand[player][2] = gold;

	//Initial gamestate sent to test function has three cards in player hand, coin total in hand is six. Gamestate coin total is zero, player one's turn. No bonus.
	testUpdateCoins(player, &G, 0);
	
	return 0;
}
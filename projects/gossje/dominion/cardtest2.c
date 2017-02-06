#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#define TRUE 0
#define FALSE 1


int test_feast(struct gameState *game){
	
	printf("Testing playFeast()\n");
	int tests_passed = 0;
	struct gameState copy;
	memcpy(&copy, game, sizeof(struct gameState)); //make copy of initial game state 
	
	printf("Testing feast on too-expensive card\n");
	int t1 = playFeast(game, adventurer); //adventurer too expensive. Should remain in supply. Shouldn't be in discard pile or hand of player. 
	
	if (t1 != 0){
		printf("Function returned incorrect value\n");
		tests_passed = 1;
	}
	
	if (game->supplyCount[adventurer] == 0){
		printf("Too-expensive card inappropriately gained by Feast\n");
		tests_passed = 1;	
	}
	
	if (game->discardCount[0] != 0){
		printf("Cards were inappropriately added to the discard pile\n");
		tests_passed = 1;	
	}
	
	
	memcpy(game, &copy, sizeof(struct gameState)); //return game state to initial state 
	
	printf("Testing feast on empty pile\n");
	int t2 = playFeast(game, gardens);
	
	if (game->supplyCount[gardens] != 0){
		printf("Empty supply pile inappropriately manipulated by Feast\n");
		tests_passed = 1;	
	}
	
	if (game->discardCount[0] != 0){
		printf("Cards were inappropriately added to the discard pile\n");
		tests_passed = 1;	
	}
	
	memcpy(game, &copy, sizeof(struct gameState)); //return game state to initial state 
	printf("Testing feast on appropriate supply pile\n");
	int t3 = playFeast(game, smithy);
	
	if (game->supplyCount[smithy] != 0){
		printf("Supply pile not adjusted appropriately by Feast\n");
		tests_passed = 1;	
	}
	
	if (game->discardCount[0] != 1){
		printf("Gained card not appropriately added to the discard pile\n");
		tests_passed = 1;	
	}
	
	if (tests_passed == 0){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

int main(){
	struct gameState game;
	game.whoseTurn = 0;
	game.numActions = 1;
	game.handCount[0] = 2;
	game.hand[0][0] = feast;
	game.hand[0][1] = copper; 
	game.playedCardCount = 0;
	game.supplyCount[smithy] = 1; 
	game.supplyCount[adventurer] = 1; 
	game.supplyCount[gardens] = 0;
	game.discardCount[0] = 0;
	int a = test_feast(&game);
	if (a == TRUE){
		printf("playFeast() passed all current tests\n");
	}
	else{
		printf("Bugs discovered in playFeast() card\n");
	}
	
	return 0;
}
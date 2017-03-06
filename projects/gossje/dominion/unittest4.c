//updateCoins test 

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#define TRUE 0
#define FALSE 1

int testUpdateCoins(struct gameState *game){
	int tests_passed = 0;
	struct gameState copy;
	memcpy(&copy, game, sizeof(struct gameState)); //make copy of initial game state 
	
	int player = 0;
	game->handCount[0] = 3; //player has 2 cards in hand 
	game->hand[0][0] = smithy; 
	game->hand[0][1] = copper; 
	game->hand[0][2] = copper; 
	//player hand value is 2;
	int bonus = 0; //bonus is value 0
	
	printf("Testing updateCoins with copper and non-treasure in hand\n");
	int t1 = updateCoins(player, game, bonus); 
	
	if (t1 != 0){
		printf("Function returned wrong value\n");
		tests_passed = 1;
	}
	
	if (game->coins != 2){
		printf("Function did not properly count copper\n");
		tests_passed = 1;
	}	
	
	if (game->handCount[0] != 3){
		printf("Hand altered by updateCoins function when it shouldn't have been\n");
		tests_passed = 1;
	}
	
	
	memcpy(game, &copy, sizeof(struct gameState)); //return game to initial state 
	game->handCount[0] = 3; //player has 2 cards in hand 
	game->hand[0][0] = smithy; 
	game->hand[0][1] = silver; 
	game->hand[0][2] = silver; 
	
	printf("Testing updateCoins with silver and non-treasure in hand\n");
	int t2 = updateCoins(player, game, bonus); 
	
	if (t2 != 0){
		printf("Function returned wrong value\n");
		tests_passed = 1;
	}
	
	if (game->coins != 4){
		printf("Function did not properly count silver\n");
		tests_passed = 1;
	}	
	
	memcpy(game, &copy, sizeof(struct gameState)); //return game to initial state 
	game->handCount[0] = 3; //player has 2 cards in hand 
	game->hand[0][0] = smithy; 
	game->hand[0][1] = gold; 
	game->hand[0][2] = gold; 
	printf("Testing updateCoins with gold and non-treasure in hand\n");
	int t3 = updateCoins(player, game, bonus); 
	
	if (t3 != 0){
		printf("Function returned wrong value\n");
		tests_passed = 1;
	}
	
	if (game->coins != 6){
		printf("Function did not properly count gold\n");
		tests_passed = 1;
	}	
	
	memcpy(game, &copy, sizeof(struct gameState)); //return game to initial state 
	game->handCount[0] = 4; //player has 4 cards in hand 
	game->hand[0][0] = smithy; 
	game->hand[0][1] = copper; 
	game->hand[0][2] = silver; 
	game->hand[0][3] = gold;
	printf("Testing updateCoins with copper, silver, gold and non-treasure in hand\n");
	int t4 = updateCoins(player, game, bonus); 
	
	if (t4 != 0){
		printf("Function returned wrong value\n");
		tests_passed = 1;
	}
	
	if (game->coins != 6){
		printf("Function did not properly count mixed treasures\n");
		tests_passed = 1;
	}	
	
	memcpy(game, &copy, sizeof(struct gameState)); //return game to initial state 
	game->handCount[0] = 2; //player has 2 cards in hand
	game->hand[0][0] = smithy; 
	game->hand[0][1] = smithy; 
	bonus = 10; 
	printf("Testing updateCoins with no treasures and a bonus of 10\n");
	int t5 = updateCoins(player, game, bonus);
	if (t5 != 0){
		printf("Function returned wrong value\n");
		tests_passed = 1;
	}
	
	if (game->coins != 10){
		printf("Function did not properly count bonus\n");
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
	int a = testUpdateCoins(&game);
	if (a == TRUE){
		printf("All tests for updateCoins passed.\n");
		
	}
	
	else{
		printf("updateCoins not functioning properly.\n");
	}
	
	return 0;
	
}
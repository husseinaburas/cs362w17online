
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#define TRUE 0
#define FALSE 1

int test_func(struct gameState *game){
	printf("\n--- TESTING updateCoins() ---\n");
	
	//initialize variables
	struct gameState dummy;         
	int passed = 0;
	int player = 0;
	memcpy(&dummy, game, sizeof(struct gameState)); //create dummy of initial game state
	
	game->handCount[0] = 3; //player has 2 cards in hand 
	game->hand[0][0] = adventurer;             
	game->hand[0][1] = copper;             
	game->hand[0][2] = copper; 
	
	int bonus = 0; //bonus is value 0
	
	printf("Testing updateCoins() with copper and non-treasure in hand\n");
	int test1 = updateCoins(player, game, bonus); 
	
	if (test1 != 0){
		printf("Function returned wrong value\n");
		passed = 1;
	}
	
	if (game->coins != 2){
		printf("Function did not properly count copper\n");
		passed = 1;
	}	
	
	if (game->handCount[0] != 3){
		printf("Error -- hand altered by updateCoins() function when it shouldn't have been\n");
		passed = 1;
	}
	
	
	memcpy(game, &dummy, sizeof(struct gameState)); //return game to initial state 
	game->handCount[0] = 3; //player has 2 cards in hand 
	game->hand[0][0] = adventurer; 
	game->hand[0][1] = silver; 
	game->hand[0][2] = silver; 
	
	printf("Testing updateCoins() with silver and non-treasure in hand\n");
	int test2 = updateCoins(player, game, bonus); 
	
	if (test2 != 0){
		printf("Function returned wrong value\n");
		passed = 1;
	}
	
	if (game->coins != 4){
		printf("Function did not properly count silver\n");
		passed = 1;
	}	
	
	memcpy(game, &dummy, sizeof(struct gameState)); //return game to initial state 
	game->handCount[0] = 3; //player has 2 cards in hand 
	game->hand[0][0] = adventurer; 
	game->hand[0][1] = gold; 
	game->hand[0][2] = gold; 
	printf("Testing updateCoins() with gold and non-treasure in hand\n");
	int test3 = updateCoins(player, game, bonus); 
	
	if (test3 != 0){
		printf("Function returned wrong value\n");
		passed = 1;
	}
	
	if (game->coins != 6){
		printf("Function did not properly count gold\n");
		passed = 1;
	}	
	
	memcpy(game, &dummy, sizeof(struct gameState)); //return game to initial state 
	game->handCount[0] = 4; //player has 4 cards in hand 
	game->hand[0][0] = adventurer; 
	game->hand[0][1] = copper; 
	game->hand[0][2] = silver; 
	game->hand[0][3] = gold;
	printf("Testing updateCoins() with copper, silver, gold and non-treasure in hand\n");
	int test4 = updateCoins(player, game, bonus); 
	
	if (test4 != 0){
		printf("Function returned wrong value\n");
		passed = 1;
	}
	
	if (game->coins != 6){
		printf("Function did not properly count mixed treasure cards\n");
		passed = 1;
	}	
	
	memcpy(game, &dummy, sizeof(struct gameState)); //return game to initial state 
	game->handCount[0] = 2; //player has 2 cards in hand
	game->hand[0][0] = adventurer; 
	game->hand[0][1] = adventurer; 
	bonus = 7; 
	printf("Testing updateCoins() with no treasures and a bonus of 7\n");
	int test5 = updateCoins(player, game, bonus);
	if (test5 != 0){
		printf("Function returned wrong value\n");
		passed = 1;
	}
	
	if (game->coins != 7){
		printf("Function did not properly count bonus\n");
		passed = 1;
	}	
	
	if (passed == 0){
		return TRUE;
	}
	
	else{
		return FALSE; 
	}
	
}

int main(){
	struct gameState game; 
	int i = test_func(&game);
	if (i == TRUE){
		printf("All tests for updateCoins() passed.\n");
		
	}
	
	else{
		printf("updateCoins() not working properly.\n");
	}
	
	printf("\n--- END TESTING ---\n");
	return 0;
	
}

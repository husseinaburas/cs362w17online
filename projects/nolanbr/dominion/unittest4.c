#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdio.h>
#include <string.h>


int testUpdateCoins(struct gameState *game){
	int testFailed = 0;
	struct gameState copy;
	memcpy(&copy, game, sizeof(struct gameState)); //make copy of initial game state 
	
	int player = 0;
	game->handCount[0] = 3; //player has 3 cards in hand 
	game->hand[0][0] = smithy; 
	game->hand[0][1] = copper; 
	game->hand[0][2] = copper; 
	//player hand value is 2;
	int bonus = 0; //bonus is value 0
	
	printf("Testing updateCoins with copper\n");
	int t1 = updateCoins(player, game, bonus); 
	
		
	if (game->coins != 2){
		printf("Function did not properly count copper\n");
		testFailed = 1;
	}	
	
	
	
	memcpy(game, &copy, sizeof(struct gameState)); //return game to initial state 
	game->handCount[0] = 3; //player has 3 cards in hand 
	game->hand[0][0] = smithy; 
	game->hand[0][1] = silver; 
	game->hand[0][2] = silver; 
	
	printf("Testing updateCoins with silver\n");
	int t2 = updateCoins(player, game, bonus); 
	
		
	if (game->coins != 4){
		printf("Function did not properly count silver\n");
		testFailed = 1;
	}	
	
	memcpy(game, &copy, sizeof(struct gameState)); //return game to initial state 
	game->handCount[0] = 3; //player has 3 cards in hand 
	game->hand[0][0] = smithy; 
	game->hand[0][1] = gold; 
	game->hand[0][2] = gold; 
	printf("Testing updateCoins with gold\n");
	int t3 = updateCoins(player, game, bonus); 
	
	
	
	if (game->coins != 6){
		printf("Function did not properly count gold\n");
		testFailed = 1;
	}	
	
	memcpy(game, &copy, sizeof(struct gameState)); //return game to initial state 
	game->handCount[0] = 4; //player has 4 cards in hand 
	game->hand[0][0] = smithy; 
	game->hand[0][1] = copper; 
	game->hand[0][2] = silver; 
	game->hand[0][3] = gold;
	printf("Testing updateCoins with copper, silver, gold\n");
	int t4 = updateCoins(player, game, bonus); 
	
	if (t4 != 0){
		printf("Function returned wrong value\n");
		testFailed = 1;
	}
	
	if (game->coins != 6){
		printf("Function did not properly count mixed treasures\n");
		testFailed = 1;
	}	
	
	memcpy(game, &copy, sizeof(struct gameState)); //return game to initial state 
	game->handCount[0] = 2; //player has 2 cards in hand
	game->hand[0][0] = smithy; 
	game->hand[0][1] = smithy; 
	bonus = 5; 
	printf("Testing updateCoins with no coins and a bonus of 5\n");
	int t5 = updateCoins(player, game, bonus);
	if (t5 != 0){
		printf("Function returned wrong value\n");
		testFailed = 1;
	}
	
	if (game->coins != 5){
		printf("Function did not properly count bonus\n");
		testFailed = 1;
	}	
	
	if (testFailed == 0){
		return 0;
	}
	
	else{
		return 1; 
	}
	
}

memcpy(game, &copy, sizeof(struct gameState)); //return game to initial state 
	game->handCount[0] = 2; //player has 2 cards in hand
	game->hand[0][0] = copper; 
	game->hand[0][1] = silver; 
	bonus = 5; 
	printf("Testing updateCoins with no coins and a bonus of 5\n");
	int t5 = updateCoins(player, game, bonus);
	if (t5 != 0){
		printf("Function returned wrong value\n");
		testFailed = 1;
	}
	
	if (game->coins != 8){
		printf("Function did not properly count treasure and bonus\n");
		testFailed = 1;
	}	
	
	if (testFailed == 0){
		return 0;
	}
	
	else{
		return 1; 
	}
	
}

int main(){
	struct gameState game; 
	int a = testUpdateCoins(&game);
	if (a == 0){
		printf("All tests for updateCoins passed.\n");
		
	}
	
	else{
		printf("updateCoins not functioning properly.\n");
	}
	
	return 0;
	
}
//buyCard unit test

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#define TRUE 0
#define FALSE 1

int testCardBuy(struct gameState *game){
	int cases_passed = 0;
	struct gameState copy;
	memcpy(&copy, game, sizeof(struct gameState)); //make copy of initial game state 
	
	//negative testing first. Lets test buying with no buys.
	int player = game->whoseTurn; 
	int t1;
	game->numBuys = 0;
	copy.numBuys = 0;
	t1 = buyCard(feast, game);
	printf("---------------------------------------------------\n");
	printf("Test 1: Attempting to make a buy with no buys\n");
	if (t1 == -1 && memcmp(&copy, game, sizeof(struct gameState)) == 0){ //game state unchanged and function returned -1
		printf("Test passed!\n");
		cases_passed++; //cases passed should be 1 now 
	}
	
	else if (t1 != -1 || memcmp(&copy, game, sizeof(struct gameState)) != 0){ //wrong return value or game state changed
		
		if (t1 != -1){ //wrong return value 
			printf("Test failed: Function returned incorrect value\n");
		}
		
		if (memcmp(&copy, game, sizeof(struct gameState)) != 0){ //game state changed
			printf("Test failed: Game state altered when it should not have been\n");
		}
	}
	
	copy.numBuys = 1; 
	
	memcpy(game, &copy, sizeof(struct gameState)); //return gamestate to initial state
	
	
	//attempt to buy a card that is out of supply 
	printf("Test 2: Attempting to buy from an empty supply pile\n");
	int t2; 
	t2 = buyCard(gardens, game);
	if (t2 == -1 && memcmp(&copy, game, sizeof(struct gameState)) == 0){ //game state unchanged and function returned -1
		printf("Test passed!\n");
		cases_passed++; //cases passed should be 2 now 
	}
	
	else if (t2 != -1 || memcmp(&copy, game, sizeof(struct gameState)) != 0){ //wrong return value or game state changed
		
		if (t2 != -1){ //wrong return value 
			printf("Test failed: Function returned incorrect value\n");
		}
		
		if (memcmp(&copy, game, sizeof(struct gameState)) != 0){ //game state changed
			printf("Test failed: Game state altered when it should not have been\n");
			memcpy(game, &copy, sizeof(struct gameState)); //return gamestate to initial state
		}
	}
	
	
	//attempt to buy something the player cannot afford 
	int t3;
	printf("Test 3: Attempting to buy something player cannot afford\n");
	t3 = buyCard(adventurer, game); 
	if (t3 == -1 && memcmp(&copy, game, sizeof(struct gameState)) == 0){ //game state unchanged and function returned -1
		printf("Test passed!\n");
		cases_passed++; //cases passed should be 3 now 
	}
	
	else if (t3 != -1 || memcmp(&copy, game, sizeof(struct gameState)) != 0){ //wrong return value or game state changed
		
		if (t3 != -1){ //wrong return value 
			printf("Test failed: Function returned incorrect value\n");
		}
		
		if (memcmp(&copy, game, sizeof(struct gameState)) != 0){ //game state changed
			printf("Test failed: Game state altered when it should not have been\n");
			memcpy(game, &copy, sizeof(struct gameState)); //return gamestate to initial state
		}
	}
	
	//buy a card the player can afford 
	int t4;
	printf("Test 4: Attempting to buy something player can afford\n");
	t4 = buyCard(feast, game);
	int t4fail = 0;
	if (t4 != 0){
		printf("Function returned incorrect value\n");
		t4fail = 1;
	}
	if (game->coins != 0){
		printf("Coins not updated successfully after buy\n");
		t4fail = 1;
	}
	if (game->numBuys != 0){
		printf("Number of buys not properly adjusted after buy\n");
		t4fail = 1;
	}
	if (game->supplyCount[feast] != 0){
		printf("Supply pile not properly adjusted after buy\n");
		t4fail = 1;
	}
	if (game->discardCount[player] != 1){
		printf("Purchased card not properly added to discard pile\n");
		t4fail = 1;
	}
	if (t4fail == 0){
		cases_passed++; //cases passed should be 4 now 
	}
	
	
	if (cases_passed == 4){
		printf("Test passed!\n");
		return TRUE;
	}
	
	else {
		return FALSE;
	}
}

int main(){
	struct gameState game;
	game.supplyCount[adventurer] = 1; //one adventurer
	game.supplyCount[feast] = 1; //one feast 
	game.supplyCount[gardens] = 0; //no gardens
	game.coins = 4;
	game.numBuys = 1;
	game.whoseTurn = 1;
	game.numPlayers = 2;
	game.discardCount[1] = 0;
	
	int a = testCardBuy(&game);
	if (a == TRUE){
		printf("buyCard function tests passed.\n");
	}
	
	else{
		printf("buyCard is not functioning as intended. Tests failed.\n");
	}
	
	printf("---------------------------------------------------\n");
	return 0;

}
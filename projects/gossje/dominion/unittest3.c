//getWinners test

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#define TRUE 0
#define FALSE 1


int testGetWinners(struct gameState *game){
	
	int tests_passed = 0;
	struct gameState copy;
	memcpy(&copy, game, sizeof(struct gameState)); //make copy of initial game state 
	//game with 4 players, one player wins 
	game->numPlayers = 4; 
	int players[4];
	game->whoseTurn = 0; 
	//set player hands and discard counts
	game->handCount[0] = 1;
	game->handCount[1] = 1;
	game->handCount[2] = 1;
	game->handCount[3] = 1;
	game->hand[0][0] = province; 
	game->hand[1][0] = estate;
	game->hand[2][0] = smithy;
	game->hand[3][0] = curse;
	game->discardCount[0] = 0;
	game->discardCount[1] = 0;
	game->discardCount[2] = 0;
	game->discardCount[3] = 0;
	//run function
	printf("Testing getWinners with no ties and max players\n");
	int t1 = getWinners(players, game);
	
	if (t1 != 0){
		printf("Function returned incorrect value\n");
		tests_passed = 1;
	}
	
	if (players[0] != 1){
		printf("Function did not properly set winning player value to 1\n");
		tests_passed = 1;
	}
	
	int i;
	for (i = 1; i < 4; i++){
		if (players[i] >= 1){
			printf("Function improperly declared a player as a winner\n");
			tests_passed = 1;
		}
	}
	
	printf("Testing getWinners with no ties and 2 players\n");
	memcpy(game, &copy, sizeof(struct gameState)); //revert game state 
	//game with 2 players, one player wins 
	game->numPlayers = 2; 
	game->whoseTurn = 0; 
	//set player hands and discard counts
	game->handCount[0] = 1;
	game->handCount[1] = 1;
	game->hand[0][0] = estate; 
	game->hand[1][0] = province;
	game->discardCount[0] = 0;
	game->discardCount[1] = 0;
	int t2 = getWinners(players, game);
	
	if (t2 != 0){
		printf("Function returned incorrect value\n");
		tests_passed = 1;
	}
	
	if (players[1] != 1){
		printf("Function did not properly set winning player value to 1\n");
		tests_passed = 1;
	}
	
	for (i = 0; i < 4; i++){
		if (i != 1 && players[i] >= 1){
			printf("Function improperly declared a player as a winner\n");
			tests_passed = 1;
		}
	}
	
	printf("Testing getWinners with a tie and 2 players. Tie should be broken by whoever had fewer turns.\n");
	memcpy(game, &copy, sizeof(struct gameState)); //revert game state 
	game->numPlayers = 2; 
	game->whoseTurn = 0; 
	//set player hands and discard counts
	game->handCount[0] = 1;
	game->handCount[1] = 1;
	game->hand[0][0] = estate; 
	game->hand[1][0] = estate;
	game->discardCount[0] = 0;
	game->discardCount[1] = 0;
	int t3 = getWinners(players, game);
	
	if (t3 != 0){
		printf("Function returned incorrect value\n");
		tests_passed = 1;
	}
	
	if (players[1] != 1){
		printf("Function did not properly break tie\n");
		tests_passed = 1;
	}
	
	for (i = 0; i < 4; i++){
		if (i != 1 && players[i] >= 1){
			printf("Function improperly declared a player as a winner\n");
			tests_passed = 1;
		}
	}
	
	printf("Testing getWinners with a tie between 3 players. Player 2 and 3 should end with a tie.\n");
	memcpy(game, &copy, sizeof(struct gameState)); //revert game state 
	game->numPlayers = 3; 
	game->whoseTurn = 0; 
	//set player hands and discard counts
	game->handCount[0] = 1;
	game->handCount[1] = 1;
	game->handCount[2] = 1;
	game->hand[0][0] = estate; 
	game->hand[1][0] = estate;
	game->hand[2][0] = estate;
	game->discardCount[0] = 0;
	game->discardCount[1] = 0;
	game->discardCount[2] = 0;
	int t4 = getWinners(players, game);
	
	if (t4 != 0){
		printf("Function returned incorrect value\n");
		tests_passed = 1;
	}
	
	if (players[0] == 1){
		printf("Function did not properly break tie\n");
		tests_passed = 1;
	}
	
	if(players[1] != 1 && players[2] != 1){
		printf("Function did not properly declare multiple winners\n");
		tests_passed = 1;
	}
	
	if(players[3] > 0){
		printf("Function declared a non-existent player as a winner\n");
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
	int testGW = testGetWinners(&game);
	
	if (testGW == TRUE){
		printf("All tests passed\n");
	}
	
	else{
		printf("GetWinners not functioning properly\n");
	}
	
	printf("---------------------------------------------\n");

	return 0;
}

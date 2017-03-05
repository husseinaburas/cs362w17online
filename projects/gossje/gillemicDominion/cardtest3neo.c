#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#define TRUE 0
#define FALSE 1


int main(){
	struct gameState game;
	game.whoseTurn = 0;
	game.numActions = 1;
	game.handCount[0] = 1;
	game.hand[0][0] = village;
	game.deck[0][4] = copper;
	game.deck[0][3] = estate;
	game.deck[0][2] = feast;
	game.deck[0][1] = curse; 
	game.deck[0][0] = silver; 
	game.deckCount[0] = 5;
	game.playedCardCount = 0;
	//int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state) 
	int t1 = playCard(0, 0, 0, 0, &game);
	int tests_passed = 0;
	
		printf("Testing Village\n");
	
	if (t1 != 0){
		printf("Function returned incorrect value\n");
		tests_passed = 1;
	}
	
	if (game.handCount[0] != 1){ //player starts with 1 card, draws 1, discards Village 
		printf("Village did not draw the proper number of cards or was not discarded properly\n");
		tests_passed = 1;
	}
	
	if (game.numActions != 2){ //1 action to start. -1 from playing village. +2 actions. net total = 2.
		printf("Number of actions not properly adjusted by Village\n");
		tests_passed = 1;
	}
	
	if (game.deckCount[0] != 4){
		printf("Village did not draw the proper number of cards from the deck\n");
		tests_passed = 1;
	}
	
	if (game.playedCardCount != 1){
		printf("Village not properly added to discard pile\n");
		tests_passed = 1;
	}
	
	if (tests_passed != 0){
		printf("playVillage() function contains bugs. Test failed.\n");
	}
	else{
		printf("playVillage() passed all tests.\n");
	}
	
	return 0;
}

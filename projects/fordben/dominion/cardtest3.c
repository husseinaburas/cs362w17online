//Name:				cardtest3.c
//Assignment:		Assignment 3
//Author:				Benjamin Ford
//Date:					2/5/2017
//Description:		Unit test for great hall card

#include "dominion.h" 
#include "dominion_helpers.h" 
#include <string.h> 
#include <stdio.h> 
#include "rngs.h" 
#include <stdlib.h>

#define TESTCARD "Adventurer"

//places the card into the first postion in the players hand
void placeCardInHand(struct gameState *state, int player,int card, int handPos){
	
	state->hand[player][handPos] = card;
	
	return;
}

//Test if kingdom cards have changed
int testSupply(struct gameState *old, struct gameState *new){
	int i;
	
	for (i = 0; i < 10; i++){
		if(old->supplyCount[i] != new->supplyCount[i]){
			return 0;
		}
	}
	return 1;
}

int testHand(struct gameState *state, int player){
	int i = 0;
	for(i=0;i<state->handCount[player];i++){
		if(testIfTreasure(state->hand[player][i])== 0){
			return	0;
		}
	}
	return 1;
}

int testIfTreasure(int card){
	
	if(card == copper || card == silver || card == gold){
		return 1;
	}
	return 0;
}

int main(){
	struct gameState game, testGame;
	const int kCards[] =  {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, great_hall};
	const int players = 2;
	const int gameSeed = 5;
	const int handPos = 0;
	int testsPassed = 1;
	
	
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	
	//Init game
	initializeGame(players,kCards,gameSeed,&game);
	
	
	//add some gold to the players deck
	gainCard(gold,&game,1,1);
	gainCard(gold,&game,1,1);
	gainCard(gold,&game,1,1);
	gainCard(gold,&game,1,1);
	gainCard(gold,&game,1,1);
	gainCard(gold,&game,1,1);
	gainCard(gold,&game,1,1);
	gainCard(gold,&game,1,1);
	gainCard(gold,&game,1,1);
	
	//Save the game state for test
	memcpy(&testGame, &game, sizeof(struct gameState));
	
	//place village in players hand
	placeCardInHand(&game,1,adventurer,handPos);
	
	playAdventurer(1,&game);
	
	
	//test to see if hand count went up by 2/
	if(game.handCount[1] != (testGame.handCount[1]+2)){
		printf("TEST FAILED - Player did not gain 2 cards\n");
		testsPassed = 0;
	}
	
	//Test if the new cards are treasure
	if(testHand(&game,1) == 0){
		printf("TEST FAILED - Player did not gain 2 treasure cards\n");
		testsPassed = 0;
	}
	
	//Test the other players state
	//Test state changed for other player
	if(game.whoseTurn != testGame.whoseTurn){
		printf("TEST FAILED - Player turn changed\n");
		testsPassed = 0;
	}
	
	//Test other players deck
	if(game.deckCount[0] != testGame.deckCount[0] ){
		printf("TEST FAILED - Other players deck changed\n");
		testsPassed = 0;
	}
	
	//Test other players hand
	if(game.handCount[0] != testGame.handCount[0] ){
		printf("TEST FAILED - Other players hand changed\n");
		testsPassed = 0;
	}
	
	//Test other players discard count
	if(game.discardCount[0] != testGame.discardCount[0] ){
		printf("TEST FAILED - Other players discards changed\n");
		testsPassed = 0;
	}
	
	
	//Test victory card piles
	if((game.supplyCount[estate] != testGame.supplyCount[estate]) || (game.supplyCount[duchy] != testGame.supplyCount[duchy]) || (game.supplyCount[province] != testGame.supplyCount[province])){
		printf("TEST FAILED - Victory Card Piles have changed\n");
		testsPassed = 0;
	}
	
	//Test Kingdom card piles
	if(testSupply(&testGame,&game) == 0){
		printf("TEST FAILED - Kingdom Card Piles have changed\n");
		testsPassed = 0;
	}
		
	
	if(testsPassed){
		printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
	}
	else{
		printf("A Test Failed\n");
	}
	return	0;
}
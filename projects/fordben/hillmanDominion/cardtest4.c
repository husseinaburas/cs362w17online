//Name:				cardtest4.c
//Assignment:		Assignment 3
//Author:				Benjamin Ford
//Date:					2/5/2017
//Description:		Unit test for village card

#include "dominion.h" 
#include "dominion_helpers.h" 
#include <string.h> 
#include <stdio.h> 
#include "rngs.h" 
#include <stdlib.h>

#define TESTCARD "Village"

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
	
	//Save the game state for test
	memcpy(&testGame, &game, sizeof(struct gameState));
	
	//place village in players hand
	placeCardInHand(&game,1,great_hall,handPos);
	
	//play village
	playVillage(&game,1,handPos);
	
	
	//Test if players actions went up by 2
	if(game.numActions != (testGame.numActions + 2)){
		printf("TEST FAILED - Actions did not increase by 2\n");
		testsPassed = 0;
	}
	
	//Test if cards came from players deck
	if(game.deckCount[1] != (testGame.deckCount[1] - 1)){
		printf("TEST FAILED - Deck count did not decrease by 1\n");
		testsPassed = 0;
	}
	
	//Test to see if player got 1 card exactly
	//Net 1 - village got discared and a new card gets drawn
	if(game.handCount[1] != (testGame.handCount[1])){
		printf("TEST FAILED - Players hand did not increase by 1\n");
		testsPassed = 0;
	}
	
	//Test Played Count
	//Should go up by 1
	if(game.playedCardCount != (testGame.playedCardCount+1)){
		printf("TEST FAILED - Played count didnt increase by 1\n");
		testsPassed = 0;
	}
	
	//Test the other players state
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
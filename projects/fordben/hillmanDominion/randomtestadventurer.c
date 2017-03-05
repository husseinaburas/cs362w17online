//Name:				randomtestadventurer.c
//Assignment:		Assignment 4
//Author:				Benjamin Ford
//Date:					2/18/2017
//Description:		Random test for Adventurer card


#include "dominion.h" 
#include "dominion_helpers.h" 
#include <string.h> 
#include <stdio.h> 
#include "rngs.h" 
#include <stdlib.h>
#include <time.h>

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

int testHand(struct gameState *state, int player, int startingHandSize){
	int i = 0;
	for(i=startingHandSize;i < state->handCount[player];i++){
		if(testIfTreasure(state->hand[player][i])== 0){
			printf("Card was %d\n",state->hand[player][i]);
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

int main(int argc, char * args[]){
	struct gameState game, testGame;
	const int kCards[] =  {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, great_hall};
	int seed = 0;
	int  players = 0;
	int i = 0;
	int deckCountZeroFlg = -1;
	int loopCntr = 0;
	int returnVal =-1;
	int testsPassed = 1;
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int startHandSize = 0;
	const int iterations = 10000;
	clock_t begin = clock();
	
	seed = atoi(args[1]);
	srand(seed);
	
	printf("Testing %s %d times\n",TESTCARD,iterations);
	
	for(loopCntr = 0; loopCntr < iterations; loopCntr++){
		//Set players
		players = 2 + (rand() % MAX_PLAYERS-2);
		
		//Init game
		initializeGame(players,kCards,seed,&game);
		
		//Set random stats for each player
		for(i = 0; i < players; i++){
			
			game.handCount[i] = 1 + (rand() % MAX_HAND);
			game.deckCount[i] = 10 + (rand() % MAX_DECK);
			game.discardCount[i] = rand() % MAX_DECK;
			
			//Test to see if deckCount is 0
			if(game.deckCount[i] == 0){
				deckCountZeroFlg = 1;
			}
			else{
				deckCountZeroFlg = 0;
			}
			
			game.whoseTurn = i;
			
			//Put a adventurer in the hand
			placeCardInHand(&game,i,adventurer,handPos);
			
			//Save the game state for test
			memcpy(&testGame, &game, sizeof(struct gameState));
			
			
			//Play Adventurer Room
			returnVal = cardEffect(adventurer, choice1, choice2, choice3, &game, handPos, &bonus);
			
			
			
			//Test Return Value
			if(returnVal != 0){
				printf("TEST FAILED - Didnt return 0\n");
				testsPassed = 0;
			}
			
			//test to see if hand count went up by 2/
			if(game.handCount[i] != (testGame.handCount[i]+2)){
				printf("Player %d hand count %d deck count %d\n",i,game.handCount[i],game.deckCount[i]);
				printf("Player %d hand count %d deck count %d\n",i,testGame.handCount[i],testGame.deckCount[i]);
				printf("TEST FAILED - Player did not gain 2 cards\n");
				testsPassed = 0;
			}
			
			//Test if the new cards are treasure
			if(testHand(&game,i,testGame.handCount[i]) == 0){
				printf("TEST FAILED - Player did not gain 2 treasure cards\n");
				testsPassed = 0;
			}
			
			//Test the other players state
			//Test state changed for other player
			if(game.whoseTurn != testGame.whoseTurn){
				printf("TEST FAILED - Player turn changed\n");
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

			endTurn(&game);
		}
		
	}
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	
	printf("Time Ran: %f\n\n",time_spent);
	
	if(testsPassed){
		printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
	}
	else{
		printf("A Test Failed\n");
	}
	
	return 0;
}
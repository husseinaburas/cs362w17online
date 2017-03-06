//Name:				cardtest2.c
//Assignment:		Assignment 4
//Author:				Benjamin Ford
//Date:					2/18/2017
//Description:		Random test for great hall card

#include "dominion.h" 
#include "dominion_helpers.h" 
#include <string.h> 
#include <stdio.h> 
#include "rngs.h" 
#include <stdlib.h>
#include <time.h>

#define TESTCARD "GreatHall"

//places the card into the first postion in the players hand
void placeCardInHand(struct gameState *state, int player,int card, int handPos){
	
	state->hand[player][handPos] = card;
	
	return;
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
	int handPos = 0;
	const int iterations = 100000;
	clock_t begin = clock();
	
	seed = atoi(args[1]);
	srand(seed);
	
	printf("Testing %s %d times\n",TESTCARD,iterations);
	
	for(loopCntr = 0; loopCntr < iterations; loopCntr++){
		//Set players
		players = 2 + (rand() % MAX_PLAYERS-1);
		
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
			
			//Put a great hall in the hand
			placeCardInHand(&game,i,great_hall,handPos);
			
			//Save the game state for test
			memcpy(&testGame, &game, sizeof(struct gameState));
			
			//Play GreatHall
			returnVal = playGreatHall(&game,i,handPos);
			
			//Test Return Value
			if(returnVal != 0){
				printf("TEST FAILED - Didnt return 0\n");
				testsPassed = 0;
			}
			
			//Test to see if player got 1 card exactly
			//Net 1 - great hall get discared and a new card gets drawn
			if(game.handCount[i] != (testGame.handCount[i])){
				printf("TEST FAILED - Players hand did not increase by 1\n");
				printf("Player %d hand count %d deck count %d\n",i,game.handCount[i],game.deckCount[i]);
				printf("Player %d hand count %d deck count %d\n",i,testGame.handCount[i],testGame.deckCount[i]);
				testsPassed = 0;
			}
			
			//Test if cards came from players deck
			//If deck count is zero to start with then the count will be greater
			if((game.deckCount[i] != (testGame.deckCount[i] - 1)) && !deckCountZeroFlg){
				printf("TEST FAILED - Card did not come from players deck\n");
				testsPassed = 0;
			}
			else if(!(game.deckCount[i] >= (testGame.deckCount[i])) && deckCountZeroFlg){
				printf("TEST FAILED - Card did not come from players deck\n");
				testsPassed = 0;
			}
			
			//Test if players actions went up by 1
			if(game.numActions != (testGame.numActions + 1)){
				printf("TEST FAILED - Actions did not increase by 1\n");
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

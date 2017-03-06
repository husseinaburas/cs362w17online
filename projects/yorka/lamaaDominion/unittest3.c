/*
 * Unit Test 3: isGameOver()
 *
 * 
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int assertTest(int a)
{
	if(a == 1)
	{
		printf("Test Success.\n");
		//return 1;
	}
	else
	{
		printf("Test Failed.\n");
		//return 0;
	}
}
int main()
{

	int numPlayers = 2; //Number of players in the game
	int player1 = 0; //Player1's identifier index
	int gameOverStatus;


	int seedVal = 150;

	struct gameState gameStateTest;

  	int kingdomCardsList[10] = {adventurer, smithy, village, remodel, gardens, steward, tribute, great_hall, salvager, sea_hag};

 	printf("---- Unit Test 3: isGameOver() ----\n");
	
	// ---- Test 1: isGameOver() should work if Province pile is exhausted ----
  	printf("---- Test 1: Check to see if GameOver() ends game when Province pile is 0----\n");
	
	 //Initialize game state and player cards
	initializeGame(numPlayers, kingdomCardsList, seedVal, &gameStateTest);

	gameStateTest.supplyCount[province]= 0;

	gameOverStatus = isGameOver(&gameStateTest);

	assertTest(gameOverStatus);
	printf("\n");

	// ---- Test 2: isGameOver() should work if 3 supply piles are exhausted ----
  	printf("---- Test 2: Check to see if GameOver() ends game when 3 Supply Piles are 0----\n");
	
	 //Initialize game state and player cards
	initializeGame(numPlayers, kingdomCardsList, seedVal, &gameStateTest);

	gameStateTest.supplyCount[silver]= 0;
	gameStateTest.supplyCount[minion]= 0;
	gameStateTest.supplyCount[adventurer] = 0;

	gameOverStatus = isGameOver(&gameStateTest);

	assertTest(gameOverStatus);
	printf("\n");

	// ---- Test 3: isGameOver() should work if 4 supply piles are exhausted ----
  	printf("---- Test 3: Check to see if GameOver() ends game when 4 Supply Piles are 0----\n");
	
	 //Initialize game state and player cards
	initializeGame(numPlayers, kingdomCardsList, seedVal, &gameStateTest);

	gameStateTest.supplyCount[silver]= 0;
	gameStateTest.supplyCount[minion]= 0;
	gameStateTest.supplyCount[adventurer] = 0;
	gameStateTest.supplyCount[gold] = 0;

	gameOverStatus = isGameOver(&gameStateTest);

	assertTest(gameOverStatus);
	printf("\n");

	// ---- Test 4: isGameOver() should work if 1 supply pile is exhausted ----
  	printf("---- Test 4: Check to see if GameOver() does not end game when 1 Supply Piles is 0----\n");
	
	 //Initialize game state and player cards
	initializeGame(numPlayers, kingdomCardsList, seedVal, &gameStateTest);
	
	gameStateTest.supplyCount[gold] = 0;

	gameOverStatus = isGameOver(&gameStateTest);

	if(gameOverStatus == 0){
		printf("Test Success.\n");}
	else{
		printf("Test Failed.\n");}
	printf("\n");

	// ---- Test 5: isGameOver() should work if no supply piles are exhausted ----
  	printf("---- Test 5: Check to see if GameOver() does not end game when none of the supply Piles are 0----\n");
	
	 //Initialize game state and player cards
	initializeGame(numPlayers, kingdomCardsList, seedVal, &gameStateTest);

	gameOverStatus = isGameOver(&gameStateTest);

	if(gameOverStatus == 0){
		printf("Test Success.\n");}
	else{
		printf("Test Failed.\n");}

	printf("\n");

	return 0;
}

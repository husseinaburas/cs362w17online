/*
 * Unit Test 1: updateCoins()
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

int assertTest(int a, int b)
{
	if(a == b)
	{
		printf("Test Success.\n");
		return 1;
	}
	else
	{
		printf("Test Failed.\n");
		return 0;
	}
}
int main()
{

	int numPlayers = 2; //Number of players in the game
	int player1 = 0; //Player1's identifier index
	int player1CoinBefore, player2CoinBefore; //Coin before
	int player1CoinAfter, player2CoinAfter; //Coin after

	int seedVal = 150;

	struct gameState gameStateTest;

  	int kingdomCardsList[10] = {adventurer, smithy, village, remodel, gardens, steward, tribute, great_hall, salvager, sea_hag};

 	printf("---- Unit Test 1: updateCoins() ----\n");
	
	// ---- Test 1: updateCoins properly adds CopperCard value(+1 coins)  ----
  	printf("---- Test 1: Check to see updateCoins() updates  correctly after Copper Card(+1) is gained by Player1. ----\n");
	
	 //Initialize game state and player cards
	initializeGame(numPlayers, kingdomCardsList, seedVal, &gameStateTest);

	
	player1CoinBefore = gameStateTest.coins; //Keeps track of player1's starting coin on hand
	printf("player1Coin starting coin: %d \n", player1CoinBefore);

	gainCard(copper, &gameStateTest, 2, player1); //Gains copper card on current hand

	updateCoins(player1, &gameStateTest, 0); 

	player1CoinAfter = gameStateTest.coins; //Keeps track of player1's finishing coin on hand

	printf("Player 1 Coins = %d, Expected Coins = %d \n", player1CoinAfter, player1CoinBefore + 1);	
	
	assertTest(player1CoinAfter,player1CoinBefore+1);

	printf("\n");
	// ---- Test 2: updateCoins properly adds SilverCard value(+2 coins)  ----
  	printf("---- Test 2: Check to see updateCoins() updates  correctly after Silver Card(+2) is gained by Player1. ----\n");
	
	 //Initialize game state and player cards
	initializeGame(numPlayers, kingdomCardsList, seedVal, &gameStateTest);

	
	player1CoinBefore = gameStateTest.coins; //Keeps track of player1's starting coin on hand
	printf("player1Coin starting coin: %d \n", player1CoinBefore);

	gainCard(silver, &gameStateTest, 2, player1); //Gains silver card on current hand

	updateCoins(player1, &gameStateTest, 0); 

	player1CoinAfter = gameStateTest.coins; //Keeps track of player1's finishing coin on hand

	printf("Player 1 Coins = %d, Expected Coins = %d \n", player1CoinAfter, player1CoinBefore + 2);	
	
	assertTest(player1CoinAfter,player1CoinBefore+2);
	
	printf("\n");
	// ---- Test 3: updateCoins properly adds Stward value(+2 coins)  ----
  	printf("---- Test 3: Check to see updateCoins() updates  correctly after Steward(+2) is played by Player1. ----\n");
	
	 //Initialize game state and player cards
	initializeGame(numPlayers, kingdomCardsList, seedVal, &gameStateTest);
	
	
	player1CoinBefore = gameStateTest.coins; //Keeps track of player1's starting coin on hand
 	printf("player1Coin starting coin: %d \n", player1CoinBefore);
	
	//gainCard(gold, &gameStateTest, 2, player1); //Gains gold card on current hand
	gameStateTest.hand[player1][0] = steward;
	playCard(0,2,0,0, &gameStateTest);
	updateCoins(player1, &gameStateTest, 0); 

	player1CoinAfter = gameStateTest.coins; //Keeps track of player1's finishing coin on hand

	printf("Player 1 Coins = %d, Expected Coins = %d \n", player1CoinAfter, player1CoinBefore + 2);	
	
	assertTest(player1CoinAfter,player1CoinBefore+2);
	
	printf("\n");
	// ---- Test 4: Test the updateCoins() bonus correctly on Player1 ----
	printf("---- Test 4: Check to see updateCoins() bonus(+3) correctly works on Player1. ----\n");
	
	initializeGame(numPlayers, kingdomCardsList, seedVal, &gameStateTest);

	player1CoinBefore = gameStateTest.coins;
	printf("player1Coin starting coin: %d \n", player1CoinBefore);

	updateCoins(player1, &gameStateTest, 3);

	player1CoinAfter = gameStateTest.coins;

	printf("Player 1 Coins = %d, Expected Coins = %d \n", player1CoinAfter, player1CoinBefore + 3);	
	
	assertTest(player1CoinAfter,player1CoinBefore+3);
	printf("\n");

	// ---- Test 5: Test the updateCoins() bonus on Player1 affects Player2 ----
	printf("---- Test 5: Check to see updateCoins() bonus(+5) on Player1 affects Player2. ----\n");
	
	initializeGame(numPlayers, kingdomCardsList, seedVal, &gameStateTest);

	updateCoins(player1,&gameStateTest,0);
	player1CoinBefore = gameStateTest.coins;
	printf("player1Coin starting coin: %d \n", player1CoinBefore);

	updateCoins(1, &gameStateTest,0);
	player2CoinBefore = gameStateTest.coins;
	printf("player2Coin starting coin: %d \n", player2CoinBefore);

	updateCoins(player1, &gameStateTest, 5);
	player1CoinAfter = gameStateTest.coins;

	updateCoins(1,&gameStateTest,0);
	player2CoinAfter = gameStateTest.coins;

	printf("Player 1 Coins = %d, Expected Coins = %d \n", player1CoinAfter, player1CoinBefore + 5);	
	printf("Player 2 Coins = %d, Expected Coins = %d \n", player2CoinAfter, player2CoinBefore);	
	
	//
	if(player2CoinBefore+5 == player2CoinAfter)
	{
	printf("Player2 has 5 coins added, when it was supposed to add nothing.Only Player1 should have +5 coins.\n");
	printf("Test Failed.\n");
	}
	else
	{
	printf("Player 2 Coin status stays the same despite change on Player 1 Coins.\n");
	printf("Test Success.\n");
	}
	printf("\n");

	return 0;	
	}

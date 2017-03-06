/*
 * Random Card Test 1: Salvager
 *
 * Citation: Used command line seeding method from playdom.c 
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include<time.h>

int assertTest(int a, int b)
{
	if(a == b)
	{
		//printf("Test Success.\n");
		return 1;
	}
	else
	{
		//printf("Test Failed.\n");
		return 0;
	}
}
int main(int argc, char** argv)
{
	int numberOfTests = 10000; //Number of times to test
	int numberOfPlayers;
	int seedVal = atoi(argv[1]);

	struct gameState gameStateTest;

  	int kingdomCardsList[10] = {smithy, adventurer, village, remodel, gardens, steward, tribute, great_hall, salvager, council_room};


 	printf("---- Random Test: Salvager played by current player ----\n");
	printf("---- Number of tests = %d ----\n", numberOfTests);
	printf("\n");

	int failCount1=0, failCount2=0, failCount3=0, failCount4=0, failCount5=0, failCount6=0, failCount7=0, failCount8=0, failCount9=0;

	//Distribute random values to all the players.
	int i, j;
	for(i = 0; i < numberOfTests; i++)
	{
		numberOfPlayers = rand() % MAX_PLAYERS + 1;
		printf("no of players %d", numberOfPlayers);
		initializeGame(numberOfPlayers, kingdomCardsList, seedVal, &gameStateTest);

		for(j = 0; j < numberOfPlayers; j++)
		{
			gameStateTest.handCount[j] = rand() % MAX_HAND; 
			gameStateTest.deckCount[j] = rand() % MAX_DECK;
			gameStateTest.discardCount[j] = rand() % MAX_DECK;
			gameStateTest.playedCardCount = rand() % MAX_DECK;
		}
		
		int p1handCountB=0, p1deckCountB=0,p1discardCountB=0, p1playedCardCountB=0, p1numBuys=0, p1CoinCount=0;
		
		//Randomize which player will be selected as current player.
		int playerNumber = rand() % numberOfPlayers; 
		gameStateTest.whoseTurn = playerNumber;
		//gameStateTest.coins = 20; //make sure we have enough coins to buy 
		
	
		gameStateTest.hand[playerNumber][0] = salvager;
		gameStateTest.hand[playerNumber][1] = adventurer;

		//Keep track of current player prior states
		p1handCountB = gameStateTest.handCount[playerNumber];
		p1deckCountB = gameStateTest.deckCount[playerNumber];
		p1discardCountB = gameStateTest.discardCount[playerNumber];
		p1playedCardCountB = gameStateTest.playedCardCount;

		//gameStateTest.numBuys = 0; //reset
		p1numBuys = gameStateTest.numBuys;
		//gameStateTest.coins = 0; //reset
		p1CoinCount = gameStateTest.coins;

		//Keep track of other players hand count
		int p2handCountB=0, p3handCountB=0, p4handCountB=0;
		int p2Number=0, p3Number=0, p4Number=0;

		if(numberOfPlayers == 2)
		{
			if(playerNumber == 0){
				p2handCountB = gameStateTest.handCount[1];
				p2Number = 1;}
			else{
				p2handCountB = gameStateTest.handCount[0];
				p2Number = 0;}
		}
		if(numberOfPlayers == 3)
		{
			if(playerNumber == 0){
				p2handCountB = gameStateTest.handCount[1];
				p3handCountB = gameStateTest.handCount[2];
				p2Number = 1;
				p3Number = 2;
			}
			else if(playerNumber == 1){
				p2handCountB = gameStateTest.handCount[0];
				p3handCountB = gameStateTest.handCount[2];
				p2Number = 0;
				p3Number = 2;
			}
			else{
				p2handCountB = gameStateTest.handCount[0];
				p3handCountB = gameStateTest.handCount[1];
				p2Number = 0;
				p3Number = 1;
			}			
		}
		if(numberOfPlayers == 4)
		{
			if(playerNumber == 0){
				p2handCountB = gameStateTest.handCount[1];
				p3handCountB = gameStateTest.handCount[2];
				p4handCountB = gameStateTest.handCount[3];
				p2Number = 1;
				p3Number = 2;
				p4Number = 3;
			}
			if(playerNumber == 1){
				p2handCountB = gameStateTest.handCount[0];
				p3handCountB = gameStateTest.handCount[2];
				p4handCountB = gameStateTest.handCount[3];
				p2Number = 0;
				p3Number = 2;
				p4Number = 3;
			}
			if(playerNumber == 2){
				p2handCountB = gameStateTest.handCount[0];
				p3handCountB = gameStateTest.handCount[1];
				p4handCountB = gameStateTest.handCount[3];
				p2Number = 0;
				p3Number = 1;
				p4Number = 3;
			}
			else{
				p2handCountB = gameStateTest.handCount[0];
				p3handCountB = gameStateTest.handCount[1];
				p4handCountB = gameStateTest.handCount[2];
				p2Number = 0;
				p3Number = 1;
				p4Number = 2;
			}
		}
	

		playCard(0,1,0,0,&gameStateTest);

		// ---- Test 1: Player trashes a card after playing Salvager and assuming player doesn't buy a card.  ----
		//printf("Hand count = %d, expected = %d \n", gameStateTest.coins, p1CoinCount+6);
		if(assertTest(gameStateTest.handCount[playerNumber], p1handCountB -1) == 0)
		{
			failCount1+= 1;			
		}
	
		// ---- Test 2: 0 cards should come from Current player's  deck after playing Salvager----
		if(assertTest(gameStateTest.deckCount[playerNumber], p1deckCountB) == 0)
		{
			failCount2+= 1;
		}
		
		// ---- Test 3: Discard count should not change for currenct Player ----
		if(assertTest(gameStateTest.discardCount[playerNumber], p1discardCountB) == 0)
		{
			failCount3+= 1;
		}

		// ---- Test 4: Played card count should increase by 1 ----
		if(assertTest(gameStateTest.playedCardCount, p1playedCardCountB+1) == 0)
		{
			failCount4+= 1;
		}

		// ---- Test 5: State change should not occer for other players. ----
		if(numberOfPlayers == 2)
		{
			if(assertTest(p2handCountB, gameStateTest.handCount[p2Number]) == 0)
			{
				failCount5+= 1;
			}
		}
		if(numberOfPlayers == 3)
		{
			if(assertTest(p2handCountB, gameStateTest.handCount[p2Number]) == 0)
			{
				failCount5+= 1;
			}

			if(assertTest(p3handCountB, gameStateTest.handCount[p3Number]) == 0)
			{
				failCount6+= 1;
			}
		}
		if(numberOfPlayers == 4)
		{
			if(assertTest(p2handCountB,gameStateTest.handCount[p2Number]) == 0)
			{
				failCount5+= 1;
			}

			if(assertTest(p3handCountB,gameStateTest.handCount[p3Number]) == 0)
			{
				failCount6+= 1;
		
			}
			if(assertTest(p4handCountB,gameStateTest.handCount[p4Number]) == 0)
			{
				failCount7+= 1;
			}
		}
		
		 //---- Test 6: Check +1 Buys increase in current player. ----
		if(assertTest(gameStateTest.numBuys, p1numBuys+1) == 0 )
		{
			failCount8+=1;
		}

		//---- Test 7: Check coin increases same amount as trashed card(adventurer)
		if(assertTest(gameStateTest.coins, p1CoinCount+6) == 0)
		{
			failCount9+= 1;
		}
	}	
	
	printf("---- Test 1: Salvager trashes 1 card and assuming current player doesn't buy a card. ----\n");
	printf("Fail count = %d \n", failCount1);
	printf("\n");

	printf("---- Test 2: 0 cards should come from current Player's deck after using Salvager ----\n");
	printf("Fail count = %d \n", failCount2);
	printf("\n");
	
	printf("---- Test 3: Discard count should not change for current player. ----\n");
	printf("Fail count = %d \n", failCount3);
	printf("\n");
	
	printf("---- Test 4: Played card count increases by 1 for current player ---- \n");
	printf("Fail count = %d \n", failCount4);
	printf("\n");

	printf("---- Test 5: Hand Count for other players should not change ---- \n");
	if(numberOfPlayers == 2)
	{
		printf("Fail count 2nd player = %d \n", failCount5);
		printf("\n");
	}
	if(numberOfPlayers == 3)
	{
		printf("Fail count 2nd player = %d \n", failCount5);
		printf("Fail count 3rd player = %d \n", failCount6);
		printf("\n");
	}
	if(numberOfPlayers == 4)
	{
		printf("Fail count 2nd player = %d \n", failCount5);
		printf("Fail count 3rd player = %d \n", failCount6);
		printf("Fail count 4th player = %d \n", failCount7);
		printf("\n");
	}
	
	printf("---- Test 6: Number of buys should increase by 1 ----\n");
	printf("Fail count = %d \n", failCount8);
	printf("\n");

	printf("---- Test 7: Coin increase by same amount as trashed card( +6coins for adventurer trash) ----\n");
	printf("Fail count = %d \n", failCount9);
	printf("\n");	
	return 0;
}

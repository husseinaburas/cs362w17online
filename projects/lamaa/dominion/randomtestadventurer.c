/*
 * Random Card Test 3: Adventurer
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
	int numberOfTests = 10000;
	int numberOfPlayers;
	int seedVal = atoi(argv[1]);

	struct gameState gameStateTest;

  	int kingdomCardsList[10] = {smithy, adventurer, village, remodel, gardens, steward, tribute, great_hall, salvager, council_room};


 	printf("---- Random Test: Adventurer card ----\n");
	printf("---- Number of tests = %d ----\n", numberOfTests);
	printf("\n");

	int failCount1=0, failCount2=0, failCount3=0, failCount4=0, failCount5=0, failCount6=0, failCount7=0, failCount8=0;
	int deckSizeTracker=0;
	
	//Distribute random values to all the players.
	int i, j;
	for(i = 0; i < numberOfTests; i++)
	{	
		numberOfPlayers = rand() % MAX_PLAYERS + 1;
		initializeGame(numberOfPlayers,kingdomCardsList, seedVal, &gameStateTest);
		for(j = 0; j < numberOfPlayers; j++)
		{
			gameStateTest.handCount[j] = rand() % MAX_HAND; 
			gameStateTest.deckCount[j] = rand() % MAX_HAND;
			gameStateTest.discardCount[j] = rand() % MAX_DECK;
			gameStateTest.playedCardCount = rand() % MAX_DECK;
		}
	
					
		//Keep track of current players card values
		int p1handCountB=0, p1deckCountB=0, p1discardCountB=0, p1playedCardCountB=0, p1numBuys=0;
		int playerNumber = rand() % numberOfPlayers; 
		gameStateTest.whoseTurn = playerNumber;
	
		//Making sure enough supply is there.	
		gameStateTest.supplyCount[smithy] = 500;
		gameStateTest.supplyCount[adventurer] = 500;
		gameStateTest.supplyCount[village] = 500;
		gameStateTest.supplyCount[remodel] = 500;
		gameStateTest.supplyCount[gardens] = 500;
		gameStateTest.supplyCount[steward] = 500;
		gameStateTest.supplyCount[copper] = 500;
		gameStateTest.supplyCount[silver] = 500;
		gameStateTest.supplyCount[gold] = 500;
	
		deckSizeTracker = gameStateTest.deckCount[playerNumber];
	  	//int deckAssort[9] = {smithy, adventurer, village, remodel, gardens, steward, copper, silver, gold};
		int deckAssort[7] = {smithy, remodel, gardens, steward, gold, silver, copper};
	
		// Fill current players deck with random cards (deckAssort array)
		int p = 0;
		for(p = 0; p < deckSizeTracker; p++)
		{
			gameStateTest.deck[playerNumber][p] = deckAssort[rand()%7];
		}
		
		//gameStateTest.coins = 20; //make sure we have enough coins to buy 
		
	
		gameStateTest.hand[playerNumber][0] = adventurer;
		
		p1handCountB = gameStateTest.handCount[playerNumber];
		p1deckCountB = gameStateTest.deckCount[playerNumber];
		p1discardCountB = gameStateTest.discardCount[playerNumber];
		p1playedCardCountB = gameStateTest.playedCardCount;
		p1numBuys = gameStateTest.numBuys;

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

		//cardEffect(adventurer,0,0,0,&gameStateTest,0,0);
		playCard(0,0,0,0,&gameStateTest);

		// ---- Test 1: Current player receives exact 2 treasure cards after playing Adventurer ----
		//printf("Hand count = %d, expected = %d \n", gameStateTest.handCount[playerNumber], p1handCountB + 2);
		if(assertTest(gameStateTest.handCount[playerNumber], p1handCountB + 2) == 0)
		{
			failCount1+= 1;			
		}
	
		// ---- Test 2: At least2 cards should come from Player1's deck after playing Adventurer ----
		if((p1deckCountB - gameStateTest.deckCount[playerNumber]) < 2)
		{
			failCount2+=1;
		}
		// ---- Test 3: Discard count should not change for Player 1 ----
		//if(assertTest(gameStateTest.discardCount[playerNumber], p1discardCountB) == 0)
		//{
		//	failCount3+= 1;
		//}

		// ---- Test 4: Played card count should increase by 1 ----
		if(assertTest(gameStateTest.playedCardCount, p1playedCardCountB+1) == 0)
		{
			failCount4+= 1;
		}

		// ---- Test 5: State change should not occur for other players. ----
		if(numberOfPlayers == 2)
		{
			if(assertTest(p2handCountB, gameStateTest.handCount[p2Number]) == 0)
			{
				failCount5+= 1;
			}
		}
		if(numberOfPlayers == 3)
		{
			if(assertTest(p2handCountB,gameStateTest.handCount[p2Number]) == 0)
			{
				failCount5+= 1;
			}

			if(assertTest(p3handCountB,gameStateTest.handCount[p3Number]) == 0)
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
		
	}
	
	printf("---- Test 1: Adventurer should allow current player to draw 2 treasure cards. ----\n");
	printf("Fail count = %d \n", failCount1);
	printf("\n");

	printf("---- Test 2: At least 2 cards should come from Player1's deck. ----\n");
	printf("Fail count = %d \n", failCount2);
	printf("\n");
	
	//printf("---- Test 3: Discard count should not change for Player 1 ----\n");
	//printf("Fail count = %d \n", failCount3);
	//printf("\n");
	
	printf("---- Test 3: Played card count should increase by 1 ---- \n");
	printf("Fail count = %d \n", failCount4);
	printf("\n");

	printf("---- Test 4: Hand Count for other players should not change ---- \n");
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
	
	return 0;
}

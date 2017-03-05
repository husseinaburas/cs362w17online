/*
 * Card Test 1: Village
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

	int numPlayers = 2; 
	int player1 = 0; 
	int player2 = 1;
	int handCountBefore, actionCountBefore, deckCountBefore,playedCountBefore;
	int handCountBefore2, deckCountBefore2;
	int seedVal = 220;

	struct gameState gameStateTest, gameStateTest2;

  	int kingdomCardsList[10] = {adventurer, smithy, village, remodel, gardens, steward, tribute, great_hall, salvager, council_room};

 	printf("---- Card Test 3: Village ----\n");
	
	
	 //Initialize game state and player cards
	initializeGame(numPlayers, kingdomCardsList, seedVal, &gameStateTest);
	
		
	handCountBefore = gameStateTest.handCount[player1];
	actionCountBefore = gameStateTest.numActions;
	deckCountBefore = gameStateTest.deckCount[player1];
	playedCountBefore = gameStateTest.playedCardCount;

	handCountBefore2 = gameStateTest.handCount[player2];
	deckCountBefore2 = gameStateTest.deckCount[player2];

	gameStateTest.hand[player1][0] = village;

	cardEffect(village,0,0,0,&gameStateTest,0,0);
	
	// ---- Test 1: +1 Card when Village played  ----
  	printf("---- Test 1: +1 card should be in your hand ----\n");

	printf("Hand count before Village card used = %d\n", handCountBefore);	
	printf("Hand count after = %d, expected = %d \n", gameStateTest.handCount[player1], handCountBefore+1);
	assertTest(gameStateTest.handCount[player1],handCountBefore+1);
		
	printf("\n");
	
	//---- Test2: +2 num count increase should happen ----
	printf("---- Test2: +2 Actions increase -----\n");
	
	printf("Action count before Village card used = %d \n", actionCountBefore );
	printf("Action hand count after = %d, expected = %d \n", gameStateTest.numActions, actionCountBefore+2);
	assertTest(gameStateTest.numActions, actionCountBefore+2);
	printf("\n");

	//---- Test3: Deck Count should decrease by 1 ----
	printf("---- Test3: -1 Deck count ----\n");
	
	printf("Deck count before Village card used = %d \n", deckCountBefore );
	printf("Deck hand count after = %d, expected = %d \n", gameStateTest.deckCount[player1], deckCountBefore-1);
	assertTest(gameStateTest.deckCount[player1], deckCountBefore-1);
	printf("\n");

	//---- Test4: Player2 hand count shouldn't be affected ----
	printf("---- Test4: Player 2 hand count shouldnt' be affected. ----\n");
	
	printf("Hand count before Village card used = %d \n", handCountBefore2 );
	printf("Hand count after = %d, expected = %d \n", gameStateTest.handCount[player2], handCountBefore2);
	assertTest(gameStateTest.handCount[player2], handCountBefore2);
	printf("\n");

	//---- Test5: Player2 deck count shouldn't be affected ----
	printf("---- Test5: Player 2 deck count shouldnt' be affected. ----\n");
	
	printf("Deck count before Village card used = %d \n", deckCountBefore2 );
	printf("Deck count after = %d, expected = %d \n", gameStateTest.deckCount[player2], deckCountBefore2);
	assertTest(gameStateTest.deckCount[player2], deckCountBefore2);
	printf("\n");

	//---- Test6: Played count shoud increase by 1 ----
	printf("---- Test6: Played count should increase by 1 ----\n");
	
	printf("Played count before Village card used = %d \n", playedCountBefore);
	printf("Played count after = %d, expected = %d \n", gameStateTest.playedCardCount, playedCountBefore+1);
	assertTest(gameStateTest.playedCardCount, playedCountBefore+1);
	printf("\n");

	return 0;
}

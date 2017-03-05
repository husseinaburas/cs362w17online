/*
 * Card Test 4: Council Room
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
	int handCountBefore, buysBefore, deckCountBefore, playedCountBefore;
	int handCountBefore2, deckCountBefore2;
	int seedVal = 220;

	struct gameState gameStateTest, gameStateTest2;

  	int kingdomCardsList[10] = {adventurer, smithy, village, remodel, gardens, steward, tribute, great_hall, salvager, council_room};

 	printf("---- Card Test 4: Council Room ----\n");
	
	
	 //Initialize game state and player cards
	initializeGame(numPlayers, kingdomCardsList, seedVal, &gameStateTest);
	
		
	handCountBefore = gameStateTest.handCount[player1];
	buysBefore = gameStateTest.numBuys;
	deckCountBefore = gameStateTest.deckCount[player1];
	playedCountBefore = gameStateTest.playedCardCount;

	handCountBefore2 = gameStateTest.handCount[player2];
	deckCountBefore2 = gameStateTest.deckCount[player2];
	
	gameStateTest.hand[player1][0] = council_room;

	cardEffect(council_room,0,0,0,&gameStateTest,0,0);
	
	// ---- Test 1: +1 Card when Council Room played  ----
  	printf("---- Test 1: +4 card should be added to your hand ----\n");

	printf("Hand count before Council Room card used = %d\n", handCountBefore);	
	printf("Hand count after = %d, expected = %d \n", gameStateTest.handCount[player1], handCountBefore+4);
	assertTest(gameStateTest.handCount[player1],handCountBefore+4);
		
	printf("\n");
	
	//---- Test2: +1 buy count increase should happen ----
	printf("---- Test2: +1 Buy increase -----\n");
	
	printf("Buy count before Council Room card used = %d \n", buysBefore );
	printf("Buy count after = %d, expected = %d \n", gameStateTest.numBuys, buysBefore+1);
	assertTest(gameStateTest.numBuys, buysBefore+1);
	printf("\n");

	//---- Test3: Deck Count should decrease by 4 ----
	printf("---- Test3: -4 Deck count ----\n");
	
	printf("Deck count before Council Room card used = %d \n", deckCountBefore );
	printf("Deck hand count after = %d, expected = %d \n", gameStateTest.deckCount[player1], deckCountBefore-4);
	assertTest(gameStateTest.deckCount[player1], deckCountBefore-4);
	printf("\n");

	//---- Test4: Played card count increases by 1 ----
	printf("---- Test4: +1 Played Card Count ----\n");
	
	printf("Played card count before Council Room card used = %d \n", playedCountBefore );
	printf("Played card count after = %d, expected = %d \n", gameStateTest.playedCardCount, playedCountBefore+1);
	assertTest(gameStateTest.playedCardCount, playedCountBefore+1);
	printf("\n");


	//---- Test5: Player2 hand count should increase by 1 ----
	printf("---- Test5: Player 2 hand count should increase by 1 ----\n");
	
	printf("Hand count before Council Room card used = %d \n", handCountBefore2 );
	printf("Hand count after = %d, expected = %d \n", gameStateTest.handCount[player2], handCountBefore2+1);
	assertTest(gameStateTest.handCount[player2], handCountBefore2+1);
	printf("\n");

	//---- Test6: Player2 deck count should decrease by 1 ----
	printf("---- Test6: Player 2 deck count should decrease by 1 ----\n");
	
	printf("Deck count before Council Room card used = %d \n", deckCountBefore2 );
	printf("Deck count after = %d, expected = %d \n", gameStateTest.deckCount[player2], deckCountBefore2-1);
	assertTest(gameStateTest.deckCount[player2], deckCountBefore2-1);
	printf("\n");

	return 0;
}

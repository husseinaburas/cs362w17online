#include "dominion.h"
#include "dominion_helpers.h"
#include "domtests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
/*
Random test for smithy
*/
//int playSmithy(struct gameState *state, int handPos, int currentPlayer){

int main(){
	
	srand(time(NULL));

	struct gameState TestGame1, TestGame2, TestGame3;
	int numPlayers = 2;
	int seed = rand() % 1000;
	int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int testFlag = 0;
	int currPlayer;
	int otherPlayer;
	int i, c, h, j;
	int deckCopy[MAX_DECK];
	int result;
	int cardsToDraw;
	int initHandCount, initDeckCount, opInitHandCount, opInitDeckCount;
	
	printf("Random Test for Smithy-----------------------------------------------------------------\n");

	for (j = 0; j < 100000; j++){
		//determine number of players (2 - 4 playrs)
		numPlayers = (rand() % (MAX_PLAYERS - 1)) + 2;
			
		//initialize games
		initializeGame(numPlayers, cards, seed, &TestGame1);
		

		//find current player and another player for control
		currPlayer = rand() % numPlayers;
		otherPlayer = currPlayer;
		while (otherPlayer == currPlayer){
			otherPlayer = rand() % numPlayers;
		}

		//end players' turn until arriving at currPlayer's turn
		for (i = 0; i < currPlayer; i++){
			endTurn(&TestGame1);
		}


		//put all cards from hand into deck, shuffle them, and redraw
		while (TestGame1.handCount[currPlayer] > 0){
			TestGame1.deck[currPlayer][TestGame1.deckCount[currPlayer]] = TestGame1.hand[currPlayer][i];
			TestGame1.deckCount[currPlayer]++;
			TestGame1.handCount[currPlayer]--;
		}
		
		shuffle(currPlayer, &TestGame1);
		
		
		//draw random number of cards from deck
		cardsToDraw = rand() % (TestGame1.deckCount[currPlayer] + 1);
		for (i = 0; i < cardsToDraw ; i++ ){
			drawCard(currPlayer, &TestGame1);
		}
		initDeckCount = TestGame1.deckCount[currPlayer];

		//put smithy in currPlayer's hand 
		gainCard(smithy, &TestGame1, 2, currPlayer);
		initHandCount = TestGame1.handCount[currPlayer];
		
		
		//gain up to 5 cards to put into discard pile
		cardsToDraw = rand() % 5;
		for (i = 0; i < cardsToDraw; i++){
			c = rand() % treasure_map;
			h = 1;
			gainCard(c, &TestGame1, 0, currPlayer);
		}

		printf("\nINITIALIZING TEST 0...\n");	
		/*
		* TEST 0: PRECONDITIONS - PLAYER NEEDS SMITHY IN HIS HAND, LOCATE SMITHY POSITION TO PASS INTO FUNCTION
		*/
		testFlag = 0;
		
		assertTrue(TestGame1.handCount[currPlayer] == initHandCount, "initHandCount and player handCount are same", TestGame1.handCount[currPlayer], initHandCount, &testFlag);

		//TestGame3 is identical copy of TestGame1 and TestGame2
		assertTrue(TestGame3.playedCardCount == 0, "no cards have been played yet", TestGame3.playedCardCount, 0, &testFlag);

		//check other player's current pile counts
		opInitDeckCount = TestGame1.deckCount[otherPlayer];
		opInitHandCount = TestGame1.handCount[otherPlayer];
		
		checkTest(testFlag, 0);
		/*
		for (i = 0; i < TestGame1.handCount[currPlayer]; i++){
			printf("Card %d: %d\n", i, TestGame3.hand[currPlayer][i]);
		}
		for (i = 0; i < TestGame1.deckCount[currPlayer]; i++){
			printf("deck %d: %d\nDeck copy %d: %d\n", i, TestGame3.deck[currPlayer][i], i, deckCopy[i]);
		}
		*/
		
		printf("\nINITIALIZING TEST 1...\n");	
		/*
		* TEST 1: PLAY SMITHY - CHECK THAT SMITHY WAS PLAYED AND PLAYER 1 HAS HANDCOUNT INCREASED BY 2
		*/
		testFlag = 0;

		callSmithy(currPlayer, &TestGame1, TestGame1.handCount[currPlayer] - 1);
		assertTrue(TestGame1.playedCardCount == 1, "only one card should be played", TestGame1.playedCardCount, 1, &testFlag);
		assertTrue(TestGame1.playedCards[0] == smithy, "card played was smithy", TestGame1.playedCards[0], smithy, &testFlag);

		assertTrue(TestGame1.handCount[currPlayer] == initHandCount + 2, "number of cards in P1 hand after smithy played", TestGame1.handCount[currPlayer], initHandCount + 2, &testFlag);

		/*for (i = 0; i < TestGame1.handCount[currPlayer]; i++){
			printf("Card %d: %d\n", i, TestGame3.hand[currPlayer][i]);
		}
		for (i = 0; i < TestGame1.deckCount[currPlayer]; i++){
			printf("deck %d: %d\n", i, TestGame3.deck[currPlayer][i]);
		}
		*/
		checkTest(testFlag, 1);
		
		printf("\nINITIALIZING TEST 2...\n");	
		/*
		* TEST 2: PLAY SMITHY FOR P1 DOES NOT AFFECT P2'S CARDS
		*/
		testFlag = 0;
		assertTrue(TestGame1.handCount[otherPlayer] == opInitHandCount, "otherPlayer does not gain cards", TestGame1.handCount[otherPlayer], opInitHandCount, &testFlag);
		assertTrue(TestGame1.deckCount[otherPlayer] == opInitDeckCount, "otherPlayer deck count", TestGame1.deckCount[otherPlayer], opInitDeckCount, &testFlag);	
		
		checkTest(testFlag, 2);

	}

	
	
	
	return 0;
}
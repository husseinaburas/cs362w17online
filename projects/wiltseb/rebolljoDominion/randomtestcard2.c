#include "dominion.h"
#include "dominion_helpers.h"
#include "domtests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
TESTS steward card effect
*/

int main(){
	struct gameState TestGame1, TestGame2, TestGame3;
	int numPlayers = 2;
	int seed = 10;
	int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, steward, smithy, council_room};
	int testFlag = 0;
	int currPlayer, otherPlayer;
	int i, c, c1, c2, j;
	int initHandCount, initDeckCount, initCoins;
	int cardsToDraw, expectedDeckCount;
	int stewardPos;

	
	printf("Random Test for Steward-----------------------------------------------------------------\n");

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
		initHandCount = 0;
		cardsToDraw = rand() % (TestGame1.deckCount[currPlayer] + 1);
		for (i = 0; i < cardsToDraw ; i++ ){
			drawCard(currPlayer, &TestGame1);
			initHandCount++;
		}
		
		//gain up to 5 cards to put into discard pile
		cardsToDraw = rand() % 5;
		for (i = 0; i < cardsToDraw; i++){
			c = rand() % treasure_map;
			gainCard(c, &TestGame1, 0, currPlayer);
		}

			
		//put steward in currPlayer's hand 
		gainCard(steward, &TestGame1, 2, currPlayer);
		initHandCount = TestGame1.handCount[currPlayer];
		initDeckCount = TestGame1.deckCount[currPlayer];
		stewardPos = TestGame1.handCount[currPlayer]-1;
		
		//make multiple copies for testing
		memcpy(&TestGame2, &TestGame1, sizeof(struct gameState));
		memcpy(&TestGame3, &TestGame1, sizeof(struct gameState));
		
		

		printf("\nINITIALIZING TEST 0...\n");	
		/*
		* TEST 0: PRECONDITIONS - PLAYER NEEDS STEWARD IN HIS HAND, LOCATE STEWARD POSITION TO PASS INTO FUNCTION
		*/
		testFlag = 0;

		assertTrue(TestGame1.hand[currPlayer][TestGame1.handCount[currPlayer]-1] == steward, "gained a steward", TestGame1.hand[currPlayer][TestGame1.handCount[currPlayer]-1], steward, &testFlag);
		assertTrue(TestGame1.playedCardCount == 0, "no cards have been played yet", TestGame1.playedCardCount, 0, &testFlag);
		
		updateCoins(currPlayer, &TestGame1, 0);
		initCoins = TestGame1.coins;
		
		checkTest(testFlag, 0);
		
		
		printf("\nINITIALIZING TEST 1...\n");	
		/*
		* TEST 1: FIRST CHOICE - +2 CARDS
		*/
		testFlag = 0;
		
		//expected deck count after gaining 2 cards is either the inital deck count - 2, or the discard pile will be used and drawn from
		expectedDeckCount = initDeckCount-2;
		if (initDeckCount < 2){
			expectedDeckCount += TestGame1.discardCount[currPlayer];
		}
		
		
		callSteward(1, 0, 0, currPlayer, &TestGame1, stewardPos);

		assertTrue(TestGame1.playedCardCount == 1, "one card should be played", TestGame1.playedCardCount, 1, &testFlag);
		assertTrue(TestGame1.handCount[currPlayer] == initHandCount + 1, "number of cards in P1 hand", TestGame1.handCount[currPlayer], initHandCount+1, &testFlag);
		assertTrue(TestGame1.playedCards[0] == steward, "card played was steward", TestGame1.playedCards[0], steward, &testFlag);


		assertTrue(TestGame1.deckCount[currPlayer] == expectedDeckCount, "number of cards in P1 deck", TestGame1.deckCount[currPlayer], expectedDeckCount, &testFlag);

		checkTest(testFlag, 1);
		
		printf("\nINITIALIZING TEST 2...\n");	
		/*
		* TEST 2: SECOND CHOICE - +2 COINS
		*/
		testFlag = 0;
		
		//new game
		updateCoins(currPlayer, &TestGame2, 0);
		callSteward(2, 0, 0, currPlayer, &TestGame2, stewardPos);

		
		assertTrue(TestGame2.handCount[currPlayer] == 5, "number of cards in P1 hand", TestGame2.handCount[currPlayer], 6, &testFlag);
		assertTrue(TestGame2.playedCardCount == 1, "1 played card ", TestGame2.playedCardCount, 1, &testFlag);
		assertTrue(TestGame2.coins == initCoins + 2, "chose +2 coins coins", TestGame2.coins, initCoins+2, &testFlag);

		checkTest(testFlag, 2);
		
		printf("\nINITIALIZING TEST 3...\n");	
		/*
		* TEST 3: THIRD CHOICE - TRASH 2 RANDOM CARDS 
		*/
		testFlag = 0;
		c1 = rand() % TestGame3.handCount[currPlayer];
		c2 = rand() % TestGame3.handCount[currPlayer];
		if (c2 == c1){
			if (TestGame3.handCount[currPlayer] <= 1){
				continue;
			}
			else{
				while (c2 == c1){
					c2 = rand() % TestGame3.handCount[currPlayer];
				}
			}
		}
		
		callSteward(3, c1, c2, currPlayer, &TestGame3, stewardPos);

		assertTrue(TestGame3.playedCardCount == 1, "one card should be played", TestGame3.playedCardCount, 1, &testFlag);
		assertTrue(TestGame3.handCount[currPlayer] == initHandCount - 3, "number of cards in P1 hand after trash", TestGame3.handCount[currPlayer], initHandCount - 3, &testFlag);
		assertTrue(TestGame3.playedCards[0] == steward, "card played was steward", TestGame3.playedCards[0], steward, &testFlag);
		assertTrue(TestGame3.deckCount[currPlayer] == initDeckCount, "number of cards in P1 deck", TestGame3.deckCount[currPlayer], initDeckCount, &testFlag);
		assertTrue(TestGame3.discardCount[currPlayer] == 0, "no cards discarded", TestGame3.discardCount[currPlayer], 0, &testFlag);
		
		checkTest(testFlag, 3);
	}

	return 0;
}
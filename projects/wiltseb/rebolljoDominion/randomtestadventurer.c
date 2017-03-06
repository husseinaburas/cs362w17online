#include "dominion.h"
#include "dominion_helpers.h"
#include "domtests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
/*
TESTS adventurer card effect with random input
*/

int main(int argc, char** argv){
	
	srand(time(NULL));
	
	struct gameState TestGame1, TestGame2, TestGame3;
	int seed = rand()%10000;
	int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int testFlag = 0;
	int currPlayer, otherPlayer;
	int cardsToDraw;
	int i, h, c, j;
	int initNumTreasure, nonTreasureDrawn, currNumTreasure;
	int numPlayers;
	int initHandCount, initDeckCount;
	int opInitHandCount, opInitTreasureCount, opInitDeckCount, opCurrTreasureCount;
	int drawntreasure = 0;
	int temphand[MAX_HAND];
	int z = 0;
	int cardDrawn = 0;

	
	printf("Random Test for Adventurer-----------------------------------------------------------------\n");

	for (j = 0; j < 100; j++){
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
		printf("deckCount after draw: %d", TestGame1.deckCount[currPlayer]);
		initDeckCount = TestGame1.deckCount[currPlayer];
		
		//gain up to 5 cards to put into discard pile
		cardsToDraw = rand() % 5;
		for (i = 0; i < cardsToDraw; i++){
			c = rand() % treasure_map;
			h = 1;
			gainCard(c, &TestGame1, 0, currPlayer);
		}

			
		//put adventurer in currPlayer's hand 
		gainCard(adventurer, &TestGame1, 2, currPlayer);
		initHandCount++;
		
		//make multiple copies for testing
		memcpy(&TestGame2, &TestGame1, sizeof(struct gameState));
		memcpy(&TestGame3, &TestGame1, sizeof(struct gameState));
		
		//FIND INITIAL TREASURE COUNT
		initNumTreasure = 0;	
		for (i = 0; i < TestGame3.handCount[currPlayer]; i++){
			h = TestGame3.hand[currPlayer][i];
			if (h == copper || h == gold || h == silver){
				initNumTreasure++;
			}
		}
		
		//find otherPlayer's hand count and treasure count
		opInitHandCount = TestGame1.handCount[otherPlayer];
		opInitDeckCount = TestGame1.deckCount[otherPlayer];
		opInitTreasureCount = 0;
		for(i = 0; i < TestGame1.handCount[otherPlayer]; i++){
			c = TestGame1.hand[otherPlayer][i];
			if (c == gold || c == silver || c == copper){
				opInitTreasureCount++;
			}
		}
		

		printf("\nINITIALIZING TEST 0...\n");	
		/*
		* TEST 0: PRECONDITIONS - PLAYER NEEDS ADVENTURER IN HIS HAND, NO PLAYED CARDS YET
		*/
		testFlag = 0;

		//TestGame3 is identical copy of TestGame1 and TestGame2
		assertTrue(TestGame3.hand[currPlayer][TestGame3.handCount[currPlayer]-1] == adventurer, "gained a adventurer", TestGame3.hand[currPlayer][TestGame3.handCount[currPlayer]-1], adventurer, &testFlag);
		assertTrue(TestGame3.playedCardCount == 0, "no cards have been played yet", TestGame3.playedCardCount, 0, &testFlag);

		checkTest(testFlag, 0);
		
		printf("\nINITIALIZING TEST 1...\n");	
		/*
		* TEST 1: PLAY ADVENTURER SHOULD RESULT IN 2 MORE (TREASURE) CARDS IN HAND, 1 FEWER ADVENTURER
		*/
		testFlag = 0;
		

		callAdventurer(drawntreasure, &TestGame1, currPlayer, temphand, z, cardDrawn);
		
		//Should be a "played card", not discarded until end of Action phase
		assertTrue(TestGame1.playedCardCount == 1, "only one card should be played", TestGame1.playedCardCount, 1, &testFlag);
		assertTrue(TestGame1.playedCards[0] == adventurer, "card played was adventurer", TestGame1.playedCards[0], adventurer, &testFlag);
		assertTrue(TestGame1.handCount[currPlayer] == initHandCount + 1, "number of cards in P1 hand", TestGame1.handCount[currPlayer], initHandCount + 1, &testFlag);
		
		//Hand should have 2 more treasure cards
		currNumTreasure = initNumTreasure;
		nonTreasureDrawn = 0;
		for (i = 0; i < TestGame1.handCount[currPlayer]; i++){
			h = TestGame1.hand[currPlayer][i];
			if (h == copper || h == gold || h == silver){
				currNumTreasure++;
			}
			else{
				nonTreasureDrawn++;
			}
		}
		assertTrue(currNumTreasure == initNumTreasure + 2, "number of treasure cards increases by 2", currNumTreasure, initNumTreasure + 2, &testFlag);
		
		//Discard pile should include cards drawn that were not treasure cards
		assertTrue(TestGame1.discardCount[currPlayer] == nonTreasureDrawn, "only nonTreasure cards discarded", TestGame1.discardCount[currPlayer], nonTreasureDrawn, &testFlag);
		checkTest(testFlag, 1);
		
		printf("\nINITIALIZING TEST 2...\n");	
		/*
		* TEST 2: PLAY ADVENTURER FOR CURRPLAYER DOES NOT AFFECT OTHERPLAYER'S CARDS
		*/
		testFlag = 0;
		
		//find otherPlayer's hand count and treasure count
		opCurrTreasureCount = 0;
		for(i = 0; i < TestGame1.handCount[otherPlayer]; i++){
			c = TestGame1.hand[otherPlayer][i];
			if (c == gold || c == silver || c == copper){
				opCurrTreasureCount++;
			}
		}
		
		assertTrue(TestGame1.handCount[otherPlayer] == opInitHandCount, "otherPlayer does not gain/lose cards", TestGame1.handCount[otherPlayer], opInitHandCount, &testFlag);
		assertTrue(TestGame1.deckCount[otherPlayer] == opInitDeckCount, "otherPlayer deck count", TestGame1.deckCount[otherPlayer], opInitDeckCount, &testFlag);	
		assertTrue(opInitTreasureCount == opCurrTreasureCount, "other player treasure count not affected", opCurrTreasureCount, opInitTreasureCount, &testFlag);
		checkTest(testFlag, 2);
	}
	
	return 0;
}


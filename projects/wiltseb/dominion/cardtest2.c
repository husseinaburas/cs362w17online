#include "dominion.h"
#include "dominion_helpers.h"
#include "domtests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
TESTS adventurer card effect
*/

int main(){
	struct gameState TestGame1, TestGame2, TestGame3;
	int numPlayers = 2;
	int seed = 10;
	int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int testFlag = 0;
	int player1 = 0;
	int player2 = 1;
	int i, h;
	int initNumTreasure, nonTreasureDrawn, currNumTreasure;
	
	//initialize games
	initializeGame(numPlayers, cards, seed, &TestGame1);
	
	//put steward in p1's hand	
	gainCard(adventurer, &TestGame1, 2, player1);
	
	//make multiple copies for testing
	memcpy(&TestGame2, &TestGame1, sizeof(struct gameState));
	memcpy(&TestGame3, &TestGame1, sizeof(struct gameState));
	
	//COUNT CURRENT TREASURE CARDS TO CHECK IF PLAYER ADDED 2 TREASURE CARDS TO HAND
	initNumTreasure = 0;	
	for (i = 0; i < TestGame3.handCount[player1]; i++){
		h = TestGame3.hand[player1][i];
		if (h == copper || h == gold || h == silver){
			initNumTreasure++;
		}
	}
	printf("CARDTEST 2 -----------------------------------------------------------------\n");

	printf("\nINITIALIZING TEST 0...\n");	
	/*
	* TEST 0: PRECONDITIONS - PLAYER NEEDS ADVENTURER IN HIS HAND, LOCATE ADVENTURER POSITION TO PASS INTO FUNCTION
	* PLAYER HAS 4 TREASURE CARDS TO START WITH
	*/
	testFlag = 0;

	//TestGame3 is identical copy of TestGame1 and TestGame2
	assertTrue(TestGame3.handCount[player1] == 6, "number of cards in P1 hand", TestGame3.handCount[player1], 6, &testFlag);
	assertTrue(TestGame3.hand[player1][5] == adventurer, "gained a adventurer", TestGame3.hand[player1][5], adventurer, &testFlag);
	assertTrue(TestGame3.playedCardCount == 0, "no cards have been played yet", TestGame3.playedCardCount, 0, &testFlag);
	assertTrue(initNumTreasure == 4, "start with 4 treasure cards", initNumTreasure, 4, &testFlag);

	checkTest(testFlag, 0);
	
	printf("\nINITIALIZING TEST 1...\n");	
	/*
	* TEST 1: PLAY ADVENTURER SHOULD RESULT IN 2 MORE (TREASURE) CARDS IN HAND
	*/
	testFlag = 0;
	
	playAdventurer(&TestGame1, player1);
	
	//Should be a "played card", not discarded until end of Action phase
	assertTrue(TestGame1.playedCardCount == 1, "only one card should be played", TestGame1.playedCardCount, 1, &testFlag);
	assertTrue(TestGame1.playedCards[0] == adventurer, "card played was adventurer", TestGame1.playedCards[0], adventurer, &testFlag);
	assertTrue(TestGame1.handCount[player1] == 7, "number of cards in P1 hand", TestGame1.handCount[player1], 7, &testFlag);
	
	//Hand should have 2 more treasure cards
	currNumTreasure = 0;
	for (i = 0; i < TestGame1.handCount[player1]; i++){
		h = TestGame1.hand[player1][i];
		if (h == copper || h == gold || h == silver){
			currNumTreasure++;
		}
	}
	assertTrue(currNumTreasure == 6, "number of treasure cards increases by 2", currNumTreasure, 6, &testFlag);
	
	//Discard pile should include cards drawn that were not treasure cards
	nonTreasureDrawn = 5 - TestGame1.deckCount[player1] - 2;
	assertTrue(TestGame1.discardCount[player1] == nonTreasureDrawn, "only nonTreasure cards discarded", TestGame1.discardCount[player1], nonTreasureDrawn, &testFlag);
	checkTest(testFlag, 1);
	
	printf("\nINITIALIZING TEST 2...\n");	
	/*
	* TEST 2: PLAY ADVENTURER FOR P1 DOES NOT AFFECT P2'S CARDS
	*/
	testFlag = 0;
	assertTrue(TestGame1.handCount[player2] == 0, "player2 does not gain cards", TestGame1.handCount[player2], 0, &testFlag);
	assertTrue(TestGame1.deckCount[player2] == 10, "player2 deck count", TestGame1.deckCount[player2], 10, &testFlag);	
	
	checkTest(testFlag, 2);
	
	
	return 0;
}
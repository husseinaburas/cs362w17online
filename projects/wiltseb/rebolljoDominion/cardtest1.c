#include "dominion.h"
#include "dominion_helpers.h"
#include "domtests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
TESTS smithy card effect
*/
//int callSmithy(struct gameState *state, int handPos, int currentPlayer){

int main(){
	struct gameState TestGame1, TestGame2, TestGame3;
	int numPlayers = 2;
	int seed = 10;
	int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int testFlag = 0;
	int player1 = 0;
	int player2 = 1;
	int i;
	int deckCopy[MAX_DECK];
	int result;
	
	
	//initialize games
	initializeGame(numPlayers, cards, seed, &TestGame1);
		
	//put smithy in p1's hand	
	gainCard(smithy, &TestGame1, 2, player1);
	
	//make a copy of deck for testing
	for (i = 0; i < TestGame1.deckCount[player1]; i++){
		deckCopy[i] = TestGame1.deck[player1][i];
	}
	
	//make multiple copies for testing
	memcpy(&TestGame2, &TestGame1, sizeof(struct gameState));
	memcpy(&TestGame3, &TestGame1, sizeof(struct gameState));
	
	printf("CARDTEST 1 -----------------------------------------------------------------\n");

	printf("\nINITIALIZING TEST 0...\n");	
	/*
	* TEST 0: PRECONDITIONS - PLAYER NEEDS SMITHY IN HIS HAND, LOCATE SMITHY POSITION TO PASS INTO FUNCTION
	*/
	testFlag = 0;

	//TestGame3 is identical copy of TestGame1 and TestGame2
	assertTrue(TestGame3.handCount[player1] == 6, "number of cards in P1 hand", TestGame3.handCount[player1], 6, &testFlag);
	assertTrue(TestGame3.hand[player1][5] == smithy, "gained a smithy", TestGame3.hand[player1][5], smithy, &testFlag);
	assertTrue(TestGame3.playedCardCount == 0, "no cards have been played yet", TestGame3.playedCardCount, 0, &testFlag);

	checkTest(testFlag, 0);
	/*
	for (i = 0; i < TestGame1.handCount[player1]; i++){
		printf("Card %d: %d\n", i, TestGame3.hand[player1][i]);
	}
	for (i = 0; i < TestGame1.deckCount[player1]; i++){
		printf("deck %d: %d\nDeck copy %d: %d\n", i, TestGame3.deck[player1][i], i, deckCopy[i]);
	}
	*/
	
	printf("\nINITIALIZING TEST 1...\n");	
	/*
	* TEST 1: PLAY SMITHY - CHECK THAT SMITHY WAS PLAYED AND PLAYER 1 HAS HANDCOUNT INCREASED BY 2
	*/
	testFlag = 0;
	
	callSmithy(player1, &TestGame1, 5);
	assertTrue(TestGame1.playedCardCount == 1, "only one card should be played", TestGame1.playedCardCount, 1, &testFlag);
	assertTrue(TestGame1.playedCards[0] == smithy, "card played was smithy", TestGame1.playedCards[0], smithy, &testFlag);

	assertTrue(TestGame1.handCount[player1] == 8, "number of cards in P1 hand after smithy played", TestGame1.handCount[player1], 8, &testFlag);
	for (i = 0; i < 3; i++){
		assertTrue(deckCopy[i] == TestGame1.hand[player1][i+5], "cards in handpos 5,6,7 should be first 3 from deck", deckCopy[i], TestGame1.hand[player1][i+5], &testFlag);
	}
	
	/*for (i = 0; i < TestGame1.handCount[player1]; i++){
		printf("Card %d: %d\n", i, TestGame3.hand[player1][i]);
	}
	for (i = 0; i < TestGame1.deckCount[player1]; i++){
		printf("deck %d: %d\n", i, TestGame3.deck[player1][i]);
	}
	*/
	checkTest(testFlag, 1);
	
	printf("\nINITIALIZING TEST 2...\n");	
	/*
	* TEST 2: PLAY SMITHY FOR P1 DOES NOT AFFECT P2'S CARDS
	*/
	testFlag = 0;
	assertTrue(TestGame1.handCount[player2] == 0, "player2 does not gain cards", TestGame1.handCount[player2], 0, &testFlag);
	assertTrue(TestGame1.deckCount[player2] == 10, "player2 deck count", TestGame1.deckCount[player2], 10, &testFlag);	
	
	checkTest(testFlag, 2);
	
	/*
	* TEST 3: NON SMITHY CARD PASSED INTO SMITHY FUNCTION
	*/
	testFlag = 0;
	assertTrue(TestGame2.hand[player1][0] == copper, "first card should be copper", TestGame2.hand[player1][0], copper, &testFlag);
	result = callSmithy(player1, &TestGame2, 1);
	assertTrue(result == -1, "using non-smithy card with callSmithy() should return error", result, -1, &testFlag);
	
	checkTest(testFlag, 3);
	
	
	
	return 0;
}
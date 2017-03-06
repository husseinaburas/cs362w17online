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
	int player1 = 0;
	
	//initialize games
	initializeGame(numPlayers, cards, seed, &TestGame1);

	
	//put steward in p1's hand	
	gainCard(steward, &TestGame1, 2, player1);
	
	//make multiple copies for testing
	memcpy(&TestGame2, &TestGame1, sizeof(struct gameState));
	memcpy(&TestGame3, &TestGame1, sizeof(struct gameState));
	printf("CARDTEST 3 -----------------------------------------------------------------\n");

	printf("\nINITIALIZING TEST 0...\n");	
	/*
	* TEST 0: PRECONDITIONS - PLAYER NEEDS STEWARD IN HIS HAND, LOCATE STEWARD POSITION TO PASS INTO FUNCTION
	*/
	testFlag = 0;

	assertTrue(TestGame1.handCount[player1] == 6, "number of cards in P1 hand", TestGame1.handCount[player1], 6, &testFlag);
	assertTrue(TestGame1.hand[player1][5] == steward, "gained a steward", TestGame1.hand[player1][5], steward, &testFlag);
	assertTrue(TestGame1.playedCardCount == 0, "no cards have been played yet", TestGame1.playedCardCount, 0, &testFlag);
	assertTrue(TestGame1.deckCount[player1] == 5, "number of cards in P1 deck", TestGame1.deckCount[player1], 5, &testFlag);
	
	updateCoins(player1, &TestGame1, 0);
	assertTrue(TestGame1.coins == 4, "start with 4 coins", TestGame1.coins, 4, &testFlag);
	
	checkTest(testFlag, 0);
	
	
	printf("\nINITIALIZING TEST 1...\n");	
	/*
	* TEST 1: FIRST CHOICE - +2 CARDS
	*/
	testFlag = 0;

	updateCoins(player1, &TestGame2, 0);
	playSteward(&TestGame1, player1, 5, 1, 0, 0);

	assertTrue(TestGame1.playedCardCount == 1, "one card should be played", TestGame1.playedCardCount, 1, &testFlag);
	assertTrue(TestGame1.handCount[player1] == 7, "number of cards in P1 hand", TestGame1.handCount[player1], 7, &testFlag);
	assertTrue(TestGame1.playedCards[0] == steward, "card played was steward", TestGame1.playedCards[0], steward, &testFlag);
	assertTrue(TestGame1.deckCount[player1] == 3, "number of cards in P1 deck", TestGame1.deckCount[player1], 3, &testFlag);

	checkTest(testFlag, 1);
	
	printf("\nINITIALIZING TEST 2...\n");	
	/*
	* TEST 2: SECOND CHOICE - +2 COINS
	*/
	testFlag = 0;
	
	//new game
	updateCoins(player1, &TestGame2, 0);
	playSteward(&TestGame2, player1, 5, 2, 0, 0);
	
	assertTrue(TestGame2.handCount[player1] == 5, "number of cards in P1 hand", TestGame2.handCount[player1], 6, &testFlag);
	assertTrue(TestGame2.playedCardCount == 1, "1 played card ", TestGame2.playedCardCount, 1, &testFlag);
	assertTrue(TestGame2.coins == 6, "chose +2 coins coins", TestGame2.coins, 6, &testFlag);

	checkTest(testFlag, 2);
	
	printf("\nINITIALIZING TEST 3...\n");	
	/*
	* TEST 3: THIRD CHOICE - TRASH 2 CARDS (TRASH FIRST AND SECOND CARD IN HAND)
	*/
	testFlag = 0;
	playSteward(&TestGame3, player1, 5, 0, 0, 1);
	
	assertTrue(TestGame3.playedCardCount == 1, "one card should be played", TestGame3.playedCardCount, 1, &testFlag);
	assertTrue(TestGame3.handCount[player1] == 3, "number of cards in P1 hand after trash", TestGame3.handCount[player1], 3, &testFlag);
	assertTrue(TestGame3.playedCards[0] == steward, "card played was steward", TestGame3.playedCards[0], steward, &testFlag);
	assertTrue(TestGame3.deckCount[player1] == 5, "number of cards in P1 deck", TestGame3.deckCount[player1], 5, &testFlag);
	assertTrue(TestGame3.discardCount[player1] == 0, "no cards discarded", TestGame3.discardCount[player1], 0, &testFlag);
	
	checkTest(testFlag, 3);


	return 0;
}
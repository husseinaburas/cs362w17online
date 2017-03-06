#include "dominion.h"
#include "dominion_helpers.h"
#include "domtests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
TESTS remodel card effect
*/

int main(){
	struct gameState TestGame1, TestGame2;
	int numPlayers = 2;
	int seed = 10;
	int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, remodel, smithy, council_room};
	int testFlag = 0;
	int player1 = 0;
	int i;
	int result;
	int numCopper;
	
	//initialize games
	initializeGame(numPlayers, cards, seed, &TestGame1);
	
	//put remodel in p1's hand	
	gainCard(remodel, &TestGame1, 2, player1);
	
	//make multiple copies for testing
	memcpy(&TestGame2, &TestGame1, sizeof(struct gameState));
	
	printf("CARDTEST 4 -----------------------------------------------------------------\n");
	
	printf("\nINITIALIZING TEST 0...\n");	
	/*
	* TEST 0: PRECONDITIONS - PLAYER NEEDS REMODEL IN HIS HAND, LOCATE REMODEL POSITION TO PASS INTO FUNCTION
	*/
	testFlag = 0;

	//TestGame3 is identical copy of TestGame1 and TestGame2
	assertTrue(TestGame1.handCount[player1] == 6, "number of cards in P1 hand", TestGame1.handCount[player1], 6, &testFlag);
	assertTrue(TestGame1.hand[player1][5] == remodel, "gained a remodel", TestGame1.hand[player1][5], remodel, &testFlag);
	assertTrue(TestGame1.playedCardCount == 0, "no cards have been played yet", TestGame1.playedCardCount, 0, &testFlag);
	
	numCopper = 0;
	for (i = 0; i < TestGame1.handCount[player1]; i++){
		if (TestGame1.hand[player1][i] == copper){
			numCopper += 1;
		}	
	}
	assertTrue(numCopper == 4, "player1 has 4 copper in his hand", numCopper, 4, &testFlag);
	//card in handPos 0 is a copper
	assertTrue(TestGame1.hand[player1][0] == copper, "handPos 0 is copper", TestGame1.hand[player1][0], copper, &testFlag);
	//copper costs 0
	assertTrue(getCost(copper) == 0, "copper is worth 0", getCost(copper), 0, &testFlag);
	
	
	checkTest(testFlag, 0);
	
	
	printf("\nINITIALIZING TEST 1...\n");	
	/*
	* TEST 1: TRASH COPPER (COST: 0), GAIN ESTATE (COST: 2)
	*/
	testFlag = 0;
	
	//int playRemodel(struct gameState* state, int currentPlayer, int handPos, int choice1, int choice2){
	/* choice1 is hand# of card to remodel, choice2 is supply# */
	
	result = playRemodel(&TestGame1, player1, 5, 0, estate); //should work because estate is worth 2 more than cost of trashed card
	assertTrue(result == 0, "no error", result, 0, &testFlag);
	
	//check played card validity
	assertTrue(TestGame1.playedCardCount == 1, "only one card should be played", TestGame1.playedCardCount, 1, &testFlag);
	assertTrue(TestGame1.playedCards[0] == remodel, "card played was remodel", TestGame1.playedCards[0], remodel, &testFlag);

	//recheck coppers; should be 3 in hand
	numCopper = 0;
	for (i = 0; i < TestGame1.handCount[player1]; i++){
		if (TestGame1.hand[player1][i] == copper){
			numCopper += 1;
		}	
	}
	assertTrue(numCopper == 3, "player1 has one less copper in his hand", numCopper, 3, &testFlag);
	checkTest(testFlag, 1);
	
	printf("\nINITIALIZING TEST 2...\n");	
	/*
	* TEST 2: TRASH COPPER (COST: 0), TRY TO GAIN SMITHY (COST: 4)
	*/
	testFlag = 0;
	//int playRemodel(struct gameState* state, int currentPlayer, int handPos, int choice1, int choice2){
	/* choice1 is hand# of card to remodel, choice2 is supply# */
	result = playRemodel(&TestGame2, player1, 5, 0, smithy); //should NOT work because smithy is worth 4 more than cost of trashed card
	assertTrue(result == -1, "should not be able to gain smithy", result, -1, &testFlag);
	
	checkTest(testFlag, 2);
	
	
	return 0;
}

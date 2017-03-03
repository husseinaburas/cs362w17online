#include "dominion.h"
#include "dominion_helpers.h"
#include "domtests.h"
#include <stdio.h>
#include <stdlib.h>

/*
TESTS updateCoins()
*/

int main(){
	struct gameState TestGame1;
	int numPlayers = 2;
	int seed = 10;
	int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int p1CurrCoins, p2CurrCoins;
	int testFlag = 0;
	int player1 = 0;
	int player2 = 1;
	int i;
	int numCardsAdded;
	int initP1HandCt, currP1HandCt;
	
	//initialize games
	initializeGame(numPlayers, cards, seed, &TestGame1);

	
	//store initial coin count for both players
	updateCoins(player1, &TestGame1, 0);
	p1CurrCoins = TestGame1.coins;
	
	printf("UNITTEST 1 -----------------------------------------------------------------\n");

/*
 * TEST 0: PRECONDITIONS - PLAYERS START WITH NONNEGATIVE COINS
 */
	printf("INITIALIZING TEST 0...\n");
	testFlag = 0;
	//Get initial coins for p2
	updateCoins(player2, &TestGame1, 0);
	p2CurrCoins = TestGame1.coins;
	
	//NOTE: "ACTUAL" CAN BE ANY INT GREATER THAN OR EQUAL TO 0
	assertTrue(p1CurrCoins == 4, "P1 initial coin count", p1CurrCoins, 4, &testFlag);
	assertTrue(p2CurrCoins == 0, "P1 initial coin count", p2CurrCoins, 0, &testFlag);
	
	checkTest(testFlag, 0);
	
	/*
	 * TEST 1: ENSURE UPDATE COINS CORRECTLY ADDS NEW TREASURE CARDS TO COIN COUNT TO PLAYER 1
	 */
	testFlag = 0;
	
	printf("INITIALIZING TEST 1...\n");

	//Adds 1 gold to p1
	gainCard(gold, &TestGame1, 2, 0);
	updateCoins(player1, &TestGame1, 0);
	p1CurrCoins = TestGame1.coins;
	assertTrue(p1CurrCoins == 7, "Player 1 added 1 gold (3 coins)", p1CurrCoins, 7, &testFlag);
	
	//Adds 1 silver to p1
	gainCard(silver, &TestGame1, 2, 0);
	updateCoins(player1, &TestGame1, 0);
	p1CurrCoins = TestGame1.coins;
	assertTrue(p1CurrCoins == 9, "Player 1 added 1 silver (2 coins)", p1CurrCoins, 9, &testFlag);
	
	//Adds 1 copper to p1
	gainCard(copper, &TestGame1, 2, 0);
	updateCoins(player1, &TestGame1, 0);
	p1CurrCoins = TestGame1.coins;
	assertTrue(p1CurrCoins == 10, "Player 1 added 1 copper (1 coin)", p1CurrCoins, 10, &testFlag);

	checkTest(testFlag, 1);
	
	/*
	 * TEST 2: ENSURE UPDATE COINS CORRECTLY ADDS BONUS TO COIN COUNT
	 */
	testFlag = 0;
	
	//Update player1's coins with 2 bonus coins
	printf("INITIALIZING TEST 2...\n");
	
	//Get initial coin values and set current coins accordingly
	updateCoins(player1, &TestGame1, 0);
	p1CurrCoins = TestGame1.coins;
	updateCoins(player2, &TestGame1, 0);
	p2CurrCoins = TestGame1.coins;
	
	//Update coins for player 1 with 2 bonus coins
	updateCoins(player1, &TestGame1, 2);
	p1CurrCoins = TestGame1.coins;
	assertTrue(p1CurrCoins == 12, "Player 1 gets 2 bonus coins", p1CurrCoins, 12, &testFlag);

	checkTest(testFlag, 2);
	
	/*
	 * TEST 3: ENSURE UPDATE COINS FOR PLAYER 1 DOES NOT AFFECT COIN COUNT FOR PLAYER 2
	 */
	testFlag = 0;
	
	printf("INITIALIZING TEST 3...\n");
	//Update coins for both players
	updateCoins(player2, &TestGame1, 0);
	p2CurrCoins = TestGame1.coins;
	assertTrue(p2CurrCoins == 0, "Player 2's coin count should not change", p2CurrCoins, 0, &testFlag);
	
	checkTest(testFlag, 3);

	/*
	 * TEST 4: ENSURE ADDING NON-TREASURE CARDS DOES NOT AFFECT COIN COUNT
	 */
	testFlag = 0;
	printf("INITIALIZING TEST 4...\n");
	
	//establish initial coint count
	updateCoins(player1, &TestGame1, 0);
	p1CurrCoins = TestGame1.coins;
	
	//Add one of each possible non-treasure card to hand
	initP1HandCt = TestGame1.handCount[player1];
	numCardsAdded = 0;
	for (i = 0; i < treasure_map+1; i++){
		//do not add treasure, and make sure card exists in supply to add
		if ((i != gold && i != silver && i != copper) && (TestGame1.supplyCount[i] > 0)){
			gainCard(i, &TestGame1, 2, player1);
			numCardsAdded += 1;
		}
	}

	//Make sure all but 3 treasure cards were added to hand (precondition)
	currP1HandCt = TestGame1.handCount[player1];
	assertTrue(currP1HandCt == (initP1HandCt + numCardsAdded), "Added all but treasure cards", currP1HandCt, initP1HandCt + numCardsAdded, &testFlag);
	
	//update coins after all non-treasure cards are added
	updateCoins(player1, &TestGame1, 0);
	p1CurrCoins = TestGame1.coins;
	//Note 2 bonus coins no longer in p1's current coin count -- back to 10 coins
	assertTrue(p1CurrCoins == 10, "Adding non treasure cards does not affect coin count", p1CurrCoins, 10, &testFlag);
	
	
	checkTest(testFlag, 4);
	return 0;
}
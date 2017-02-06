#include "dominion.h"
#include "dominion_helpers.h"
#include "domtests.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*
TESTS discardCard()
*/

int main(){
	struct gameState TestGame1;
	int numPlayers = 2;
	int seed = 10;
	int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int p1InitHandCt, p2InitHandCt, p1CurrHandCt, p2CurrHandCt;
	int initPlayedCardCt, currPlayedCardCt;
	int p1InitDeckCt, p2InitDeckCt, p1CurrDeckCt, p2CurrDeckCt;
	int p1InitDiscardCt, p2InitDiscardCt, p1CurrDiscardCt, p2CurrDiscardCt;
	int testFlag = 0;
	int player1 = 0;
	int player2 = 1;
	int initSupplyCt[treasure_map+1];
	int i;
	
	initializeGame(numPlayers, cards, seed, &TestGame1);
	printf("Player1 deck count: %d\n", TestGame1.deckCount[player1]);

	//Get initial count of hand, discard, deck
	p1InitHandCt = p1CurrHandCt = TestGame1.handCount[player1];
	p2InitHandCt = p2CurrHandCt = TestGame1.handCount[player2];
	p1InitDeckCt = p1CurrDeckCt = TestGame1.deckCount[player1];
	p2InitDeckCt = p2CurrDeckCt = TestGame1.deckCount[player2];
	p1InitDiscardCt = p1CurrDiscardCt = TestGame1.discardCount[player1];
	p2InitDiscardCt = p2CurrDiscardCt = TestGame1.discardCount[player2];
	
	//Copy initial supply count
	for (i = 0; i < treasure_map+1; i++){
		initSupplyCt[i] = TestGame1.supplyCount[i];
	}
	printf("UNITTEST 3 -----------------------------------------------------------------\n");

	printf("INITIATING TEST 0...\n");
	/*
	TEST 0: PRECONDITIONS - PLAYED CARD COUNT SHOULD BE INITIALIZED TO 0, HANDCOUNT IS 5, DECK IS 5, DISCARD IS 0
	*/
	testFlag = 0;
	initPlayedCardCt = currPlayedCardCt =  TestGame1.playedCardCount;
	assertTrue(initPlayedCardCt == 0, "Played card count initialized to 0", 0, initPlayedCardCt, &testFlag);
	assertTrue(p1InitHandCt == 5, "hand count is 5", p1InitHandCt, 5, &testFlag);
	assertTrue(p1InitDeckCt == 5, "Deck count is 5", p1InitDeckCt, 5, &testFlag);
	assertTrue(p1InitDiscardCt == 0, "discard pile is empty", p1InitDiscardCt, 0, &testFlag);
	
	checkTest(testFlag, 0);
	
	printf("INITIATING TEST 1...\n");
	//int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
	/*
	TEST 1: DISCARD FIRST CARD IN HAND
	*/
	testFlag = 0;	
	//Player 1 discards first card to played cards (not trashed)
	discardCard(0, player1, &TestGame1, 0);
	
	//Update current hand, deck, discard count
	p1CurrHandCt = TestGame1.handCount[player1];
	p1CurrDeckCt = TestGame1.deckCount[player1];
	p1CurrDiscardCt = TestGame1.discardCount[player1];
	currPlayedCardCt = TestGame1.playedCardCount;
	
	assertTrue((p1CurrHandCt == 4), "Player1 hand count", p1CurrHandCt, 4, &testFlag);
	assertTrue((p1CurrDeckCt == 5), "Player1 deck count", p1CurrDeckCt, 5, &testFlag);
	assertTrue((p1CurrDiscardCt == 0), "Player1 discard count", p1CurrDiscardCt, 0, &testFlag);
	assertTrue((currPlayedCardCt == 1), "Played card count", currPlayedCardCt, 1, &testFlag);
	
	//NOTE: CARD SLOTS SHOULD ALL BE NONNEGATVE
	for (i = 0; i < TestGame1.handCount[player1]; i++){
		assertTrue(TestGame1.hand[player1][i] != -1, "no empty hand slots", TestGame1.hand[player1][i], 1, &testFlag);
	}
	
	checkTest(testFlag, 1);
	
	printf("INITIATING TEST 2...\n");	
	/*
	TEST 2: DISCARD LAST CARD IN HAND TO TRASH
	*/
	testFlag = 0;	
	discardCard(3, player1, &TestGame1, 1);
	
	//Update piles
	p1CurrHandCt = TestGame1.handCount[player1];
	p1CurrDeckCt = TestGame1.deckCount[player1];
	p1CurrDiscardCt = TestGame1.discardCount[player1];
	currPlayedCardCt = TestGame1.playedCardCount;
	
	assertTrue((p1CurrHandCt == 3), "Player1 hand count", p1CurrHandCt, 3, &testFlag);
	assertTrue((p1CurrDeckCt == 5), "Player1 deck count", p1CurrDeckCt, 5, &testFlag);
	assertTrue((p1CurrDiscardCt == 0), "Player1 discard count", p1CurrDiscardCt, 0, &testFlag);
	assertTrue((currPlayedCardCt == 1), "Played card count", currPlayedCardCt, 1, &testFlag);
	
	
	checkTest(testFlag, 2);
	
	printf("INITIATING TEST 3...\n");
	/*
	TEST 3: ENSURE P1 DISCARD DOES NOT AFFECT P2
	*/
	testFlag = 0;	
	//Note Player 2 has not drawn 5 cards to hand yet
	assertTrue((p2CurrHandCt == 0), "Player2 hand count", p2CurrHandCt, 0, &testFlag);
	assertTrue((p2CurrDeckCt == 10), "Player2 deck count", p2CurrDeckCt, 10, &testFlag);
	assertTrue((p2CurrDiscardCt == 0), "Player2 discard count", p2CurrDiscardCt, 0, &testFlag);
	
	checkTest(testFlag, 3);
	
	printf("INITIATING TEST 4...\n");
	/*
	TEST 4: ENSURE NO EMPTY SLOTS IN PLAYER 1 HAND
	*/
	testFlag = 0;
	//Expect a nonnegative number
	for(i = 0; i < p1CurrHandCt; i++){
		assertTrue(TestGame1.hand[player1][i] != -1, "hand slots full", TestGame1.hand[player1][i], 1, &testFlag);
	}
	checkTest(testFlag, 4);
	
	printf("INITIATING TEST 5...\n");
	/*
	TEST 5: PLAY ONLY CARD LEFT IN HAND 
	*/
	testFlag = 0;

	TestGame1.handCount[player1] = 1;
	discardCard(0, player1, &TestGame1, 0);
	
	//Update piles
	p1CurrHandCt = TestGame1.handCount[player1];
	p1CurrDeckCt = TestGame1.deckCount[player1];
	p1CurrDiscardCt = TestGame1.discardCount[player1];
	currPlayedCardCt = TestGame1.playedCardCount;
	
	assertTrue((p1CurrHandCt == 0), "Player1 hand count", p1CurrHandCt, 0, &testFlag);
	assertTrue((p1CurrDeckCt == 5), "Player1 deck count", p1CurrDeckCt, 5, &testFlag);
	assertTrue((p1CurrDiscardCt == 0), "Player1 discard count", p1CurrDiscardCt, 0, &testFlag);
	assertTrue((currPlayedCardCt == 2), "Played card count", currPlayedCardCt, 2, &testFlag);
	
		
	checkTest(testFlag, 5);
	return 0;
}





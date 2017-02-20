/*Name of file: randomtestcard2.c
  Author: Clare Brown
  ONID: browncla
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Salvager"
#define PRINT_ALL 0
#define TEST_LENGTH 1000

//Own assert function
int asserttrue(int input, int number){
	if (PRINT_ALL){
		if (input){
			printf("\tTEST %d SUCCESSFUL\n", number);
		}
		else
			printf("\tTEST %d FAILED\n", number);
	}
	return 0;
}

int verifySameState(struct gameState * G, struct gameState * testG){
	int i, success;
	int totalSuccess = 0;
	if (PRINT_ALL)
		printf("TEST 1: Supply counts remain the same\n");
	for (i = 0; i < treasure_map + 1; i++){
		if (G->supplyCount[i] != testG->supplyCount[i]){
			success = 0;
			asserttrue(0, 1);
			totalSuccess++;
			break;
		}
		else{
			success = 1;
		}
	}
	if (success == 1){
		asserttrue(1, 1);
	}

	if (PRINT_ALL)
		printf("TEST 2: Embargo tokens remain the same\n");
	for (i = 0; i < treasure_map + 1; i++){
		if (G->embargoTokens[i] != testG->embargoTokens[i]){
			success = 0;
			asserttrue(0, 1);
			totalSuccess++;
			break;
		}
		else{
			success = 1;
		}
	}
	if (success == 1){
		asserttrue(1, 1);
	}

	if (PRINT_ALL)
		printf("TEST 3: Outposts played remain the same\n");
	asserttrue(G->outpostPlayed == testG->outpostPlayed, 3);
	if (G->outpostPlayed != testG->outpostPlayed)
		totalSuccess++;

	if (PRINT_ALL)
		printf("TEST 4: Outpost turn remains the same\n");
	asserttrue(G->outpostTurn == testG->outpostTurn, 4);
	if (G->outpostTurn != testG->outpostTurn)
		totalSuccess++;

	if (PRINT_ALL)
		printf("TEST 5: Number of players remains the same\n");
	asserttrue(G->numPlayers == testG->numPlayers, 5); 
	if (G->numPlayers != testG->numPlayers){
		totalSuccess++;
	}

	if (PRINT_ALL)
		printf("TEST 6: Whose turn remains the same\n");
	asserttrue(G->whoseTurn == testG->whoseTurn, 6);
	if (G->whoseTurn != testG->whoseTurn)
		totalSuccess++;

	if (PRINT_ALL)
		printf("TEST 7: Phase remains the same\n");
	asserttrue(G->phase == testG->phase, 7);
	if (G->phase != testG->phase)
		totalSuccess++;

	if (PRINT_ALL)
		printf("TEST 8: Number of actions remains the same\n");
	asserttrue(G->numActions == testG->numActions, 8);
	if (G->numActions != testG->numActions)
		totalSuccess++;

	if (PRINT_ALL)
		printf("TEST 9: Number of coins remains the same\n");
	asserttrue(G->coins == testG->coins, 9);
	if (G->coins != testG->coins)
		totalSuccess++;

	if (PRINT_ALL)
		printf("TEST 10: Number of buys remains the same\n");
	asserttrue(G->numBuys == testG->numBuys, 10);
	if (G->numBuys != testG->numBuys)
		totalSuccess++;
	
	if (PRINT_ALL)
		printf("TEST 11: Hand counts remain the same\n");
	for (i = 0; i < G->numPlayers; i++){
		if (G->handCount[i] != testG->handCount[i]){
			success = 0;
			asserttrue(0, 11);
			totalSuccess++;
			break;
		}
		else{
			success = 1;
		}
	}
	if (success == 1){
		asserttrue(1, 11);
	}
	
	if (PRINT_ALL)
		printf("TEST 12: Deck counts remain the same\n");
	for (i = 0; i < G->numPlayers; i++){
		if (G->deckCount[i] != testG->deckCount[i]){
			success = 0;
			asserttrue(0, 12);
			totalSuccess++;
			break;
		}
		else{
			success = 1;
		}
	}
	if (success == 1){
		asserttrue(1, 12);
	}

	if (PRINT_ALL)
		printf("TEST 13: Discard counts remain the same\n");
	for (i = 0; i < G->numPlayers; i++){
		if (G->discardCount[i] != testG->discardCount[i]){
			success = 0;
			asserttrue(0, 13);
			totalSuccess++;
			break;
		}
		else{
			success = 1;
		}
	}
	if (success == 1){
		asserttrue(1, 13);
	}		
	
	if (PRINT_ALL)
		printf("TEST 14: Played card count remains the same\n");			
	asserttrue(G->playedCardCount == testG->playedCardCount, 14);
	if (G->playedCardCount != testG->playedCardCount)
		totalSuccess++;
	return totalSuccess;

}

int verifyDifferentState(struct gameState * G, struct gameState * testG, int choice1){
	int i, success, tester, preCards, postCards;
	int totalSuccess = 0;
	int currentPlayer = G->whoseTurn;
	if (PRINT_ALL)
		printf("Test 1: Phase stays the same\n");
	if (testG->phase == G->phase){
		asserttrue(1, 1);
	}
	else{
		asserttrue(0, 1);
		totalSuccess++;
	}

	if (PRINT_ALL)
		printf("Test 2: Number of buys increases by 1\n");
	if (testG->numBuys == G->numBuys + 1){
		asserttrue(1, 2);
	}
	else{
		asserttrue(0, 2);
		totalSuccess++;
	}

	if (PRINT_ALL)
		printf("Test 3: Number of actions stay the same\n");
	if (testG->numActions == G->numActions){
		asserttrue(1, 3);
	}
	else{
		asserttrue(0, 3);
		totalSuccess++;
	}

	if (PRINT_ALL)
		printf("Test 4: handCount for current player has decreased by 2\n");
	if (testG->handCount[currentPlayer] == G->handCount[currentPlayer] - 2){
		asserttrue(1, 4);
	}
	else{
		asserttrue(0, 4);
		totalSuccess++;
	}

	if (PRINT_ALL)
		printf("Test 5: Salvager card is in the discard pile\n");
	if (testG->discard[currentPlayer][testG->discardCount[currentPlayer]-1] == salvager){
		asserttrue(1, 5);
	}
	else{
		asserttrue(0, 5);
		totalSuccess++;
	}

	if (PRINT_ALL)
		printf("TEST 6: Current players total number of cards has decreased by 1\n");
	preCards = G->handCount[currentPlayer] + G->deckCount[currentPlayer] + G->discardCount[currentPlayer] + G->playedCardCount;
	// count post number of cards
	postCards = testG->handCount[currentPlayer] + testG->deckCount[currentPlayer] + testG->discardCount[currentPlayer] + testG->playedCardCount;

	if (postCards == preCards -1){
		asserttrue(1, 6);
	}
	else{
		asserttrue(0, 6);
		totalSuccess++;
	}

	if (PRINT_ALL)
		printf("Test 7: Number of coins has increased by the value of choice1\n");
	tester = 0;
	tester = 0;
		for (i = 0; i < testG->handCount[currentPlayer]; i++){
			if (testG->hand[currentPlayer][i] == copper)
				tester += 1;
			else if (testG->hand[currentPlayer][i] == silver){
				tester += 2;
			}
			else if (testG->hand[currentPlayer][i] == gold){
				tester += 3;
			}
		}
		if (tester == testG->coins){
			if (tester - getCost(choice1) ){
				asserttrue(1, 8);
			}
		}
	else{
		asserttrue(0, 7);
		totalSuccess++;
	}

	if (PRINT_ALL)
		printf("Test 8: Victory cards have not been affected\n");
	for (i = estate; i <= province; i++){
		if (testG->supplyCount[i] != G->supplyCount[i]){
			asserttrue(0, 8);
			totalSuccess++;
			success = 0;
			break;
		}
		else{
			success = 1;
		}
	}
	if (success == 1){
		asserttrue(1, 8);
	}

	if (PRINT_ALL)
		printf("Test 9: Supply cards have not been affected\n");
	for (i = copper; i <= treasure_map; i++){
		if (testG->supplyCount[i] != G->supplyCount[i]){
			asserttrue(0, 9);
			totalSuccess++;
			success = 0;
			break;
		}
		else{
			success = 1;
		}
	}
	if (success == 1){
		asserttrue(1, 9);
	}

	if (PRINT_ALL)
		printf("Test 10: Card counts for other players have not been affected\n");
	for (i = 0; i < G->numPlayers; i++){
		if (i != currentPlayer){
			if (testG->handCount[i] + testG->deckCount[i] + testG->discardCount[i] != G->handCount[i] + G->deckCount[i] + G->discardCount[i]){
				asserttrue(0, 10);
				totalSuccess++;
				success = 0;
				break;
			}
			else{
				success = 1;
			}
		}
	}
	if (success == 1){
		asserttrue(1, 10);
	}
	return totalSuccess;
}



int printGameState(struct gameState * G){
	int i, j;
	printf("Number of players: %d\n", G->numPlayers); 
	for (i = 0; i < treasure_map + 1; i++){
		printf("Supply count for %d: %d\n", i, G->supplyCount[i]);
	}
	for (i = 0; i < treasure_map + 1; i++){
		printf("Embargo tokens for %d: %d\n", i, G->embargoTokens[i]);
	}
	printf("Outpost played: %d\n", G->outpostPlayed);
	printf("Outpost turn: %d\n", G->outpostTurn);
	printf("Whose turn: %d\n", G->whoseTurn);
	printf("Phase: %d\n", G->phase);
	printf("Number of Actions: %d\n", G->numActions);
	printf("Number of Coins: %d\n", G->coins);
	printf("Number of Buys: %d\n", G->numBuys);
	for (i = 0; i < G->numPlayers; i++){
		printf("Player: %d    Hand Count: %d\n", i, G->handCount[i]);
		printf("Hand: ");
		for (j = 0; j < G->handCount[i]; j++){
			printf("%d ", G->hand[i][j]);
		}
		printf("\n");
	}
	for (i = 0; i < G->numPlayers; i++){
		printf("Player: %d    Deck Count: %d\n", i, G->deckCount[i]);
		printf("Deck: ");
		for (j = 0; j < G->deckCount[i]; j++){
			printf("%d ", G->deck[i][j]);
		}
		printf("\n");
	}
	for (i = 0; i < G->numPlayers; i++){
		printf("Player: %d    Discard Count: %d\n", i, G->discardCount[i]);
		printf("Discard: ");
		for (j = 0; j < G->discardCount[i]; j++){
			printf("%d ", G->discard[i][j]);
		}
		printf("\n");
	}
	printf("Played Card Count: %d\nPlayed cards: ", G->playedCardCount);
	for (i = 0; i < G->playedCardCount; i++){
		printf("%d ", G->playedCards[i]);
	}
	printf("\n");
	return 0;
}


int main (int argc, char** argv){
	if (argc != 2){
		printf("Usage: randomtestcard2 [RandomSeed]\n");
		return 1;
	}
	int j, result, cardPlacement, numPlayers, currentPlayer, totalSuccess;
	int testLocation, testPhase, testActions, testChoice;
	int testPassCount, testFailCount, totalTestCount, validCount, invalidCount;
	srand(atoi(argv[1]));
	int seed = rand()%1000;
	struct gameState G, testG;
	int test_length = TEST_LENGTH;
	// TO DO: RANDOMIZE ASSIGNING OF K CARDS
	int k[10] = {adventurer, embargo, village, minion, salvager, cutpurse,
			sea_hag, tribute, smithy, council_room}; 
	printf("----------------- Card: %s ----------------\n", TESTCARD);
	totalTestCount= 0;
	testPassCount=0;
	testFailCount=0;
	validCount=0;
	invalidCount=0;
	printf("TEST SET 1\nTesting pre-condition: Phase must be 0\n");
	for (j = 1; j <= test_length; j++){
		totalTestCount++;
		numPlayers = rand()%(MAX_PLAYERS-1) + 2;
		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);

		currentPlayer = whoseTurn(&G);
		cardPlacement = rand()%G.handCount[currentPlayer];
		testLocation = cardPlacement;
		testPhase = rand()%3;
		testActions = 1;
		testChoice = rand()%G.handCount[currentPlayer];
		while (G.hand[currentPlayer][testChoice] == cardPlacement){
			testChoice = rand()%G.handCount[currentPlayer];
		}
		// placing the card in the players hand
		G.hand[currentPlayer][cardPlacement] = salvager; 
		// setting phase and actions
		G.phase = testPhase;
		G.numActions = testActions;
		updateCoins(currentPlayer, &G, 0);
		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
		
		if (PRINT_ALL)	{	
			printf("=========================== INPUT %d =========================\n", j);
			printf("Players: %d  Current Player: %d\n", G.numPlayers, currentPlayer);
			printf("Actions: %d  Phase: %d  Buys: %d\n", G.numActions, G.phase, G.numBuys);
			printf("Salvager Location: %d  Tested Card Location: %d  Choice1 Location: %d\n\n", cardPlacement, testLocation, testChoice);
		}
		result = playSalvager(&testG, currentPlayer, testChoice, testLocation);
		if (result == 0){
			validCount++;
			if (PRINT_ALL)
				printf("%s received valid input\n\n", TESTCARD);
			totalSuccess = verifyDifferentState(&G, &testG, testChoice);
			if (PRINT_ALL)
				printf("\n----------------- Results for Valid Input %d -----------------\n", j);
			
			if (totalSuccess == 0){
				if (PRINT_ALL)
					printf("ALL TESTS PASSED\n");
				testPassCount++;
				
			}
			else{
				if (PRINT_ALL)
					printf("%d TEST(S) FAILED\n", totalSuccess);
				testFailCount++;
			}
			if (PRINT_ALL)
				printf("===============================================================\n\n");
		}
		else{
			invalidCount++;
			if (PRINT_ALL)
				printf("%s received invalid input\n\n", TESTCARD);

			totalSuccess = verifySameState(&G, &testG);

			if (PRINT_ALL)
				printf("\n----------------- Results for Invalid Input %d -----------------\n", j);
			
			if (totalSuccess == 0){
				if (PRINT_ALL)
					printf("ALL TESTS PASSED\n");
				testPassCount++;
				
			}
			else{
				if (PRINT_ALL)
					printf("%d TEST(S) FAILED\n", totalSuccess);
				testFailCount++;
			}
			if (PRINT_ALL)
				printf("==================================================================\n\n");
		}
		

		
	}
	printf("Testing phase must be 0...\nValid input tests: %d   Invalid input tests: %d\nTotal tests passed: %d   Total tests failed: %d   Total tests completed: %d\n\n\n", validCount, invalidCount, testPassCount,testFailCount, totalTestCount);
	printf("TEST SET 2\nTesting pre-condition: Number of actions must be greater than 0\n");
	totalTestCount= 0;
	testPassCount=0;
	testFailCount=0;
	validCount=0;
	invalidCount=0;
	for (j = 1; j <= test_length; j++){
		totalTestCount++;
		numPlayers = rand()%(MAX_PLAYERS-1) + 2;
		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);

		currentPlayer = whoseTurn(&G);
		cardPlacement = rand()%G.handCount[currentPlayer];
		testLocation = cardPlacement;
		testPhase = 0;
		testActions = (rand()%10)-5;
		testChoice = rand()%G.handCount[currentPlayer];
		while (G.hand[currentPlayer][testChoice] == cardPlacement){
			testChoice = rand()%G.handCount[currentPlayer];
		}
		// placing the card in the players hand
		G.hand[currentPlayer][cardPlacement] = salvager; 
		// setting phase and actions
		G.phase = testPhase;
		G.numActions = testActions;
		updateCoins(currentPlayer, &G, 0);
		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
		
		if (PRINT_ALL){
			printf("=========================== INPUT %d =========================\n", j);
			printf("Players: %d  Current Player: %d\n", G.numPlayers, currentPlayer);
			printf("Actions: %d  Phase: %d  Buys: %d\n", G.numActions, G.phase, G.numBuys);
			printf("Salvager Location: %d  Tested Card Location: %d  Choice1 Location: %d\n\n", cardPlacement, testLocation, testChoice);
		}
		result = playSalvager(&testG, currentPlayer, testChoice, testLocation);
		if (result == 0){
			validCount++;
			if (PRINT_ALL)
				printf("%s received valid input\n\n", TESTCARD);
			totalSuccess = verifyDifferentState(&G, &testG, testChoice);
			if (PRINT_ALL)
				printf("\n----------------- Results for Valid Input %d -----------------\n", j);
			
			if (totalSuccess == 0){
				if (PRINT_ALL)
					printf("ALL TESTS PASSED\n");
				testPassCount++;
				
			}
			else{
				if (PRINT_ALL)
					printf("%d TEST(S) FAILED\n", totalSuccess);
				testFailCount++;
			}
			if (PRINT_ALL)
				printf("===============================================================\n\n");
		}
		else{
			invalidCount++;
			if (PRINT_ALL)
				printf("%s received invalid input\n\n", TESTCARD);

			totalSuccess = verifySameState(&G, &testG);

			if (PRINT_ALL)
				printf("\n----------------- Results for Invalid Input %d -----------------\n", j);
			
			if (totalSuccess == 0){
				if (PRINT_ALL)
					printf("ALL TESTS PASSED\n");
				testPassCount++;
				
			}
			else{
				if (PRINT_ALL)
					printf("%d TEST(S) FAILED\n", totalSuccess);
				testFailCount++;
			}
			if (PRINT_ALL)
				printf("==================================================================\n\n");
		}
		

		
	}
	printf("Testing number of actions must be greater than 0...\nValid input tests: %d   Invalid input tests: %d\nTotal tests passed: %d   Total tests failed: %d   Total tests completed: %d\n\n\n", validCount, invalidCount, testPassCount,testFailCount, totalTestCount);
	printf("TEST SET 3\nTesting pre-condition: Name of card must be Salvager\n");
	totalTestCount= 0;
	testPassCount=0;
	testFailCount=0;
	validCount=0;
	invalidCount = 0;
	for (j = 1; j <= test_length; j++){
		totalTestCount++;
		numPlayers = rand()%(MAX_PLAYERS-1) + 2;
		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);

		currentPlayer = whoseTurn(&G);
		cardPlacement = rand()%G.handCount[currentPlayer]; //setting Salvager in random place
		testLocation = rand()%G.handCount[currentPlayer]; //card to play from hand
		testPhase = 0;
		testActions = 1;
		testChoice = rand()%G.handCount[currentPlayer];
		while (G.hand[currentPlayer][testChoice] == cardPlacement){
			testChoice = rand()%G.handCount[currentPlayer];
		}
		// placing the card in the players hand
		G.hand[currentPlayer][cardPlacement] = salvager; 
		// setting phase and actions
		G.phase = testPhase;
		G.numActions = testActions;
		updateCoins(currentPlayer, &G, 0);
		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
		
		if (PRINT_ALL){
			printf("=========================== INPUT %d =========================\n", j);
			printf("Players: %d  Current Player: %d\n", G.numPlayers, currentPlayer);
			printf("Actions: %d  Phase: %d  Buys: %d\n", G.numActions, G.phase, G.numBuys);
			printf("Salvager Location: %d  Tested Card Location: %d  Choice1 Location: %d\n\n", cardPlacement, testLocation, testChoice);
		}
		result = playSalvager(&testG, currentPlayer, testChoice, testLocation);
		if (result == 0){
			validCount++;
			if (PRINT_ALL)
				printf("%s received valid input\n\n", TESTCARD);
			totalSuccess = verifyDifferentState(&G, &testG, testChoice);
			if (PRINT_ALL)
				printf("\n----------------- Results for Valid Input %d -----------------\n", j);
			
			if (totalSuccess == 0){
				if (PRINT_ALL)
					printf("ALL TESTS PASSED\n");
				testPassCount++;
				
			}
			else{
				if (PRINT_ALL)
					printf("%d TEST(S) FAILED\n", totalSuccess);
				testFailCount++;
			}
			if (PRINT_ALL)
				printf("===============================================================\n\n");
		}
		else{
			invalidCount++;
			if (PRINT_ALL)
				printf("%s received invalid input\n\n", TESTCARD);

			totalSuccess = verifySameState(&G, &testG);

			if (PRINT_ALL)
				printf("\n----------------- Results for Invalid Input %d -----------------\n", j);
			
			if (totalSuccess == 0){
				if (PRINT_ALL)
					printf("ALL TESTS PASSED\n");
				testPassCount++;				
			}
			else{
				if (PRINT_ALL)
					printf("%d TEST(S) FAILED\n", totalSuccess);
				testFailCount++;
			}
			if (PRINT_ALL)
				printf("==================================================================\n\n");
		}
		

		
	}
	printf("Testing name of card must be salvager...\nValid input tests: %d   Invalid input tests: %d\nTotal tests passed: %d   Total tests failed: %d   Total tests completed: %d\n\n\n", validCount, invalidCount, testPassCount,testFailCount, totalTestCount);
		printf("TEST SET 4\nTesting pre-condition: Played card must be in hand\n");
	testPassCount = 0;
	testFailCount=0;
	totalTestCount=0;
	invalidCount=0;
	validCount=0;
	for (j = 1; j <= test_length; j++){
		totalTestCount++;
		numPlayers = rand()%(MAX_PLAYERS-1) + 2;
		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);

		currentPlayer = whoseTurn(&G);
		cardPlacement = rand()%(G.handCount[currentPlayer]*3)-G.handCount[currentPlayer]; //setting salvager in random place
		testLocation = cardPlacement; //card to play from hand
		testPhase = 0;
		testActions = 1;
		// placing the card in the players hand if possible
		if (cardPlacement >= 0){
			G.hand[currentPlayer][cardPlacement] = salvager; 
		}
		testChoice = rand()%G.handCount[currentPlayer];
		while (G.hand[currentPlayer][testChoice] == cardPlacement){
			testChoice = rand()%G.handCount[currentPlayer];
		}
		// setting phase and actions
		G.phase = testPhase;
		G.numActions = testActions;
		updateCoins(currentPlayer, &G, 0);
		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
		
		if (PRINT_ALL){
			printf("=========================== INPUT %d =========================\n", j);
			printf("Players: %d  Current Player: %d\n", G.numPlayers, currentPlayer);
			printf("Actions: %d  Phase: %d\n", G.numActions, G.phase);
			printf("Salvager Location: %d  Tested Card Location: %d\n\n", cardPlacement, testLocation);
		}
		result = playSalvager(&testG, currentPlayer, testChoice, testLocation);
		if (result == 0){
			validCount++;
			if (PRINT_ALL)
				printf("%s received valid input\n\n", TESTCARD);
			totalSuccess = verifyDifferentState(&G, &testG, testChoice);
			if (PRINT_ALL)
				printf("\n----------------- Results for Valid Input %d -----------------\n", j);
			
			if (totalSuccess == 0){
				if (PRINT_ALL)
					printf("ALL TESTS PASSED\n");
				testPassCount++;
				
			}
			else{
				if (PRINT_ALL)
					printf("%d TEST(S) FAILED\n", totalSuccess);
				testFailCount++;
			}
			if (PRINT_ALL)
				printf("===============================================================\n\n");
		}
		else{
			invalidCount++;
			if (PRINT_ALL)
				printf("%s received invalid input\n\n", TESTCARD);

			totalSuccess = verifySameState(&G, &testG);

			if (PRINT_ALL)
				printf("\n----------------- Results for Invalid Input %d -----------------\n", j);
			
			if (totalSuccess == 0){
				if (PRINT_ALL)
					printf("ALL TESTS PASSED\n");
				testPassCount++;
				
			}
			else{
				if (PRINT_ALL)
					printf("%d TEST(S) FAILED\n", totalSuccess);
				testFailCount++;
			}
			if (PRINT_ALL)
				printf("==================================================================\n\n");
		}
		

		
	}
	printf("Testing played card must be in hand...\nValid input tests: %d   Invalid input tests: %d\nTotal tests passed: %d   Total tests failed: %d   Total tests completed: %d\n\n\n", validCount, invalidCount, testPassCount,testFailCount, totalTestCount);
	
	printf("TEST SET 5\nTesting pre-condition: Choice1 must be a valid card in the hand\n");
	totalTestCount= 0;
	testPassCount=0;
	testFailCount=0;
	invalidCount=0;
	validCount = 0;
	for (j = 1; j <= test_length; j++){
		totalTestCount++;
		numPlayers = rand()%(MAX_PLAYERS-1) + 2;
		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);

		currentPlayer = whoseTurn(&G);
		cardPlacement = rand()%G.handCount[currentPlayer];
		testLocation = cardPlacement;
		testPhase = 0;
		testActions = 1;
		testChoice = rand()%(3* G.handCount[currentPlayer])-G.handCount[currentPlayer];
		while (G.hand[currentPlayer][testChoice] == cardPlacement){
			testChoice = rand()%(3* G.handCount[currentPlayer])-G.handCount[currentPlayer];
		}
		// placing the card in the players hand
		G.hand[currentPlayer][cardPlacement] = salvager; 
		// setting phase and actions
		G.phase = testPhase;
		G.numActions = testActions;
		updateCoins(currentPlayer, &G, 0);
		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
		
		if (PRINT_ALL){
			printf("=========================== INPUT %d =========================\n", j);
			printf("Players: %d  Current Player: %d\n", G.numPlayers, currentPlayer);
			printf("Actions: %d  Phase: %d  Buys: %d\n", G.numActions, G.phase, G.numBuys);
			printf("Salvager Location: %d  Tested Card Location: %d  Choice1 Location: %d\n\n", cardPlacement, testLocation, testChoice);
		}
		result = playSalvager(&testG, currentPlayer, testChoice, testLocation);
		if (result == 0){
			validCount++;
			if (PRINT_ALL)
				printf("%s received valid input\n\n", TESTCARD);
			totalSuccess = verifyDifferentState(&G, &testG, testChoice);
			if (PRINT_ALL)
				printf("\n----------------- Results for Valid Input %d -----------------\n", j);
			
			if (totalSuccess == 0){
				if (PRINT_ALL)
					printf("ALL TESTS PASSED\n");
				testPassCount++;
				
			}
			else{
				if (PRINT_ALL)
					printf("%d TEST(S) FAILED\n", totalSuccess);
				testFailCount++;
			}
			if (PRINT_ALL)
				printf("===============================================================\n\n");
		}
		else{
			invalidCount++;
			if (PRINT_ALL)
				printf("%s received invalid input\n\n", TESTCARD);

			totalSuccess = verifySameState(&G, &testG);

			if (PRINT_ALL)
				printf("\n----------------- Results for Invalid Input %d -----------------\n", j);
			
			if (totalSuccess == 0){
				if (PRINT_ALL)
					printf("ALL TESTS PASSED\n");
				testPassCount++;
				
			}
			else{
				if (PRINT_ALL)
					printf("%d TEST(S) FAILED\n", totalSuccess);
				testFailCount++;
			}
			if (PRINT_ALL)
				printf("==================================================================\n\n");
		}
		

		
	}
	printf("Testing choice1 is a valid card in hand...\nValid input tests: %d   Invalid input tests: %d\nTotal tests passed: %d   Total tests failed: %d   Total tests completed: %d\n\n\n", validCount, invalidCount, testPassCount,testFailCount, totalTestCount);
	totalTestCount= 0;
	testPassCount=0;
	testFailCount=0;
	validCount = 0;
	invalidCount = 0;
	printf("TEST SET 6\nTesting pre-condition: Choice1 must be not be the Salvager card being played\n");
	for (j = 1; j <= test_length; j++){
		totalTestCount++;
		numPlayers = rand()%(MAX_PLAYERS-1) + 2;
		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);

		currentPlayer = whoseTurn(&G);
		cardPlacement = rand()%G.handCount[currentPlayer];
		testLocation = cardPlacement;
		testPhase = 0;
		testActions = 1;
		testChoice = rand()%G.handCount[currentPlayer];
		// placing the card in the players hand
		G.hand[currentPlayer][cardPlacement] = salvager; 
		// setting phase and actions
		G.phase = testPhase;
		G.numActions = testActions;
		updateCoins(currentPlayer, &G, 0);
		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
		
		if (PRINT_ALL){
			printf("=========================== INPUT %d =========================\n", j);
			printf("Players: %d  Current Player: %d\n", G.numPlayers, currentPlayer);
			printf("Actions: %d  Phase: %d  Buys: %d\n", G.numActions, G.phase, G.numBuys);
			printf("Salvager Location: %d  Tested Card Location: %d  Choice1 Location: %d\n\n", cardPlacement, testLocation, testChoice);
		}
		result = playSalvager(&testG, currentPlayer, testChoice, testLocation);
		if (result == 0){
			validCount++;
			if (PRINT_ALL)
				printf("%s received valid input\n\n", TESTCARD);
			totalSuccess = verifyDifferentState(&G, &testG, testChoice);
			if (PRINT_ALL)
				printf("\n----------------- Results for Valid Input %d -----------------\n", j);
			
			if (totalSuccess == 0){
				if (PRINT_ALL)
					printf("ALL TESTS PASSED\n");
				testPassCount++;
				
			}
			else{
				if (PRINT_ALL)
					printf("%d TEST(S) FAILED\n", totalSuccess);
				testFailCount++;
			}
			if (PRINT_ALL)
				printf("===============================================================\n\n");
		}
		else{
			invalidCount++;
			if (PRINT_ALL)
				printf("%s received invalid input\n\n", TESTCARD);

			totalSuccess = verifySameState(&G, &testG);

			if (PRINT_ALL)
				printf("\n----------------- Results for Invalid Input %d -----------------\n", j);
			
			if (totalSuccess == 0){
				if (PRINT_ALL)
					printf("ALL TESTS PASSED\n");
				testPassCount++;
				
			}
			else{
				if (PRINT_ALL)
					printf("%d TEST(S) FAILED\n", totalSuccess);
				testFailCount++;
			}
			if (PRINT_ALL)
				printf("==================================================================\n\n");
		}
		

		
	}
	printf("Testing choice1 is not the salvager card...\nValid input tests: %d   Invalid input tests: %d\nTotal tests passed: %d   Total tests failed: %d   Total tests completed: %d\n\n\n", validCount, invalidCount, testPassCount,testFailCount, totalTestCount);
	return 0;
}


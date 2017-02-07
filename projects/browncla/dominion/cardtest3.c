/*cardtest3.c*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "salvager"

/* Description: If a player plays a salvager card, the player gains the ability to make
   one extra buy in the buying phase. The player then must trash a card from their hand and
   gains the number of coins equal to the cost of the trashed card to use in the buying phase.
   Pre-Conditions: state->phase == 0, the player must be in the action phase
                   state->numActions > 0, the player must have an action to play
                   The name of the card must be salvager and the value must be between 7 and 26
                   Choice1 must be a valid card in the players hand
   Post-Conditions: state->numActions must be >= 0 because the number of actions isn't changed in this function
                    state->numBuys should be increased by 1
                    The card represented by choice1 should not be in the players deck
                    The salvager card should be the last discarded card
int playSalvager(struct gameState *state, int currentPlayer, int choice1, int handPos, int card){
   

   //+1 buy
    state->numBuys++;
    
    if (choice1 == smithy){ //BUG
      //gain coins equal to trashed card
      state->coins = state->coins + getCost( handCard(choice1, state) );
      //trash card
      discardCard(choice1, currentPlayer, state, 0);  //BUG
    }
      
    //discard  salvager card
    discardCard(handPos, currentPlayer, state, 0);


    return 0;
}

//Helper function for playSalvager
//Verifies that a certain card is in the given players hand. If the card is in the players hand
// returns 0, else returns 1
int inHand(struct gameState *state, int currentPlayer, int choice1){
  int i;

    for (i = 0; i < state->handCount[currentPlayer]; i++){
      if (state->hand[currentPlayer][i] == choice1){
          return 0;
      }
    }
    return 1;
}
*/

//Own assert function
int asserttrue(int input, int number){
	if (input){
		printf("\tTEST %d SUCCESSFUL\n", number);
	}
	else
		printf("\tTEST %d FAILED\n", number);
	return 0;
}

int main(){

	int i, success, result, preCards, postCards, tester;
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    int otherPlayer = 1;
    int choice1 = 3;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, salvager, cutpurse,
			sea_hag, tribute, smithy, council_room};
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	G.hand[currentPlayer][2] = salvager;
	updateCoins(currentPlayer, &G, 0);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// ----------- TEST 1: Test correct return statements for valid input -----------
	printf("%s TEST 1: Correct return statements for valid input\n", TESTCARD);
	result = playSalvager(&testG, currentPlayer, choice1, 2);
	if (result == 0){
		asserttrue(1, 1);
	}
	else{
		asserttrue(0, 1);
	}

	// ----------- TEST 2: Test phase before and after is 0 -----------
	printf("%s TEST 2: Phase stays as phase 0\n", TESTCARD);
	if (result == 0){
		if (testG.phase == G.phase){
			asserttrue(1, 2);
		}
		else{
			asserttrue(0, 2);
		}
	}
	else{
		printf("TEST 2 could not be run due to invalid input\n");
	}
	// ----------- TEST 3: Test number of actions before is > 1 -----------
	printf("%s TEST 3: Number of actions after is decreased by 1\n", TESTCARD);
	if (result == 0){
		if (testG.numActions == (G.numActions - 1)){
			asserttrue(1, 3);
		}
		else{
			asserttrue(0, 3);
		}
	}
	else{
		printf("TEST 3 could not be run due to invalid input\n");
	}
	// ----------- TEST 4: Test number of actions after is greater than 0 -----------
	printf("%s TEST 4: Number of actions after is greater than 0\n", TESTCARD);
	if (result == 0){
		if (testG.numActions > 0){
			asserttrue(1, 4);
		}
		else{
			asserttrue(0, 4);
		}
	}
	else{
		printf("TEST 4 could not be run due to invalid input\n");
	}
	// ----------- TEST 5: Test handCount of player decreased by 2 -----------
	printf("%s TEST 5: handCount for current player has decreased by 2\n", TESTCARD);
	if (result == 0){
		if (testG.handCount[currentPlayer] == G.handCount[currentPlayer] - 2){
			asserttrue(1, 5);
		}
		else{
			asserttrue(0, 5);
		}
	}
	else{
		printf("TEST 5 could not be run due to invalid input\n");
	}
	// ----------- TEST 6: Test that the Salvager card is in the discard pile -----------
	printf("%s TEST 6: Salvager card is in the discard pile\n", TESTCARD);
	if (result == 0){
		if (testG.discard[currentPlayer][testG.discardCount[currentPlayer]] == salvager){
			asserttrue(1, 6);
		}
		else{
			asserttrue(0, 6);
		}
	}
	else{
		printf("TEST 6 could not be run due to invalid input\n");
	}
	// ----------- TEST 7: Test that the players total number of cards has decreased by 1 -----------
	printf("%s TEST 7: Current players total number of cards has decreased by 1\n", TESTCARD);
	if (result == 0){
		preCards = G.handCount[currentPlayer] + G.deckCount[currentPlayer] + G.discardCount[currentPlayer] + G.playedCardCount;

		// count post number of cards
		postCards = testG.handCount[currentPlayer] + testG.deckCount[currentPlayer] + testG.discardCount[currentPlayer] + testG.playedCardCount;

		if (postCards == preCards -1){
			asserttrue(1, 7);
		}
		else{
			asserttrue(0, 7);
		}	
	}
	else{
		printf("TEST 7 could not be run due to invalid input\n");
	}
	// ----------- TEST 8: Test that the number of coins has increased by the value of choice 1 -----------
	printf("%s TEST 8: Number of coins has increased by value of choice 1\n", TESTCARD);
	if (result == 0){
		tester = 0;
		for (i = 0; i < testG.handCount[currentPlayer]; i++){
			if (testG.hand[currentPlayer][i] == copper)
				tester += 1;
			else if (testG.hand[currentPlayer][i] == silver){
				tester += 2;
			}
			else if (testG.hand[currentPlayer][i] == gold){
				tester += 3;
			}
		}
		if (tester == testG.coins){
			if (tester - getCost(choice1) ){
				asserttrue(1, 8);
			}
		}
		else{
			asserttrue(0, 8);
		}
	}
	else{
		printf("TEST 8 could not be run due to invalid input\n");
	}
	// ----------- TEST 9: Test that the number of buys has increased by 1 -----------
	printf("%s TEST 9: Number of buys has increased by 1\n", TESTCARD);
	if (result == 0){
		if (testG.numBuys == G.numBuys + 1){
			asserttrue(1, 9);
		}
		else{
			asserttrue(0, 9);
		}
	}
	else{
		printf("TEST 9 could not be run due to invalid input\n");
	}
	// ----------- TEST 10: Test that the number of victory (province, estate, duchy) cards has not changed -----------
	printf("%s TEST 10: Victory cards have not been affected\n", TESTCARD);
	if (result == 0){
		for (i = estate; i <= province; i++){
			if (testG.supplyCount[i] != G.supplyCount[i]){
				asserttrue(0, 10);
				success = 0;
				break;
			}
			else{
				success = 1;
			}
		}
		if (success == 1){
			asserttrue(1, 10);
		}
	}
	else{
		printf("TEST 10 could not be run due to invalid input\n");
	}
	// ----------- TEST 11: Test that number of kingdom cards (supply...) has not changed -----------
	printf("%s TEST 11: Supply cards have not been changed\n", TESTCARD);
	if (result == 0){
		for (i = copper; i <= treasure_map; i++){
			if (testG.supplyCount[i] != G.supplyCount[i]){
				asserttrue(0, 11);
				success = 0;
				break;
			}
			else{
				success = 1;
			}
		}
		if (success == 1){
			asserttrue(1, 11);
		}
	}
	else{
		printf("TEST 11 could not be run due to invalid input\n");
	}

	// reset a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// placing the card in the players hand
	G.hand[currentPlayer][2] = salvager;
	updateCoins(currentPlayer, &G, 0);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	// ----------- TEST 12 : Test correct return statements for invalid input -----------
	printf("%s TEST 12: Correct return statements for invalid input\n", TESTCARD);
	result = playSmithy(&testG, currentPlayer, 4);
	if (result == -1){
		asserttrue(1, 12);
	}
	else{
		asserttrue(0, 12);
	}

	// ----------- TEST 13: Test state stays same invalid input -----------
	printf("%s TEST 13: State says the same with invalid input\n", TESTCARD);
	if (result == -1){

		for (i = 0; i <= treasure_map; i++){
			if (testG.supplyCount[i] != G.supplyCount[i]){
				asserttrue(0, 13);
				success = 0;
				break;
			}
			else{
				success = 1;
			}
		}
		if (success == 1){ // supplies staying the same
			asserttrue(1, 13);
		}
		else if (testG.coins != G.coins){
			asserttrue(0, 13);
		}
		else if (testG.numBuys != G.numBuys){
			asserttrue(0, 13);

		}
		else if (testG.numActions != G.numActions){
			asserttrue(0, 13);
		} 
		else if ((G.handCount[currentPlayer] + G.deckCount[currentPlayer] + G.discardCount[currentPlayer] + G.playedCardCount) != (
		testG.handCount[currentPlayer] + testG.deckCount[currentPlayer] + testG.discardCount[currentPlayer] + testG.playedCardCount))	{
			asserttrue(0, 13);
		}
		else if ((G.handCount[otherPlayer] + G.deckCount[otherPlayer] + G.discardCount[otherPlayer]) != (
		testG.handCount[otherPlayer] + testG.deckCount[otherPlayer] + testG.discardCount[otherPlayer])){
			asserttrue(0, 13);
		}
		else{
			asserttrue(1, 13);
		}
	}
	else{
		printf("TEST 13 could not be run due to unplanned input\n");
	}
	return 0;
}
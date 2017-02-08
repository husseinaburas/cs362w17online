#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"

//unit test for the buyCard() function

//Assert function, 3rd argument is operator, use: 0 for =, 1 for <, 2 for >
int assertTrue(int arg1, int arg2, int op){
	if(op == 0){
		if(arg1 == arg2){
			printf(">>>test successful\n\n");			
		}else{printf(">>>test failed\n\n");
			return -1;}
	}else if(op == 1){
		if(arg1 < arg2){
			printf(">>>test successful\n\n");
		}else{printf(">>>test failed\n\n");
			return -1;}
	}else if(op == 2){
		if(arg1 > arg2){
			printf(">>>test successful\n\n");
		}else{printf(">>>test failed\n\n");
			return -1;}
	}
	return 0;
}//end assertTrue

int main(){
	int 	numPlayers = 2;
	int 	seed = 5;
	struct 	gameState pretest;
	char 	*testCard;
	//char 	*curCard;
	int 	curPlayer;
	int 	cardCnt;
	int 	tmpCnt;
	int 	results;
	int 	i, n;
	int 	failFlag;

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy};

	struct gameState state;
	n = 0;
	//loop through each card in the supply pile and test buying it

	//**********enable loop here to test all supply cards****************//
	//for(n = 0; n < sizeof(k)/sizeof(k[0]); n++){
		//set test card to current card
		testCard = (char*)malloc(15 * sizeof(char));
		cardNumToName(k[n], testCard);

		initializeGame(numPlayers, k, seed, &state);
		curPlayer = state.whoseTurn;
		//adding  coins to state->coins to ensure enough to test buy a card
		state.coins = state.coins + getCost(k[n]);

		//set phase to buy phase
		state.phase = 1;

		//Save game state before testing
		memcpy(&pretest, &state, sizeof(struct gameState));

		printf("********************************Testing buyCard() function****************************\n");
		results = buyCard(k[n], &state);

		//check return value
		printf("expected return value = 0\n");
		printf("acutal return value = %d\n", results);
		assertTrue(0, results, 0);

		//test coins
		printf("Coins before purchase: %d\n", pretest.coins);
		printf("Coins expected after purchase: %d, actual coins: %d\n", pretest.coins - getCost(k[n]), state.coins);
		assertTrue(pretest.coins - getCost(k[n]), state.coins, 0);

		//test buy points
		printf("Buys before purchase: %d\n", pretest.numBuys);
		printf("Buys expected after purchase: %d, actual buys: %d\n", pretest.numBuys - 1, state.numBuys);
		assertTrue(pretest.numBuys - 1, state.numBuys, 0);


		//check that hand count increase by 1 for current player
		printf("check that hand count increased by 1\n");
		printf("hand count before calling buyCard() = %d\n", pretest.handCount[curPlayer]);
		printf("hand count after calling buyCard() = %d\n", state.handCount[curPlayer]);
		assertTrue(pretest.handCount[curPlayer] + 1, state.handCount[curPlayer], 0);


		//test proper card added to hand
		printf("Check that %s card is added to hand\n", testCard);

		//count cards in hand before and after test
		tmpCnt = 0;
		cardCnt = 0;
		for(i=0; i<pretest.handCount[curPlayer]; i++){
			if(pretest.hand[curPlayer][i] == k[n])
				tmpCnt++;
		}	
		printf("%s cards in hand before call: %d\n",testCard, tmpCnt);

		for(i=0; i<state.handCount[curPlayer]; i++){
			//cardNumtoName(state.hand[curPlayer][i], &curCard);
			//printf("Card %d= %s\n", i, curCard);
			if(state.hand[curPlayer][i] == k[n])
				cardCnt++;
		}
		printf("%s cards in hand after call: %d\n",testCard, cardCnt);
		assertTrue(tmpCnt + 1, cardCnt, 0);

		//Verify that supply count decremented properly
		printf("Check that supply pile count is decremented\n");
		printf("%s Supply count before call: %d\n",testCard, pretest.supplyCount[k[n]]);
		printf("%s supply count after call: %d\n",testCard, state.supplyCount[k[n]]);
		assertTrue(pretest.supplyCount[k[n]] - 1, state.supplyCount[k[n]], 0);

		//verify that other fields in the state have not changed that dont need to
		printf("whose turn before call: %d\n", pretest.whoseTurn);
		printf("whose turn after call: %d\n", state.whoseTurn);
		assertTrue(pretest.whoseTurn, state.whoseTurn, 0);

		printf("phase before call: %d\n", pretest.phase);
		printf("phase after call: %d\n", state.phase);
		assertTrue(pretest.phase, state.phase, 0);

		printf("discardCount before call %d, after call: %d\n", pretest.discardCount[curPlayer], state.discardCount[curPlayer]);
		assertTrue(pretest.discardCount[curPlayer], state.discardCount[curPlayer], 0);

		printf("check that hand count for other supply piles has not changed\n");
		printf("skip adventurer card\n");
		for(i = 1; i < 10; i++){
		printf("pretest supply %d = %d", i, pretest.supplyCount[k[i]]);
		printf("state supply %d = %d", i, state.supplyCount[k[i]]);
		assertTrue(pretest.supplyCount[k[i]], state.supplyCount[k[i]], 0);
		}

		//now going to call the buyCard() function under different scenarios
		//reseting game state to the pretest one before altering some fields
		memcpy(&state, &pretest, sizeof(struct gameState));

		//test with no buy points but sufficient coins
		state.numBuys = 0;
		state.coins = 3;
		results = buyCard(k[n], &state);
		printf("No buy points test, should fail, expected return value -1\n");
		assertTrue(-1, results, 0);

		//add buy point back in and test with no coins
		state.numBuys = 1;
		state.coins = 0;
		results = buyCard(k[n], &state);
		printf("No coins, should fail, expected return value -1\n");
		printf("actual return value: %d\n", results);
		assertTrue(-1, results, 0);

		//test with insufficient coins and buy points
		state.numBuys = 0;
		state.coins = 0;
		results = buyCard(k[n], &state);
		printf("No buys or coins, should fail, expected return value -1\n");
		printf("actual return value: %d\n", results);

		assertTrue(-1, results, 0);

		//ensure other players hand and hand count are not affected
		printf("check that hand count for other player unchanged\n");
		printf("hand count before calling buyCard() = %d\n", pretest.handCount[curPlayer+1]);
		printf("hand count after calling buyCard() = %d\n", state.handCount[curPlayer+1]);
		assertTrue(pretest.handCount[curPlayer+1], state.handCount[curPlayer+1], 0);
		
		printf("Check that other player hand unchanged\n");

		//count cards in hand before and after test
		tmpCnt = 0;
		
		if(state.handCount[curPlayer+1] >= pretest.handCount[curPlayer+1]){
			tmpCnt = state.handCount[curPlayer+1];		
		}else{
			tmpCnt = pretest.handCount[curPlayer+1];
		}

		failFlag = 0;
		for(i=0; i<tmpCnt; i++){
			if(pretest.hand[curPlayer+1][i] != state.hand[curPlayer+1][i]){
				failFlag = 1;
			}
		}
		if(failFlag == 1){
			printf("Test Failed\n");
		}else{printf("Test Successful\n");}
		

	//}//end loop ---to enable loop uncommment end of loop
	free(testCard);
	//
	printf("\n*****************************BuyCard Testing Complete*************************************************\n");
	return 0;

}
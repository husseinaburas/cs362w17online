#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"

//unit test for the gainCard() function

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
	struct 	gameState pretest;
	struct 	gameState state;

	int 	numPlayers = 2;
	int 	seed = 5;
	char 	*testCard;
	//char 	*curCard;
	int 	curPlayer;
	int 	cardCnt;
	int 	tmpCnt;
	int 	results;
	int 	i, n;
	

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy};



	n=0;
	testCard = (char*)malloc(15 * sizeof(char));
	cardNumToName(k[n], testCard);

	initializeGame(numPlayers, k, seed, &state);
	curPlayer = state.whoseTurn;
			
	//Save game state before testing
	memcpy(&pretest, &state, sizeof(struct gameState));

	printf("********************************Testing gainCard() function****************************\n");
	
	//check return values
	//first check when insufficient supply
	state.supplyCount[k[n]] = 0;
	
	results = gainCard(k[n], &state, 2, curPlayer);
	printf("Check return value when insufficient supply\n");
	printf("expected return value = -1\n");
	printf("acutal return value = %d\n", results);
	assertTrue(-1, results, 0);

	//next check with sufficient supply, testing adding to hand, toFlag = 2
	state.supplyCount[k[n]] = pretest.supplyCount[k[n]];
	results = gainCard(k[n], &state, 2, curPlayer);

	printf("Check return value when sufficient supply\n");
	printf("expected return value = 0\n");
	printf("acutal return value = %d\n", results);
	assertTrue(0, results, 0);

	////Verify that supply count decremented properly
	printf("Check that supply pile count is decremented\n");
	printf("Supply count before call: %d\n", pretest.supplyCount[k[n]]);
	printf("Supply count after call: %d\n", state.supplyCount[k[n]]);
	assertTrue(pretest.supplyCount[k[n]] - 1, state.supplyCount[k[n]], 0);

	//when sent to hand verify it was added and count increase
	printf("adding to hand\n");
	printf("check that hand count increased by 1\n");
	printf("hand count before calling gainCard() = %d\n", pretest.handCount[curPlayer]);
	printf("hand count after calling gainCard() = %d\n", state.handCount[curPlayer]);
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
		if(state.hand[curPlayer][i] == k[n])
			cardCnt++;
	}
	printf("%s cards in hand after call: %d\n",testCard, cardCnt);
	assertTrue(tmpCnt + 1, cardCnt, 0);





	//now check when card moved to discard pile, toFlag = 0(actually anything but 1 or 2)
	//reset state from pretest
	memcpy(&state, &pretest, sizeof(struct gameState));
	results = gainCard(k[n], &state, 0, curPlayer);

	//check discard pile and count
	printf("adding to discard pile\n");
	printf("check that discard pile count increased by 1\n");
	printf("discard count before calling gainCard() = %d\n", pretest.discardCount[curPlayer]);
	printf("discard count after calling gainCard() = %d\n", state.discardCount[curPlayer]);
	assertTrue(pretest.discardCount[curPlayer] + 1, state.discardCount[curPlayer], 0);

	//count cards in discard pile before and after test
	tmpCnt = 0;
	cardCnt = 0;

	for(i=0; i<pretest.discardCount[curPlayer]; i++){
		if(pretest.discard[curPlayer][i] == k[n])
			tmpCnt++;
	}	
	printf("%s cards in discard before call: %d\n",testCard, tmpCnt);

	for(i=0; i<state.discardCount[curPlayer]; i++){
		if(state.discard[curPlayer][i] == k[n])
			cardCnt++;
	}
	printf("%s cards in discard after call: %d\n",testCard, cardCnt);
	assertTrue(tmpCnt + 1, cardCnt, 0);


	//now check when card moved to the deck, toFlag = 1
	//reset state from pretest
	memcpy(&state, &pretest, sizeof(struct gameState));
	results = gainCard(k[n], &state, 1, curPlayer);

	//check deck and count
	printf("adding to deck\n");
	printf("check that deck pile count increased by 1\n");
	printf("deck count before calling gainCard() = %d\n", pretest.deckCount[curPlayer]);
	printf("deck count after calling gainCard() = %d\n", state.deckCount[curPlayer]);
	assertTrue(pretest.deckCount[curPlayer] + 1, state.deckCount[curPlayer], 0);

	//count cards in deck pile before and after test
	tmpCnt = 0;
	cardCnt = 0;

	for(i=0; i<pretest.deckCount[curPlayer]; i++){
		if(pretest.deck[curPlayer][i] == k[n])
			tmpCnt++;
	}	
	printf("%s cards in deck before call: %d\n",testCard, tmpCnt);

	for(i=0; i<state.deckCount[curPlayer]; i++){
		if(state.deck[curPlayer][i] == k[n])
			cardCnt++;
	}
	printf("%s cards in deck after call: %d\n",testCard, cardCnt);
	assertTrue(tmpCnt + 1, cardCnt, 0);

	///
	printf("Check that other state fields have not changed");
	printf("check that hand count for other player unchanged\n");
	printf("hand count before calling buyCard() = %d\n", pretest.handCount[curPlayer+1]);
	printf("hand count after calling buyCard() = %d\n", state.handCount[curPlayer+1]);
	assertTrue(pretest.handCount[curPlayer+1], state.handCount[curPlayer+1], 0);

	printf("check that hand count for other supply piles has not changed\n");
	printf("skip adventurer card\n");
	for(i = 1; i < 10; i++){
		printf("pretest supply %d = %d", i, pretest.supplyCount[k[i]]);
		printf("state supply %d = %d", i, state.supplyCount[k[i]]);
		assertTrue(pretest.supplyCount[k[i]], state.supplyCount[k[i]], 0);
	}

	

	printf("********************************gainCard() Testing Complete****************************\n");































		////test coins
		//printf("Coins before purchase: %d\n", pretest.coins);
		//printf("Coins expected after purchase: %d, actual coins: %d\n", pretest.coins - getCost(k[n]), state.coins);
		//assertTrue(pretest.coins - getCost(k[n]), state.coins, 0);
//
		////test buy points
		//printf("Buys before purchase: %d\n", pretest.numBuys);
		//printf("Buys expected after purchase: %d, actual buys: %d\n", pretest.numBuys - 1, state.numBuys);
		//assertTrue(pretest.numBuys - 1, state.numBuys, 0);
//
//
		////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////untested starts here
//
		////check that hand count increase by 1 for current player
		//printf("check that hand count increased by 1\n");
		//printf("hand count before calling buyCard() = %d\n", pretest.handCount[curPlayer]);
		//printf("hand count after calling buyCard() = %d\n", state.handCount[curPlayer]);
		//assertTrue(pretest.handCount[curPlayer] + 1, state.handCount[curPlayer], 0);
//
//
//
//
		////test proper card added to hand
		//printf("Check that %s card is added to hand\n", testCard);
//
		////count cards in hand before and after test
		//tmpCnt = 0;
		//cardCnt = 0;
		//for(i=0; i<pretest.handCount[curPlayer]; i++){
		//	if(pretest.hand[curPlayer][i] == k[n])
		//		tmpCnt++;
		//}	
		//printf("%s cards in hand before call: %d\n",testCard, tmpCnt);
//
		//for(i=0; i<state.handCount[curPlayer]; i++){
		//	//cardNumtoName(state.hand[curPlayer][i], &curCard);
		//	//printf("Card %d= %s\n", i, curCard);
		//	if(state.hand[curPlayer][i] == k[n])
		//		cardCnt++;
		//}
		//printf("%s cards in hand after call: %d\n",testCard, cardCnt);
		//assertTrue(tmpCnt + 1, cardCnt, 0);
//
		////Verify that supply count decremented properly
		//printf("Check that supply pile count is decremented\n");
		//printf("%s Supply count before call: %d\n",testCard, pretest.supplyCount[k[n]]);
		//printf("%s supply count after call: %d\n",testCard, state.supplyCount[k[n]]);
		//assertTrue(pretest.supplyCount[k[n]] - 1, state.supplyCount[k[n]], 0);
//
		////verify that other fields in the state have not changed that dont need to
		//printf("whose turn before call: %d\n", pretest.whoseTurn);
		//printf("whose turn after call: %d\n", state.whoseTurn);
		//assertTrue(pretest.whoseTurn, state.whoseTurn, 0);
//
		//printf("phase before call: %d\n", pretest.phase);
		//printf("phase after call: %d\n", state.phase);
		//assertTrue(pretest.phase, state.phase, 0);
//
		////now going to call the buyCard() function under different scenarios
		////reseting game state to the pretest one before altering some fields
		//memcpy(&state, &pretest, sizeof(struct gameState));
//
		////test with no buy points but sufficient coins
		//state.numBuys = 0;
		//state.coins = 3;
		//results = buyCard(k[n], &state);
		//printf("No buy points test, should fail, expected return value -1\n");
		//assertTrue(-1, results, 0);
//
		////add buy point back in and test with no coins
		//state.numBuys = 1;
		//state.coins = 0;
		//results = buyCard(k[n], &state);
		//printf("No coins, should fail, expected return value -1\n");
		//printf("actual return value: %d\n", results);
		//assertTrue(-1, results, 0);
//
		////test with insufficient coins and buy points
		//state.numBuys = 0;
		//state.coins = 0;
		//results = buyCard(k[n], &state);
		//printf("No buys or coins, should fail, expected return value -1\n");
		//printf("actual return value: %d\n", results);
//
		//assertTrue(-1, results, 0);
	//}//end loop
	free(testCard);
	//
	return 0;

}
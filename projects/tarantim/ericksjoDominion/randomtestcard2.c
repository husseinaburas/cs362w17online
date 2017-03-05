#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"
#include "randomtests.h"

#define TESTSTATEMENTS false
#define N 100000

//Assert function, 3rd argument is operator, use: 0 for =, 1 for <, 2 for >
int assertTrue(int arg1, int arg2, int op){
	if(op == 0){
		if(arg1 == arg2){
			if(TESTSTATEMENTS){
				printf(">>>test successful\n\n");
			}
			return 0;					
		}else{
			if(TESTSTATEMENTS){
				printf(">>>test failed\n\n");
			}
			return -1;
		}
	}else if(op == 1){
		if(arg1 < arg2){
			if(TESTSTATEMENTS){
				printf(">>>test successful\n\n");			
			}
			return 0;
		}else{
			if(TESTSTATEMENTS){
				printf(">>>test failed\n\n");
			}
			return -1;
		}
	}else if(op == 2){
		if(arg1 > arg2){
			if(TESTSTATEMENTS){
				printf(">>>test successful\n\n");
			}
		}else{
			if(TESTSTATEMENTS){
				printf(">>>test failed\n\n");
			}
			return -1;
		}
	}
	return 0;
}//end assertTrue


//Generates random inputs for the state to initialize before testing
int randInit(struct gameState *state, int testCard){
	int 	numPlayers;
	int 	randPos, randCard;
	int 	seed;
	int 	i, j;
	int 	dup;
	int 	k[10];
	char	*tmpCard;

//test printing
	if(TESTSTATEMENTS){
		printf("size of k = %lu, size of int = %lu, so k/ so int = %lu\n\n", sizeof(k), sizeof(k[0]), sizeof(k)/sizeof(k[0]));
	}
	
	//Set k[] array to randomly determined cards. will assign card from valid range(no 
	// curse, victory, or treasure cards), also makes sure no cards are repeated.
	for(i = 0; i < (sizeof(k) / sizeof(k[0])); i++){
		do{
			dup = 0;
			k[i] = rand() % 20 + 7;
			for(j = 0; j < i; j++){
				if(k[j] == k[i])
					dup = 1; 
			}			
		}while(dup == 1);
	}
	////test printing
	if(TESTSTATEMENTS){
		for(i = 0; i < 10; i++){
			printf("k[%d] = %d\n", i, k[i]);
		}
	}

////////////////////////////////////////randomly set num players, seed
	numPlayers = rand() % (MAX_PLAYERS - 1) + 2;
	if(TESTSTATEMENTS){
		printf("numPlayers = %d\n",  numPlayers);
	}

	seed = rand() % 10000 + 1;
	//randomly choose choice options, wont be relevant for most cards, would need to be adjusted
	//for cards that do use, as each one is used differently.
	

	//Call initialize to set initial values with random fields from above
	initializeGame(numPlayers, k, seed, state);
	int x;
	//after initial settings, set some other fields to be random
	state->outpostPlayed = rand() % 2;
	state->outpostTurn = rand() % 2;
	if(numPlayers > 0){
		x = rand() % numPlayers;
		state->whoseTurn = x;
	}
	state->phase = rand() % 3;
	state->numActions = rand() % 10;
	state->coins = rand() % 7;
	state->numBuys = rand() % 6;
	

	//add card being tested to random position in hand
	if(state->handCount[state->whoseTurn] > 0){
		randPos = rand() % state->handCount[state->whoseTurn];
	}else{
		randPos = 0;
	}
	state->hand[state->whoseTurn][randPos] = testCard;
	if(TESTSTATEMENTS){
		printf("state->handCount[state->whoseTurn = %d\n",  state->handCount[state->whoseTurn]);
		printf("randPos = %d\n", randPos);
	}

	//test printing supply counts and hand
	tmpCard = (char*)malloc(15 * sizeof(char));
	if(TESTSTATEMENTS){
		for(i = 0; i < 27; i++){
			cardNumToName(i, tmpCard);
			printf("Supply count for %s = %d\n", tmpCard, state->supplyCount[i]);
		}

		for(i = 0; i < state->handCount[state->whoseTurn]; i++){
			cardNumToName(state->hand[state->whoseTurn][i], tmpCard);
			printf("Card in hand pos %d = %s\n", i, tmpCard);
		}
	}

	//set deck to have a random selection of cards from available supply
	state->deckCount[state->whoseTurn] = rand() % 10 + 1;
	for(i = 0; i < state->deckCount[state->whoseTurn]; i++){
		do{
			randCard = rand() % 27;
			state->deck[state->whoseTurn][i] = randCard;
			
		}while(state->supplyCount[randCard] < 0);
	}

	if(TESTSTATEMENTS){
		for(i = 0; i < state->deckCount[state->whoseTurn]; i++){
			cardNumToName(state->deck[state->whoseTurn][i], tmpCard);
			printf("Card in deck pos %d = %s\n", i, tmpCard);
		}
	}

	return 0;
}

int main(int argc, char *argv[]){
	char 	*testCard;
	char 	*curCard;
	int 	testCardNum;
	int 	curPlayer;
	int 	cardCnt;
	int 	results;
	int 	randSeed;
	int 	i, k;
	int 	choice1, choice2, choice3;
	int 	handpos = 0;
	int 	bonus = 0;
	struct 	gameState state;
	struct 	gameState pretest;
	
	if(argc == 2){
		randSeed = atoi(argv[1]);
		srand(randSeed);
	}else{
		srand(time(NULL));	
	}
	
	///Set n to how many times to run the tests
	//n = 10000;

	//Set Test Card Here - testing Adventurer Card
	testCardNum = village; 
	testCard = (char*)malloc(15 * sizeof(char));
	cardNumToName(testCardNum, testCard);
	printf("testcard = %s\n\n", testCard);

	struct 	testResults rndmTests = {
		{0,0,0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0},
		{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}
	};

		printf("********************************Testing %s Card****************************\n", testCard);
	for(k = 0; k < N; k++){
		randInit(&state, testCardNum);
		//set all struct values to 0
		//set choices to random int, N/A for these tests
		choice1 = rand () % 27;
		choice2 = rand () % 27;
		choice3 = rand () % 27;
		bonus = rand() % 10;

		curCard = (char*)malloc(15 * sizeof(char));

		curPlayer = state.whoseTurn;

		//save state before running tests
		memcpy(&pretest, &state, sizeof(struct gameState));


		//print who current player is
		if(TESTSTATEMENTS){
			printf("state.whoseTurn = %d\n\n", state.whoseTurn);
		}
		rndmTests.whoseTurnCnt[state.whoseTurn]++;
		//confirm test card in hand before attempting to play
		for(i=0; i<state.handCount[curPlayer]; i++){
			if(state.hand[curPlayer][i] == testCardNum){
				cardCnt++;
				handpos = i;//keeps track of last place card is found
			}
		}
		if(TESTSTATEMENTS){
			printf("%s cards in hand before call: %d\n",testCard, cardCnt);
		}
		if(assertTrue(cardCnt, 0, 2) == 0){
			rndmTests.targetcardCnt[0]++;
		}else{
			rndmTests.targetcardCnt[1]++;
		}

		results = cardEffect(testCardNum, choice1, choice2, choice3, &state, handpos, &bonus);
		
		//check return value
		if(TESTSTATEMENTS){
			printf("expected return value = 0\n");
			printf("acutal return value = %d\n", results);
		}
		if(assertTrue(0, results, 0) == 0){
			rndmTests.returnVal[0]++;		
		}else{
			rndmTests.returnVal[1]++;
		}

		if(TESTSTATEMENTS){
			printf("card played, check 1 card added and 1 removed\n");
			//check that hand count increase by 2 for current player
			printf("check that hand count increased by net 0(1 added 1 removed)\n");
			printf("hand count before calling buyCard() = %d\n", pretest.handCount[curPlayer]);
			printf("hand count after calling buyCard() = %d\n", state.handCount[curPlayer]);
		}
		if(assertTrue(pretest.handCount[curPlayer], state.handCount[curPlayer], 0) == 0){
			rndmTests.handcountTest[0]++;
		}else{
			rndmTests.handcountTest[1]++;
		}

		if(TESTSTATEMENTS){
			printf("check that deckCount decremented by 1\n");
			printf("deckCount before call = %d, after call %d\n", pretest.deckCount[curPlayer], state.deckCount[curPlayer]);
		}
		if(assertTrue(pretest.deckCount[curPlayer], state.deckCount[curPlayer], 0) == 0){
			rndmTests.deckcountTest[0]++;
		}else{
			rndmTests.deckcountTest[1]++;
		}

		if(TESTSTATEMENTS){
			printf("check playedCard count incremented by 1\n");
			printf("playedCardCount before call = %d, after call %d\n", pretest.playedCardCount, state.playedCardCount);
		}
		if(assertTrue(pretest.playedCardCount + 1, state.playedCardCount, 0) == 0){
			rndmTests.playedcardcntTest[0]++;		
		}else{
			rndmTests.playedcardcntTest[1]++;
		}

		cardNumToName(state.playedCards[state.playedCardCount-1], curCard);
		if(TESTSTATEMENTS){
			printf("check playedCard includes %s in last spot\n", testCard);	
			if(state.playedCardCount > pretest.playedCardCount){
				printf("card in index %d is %s\n", state.playedCardCount-1, curCard );
			}else{
				printf("No cards in the playedCard pile\n");
			}
		}
		if(assertTrue(state.playedCards[state.playedCardCount-1], testCardNum, 0) == 0){
			rndmTests.playedcardpileTest[0]++;		
		}else{
			rndmTests.playedcardpileTest[1]++;
		}

		if(TESTSTATEMENTS){
			printf("pretest numActions: %d, posttest numActions %d\n", pretest.numActions, state.numActions);
		}
		if(assertTrue(pretest.numActions + 2, state.numActions, 0) == 0){
			rndmTests.numactionTest[0]++;		
		}else{
			rndmTests.numactionTest[1]++;
		}

		/////////////////////////////////////////////////

		if(TESTSTATEMENTS){
			printf("check other game state field to ensure not altered\n");
			printf("pretest outpostPlayed: %d, posttest outpostPlayed: %d\n", pretest.outpostPlayed, state.outpostPlayed);
		}
		
		if(assertTrue(pretest.outpostPlayed, state.outpostPlayed, 0) == 0){
			rndmTests.outpostTest[0]++;
		}else{
			rndmTests.outpostTest[1]++;
		}

		if(TESTSTATEMENTS){
			printf("pretest phase: %d, posttest phase: %d\n", pretest.phase, state.phase);
		}
		if(assertTrue(pretest.phase, state.phase, 0) == 0){
			rndmTests.phaseTest[0]++;
		}else{
			rndmTests.phaseTest[1]++;
		}


		if(TESTSTATEMENTS){
			printf("pretest numBuys: %d, posttest numBuys %d\n", pretest.numBuys, state.numBuys);
		}
		if(assertTrue(pretest.numBuys, state.numBuys, 0) == 0){
			rndmTests.numbuysTest[0]++;
		}else{
			rndmTests.numbuysTest[1]++;
		}

		if(TESTSTATEMENTS){
			printf("check that hand count for other players unchanged\n");
		}
		for(i = 0; i < state.numPlayers; i++){
			if(i != state.whoseTurn){
				if(TESTSTATEMENTS){
					printf("Player %d hand count before call= %d, after call() = %d\n", i, pretest.handCount[i], state.handCount[i]);
				}
				if(assertTrue(pretest.handCount[i], state.handCount[i], 0) == 0){
					rndmTests.otherhandsTest[0]++;
				}else{
					rndmTests.otherhandsTest[1]++;
				}
			}//end if
		}//end for

		if(TESTSTATEMENTS){
			printf("check that deck count for other players unchanged\n");
		}

		for(i = 0; i < state.numPlayers; i++){
			if(i != state.whoseTurn){
				if(TESTSTATEMENTS){
					printf("Player %d deck count before call= %d, after call() = %d\n", i, pretest.deckCount[i], state.deckCount[i]);
				}
				if(assertTrue(pretest.deckCount[i], state.deckCount[i], 0) == 0){
					rndmTests.otherdecksTest[0]++;
				}else{
					rndmTests.otherdecksTest[1]++;
				}
			}
		}

		
	}//end main for loop

////////////////////////////////////////////////////end test run
	/////////////////////print stats from test run

	printf("************************************* Test Results *********************************\n");
	printf("Number of times tests ran = %d\n", N);/////add in iteration counter
	for(i = 0; i < MAX_PLAYERS; i++){
		printf("Number of tests for Player %d = %d\n", i + 1, rndmTests.whoseTurnCnt[i]);
	}
	printf("Verify that %s card was in current players hand\nPassed: %d\nFailed: %d\n", \
		testCard, rndmTests.targetcardCnt[0], rndmTests.targetcardCnt[1]);
	
	printf("Check return value of cardEffect with %s card\nPassed: %d\nFailed: %d\n", \
		testCard, rndmTests.returnVal[0], rndmTests.returnVal[1]);
	
	printf("Verify playedCardCount incremented\nPassed: %d\nFailed: %d\n", \
		rndmTests.playedcardcntTest[0], rndmTests.playedcardcntTest[1]);
	
	printf("Verify outpost not altered\n");
	printf("Passed: %d\nFailed: %d\n", rndmTests.outpostTest[0], rndmTests.outpostTest[1]);


	printf("Verify phase not altered\n");
	printf("Passed: %d\nFailed: %d\n", rndmTests.phaseTest[0], rndmTests.phaseTest[1]);
	
	printf("Verify numActions increased by 2\n");
	printf("Passed: %d\nFailed: %d\n", rndmTests.numactionTest[0], rndmTests.numactionTest[1]);
	
	printf("Verify numBuys not altered\n");
	printf("Passed: %d\nFailed: %d\n", rndmTests.numbuysTest[0], rndmTests.numbuysTest[1]);
	
	printf("Verify the other players hands not altered\n");
	printf("Passed: %d\nFailed: %d\n", rndmTests.otherhandsTest[0], rndmTests.otherhandsTest[1]);
	
	printf("Verify the other players decks not altered\n");
	printf("Passed: %d\nFailed: %d\n", rndmTests.otherdecksTest[0], rndmTests.otherdecksTest[1]);
	
	printf("Verify that hand count increased by 0 (1 added, 1 removed\n");
	printf("Passed: %d\nFailed: %d\n", rndmTests.handcountTest[0], rndmTests.handcountTest[1]);

	printf("Verify that deck count decreased by 1\n");
	printf("Passed: %d\nFailed: %d\n", rndmTests.deckcountTest[0], rndmTests.deckcountTest[1]);
	
	
	
	printf("********************************%s Card Testing complete****************************\n", testCard);




	return 0;
}
/***************************************
Ambrelle Palmer
cardtest4.c
Unit Test for Salvager card

cardtest4: cardtest4.c dominion.o rngs.o
     gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
*****************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

/*
Functionality to test for:
     •Current player's buyCount is increased by 1
	•Cost of the trashed card is found and added to coinCount
	•Trashed card is not returned to player hand
	•Salvager card is discarded from hand
     •No state change for other players
     •No state change in victory or kingdom card files
*/

//#define TESTCARD "salvager"
#define NOISY_TEST 1

int main(){

int handpos = 0;
int choice1 = 1;
int choice2 = 0;
int choice3 = 0;
int bonus = 0;
int numPlayers =2;
int thisPlayer = 0;
int i;
int j;
int remove;
int discarded;
int seed=1000;	

	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	//initialize game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("Testing Salvager Card");
	//Test 1: Check that buy count and coin count have changed
	printf("TEST 1: Buy count should update and coin count should update when card is played \n");

	//copy game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	//testBuyCount = testG.numBuys
	//testCoins = testG.coins;
	choice1 = 1;
	cardEffect(salvager, choice1, choice2, choice3, &testG, handpos, &bonus);

	//printf("buy count = %d, expected = %d\n", testG.numBuys[thisPlayer], G.numBuys[thisPlayer] + 1);
	//assert(testG.numBuys[thisPlayer] == G.numBuys[thisPlayer] + 1);

	//printf("coin count = %d, expected = %d\n", testG.coins, G.coins + getCost(handCard(choice1,state)));
	//assert(testG.coins == G.coins + getCost(handCard(choice1, state)));  	

	//Test 2: Check that selected card is trashed
	printf("TEST 2: Chosen card should be trashed\n");
	
	//cycle through and choose card to trash
	for (i=0; i<G.handCount[thisPlayer]; i++){
		G.hand[thisPlayer][0] = salvager;
		G.hand[thisPlayer][1] = silver;
		G.hand[thisPlayer][2] = smithy;
		G.hand[thisPlayer][3] = estate;
		G.hand[thisPlayer][4] = gold;

	//copy game state to test case
	memcpy(&testG, &G, sizeof(struct gameState));

	for (j =0; j<testG.handCount[thisPlayer]; j++){
		printf("(%d)", testG.hand[thisPlayer][j]);
		}
		printf("; ");

		choice2 = i;
		remove = testG.hand[thisPlayer][i];
		cardEffect(salvager, choice1, choice2, choice3, &testG, handpos, &bonus);

		printf("Card no longer in hand: (%d); ", remove);
		
		//make sure removed card isn't in hand anymore
		for(j=0; j<testG.handCount[thisPlayer];j++){
			printf("(%d)", testG.hand[thisPlayer][j]);
			assert(testG.hand[thisPlayer][j] != remove);
		}

		printf(", expected: ");
		for (j=1; j<G.handCount[thisPlayer]; j++){
			if (G.hand[thisPlayer][j] != G.hand[thisPlayer][i]){
				printf("(%d)", G.hand[thisPlayer][j]);
			}
		} 
	//test that one card has been trashed and the played card has been discarded
	printf("TEST 3: Check that number of cards in hand are correct");
	discarded = 2;

	printf("hand count = %d, expected = %d \n", testG.handCount[thisPlayer], G.handCount[thisPlayer] -discarded)		;
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - discarded);
	}
	
	//check that number of treasure cards in piles have not changed
	printf("TEST 4: Check that state of kingdom and treasure cards have not changed");
	
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(salvager, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	printf("copper count = %d, expected = %d \n", testG.supplyCount[copper], G.supplyCount[copper]);
	printf("silver count = %d, expected = %d \n", testG.supplyCount[silver], G.supplyCount[silver]);
	printf("gold count = %d, expected = %d \n", testG.supplyCount[gold], G.supplyCount[gold]); 
	assert(testG.supplyCount[copper] == G.supplyCount[copper]);
	assert(testG.supplyCount[silver] == G.supplyCount[silver]);
	assert(testG.supplyCount[gold] == G.supplyCount[gold]);

	for(i = 0; i < treasure_map; i++)
          if(testG.supplyCount[i] != G.supplyCount[i])
          {
               printf("Test Failed. Supply count changed for %d card\n", i);
          }

     //Test 4: Check for no state changes in other players
     printf("TEST 4: Check to see that there are no state changes for other players\n");
     for(int i = 0; i < numPlayers; i++)
     {
          if(i != thisPlayer)
          {
               //check that player's deck count didn't change
               if(testG.deckCount[i] != G.deckCount[i])
               {
                    printf("Test Failed. Incorrect deck count change for player %d\n", i);
               }

               if(testG.handCount[i] != G.handCount[i])
               {
                    printf("Test Failed. Incorrect hand count change for player %d\n", i);
               }

          }
     }


	printf("\n TESTING OF SALVAGER CARD COMPLETED\n");

	return 0;
}

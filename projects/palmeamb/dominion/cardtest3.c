/****************************************
Ambrelle Palmer
cardtest3.c
Unit Test for Smithy card

cardtest3: cardtest3.c dominion.o rngs.o
     gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
*****************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

/*
Functionality to test for:
     •Current player draws exactly 3 cards from their deck
	•Player has one less action to play
	•No state change for other players (not sure how to implement)
     •No state change in victory or kingdom card files
	•Smithy card is discarded
*/

#define TESTCARD "smithy"
#define NOISY_TEST 1

int main(){

     int choice1 =0, choice2 = 0, choice3 = 0, handpos = 0, bonus = 0;
     int numPlayers = 2;
     int newCards = 0;
     int discarded = 1;
     int shuffledCards = 0;
     int newActions = 0;
	int thisPlayer = 0;

     struct gameState G, testG;
     int  k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

     //initialize game state and player cards
     initializeGame(numPlayers, k, seed, &G);

     printf("Testing Card: &s \n", TESTCARD);
     //Test 1: Check that buy card count and deck count have changed
     printf("TEST 1: 3 cards are added to player's hand from deck \n")

	//copy game state to a test case
     memcpy(&testG, &G, sizeof(struct gameState));

     cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

     newCards = 3;

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);

	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	assert(testG.deckCount[thisPlayer] == G.handCount[thisPlayer] - newCards + shuffledCards);

	//Test2: Check that smithy card has been discarded
	printf("TEST 2: Check to see that smithy card has been discarded from hand\n")

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - discarded);

	 //Test 3: Check for no state change in victory or kingdom card piles
     printf("TEST 3: Check to see that there has been no change in victory or kingdom card piles\n");

     printf("copper count = %d, expected = %d \n", testG.supplyCount[copper], G.supplyCount[copper]);
     printf("silver count = %d, expected = %d \n", testG.supplyCount[silver], G.supplyCount[silver]);
     printf("gold count = %d, expected = %d \n", testG.supplyCount[gold], G.supplyCount, [gold]);
     assert(testG.supplyCount[copper] == G.supplyCount[copper]);
     assert(testG.supplyCount[silver] == G.supplyCount[silver]);
     assert(testG.supplyCount[gold] == G.supplyCount[gold]);

	for(i = 0; i < treasure_map, i++)
          if(testG.supplyCount[i] != G.supplyCount[i])
          {
               printf("Test Failed. Supply count changed for %d card\n", i)
          }

     //Test 4: Check for no state changes in other players
     printf("TEST 4: Check to see that there are no state changes for other players\n");
     for(int i = 0; i < numPlayers, i++)
     {
          if(i != thisPlayer)
          {
               //check that player's deck count didn't change
               if(testG.deckCount[i] != G.deckCount[i])
               {
                    printf("Test Failed. Incorrect deck count change for player %d\n", i);
                    return = -1
               }

               if(testG.handCount[i] != G.handCount[i])
               {
                    printf("Test Failed. Incorrect hand count change for player %d\n", i);
               }

          }
     }


     printf("\n TESTING OF SMITHY CARD COMPLETED\n");

     return 0;
}

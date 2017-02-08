/***************************************
Ambrelle Palmer
cardtest2.c
Unit Test for Adventurer card

cardtest2: cardtest2.c dominion.o rngs.o
     gcc -o cardtest1 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
*****************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

/*
Functionality to test for:
	•Cards are drawn until 2 treasure cards are added to player's hand from their deck
	•All other cards drawn are discarded (handCount only increased by 2)
	•No state change for other players 
	•No state change for victory or kingdom card files
	•adventurer card is discarded
*/

//#define TESTCARD "adventurer"
#define NOISY_TEST 1

int main(){

     int choice1 =0, choice2 = 0, choice3 = 0, handpos = 0, bonus = 0;
     int numPlayers = 2;
     int newCards = 0;
     int discarded = 1;
     int shuffledCards = 0;
     int newActions = 1;
     int thisPlayer = 0;
	int addTreasure = 0;
	int seed = 1000;
	int i;

     struct gameState G, testG;
     int  k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

     //initialize game state and player cards
     initializeGame(numPlayers, k, seed, &G);

     printf("Testing Adventurer Card");
	//Test 1:Check that hand Count has increased by 2 and deck has decreased by appropriate number ----- Having trouble figuring out how to test discarded cards and deck count
	printf("TEST 1: Checking to see that hand and deck counts have adjusted correctly\n");	

	//copy game state to a test case
     memcpy(&testG, &G, sizeof(struct gameState));

     cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);	     

	printf("hand count = %d, expected hand count = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 2 - 1);
     assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 2 - 1);

     printf("deck count = %d, expected deck count = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
     assert(testG.deckCount[thisPlayer] == G.handCount[thisPlayer] - newCards + shuffledCards);

     //Test 2: Check that Adventurer card is discarded
     printf("TEST 2: Check to see that number of cards in hand is correct after Adventurer has been discarded\n");
     discarded = 1;

     printf("hand count = %d, expected hand count = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded);
     assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - discarded);
	
	//Test 3: check that number of treasure cards in piles have not changed
     printf("TEST 3: Check that state of kingdom and treasure cards have not changed");

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


     printf("\n TESTING OF ADVENTURER CARD COMPLETED\n");

     return 0;
}


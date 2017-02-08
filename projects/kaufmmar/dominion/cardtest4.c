/* Name: Marina Kaufman
OSU_CS362_Assignment 3
Due Date: 02.07.17
Description: Unit test for card Great Hall. Postconditions: player gets 1 more card and 1 Action. 
*/

#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"

#define TESTCARD "great_hall"

int main(){
  int handPos = 0;
  int num_players = 2; 
  int seed = 1000; 
  int ch1  = 0; 
  int ch2 = 0; 
  int ch3 = 0; 
  int newActions = 1; 
  int gained = 1; 
  int discarded = 1; 
  int success = 0;
  int player = 0;
	struct gameState G, testG;
	int k[10] = {smithy, great_hall, gardens, minion, mine, cutpurse,
    sea_hag, tribute, adventurer, council_room};
	
	//initialize the game 
	initializeGame(num_players, k, seed, &G);
  memcpy(&testG, &G, sizeof(struct gameState));

	printf("-------------------------- Testing Card: %s ------------------------\n", TESTCARD);
	
	printf("\nTEST 1:\n Player draws Great Hall card \n");
	
   //player draws Great Hall Card
  testG.hand[player][handPos]= great_hall;
  cardEffect(great_hall,ch1,ch2,ch3,&testG,handPos,0);
  
  // handCount doesn't change (+1 card, - great hall)
  printf("handCount = %d, expected = %d\n",testG.handCount[player],G.handCount[player]);
  success = testG.handCount[player]==G.handCount[player];
  
  // number of Actions is increased by 1 
  printf(" actionsNum = %d, expected = %d\n",testG.numActions,G.numActions+newActions);
  success = success && testG.numActions==G.numActions+newActions;
  
  // deckCount is decreased by 1
  printf("deckCount = %d, expected = %d\n",testG.deckCount[player],G.deckCount[player]-gained);
  success = success && testG.deckCount[player]==G.deckCount[player]-gained;

 
  // discardCount is increased by 1 (great hall)
  printf("discardCount = %d, expected = %d\n",testG.discardCount[player],G.discardCount[player]+discarded);
  success = success && testG.discardCount[player]==G.discardCount[player]+discarded;

  
   printf("TEST 2: The state of the game should not change\n");
  
  // the same player still has the turn   
  printf("player = %d, expected = %d\n", testG.whoseTurn, G.whoseTurn); 
  success = success && testG.whoseTurn == G.whoseTurn; 

  //output the test results
  if(success){
    printf("\n >>>>> SUCCESS: Testing complete for: %s <<<<<\n\n", TESTCARD);
  }else{
    printf("\n >>>>> FAILURE: Testing failed for:  %s <<<<<\n\n", TESTCARD);
  }
  return 0;
}
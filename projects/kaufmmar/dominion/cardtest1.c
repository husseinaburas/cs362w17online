/* Name: Marina Kaufman
OSU_CS362_Assignment 3
Due Date: 02.07.17
Description: success unit for Smithy card. 
Postconditions: handCount of a current player is increased by 3; deckCount of a current player is
decreased by 3.
*/

#include "dominion.h"
#include <stdlib.h>
#include <stdio.h>

#define TESTCARD "smithy"

int main(){
  int handPos = 0;
  int player = 0;
  int num_players = 2; 
  int ch1 = 0; 
  int ch2 = 0; 
  int ch3 = 0; 
  int seed = 1000;
  int success=0;
  int new_cards = 3; 
  int discarded = 1; 
   
	struct gameState G, testG;
	int k[10] = {smithy, great_hall, gardens, minion, mine, cutpurse,
    sea_hag, tribute, adventurer, council_room};
	
	//initialize the game
	initializeGame(num_players, k, seed, &G);
	
	//copy pre game state to post state
    memcpy(&testG, &G, sizeof(struct gameState));

	printf("-------------------------- Testing Card: %s ------------------------\n", TESTCARD);
	
	printf("TEST 1: player plays smithy card\n");
  //player gets smithy card
  testG.hand[player][handPos]= smithy;
  cardEffect(smithy,ch1,ch2,ch3,&testG,handPos,0);

  // post handCount of current player == pre HandCount + 3 new cards - 1 discarded smithy
  printf("handCount = %d, expected %d\n",testG.handCount[player],G.handCount[player]+new_cards-discarded);
  success = testG.handCount[player]==G.handCount[player]+new_cards-discarded;
  
  // smithy added to discarded deck
  printf("discardCount = %d, expected %d\n",testG.discardCount[player],G.discardCount[player]+discarded);
  success = success && testG.discardCount[player]==G.discardCount[player]+discarded;

  // post deck of current player == pre deck - 3 new cards
  printf("deckCount = %d, expected %d\n",testG.deckCount[player],G.deckCount[player]-new_cards);
  success = success && testG.deckCount[player]==G.deckCount[player]-new_cards;

  printf("TEST 2: The state of the game should not change\n");
  
  // the same player still has the turn   
  printf("player = %d, expected = %d\n", testG.whoseTurn, G.whoseTurn); 
  success = success && testG.whoseTurn == G.whoseTurn; 
  
  // victory cards pile should stay the same
  printf( "supplyCount[estate] = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);
  success = success && testG.supplyCount[estate] == G.supplyCount[estate]; 
  printf( "supplyCount[duchy] = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
  success = success && testG.supplyCount[duchy] == G.supplyCount[duchy]; 
  printf( "supplyCount[province] = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
  success = success && testG.supplyCount[province] == G.supplyCount[province];
  
  //output the test results 
  if(success){
    printf("\n >>>>> SUCCESS: Testing complete for: %s <<<<<\n\n", TESTCARD);
  }else{
    printf("\n >>>>> FAILURE: Testing failed for:  %s <<<<<\n\n", TESTCARD);
  }
  
  return 0;
}

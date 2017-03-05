/* Name: Marina Kaufman
OSU_CS362_Assignment 4
Due Date: 02.16.17
Description: Random Test generator for Smithy card. 
Postconditions: handCount of a current player is increased by 3; deckCount of a current player is
decreased by 3.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#define TESTCARD "smithy"

int main(){
	
  int testNum = 1; 
  int i; 
  int numTests = 10; 
  int handPos = 0;
  int player; 
  int ch1 = 0; 
  int ch2 = 0; 
  int ch3 = 0; 
  int seed = 1000;
  int new_cards = 3; 
  int discarded = 1; 
  srand((unsigned)time(NULL));  
	struct gameState G, testG;
	int k[10] = {smithy, great_hall, gardens, minion, mine, cutpurse,
    sea_hag, tribute, adventurer, council_room};
	
	for (i = 0; i < numTests; i++){ 
	
	int success=0; 
	int num_players = rand()% 4 +1; 
    player = rand()% 2 + 1; 
	G.deckCount[player] = rand()% MAX_DECK+1;
    G.discardCount[player] = rand()%MAX_DECK+1;
    G.handCount[player] =rand()%MAX_HAND+1;
	
	
	
	//initialize the game
	initializeGame(num_players, k, seed, &G);
	
	//copy pre game state to post state
    memcpy(&testG, &G, sizeof(struct gameState));
	
	

	printf("-------------------------- Test #: %d for Card: %s ------------------------\n", testNum, TESTCARD);
	
	printf("The number of players: %d\n", num_players);
	
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
   
  printf("Test Number: %d", testNum); 
  testNum++;
  if(success){
    printf("\n >>>>> SUCCESS: Testing complete for: %s <<<<<\n\n", TESTCARD);
  }else{
    printf("\n >>>>> FAILURE: Testing failed for:  %s <<<<<\n\n", TESTCARD);
  }
	} 
  
  return 0;
}

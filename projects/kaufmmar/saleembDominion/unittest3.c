/* Name: Marina Kaufman
OSU_CS362_Assignment 3
Due Date: 02.07.17
Description: Test Unit for a method isGameOver(). Game ends either 1. All 3 supply piles 
are empty or 2. Province stack is empty
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>


int main() {
  int i;
  int success = 0;
  int result;
  int num_players = 2; 
  int seed  = 1000; 
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    
	//initialize the game 
	initializeGame(num_players, k, seed, &G);

	printf("------------------------ Testing a function isGameOver() -------------------------\n");

  printf("\nTEST 1:\n Supply piles are not empty)\n");
  
  //supply piles are not empty
  for(i=0; i<=treasure_map; i++){
    G.supplyCount[i] = 1;
  }
  result = isGameOver(&G);
  printf("isGameOver = %d, expected = %d\n",result,0);
  
  success = result == 0; 

   printf("\nTEST 2:\n Province stack is not empty\n");
  G.supplyCount[province] = 2;
  result = isGameOver(&G);
  printf("isGameOver =  %d, expected =  %d\n",result,0);
  
  success = success && result == 0; 
  
  printf("\nTEST 3:\n Province supply is empty\n");
  G.supplyCount[province] = 0;
  result = isGameOver(&G);
  printf(" isGameOver returned %d, expected %d\n",result,1);
  
  success = success && result == 1; 

  printf("\nTEST 4:\n All 3 supply piles are empty\n");
  G.supplyCount[province] = 1;
  G.supplyCount[curse] = 0;
  G.supplyCount[gold] = 0;
  G.supplyCount[treasure_map] = 0;
  result = isGameOver(&G);
  printf("isGameOver = %d, expected  = %d\n",result,1);
  
  success = success && result == 1; 
  
  //output the test results
  if(success){
    printf("\n >>>>> SUCCESS: Testing complete for: isGameOver()<<<<<\n\n");
  }else{
    printf("\n >>>>> FAILURE: Testing failed for: isGameOver() <<<<<\n\n");
  }
  
  return 0;
}
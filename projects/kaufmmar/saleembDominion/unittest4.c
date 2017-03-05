/* Name: Marina Kaufman
OSU_CS362_Assignment 3
Due Date: 02.07.17
Description: Test Unit for a method shuffle(). 
*/

#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(){
	struct gameState G, testG;
	int result; 
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 1000; 
	int num_players = 2; 
	int success = 0; 
	
	//initialize the game
	initializeGame(num_players, k, seed, &G);
	
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("------------------------ Testing a function shuffle() -------------------------\n");

    printf("\nTEST 1:\n Shuffling a deck with a count < 1\n");
	G.deckCount[1] = -5;
	result = shuffle(1, &G);
	printf("shuffle = %d, expected = %d\n",result,-1);
	success = result == -1;
	
	
	printf("\nTEST 2:\n Shuffling a deck with a count >0\n");
	G.deckCount[1] = 5;
	result = shuffle(1, &G);
	printf("shuffle = %d, expected = %d\n",result,0);
	success = success && result == 0;
	
	printf("\nTEST 3:\n A method does not change the game state\n");
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
  
  // curse cards pile should stay the same 
  printf( "supplyCount[curse] = %d, expected = %d\n", testG.supplyCount[curse], G.supplyCount[curse]);
  success = success && testG.supplyCount[curse] == G.supplyCount[curse]; 
 
  
  // treasure cards pile should stay the same
  printf( "supplyCount[copper] = %d, expected = %d\n", testG.supplyCount[copper], G.supplyCount[copper]);
  success = success && testG.supplyCount[copper] == G.supplyCount[copper]; 
  printf( "supplyCount[silver] = %d, expected = %d\n", testG.supplyCount[silver], G.supplyCount[silver]);
  success = success && testG.supplyCount[silver] == G.supplyCount[silver]; 
  printf( "supplyCount[gold] = %d, expected = %d\n", testG.supplyCount[gold], G.supplyCount[gold]);
  success = success && testG.supplyCount[gold] == G.supplyCount[gold];
	
  //output the test results
  if(success){
    printf("\n >>>>> SUCCESS: Testing complete for: shuffle()<<<<<\n\n");
  }else{
    printf("\n >>>>> FAILURE: Testing failed for: shuffle() <<<<<\n\n");
  }
	return 0;
}
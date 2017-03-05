/* Name: Marina Kaufman
OSU_CS362_Assignment 3
Due Date: 02.07.17
Description: Test Unit for method fullDeckCount() 
*/ 

#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"


int main(){
  int i;
  int result;
  int totalCount;
  int success = 0;
  int player = 0;
  int num_players = 2; 
  int seed = 1000; 
	struct gameState G, testG;
	int k[10] = {steward, great_hall, gardens, minion, mine, cutpurse,
    sea_hag, tribute, adventurer, council_room};
	
	//initialize the game
	initializeGame(num_players, k, seed, &G);
  memcpy(&testG, &G, sizeof(struct gameState));

	printf("------------------------ Testing function fullDeckCount() -------------------------\n");
	
	printf("\nTEST 1:\n Card is not in game\n");
	
	totalCount = 0;
	//smithy is not in game, count == 0
	result = fullDeckCount(player, smithy, &testG);
	printf("fullDeckCount = %d, expected = %d\n",result,totalCount);
	success = totalCount == result; 
	
	printf("\nTEST 2:\n A card is in deck\n");
    memcpy(&testG, &G, sizeof(struct gameState));

	totalCount = 1;
    testG.deckCount[player]=4;
	for(i=0; i<testG.deckCount[player];i++){
      testG.deck[player][i]=smithy;
	}
	for(i=0; i<testG.handCount[player];i++){
      testG.hand[player][i]=smithy;
	}
	for(i=0; i<testG.discardCount[player];i++){
      testG.discard[player][i]=smithy;
	}
	//set up a deck
	testG.deck[player][0] = silver;
	testG.deck[player][testG.deckCount[player]-1] = silver;
	
	result = fullDeckCount(player, silver, &testG);
	printf("fullDeckCount = %d, expected = %d\n",result,totalCount);
	
    success = success && result == totalCount; 
  

  
    printf("\nTEST 3:\n A card is in discard pile\n");
    memcpy(&testG, &G, sizeof(struct gameState));

	totalCount = 1;

	for(i=0; i<testG.deckCount[player];i++){
      testG.deck[player][i]=smithy;
	}
	for(i=0; i<testG.handCount[player];i++){
      testG.hand[player][i]=smithy;
	}
	testG.discardCount[player]=4;
	for(i=0; i<testG.discardCount[player];i++){
      testG.discard[player][i]=smithy;
	}
	
	//set up discard pile 
	testG.discard[player][0] = silver;
	testG.discard[player][testG.discardCount[player]-1] = silver;
	
	result = fullDeckCount(player, silver, &testG);
	printf("fullDeckCount = %d, expected = %d\n",result,totalCount);
 
    success = success && result == totalCount; 
	
	printf("\nTEST 4:\n A card in playerHand\n");
    memcpy(&testG, &G, sizeof(struct gameState));

	totalCount = 1;
	for(i=0; i<testG.deckCount[player];i++){
      testG.deck[player][i]=smithy;
	}
	testG.handCount[player]=4;
	for(i=0; i<testG.handCount[player];i++){
      testG.hand[player][i]=smithy;
	}
	for(i=0; i<testG.discardCount[player];i++){
      testG.discard[player][i]=smithy;
	}
	
	// set up playerHand 
	testG.hand[player][0] = silver;
	testG.hand[player][testG.handCount[player]-1] = silver;
	
	result = fullDeckCount(player, silver, &testG);
	printf("fullDeckCount = %d, expected %d\n",result,totalCount);
    
	success = success && result == totalCount; 
	
	printf("\nTEST 5:\n A method does not change the game state\n");
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

  //output test results
  if(success){
    printf("\n >>>>> SUCCESS: Testing complete for: fullDeckCount()<<<<<\n\n");
  }else{
    printf("\n >>>>> FAILURE: Testing failed for: fullDeckCount() <<<<<\n\n");
  }
  return 0;
}
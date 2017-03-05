/* Name: Marina Kaufman
OSU_CS362_Assignment 3
Due Date: 02.07.17
Description: TEst Unit for a method scoreFor()
*/

#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"

int main(){
  int i;
  int result;
  int countTotal;
  int success = 0;
  int player = 0;
  int num_players = 2; 
  int seed = 1000; 
	struct gameState G, testG;
	int k[10] = {adventurer, great_hall, gardens, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};
	
	//initialize the game
	initializeGame(num_players, k, seed, &G);
  memcpy(&testG, &G, sizeof(struct gameState));

	printf("------------------------ Testing a function scoreFor() -------------------------\n");
	
	printf("\nTEST 1:\n Score from playerHand\n");
	for(i=0; i<testG.deckCount[player];i++){
      testG.deck[player][i]=smithy;
	}
	for(i=0; i<testG.handCount[player];i++){
      testG.hand[player][i]=smithy;
	}
	for(i=0; i<testG.discardCount[player];i++){
      testG.discard[player][i]=smithy; 
	}
	//set up playerHand 
	testG.handCount[player]=5;
	testG.hand[player][0]= estate;
	testG.hand[player][1]= province;
	testG.hand[player][2]= duchy;
	testG.hand[player][3]= great_hall;
	testG.hand[player][4]= curse;
	countTotal = 1+6+3+1-1;

	result = scoreFor(player,&testG);
	printf(" scoreFor returned %d, expected %d\n",result,countTotal);
	success = result == countTotal; 
	
	 printf("\nTEST 2:\n Score from the deck\n");
    memcpy(&testG, &G, sizeof(struct gameState));
	for(i=0; i<testG.deckCount[player];i++){
      testG.deck[player][i]=smithy;
	}
	for(i=0; i<testG.handCount[player];i++){
      testG.hand[player][i]=smithy;
	}
	for(i=0; i<testG.discardCount[player];i++){
      testG.discard[player][i]=smithy;
	}
	
	//set up deck
	testG.deckCount[player]=5;
	testG.deck[player][0]= estate;
	testG.deck[player][1]= province;
	testG.deck[player][2]= duchy;
	testG.deck[player][3]= great_hall;
	testG.deck[player][4]= curse;
	countTotal = 1+6+3+1-1;

	result = scoreFor(player,&testG);
	printf("scoreFor = %d, expected = %d\n",result,countTotal);
    success = success && result == countTotal; 
	
	 printf("\nTEST 3:\n Score from discard pile\n");
    memcpy(&testG, &G, sizeof(struct gameState));
	for(i=0; i<testG.deckCount[player];i++){
      testG.deck[player][i]=adventurer;
	}
	for(i=0; i<testG.handCount[player];i++){
      testG.hand[player][i]=adventurer;
	}
	
	//set up discard pile 
	testG.discardCount[player] = 5;
	testG.discard[player][0]= estate;
	testG.discard[player][1]= province;
	testG.discard[player][2]= duchy;
	testG.discard[player][3]= great_hall;
	testG.discard[player][4]= curse;
	countTotal = 1+6+3+1-1;

	result = scoreFor(player,&testG);
	printf("scoreFor = %d, expected = %d\n",result,countTotal);
    success = success && result == countTotal; 
  

  printf("\nTEST 4:\n Score for garden card\n");
    memcpy(&testG, &G, sizeof(struct gameState));
	testG.deckCount[player]=5;
	testG.handCount[player]=5;
	testG.discardCount[player]=5;
	
	for(i=0; i<testG.deckCount[player];i++){
      testG.deck[player][i]=smithy;
	}
	for(i=0; i<testG.handCount[player];i++){
      testG.hand[player][i]=smithy;
	}
	for(i=0; i<testG.discardCount[player];i++){
      testG.discard[player][i]=smithy;
	}
	
	//set up playerHand with one garden card 
	testG.hand[player][0]= gardens;
	countTotal = (testG.discardCount[player]+testG.deckCount[player]+testG.handCount[player])/10;

	result = scoreFor(player,&testG);
	printf("scoreFor = %d, expected = %d\n",result,countTotal);
	success = success && result == countTotal; 
  
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
  
    //output test resuls
	if(success){
    printf("\n >>>>> SUCCESS: Testing complete for: scoreFor()<<<<<\n\n");
  }else{
    printf("\n >>>>> FAILURE: Testing failed for: scoreFor() <<<<<\n\n");
  }
	
	
  return 0;
}
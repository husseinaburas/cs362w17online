/* Name: Marina Kaufman
OSU_CS362_Assignment 3
Due Date: 02.07.17
Description: Test unit for card salvager. Postcondition: Player has one more Buy, one card is 
trashed, get the number of coins == cost of a trashed card. 
*/

#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"

#define TESTCARD "salvager"

int main(){
  
  int handPos = 0;
  int player = 0;
  int num_players = 2; 
  int seed = 1000; 
  int ch1 = 1;
  int ch2 = 0; 
  int ch3 = 0; 
  int newBuys = 1;
  int discarded = 1;   
  int discardedCost = 3;
  int success = 0;
	struct gameState G, testG;
	int k[10] = {smithy, great_hall, salvager, minion, mine, cutpurse,
    sea_hag, tribute, adventurer, council_room};
	
	//initialize the game 
	initializeGame(num_players, k, seed, &G);
  memcpy(&testG, &G, sizeof(struct gameState));

	printf("-------------------------- Testing Card: %s ------------------------\n", TESTCARD);
	
	printf("\nTEST 1:\n Player draws Salvager Card and trashes Silver card with cost 3 \n");
	
  //player gets salvager card
  testG.hand[player][handPos]= salvager;
  
  //player will trash silver card with cost == 3
  testG.hand[player][ch1]= silver;
  cardEffect(salvager,ch1,ch2,ch3,&testG,handPos,0);
  
  // the number of Buys is increased by 1 
  printf("numBuys = %d, expected = %d\n",testG.numBuys, G.numBuys+newBuys);
  success = testG.numBuys== G.numBuys+newBuys;

  // number of coins is increased by the cost of trashed card == 3 
  printf("coins = %d, expected  = %d\n",testG.coins, G.coins+discardedCost);
  success =  success && testG.coins == G.coins+discardedCost;
  
    //  discarded card is not in playerHand
  printf("discarded card pos = %d, expected != %d\n",testG.hand[player][ch1], silver);
  success = success && testG.hand[player][ch1] != silver;

   // salvager card is not in playerHand
  printf("salvager card pos = %d, expected != %d\n",testG.hand[player][handPos], salvager);
  success = success && testG.hand[player][ch1] != salvager;

  // discard pile receives a discarded card 
  printf("discardCount = %d, expected = %d\n",testG.discardCount[player],G.discardCount[player]+discarded);
  success = success && testG.discardCount[player]==G.discardCount[player]+discarded;
  
  // deck doesn't not receive a discarded card
  printf("deckCount = %d, expected =  %d\n",testG.deckCount[player],G.deckCount[player]);
  success = success && testG.deckCount[player]==G.deckCount[player];

  
  printf("\nTEST 2:\n The  game G phase didn't change \n");
  
  // the same player still has the turn   
  printf("player = %d, expected = %d\n", testG.whoseTurn, G.whoseTurn); 
  success = success && testG.whoseTurn == G.whoseTurn; 

  //output test results
  if(success){
    printf("\n >>>>> SUCCESS: Testing complete for: %s <<<<<\n\n", TESTCARD);
  }else{
    printf("\n >>>>> FAILURE: Testing failed for:  %s <<<<<\n\n", TESTCARD);
  }
  return 0;
}
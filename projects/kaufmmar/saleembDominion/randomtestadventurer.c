/* Name: Marina Kaufman
OSU_CS362_Assignment 3
Due Date: 02.07.17
Description: Random test generator for Adventurer card. Postconditions: handCount of a current player is 
increased by 2 Treasure cards; all other played card are discarded.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>

#define TESTCARD "adventurer"

int main(){
	
  int testNum = 1; 
  int i;
  int numTests = 100; 
  int handPos = 0;
  int player;
  int discarded = 3; 
  int gained = 1;  
  int seed = 1000; 
  int ch1 =0; 
  int ch2 = 0; 
  int ch3 = 0; 
  
  
    srand((unsigned)time(NULL));
	struct gameState G, testG;
	int k[10] = {adventurer, great_hall, gardens, minion, mine, cutpurse,
    sea_hag, tribute,salvager , council_room};
	
	 
	for (i = 0; i < numTests; i++){ 
	
	int success=0; 
	int num_players = rand()% 4 +1; 
    player = rand()% 2 + 1; 
	G.deckCount[player] = rand()% 501;
    G.discardCount[player] = rand()%MAX_DECK+1;
    G.handCount[player] =rand()%MAX_HAND+1;
	
	//initialize the game
	initializeGame(num_players, k, seed, &G);
	
	//copy pre game G to post G
    memcpy(&testG, &G, sizeof(struct gameState));

	printf("-------------------------- Test #: %d Card: %s ------------------------\n", testNum, TESTCARD);
	
	printf("The number of players: %d\n", num_players); 
	printf("\nTEST 1:\n Playing Adventurer with treasure cards as the last one from the deck\n");

	//set player hand with adventurer
  testG.hand[player][handPos]= adventurer;
  //player must have at least 2 treasure cards or adventurer fails
  testG.deckCount[player]=4;
  testG.deck[player][0]= gold;
  testG.deck[player][1]= duchy;
  testG.deck[player][2]= province;
  testG.deck[player][3]= silver;
  cardEffect(adventurer,ch1,ch2,ch3,&testG,handPos,0);

  // the 4 card deck is empty till the second treasure card is found, which is the last card in the deck
  printf("deckCount = %d, expected  = %d\n",testG.deckCount[player],0);
  success = testG.deckCount[player]==0;
  
    // player has 2 new treasure card but no adventurer card 
  printf("handCount = %d, expected = %d\n",testG.handCount[player],G.handCount[player]+ gained);
  printf("playerHand = ");
  for(i=0; i<testG.handCount[player];i++){
    printf("%d ",testG.hand[player][i]);
  }
  printf("\n  expected hand = ");
  for(i=1; i<G.handCount[player];i++){
    printf("%d ",testG.hand[player][i]);
  }
  printf("%d %d\n", gold,silver);
  success = success && testG.handCount[player]== G.handCount[player]+gained;

  // discard pile has 2 extra victory cards and 1 adventurer card from the playerHand
  printf(" discardCount = %d, expected = %d\n",testG.discardCount[player],G.discardCount[player]+discarded);
  success = success && testG.discardCount[player]==G.discardCount[player]+discarded;
  printf("player discarded = ");
  for(i=0; i<testG.discardCount[player];i++){
    printf("%d ",testG.discard[player][i]);
  }
  printf("\n  expected = %d ",adventurer);
  for(i=0; i<G.discardCount[player];i++){
    printf("%d ",testG.discard[player][i]);
  }
  printf("%d %d\n", duchy,province);
  
  
  printf("\nTEST 2:\n Playing Adventurer with treasure cards drawn from the top of deck \n");

	//player gets an adventurer card
  testG.hand[player][handPos]= adventurer;
  
  //player must have at least 2 treasure cards or adventurer fails
  testG.deckCount[player]=4;
  testG.deck[player][0]= gold;
  testG.deck[player][1]= silver;
  testG.deck[player][2]= duchy;
  testG.deck[player][3]= province;
  cardEffect(adventurer,ch1,ch2,ch3,&testG,handPos,0);

  // deck has 2 cards left as the 2 treasure cards were drawn from the top of the deck
  printf("deckCount = %d, expected  = %d\n",testG.deckCount[player],2);
  success = testG.deckCount[player]==2;
  
    // player has 2 new treasure card but no adventurer card 
  printf("handCount = %d, expected = %d\n",testG.handCount[player],G.handCount[player]+ gained);
  printf("playerHand = ");
  for(i=0; i<testG.handCount[player];i++){
    printf("%d ",testG.hand[player][i]);
  }
  printf("\n  expected hand = ");
  for(i=1; i<G.handCount[player];i++){
    printf("%d ",testG.hand[player][i]);
  }
  printf("%d %d\n", gold,silver);
  success = success && testG.handCount[player]== G.handCount[player]+gained;

  // discard pile has 1 adventurer card from the playerHand
  printf(" discardCount = %d, expected = %d\n",testG.discardCount[player],G.discardCount[player]+gained);
  success = success && testG.discardCount[player]==G.discardCount[player]+gained;
  printf("player discarded = ");
  for(i=0; i<testG.discardCount[player];i++){
    printf("%d ",testG.discard[player][i]);
  }
  printf("\n  expected = %d ",adventurer);
  // for(i=0; i<G.discardCount[player];i++){
    // printf("%d ",testG.discard[player][i]);
  // }
  // printf("%d %d\n", duchy,province);


  printf("\nTEST 3:\n The  game state phase didn't change \n");
  
  // the same player still has the turn   
  printf("player = %d, expected = %d\n", testG.whoseTurn, G.whoseTurn); 
  success = success && testG.whoseTurn == G.whoseTurn; 
  

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

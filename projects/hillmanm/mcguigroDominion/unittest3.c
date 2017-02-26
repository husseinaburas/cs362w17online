/* matthew hillman
 * unittest4.c  updateCoins()
 * 
 */

 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTUNIT "updateCoins"

void my_assert(int test, char* msg)
{
	if (!test) {
		printf ("ASSERT HAS FAILED: %s\n", msg);
	}
	return;
}

int main() {
	int i;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

// initialize a game state 
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Unit: %s ----------------\n", TESTUNIT);
	

// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
//verify that function returns correct results for different seeded hands
	
//all copper	
	  for (i = 0; i < testG.handCount[thisPlayer]; i++) {
		testG.hand[thisPlayer][i] = copper;
		G.hand[thisPlayer][i] = copper;
	 }
	//call function and verify correct amount
		updateCoins (0, &testG, 0);
		my_assert(testG.coins == 5, "msg1");
	
	//verify nothing else in struct gamestate has changed (post call)
		G.coins = 5;
		my_assert(memcmp(&G, &testG, sizeof(struct gameState)) == 0, "msg1");  		
				
		
//all copper (as 4)	
	  for (i = 0; i < testG.handCount[thisPlayer]; i++) {
		testG.hand[thisPlayer][i] = 4;
		G.hand[thisPlayer][i] = 4;
	 }
	 //call function and verify correct amount
		updateCoins (0, &testG, 0);
		my_assert(testG.coins == 5, "msg1");
	//verify nothing else in struct state has changed (post call)
		G.coins = 5;
		my_assert(memcmp(&G, &testG, sizeof(struct gameState)) == 0, "msg1A"); 	
		
//no copper silver or gold	(cards 10-14)
	  for (i = 0; i < testG.handCount[thisPlayer]; i++) {
		testG.hand[thisPlayer][i] = (i + 10);
		G.hand[thisPlayer][i] = (i + 10);
	 }
	 //call function and verify correct amount
		updateCoins (0, &testG, 0);
		my_assert(testG.coins == 0, "msg2");
	//verify nothing else in struct state has changed (post call)
		G.coins = 0;
		my_assert(memcmp(&G, &testG, sizeof(struct gameState)) == 0, "msg2A"); 
		
		
//all silver	
	  for (i = 0; i < testG.handCount[thisPlayer]; i++) {
		testG.hand[thisPlayer][i] = silver;
		G.hand[thisPlayer][i] = silver;
	 }
	//call function and verify correct amount
		updateCoins (0, &testG, 0);
		my_assert(testG.coins == 10, "msg3");
	//verify nothing else in struct state has changed (post call)
		G.coins = 10;
		my_assert(memcmp(&G, &testG, sizeof(struct gameState)) == 0, "msg3A"); 


//all gold	
	  for (i = 0; i < testG.handCount[thisPlayer]; i++) {
		testG.hand[thisPlayer][i] = gold;
		G.hand[thisPlayer][i] = gold;
	 }
	//call function and verify correct amount
		updateCoins (0, &testG, 0);
		my_assert(testG.coins == 15, "msg4");
	//verify nothing else in struct state has changed (post call)
		G.coins = 15;
		my_assert(memcmp(&G, &testG, sizeof(struct gameState)) == 0, "msg4A"); 
		
//one of each	
		testG.hand[thisPlayer][0] = copper;
		G.hand[thisPlayer][0] = copper;
		testG.hand[thisPlayer][1] = silver;
		G.hand[thisPlayer][1] = silver;
		testG.hand[thisPlayer][2] = gold;
		G.hand[thisPlayer][2] = gold;
		testG.hand[thisPlayer][3] = smithy;
		G.hand[thisPlayer][3] = smithy;
		testG.hand[thisPlayer][4] = adventurer;
		G.hand[thisPlayer][4] = adventurer;
	//call function and verify correct amount
		updateCoins (0, &testG, 0);
		my_assert(testG.coins == 6, "msg5");
	//verify nothing else in struct state has changed (post call)
		G.coins = 6;
		my_assert(memcmp(&G, &testG, sizeof(struct gameState)) == 0, "msg5A"); 
		
//add bonus of 1


//all copper	(bonus of 1)
	  for (i = 0; i < testG.handCount[thisPlayer]; i++) {
		testG.hand[thisPlayer][i] = copper;
		G.hand[thisPlayer][i] = copper;
	 }
	//call function and verify correct amount
		updateCoins (0, &testG, 1);
		my_assert(testG.coins == 6, "msg1");
	
	//verify nothing else in struct state has changed (post call)
		G.coins = 6;
		my_assert(memcmp(&G, &testG, sizeof(struct gameState)) == 0, "msg1");  		
				
		
//all copper (as 4)		(bonus of 1)
	  for (i = 0; i < testG.handCount[thisPlayer]; i++) {
		testG.hand[thisPlayer][i] = 4;
		G.hand[thisPlayer][i] = 4;
	 }
	 //call function and verify correct amount
		updateCoins (0, &testG, 1);
		my_assert(testG.coins == 6, "msg1");
	//verify nothing else in struct state has changed (post call)
		G.coins = 6;
		my_assert(memcmp(&G, &testG, sizeof(struct gameState)) == 0, "msg1A"); 	
		
//no copper silver or gold	(cards 10-14) 	(bonus of 1)
	  for (i = 0; i < testG.handCount[thisPlayer]; i++) {
		testG.hand[thisPlayer][i] = (i + 10);
		G.hand[thisPlayer][i] = (i + 10);
	 }
	 //call function and verify correct amount
		updateCoins (0, &testG, 1);
		my_assert(testG.coins == 1, "msg2");
	//verify nothing else in struct state has changed (post call)
		G.coins = 1;
		my_assert(memcmp(&G, &testG, sizeof(struct gameState)) == 0, "msg2A"); 
		
		
//all silver		(bonus of 1)
	  for (i = 0; i < testG.handCount[thisPlayer]; i++) {
		testG.hand[thisPlayer][i] = silver;
		G.hand[thisPlayer][i] = silver;
	 }
	//call function and verify correct amount
		updateCoins (0, &testG, 1);
		my_assert(testG.coins == 11, "msg3");
	//verify nothing else in struct state has changed (post call)
		G.coins = 11;
		my_assert(memcmp(&G, &testG, sizeof(struct gameState)) == 0, "msg3A"); 


//all gold		(bonus of 1)
	  for (i = 0; i < testG.handCount[thisPlayer]; i++) {
		testG.hand[thisPlayer][i] = gold;
		G.hand[thisPlayer][i] = gold;
	 }
	//call function and verify correct amount
		updateCoins (0, &testG, 1);
		my_assert(testG.coins == 16, "msg4");
	//verify nothing else in struct state has changed (post call)
		G.coins = 16;
		my_assert(memcmp(&G, &testG, sizeof(struct gameState)) == 0, "msg4A"); 
		
//one of each		(bonus of 1)
		testG.hand[thisPlayer][0] = copper;
		G.hand[thisPlayer][0] = copper;
		testG.hand[thisPlayer][1] = silver;
		G.hand[thisPlayer][1] = silver;
		testG.hand[thisPlayer][2] = gold;
		G.hand[thisPlayer][2] = gold;
		testG.hand[thisPlayer][3] = smithy;
		G.hand[thisPlayer][3] = smithy;
		testG.hand[thisPlayer][4] = adventurer;
		G.hand[thisPlayer][4] = adventurer;
	//call function and verify correct amount
		updateCoins (0, &testG, 1);
		my_assert(testG.coins == 7, "msg5");
	//verify nothing else in struct state has changed (post call)
		G.coins = 7;
		my_assert(memcmp(&G, &testG, sizeof(struct gameState)) == 0, "msg5A");
	
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTUNIT);


	return 0;
}

/* int updateCoins(int player, struct gameState *state, int bonus)
{
  int i;
	
  //reset coin count
  state->coins = 0;

  //add coins for each Treasure card in player's hand
  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == copper)
	{
	  state->coins += 1;
	}
      else if (state->hand[player][i] == silver)
	{
	  state->coins += 2;
	}
      else if (state->hand[player][i] == gold)
	{
	  state->coins += 3;
	}	
    }	

  //add bonus
  state->coins += bonus;

  return 0;
} */
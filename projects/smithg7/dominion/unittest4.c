/***************************************
 CS362 - Assignment 3
 Gary Smith
 Unit Test for updateCoins() from dominion.c

int updateCoins(int player, struct gameState *state, int bonus)
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
}
***************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

void assertTrue(int firstValue, int secondValue, char* message);

int main()
{
  struct gameState *myState = newGame();
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
  initializeGame(2, k, 2, myState);



  /******************************************
   Testing player parameter of updateCoins() (first parameter)
  ******************************************/
  //Player 0
  int i = 0;
  int copperCount = 0;
  for (i = 0; i < myState->handCount[0]; i++)
  {
    if(myState->hand[0][i] == 4) copperCount++;
  }
  int result = updateCoins(0, myState, 0);
  assertTrue(result, 0, "Updated coins for player 0. No error from updateCoins().");
  assertTrue(myState->coins, copperCount, "Update Coins for player 0.  Correct number count.");
  initializeGame(2, k, 2, myState);

  //Player 1
  i = 0;
  copperCount = 0;
  for (i = 0; i < myState->handCount[1]; i++)
  {
    if(myState->hand[1][i] == 4) copperCount++;
  }
  result = updateCoins(1, myState, 0);
  assertTrue(result, 0, "Updated coins for player 1. No error from updateCoins().");
  assertTrue(myState->coins, copperCount, "Update Coins for player 1.  Correct number count.");
  initializeGame(2, k, 2, myState);

  //Player -1
  result = updateCoins(1, myState, 0);
  assertTrue(result, -1, "Updated coins for player -1. Error thrown from updateCoins().");
  initializeGame(2, k, 2, myState);

  //Player 4
  result = updateCoins(4, myState, 0);
  assertTrue(result, -1, "Updated coins for player 4 (in 2 player game). Error thrown from updateCoins().");
  initializeGame(2, k, 2, myState);


  /******************************************
   Testing bonus parameter of updateCoins() (third parameter)
  ******************************************/
  //bonus = 1
  i = 0;
  copperCount = 0;
  for (i = 0; i < myState->handCount[0]; i++)
  {
    if(myState->hand[0][i] == 4) copperCount++;
  }
  result = updateCoins(0, myState, 1);
  assertTrue(result, 0, "Updated coins with bonus = 1. No error from updateCoins().");
  assertTrue(myState->coins, copperCount+1, "Update Coins with bonus = 1.  Correct treause count + 1 bonus.");
  initializeGame(2, k, 2, myState);

  //bonus = -1
  i = 0;
  copperCount = 0;
  for (i = 0; i < myState->handCount[0]; i++)
  {
    if(myState->hand[0][i] == 4) copperCount++;
  }
  result = updateCoins(0, myState, -1);
  assertTrue(result, 0, "Updated coins with bonus = -1. No error from updateCoins().");
  assertTrue(myState->coins, copperCount, "Update Coins with bonus = -1.  No change should happen if bonus is less than 0.");
  initializeGame(2, k, 2, myState);

  //bonus = 9999
  i = 0;
  copperCount = 0;
  for (i = 0; i < myState->handCount[0]; i++)
  {
    if(myState->hand[0][i] == 4) copperCount++;
  }
  result = updateCoins(0, myState, 9999);
  assertTrue(result, -1, "Updated coins with bonus = 9999. Error expected from bonus, max treasure is less than 9999.");
  assertTrue(myState->coins, copperCount, "Update Coins with bonus = 9999.  No change should happen if bonus is greater than sum of all treasure.");
  initializeGame(2, k, 2, myState);


  /******************************************
   Testing state parameter of updateCoins() (second parameter)
  ******************************************/
  //Player hand count = 0. Update coins should yield 0.
  myState->hand[0][0] = -1;
  myState->hand[0][1] = -1;
  myState->hand[0][2] = -1;
  myState->hand[0][3] = -1;
  myState->hand[0][4] = -1;
  myState->handCount[0] = 0;
  result = updateCoins(0, myState, 0);
  assertTrue(result, 0, "Updated coins with no cards in hand. No error from updateCoins().");
  assertTrue(myState->coins, 0, "Update Coins with no cards in hand.  Coins = 0.");
  initializeGame(2, k, 2, myState);

  //Player has cards but no treasure cards.
  myState->hand[0][0] = estate; 
  myState->hand[0][1] = estate;
  myState->hand[0][2] = estate;
  myState->hand[0][3] = estate;
  myState->hand[0][4] = estate;
  result = updateCoins(0, myState, 0);
  assertTrue(result, 0, "Updated coins with no treasure cards. No error from updateCoins().");
  assertTrue(myState->coins, 0, "Update Coins with no treasure cards.  Coins = 0.");
  initializeGame(2, k, 2, myState);

  //player has 3 gold => sum = 9
  myState->hand[0][0] = gold; 
  myState->hand[0][1] = gold;
  myState->hand[0][2] = gold;
  myState->hand[0][3] = estate;
  myState->hand[0][4] = estate;
  result = updateCoins(0, myState, 0);
  assertTrue(result, 0, "Updated coins with 3 gold cards. No error from updateCoins().");
  assertTrue(myState->coins, 9, "Update Coins with 3 gold cards.  Coins = 9.");
  initializeGame(2, k, 2, myState);


  //player has 2 silver => sum = 4
  myState->hand[0][0] = silver; 
  myState->hand[0][1] = estate;
  myState->hand[0][2] = silver;
  myState->hand[0][3] = estate;
  myState->hand[0][4] = estate;
  result = updateCoins(0, myState, 0);
  assertTrue(result, 0, "Updated coins with 2 silver cards. No error from updateCoins().");
  assertTrue(myState->coins, 4, "Update Coins with 2 silver cards.  Coins = 4.");
  initializeGame(2, k, 2, myState);

  //Player has 3 copper => sum = 3
  myState->hand[0][0] = copper; 
  myState->hand[0][1] = copper;
  myState->hand[0][2] = copper;
  myState->hand[0][3] = estate;
  myState->hand[0][4] = estate;
  result = updateCoins(0, myState, 0);
  assertTrue(result, 0, "Updated coins with 3 copper cards. No error from updateCoins().");
  assertTrue(myState->coins, 3, "Update Coins with 3 copper cards.  Coins = 3.");
  initializeGame(2, k, 2, myState);

  //Player has 1 gold, 1 silver, 1 copper & 1 bonus => sum = 7
  myState->hand[0][0] = gold; 
  myState->hand[0][1] = silver;
  myState->hand[0][2] = copper;
  myState->hand[0][3] = estate;
  myState->hand[0][4] = estate;
  result = updateCoins(0, myState, 1);
  assertTrue(result, 0, "Updated coins with 1 gold, 1 silver, 1 copper & 1 bonus. No error from updateCoins().");
  assertTrue(myState->coins, 7, "Update Coins with 1 gold, 1 silver, 1 copper & 1 bonus.  Coins = 7.");
  initializeGame(2, k, 2, myState);

  return 0;
}


/***************************************
Custom AssertTrue function to provide more info and prevent
the whole program from crashing
***************************************/
void assertTrue(int firstValue, int secondValue, char* message)
{
  if(firstValue == secondValue)
  {
    printf("TEST PASSED SUCCESSFULLY: %s\n", message);
  }
  else
  {
    printf("TEST FAILED: %s Actual value: %i; Expected Value: %i\n", message, firstValue, secondValue);
  }

}

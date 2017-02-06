/***************************************
 CS362 - Assignment 3
 Gary Smith
 Unit Test for gainCard() from dominion.c

CODE: (starts on line 1205)
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
{
  //Note: supplyPos is enum of choosen card
  
  //check if supply pile is empty (0) or card is not used in game (-1)
  if ( supplyCount(supplyPos, state) < 1 )
    {
      return -1;
    }
  
  //added card for [whoseTurn] current player:
  // toFlag = 0 : add to discard
  // toFlag = 1 : add to deck
  // toFlag = 2 : add to hand

  if (toFlag == 1)
    {
      state->deck[ player ][ state->deckCount[player] ] = supplyPos;
      state->deckCount[player]++;
    }
  else if (toFlag == 2)
    {
      state->hand[ player ][ state->handCount[player] ] = supplyPos;
      state->handCount[player]++;
    }
  else
    {
      state->discard[player][ state->discardCount[player] ] = supplyPos;
      state->discardCount[player]++;
    }
  
  //decrease number in supply pile
  state->supplyCount[supplyPos]--;
   
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
   Testing supplyPos parameter of gainCard() (first parameter)
  ******************************************/
  //Gain card as expected.
  int preDiscardCount = myState->discardCount[0];
  int preSupplyCount = myState->supplyCount[province];
  int result = gainCard(province, myState, 0, 0);
  assertTrue(preDiscardCount+1, myState->discardCount[0], "Gained card to discard pile. Increased Discard pile count by 1.");
  assertTrue(result, 0, "Gained card to discard pile. No error from gainCard().");
  assertTrue(preSupplyCount-1, myState->supplyCount[province], "Gained card to discard pile. Decreased supply pile count by 1.");
  initializeGame(2, k, 2, myState);


  //Gain card when the supply count is 0.
  myState->supplyCount[province] = 0;
  preDiscardCount = myState->discardCount[0];
  preSupplyCount = myState->supplyCount[province];
  result = gainCard(province, myState, 0, 0);
  assertTrue(result, -1, "Gained card to discard pile with empty supply.  Error caught.");
  assertTrue(preDiscardCount, myState->discardCount[0], "Gained card to discard pile. No change to Discard count.");
  assertTrue(preSupplyCount, myState->supplyCount[province], "Gained card to discard pile. No change to supply count.");
  initializeGame(2, k, 2, myState);

  //gain card of type -1.  (Doesn't exist)
  result = gainCard(-1, myState, 0, 0);
  assertTrue(result, -1, "Gained card to discard pile for invalid card (-1). Pass if error is caught. ");
  //gain card of type 999.  (Doesn't exist)
  result = gainCard(999, myState, 0, 0);
  assertTrue(result, -1, "Gained card to discard pile for invalid card (999). Pass if error is caught. ");
  initializeGame(2, k, 2, myState);
  
  /******************************************
   Testing toFlag parameter of gainCard() (third parameter)
  ******************************************/

  //to discard pile
  preDiscardCount = myState->discardCount[0];
  preSupplyCount = myState->supplyCount[province];
  result = gainCard(province, myState, 0, 0);
  assertTrue(result, 0, "Gained card to discard pile. Result with no errors.");
  assertTrue(preDiscardCount+1, myState->discardCount[0], "Gained card to discard pile. Discard count increases by 1.");
  assertTrue(preSupplyCount-1, myState->supplyCount[province], "Gained card to discard pile. Supply of province cards decreases by 1.");
  initializeGame(2, k, 2, myState);
  
  //to deck pile
  int preDeckCount = myState->deckCount[0];
  preSupplyCount = myState->supplyCount[province];
  result = gainCard(province, myState, 1, 0);
  assertTrue(result, 0, "Gained card to deck pile. Result with no errors.");
  assertTrue(preDeckCount+1, myState->deckCount[0], "Gained card to deck pile. Deck count increases by 1.");
  assertTrue(preSupplyCount-1, myState->supplyCount[province], "Gained card to deck pile. Supply of province cards decreases by 1.");
  initializeGame(2, k, 2, myState);

  //to hand pile
  int preHandCount = myState->handCount[0];
  preSupplyCount = myState->supplyCount[province];
  result = gainCard(province, myState, 2, 0);
  assertTrue(result, 0, "Gained card to hand pile. Result with no errors.");
  assertTrue(preHandCount+1, myState->handCount[0], "Gained card to hand pile. Hand count increases by 1.");
  assertTrue(preSupplyCount-1, myState->supplyCount[province], "Gained card to hand pile. Supply of province cards decreases by 1.");
  initializeGame(2, k, 2, myState);


  //invalid destination (-1)
  preDiscardCount = myState->discardCount[0];
  preSupplyCount = myState->supplyCount[province];
  result = gainCard(province, myState, -1, 0);
  assertTrue(result, -1, "Gained card to invalid pile (-1). Pass if error is caught.");
  assertTrue(preDiscardCount, myState->discardCount[0], "Gained card to invalid pile (-1). No change to piles.");
  assertTrue(preSupplyCount, myState->supplyCount[province], "Gained card to invalid pile (-1). No change to piles.");
  initializeGame(2, k, 2, myState);


  //invalid destination (4)
  preDiscardCount = myState->discardCount[0];
  preSupplyCount = myState->supplyCount[province];
  result = gainCard(province, myState, 4, 0);
  assertTrue(result, -1, "Gained card to invalid pile (4). Pass if error is caught.");
  assertTrue(preDiscardCount, myState->discardCount[0], "Gained card to invalid pile (4). No change to piles.");
  assertTrue(preSupplyCount, myState->supplyCount[province], "Gained card to invalid pile (4). No change to piles.");
  initializeGame(2, k, 2, myState);
  
  /******************************************
   Testing player parameter of gainCard() (fourth parameter)
  ******************************************/
  //Player = 0
  preDiscardCount = myState->discardCount[0];
  preSupplyCount = myState->supplyCount[province];
  result = gainCard(province, myState, 0, 0);
  assertTrue(result, 0, "Gained card to discard pile for player 0. Returns no error.");
  assertTrue(preDiscardCount+1, myState->discardCount[0], "Gained card to discard pile for player 0. +1 to discard count.");
  assertTrue(preSupplyCount-1, myState->supplyCount[province], "Gained card to discard pile for player 0. -1 to supply Count.");
  initializeGame(2, k, 2, myState);

  //Player = 1
  preDiscardCount = myState->discardCount[1];
  preSupplyCount = myState->supplyCount[province];
  result = gainCard(province, myState, 0, 1);
  assertTrue(result, 0, "Gained card to discard pile for player 1. Returns no error.");
  assertTrue(preDiscardCount+1, myState->discardCount[1], "Gained card to discard pile for player 1. +1 to discard count.");
  assertTrue(preSupplyCount-1, myState->supplyCount[province], "Gained card to discard pile for player 1. -1 to supply Count.");
  initializeGame(2, k, 2, myState);
  
  //Player = -1
  preSupplyCount = myState->supplyCount[province];
  result = gainCard(province, myState, 0, -1);
  assertTrue(result, -1, "Gained card to discard pile for player -1. Pass if error is caught.");
  assertTrue(preSupplyCount, myState->supplyCount[province], "Gained card to discard pile for player -1. No change to supply Count.");
  initializeGame(2, k, 2, myState);

  //Player = 4 (in a 2 player game)
  preSupplyCount = myState->supplyCount[province];
  result = gainCard(province, myState, 0, -1);
  assertTrue(result, -1, "Gained card to discard pile for player 4 (in 2 player game). Pass if error is caught.");
  assertTrue(preSupplyCount, myState->supplyCount[province], "Gained card to discard pile for player 4 (in 2 player game). No change to supply Count.");
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
    printf("TEST FAILED: %s\n", message);
  }

}
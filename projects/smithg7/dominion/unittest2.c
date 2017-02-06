/***************************************
 CS362 - Assignment 3
 Gary Smith
 Unit Test for scoreFor() from dominion.c
 Code found starting at line 417 of dominion.c

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

  int score = scoreFor(0, myState);
  assertTrue(score, 3, "Score at beginning of game for player 1 is 3.  0 provinces and 3 estates. ");
  initializeGame(2, k, 2, myState);

  score = scoreFor(-1, myState);
  assertTrue(score, -1, "Score at beginning of game for player -1 is an error.");  
  initializeGame(2, k, 2, myState);

  score = scoreFor(3, myState);
  assertTrue(score, -1, "Score at beginning of game for player 3 in a 2 player game is an error.");  
  initializeGame(2, k, 2, myState);

  //Change the first non estate card in the hand to be a province
  int i = 0;
  for (i = 0; i < myState->handCount[0]; i++)
  {
    if(myState->hand[0][i] != 1)  //Is not an estate
    {
      myState->hand[0][i] = province;
      break;
    }
  }


  score = scoreFor(0, myState);
  assertTrue(score, 9, ("Adding a province to player 1's hand. Expected Score: 9 = province + 3 estates. "));


  //Change the first card in the Deck to be a Province
  i = 0;
  for (i = 0; i < myState->deckCount[0]; i++)
  {
    if(myState->deck[0][i] != 1)  //Is not an estate
    {
      myState->deck[0][i] = province;
      break;
    }
  }

  score = scoreFor(0, myState);
  assertTrue(score, 15, ("Adding a province to player 1's hand. Expected Score: 15 = 2 province (12) + 3 estates. "));

  // //Add one to the Discard pile and make it a province
  myState->discardCount[0] = 1;
  myState->discard[0][0] = province;
  score = scoreFor(0, myState);
  assertTrue(score, 21, ("Adding a province to player 1's discard pile. Expected Score: 21 = 3 province (18) + 3 estates. "));

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
    printf("TEST PASSED SUCCESSFULLY: %s; Actual Score: %i\n", message, firstValue);
  }
  else
  {
    printf("TEST FAILED: %s; Actual Score: %i\n", message, firstValue);
  }

}
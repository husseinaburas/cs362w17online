#include <stdlib.h>
#include <stdio.h>
#include "assertFunction.h"
#include "dominion.h"
#include "dominion_helpers.h"

/*
  Test of gainCard function.
*/

int main()
{
  printf("\n--- TESTING gainCard FUNCTION ---\n");
  // Declare variables for pass/fail count
  int passes = 0;
  int fails = 0;

  // Setup test conditions
  struct gameState testState;
  int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
  int randSeed = rand() % 10;
  int numPlayers = 2;

  // Initialize game
  initializeGame(numPlayers, cards, randSeed, &testState);

  // Declare variables needed for tests
  int deckCountBefore, deckCountAfter;
  int handCountBefore, handCountAfter;
  int discardCountBefore, discardCountAfter;
  int supplyCountBefore, supplyCountAfter;
  int resultOne = 0;
  int resultTwo = 0;
  int resultThree = 0;
  int resultFour = 0;
  int currentPlayer = 0;
  int testFlag;
  int testCard;

  /*
    TEST CASE 1: gainCard is sent to hand
    Expected outcome: hand count increments, others remain unchanged
  */
  printf("\nTEST 1 - Testing gainCard sent to hand.\n");

  // Set testFlag to 2 and testCard to gardens
  testCard = gardens;
  testFlag = 2;
  // save current values
  deckCountBefore = testState.deckCount[currentPlayer];
  handCountBefore = testState.handCount[currentPlayer];
  discardCountBefore = testState.discardCount[currentPlayer];

  // Call gainCard
  gainCard(testCard, &testState, testFlag, currentPlayer);

  // save values after gaining card
  deckCountAfter = testState.deckCount[currentPlayer];
  handCountAfter = testState.handCount[currentPlayer];
  discardCountAfter = testState.discardCount[currentPlayer];

  // Compare and store results
  resultOne = deckCountAfter == deckCountBefore;
  resultTwo = handCountAfter == handCountBefore + 1;
  resultThree = discardCountBefore == discardCountAfter;

  // Test result increment pass/fail
  if (assertTrue(resultOne) && assertTrue(resultTwo) && assertTrue(resultThree))
    passes++;
  else
    fails++;

  // Reset test variables
  resultOne = 0;
  resultTwo = 0;
  resultThree = 0;

  /*
    TEST CASE 2: Calling gainCard on a particular supply pile
    Expected outcome: That supply pile decrements by one
  */

  printf("\nTEST 2 - Testing gainCard decrements a given supply pile.\n");

  // Set testCard to smithy
  testCard = smithy;
  // save current count of smithy cards left
  supplyCountBefore = testState.supplyCount[testCard];

  // Call gainCard
  gainCard(testCard, &testState, testFlag, currentPlayer);

  // save count after gaining card
  supplyCountAfter = testState.supplyCount[testCard];

  // Compare and store results
  resultOne = supplyCountAfter == supplyCountBefore - 1;

  // Test result increment pass/fail
  if (assertTrue(resultOne))
    passes++;
  else
    fails++;

  // Reset test variables
  resultOne = 0;

  /*
    TEST CASE 3: Attempt to gain a card not in game
    Expected outcome: Unable to gain card (-1 result)
  */

  printf("\nTEST 3 - Testing that cards not in game cannot be gained\n");

  // Set testCard to steward and testFlag to 2
  testCard = steward;
  testFlag = 2;

  // save current values
  deckCountBefore = testState.deckCount[currentPlayer];
  handCountBefore = testState.handCount[currentPlayer];
  discardCountBefore = testState.discardCount[currentPlayer];

  // attempt to gainCard, store result
  resultFour = gainCard(testCard, &testState, testFlag, currentPlayer);

  // save values after gaining card
  deckCountAfter = testState.deckCount[currentPlayer];
  handCountAfter = testState.handCount[currentPlayer];
  discardCountAfter = testState.discardCount[currentPlayer];

  // Compare and store results
  resultOne = deckCountAfter == deckCountBefore;
  resultTwo = handCountAfter == handCountBefore;
  resultThree = discardCountBefore == discardCountAfter;

  // Test result increment pass/fail
  if (assertTrue(resultOne) && assertTrue(resultTwo) && assertTrue(resultThree) && assertTrue(resultFour))
    passes++;
  else
    fails++;

  // Reset test variables
  resultOne = 0;
  resultTwo = 0;
  resultThree = 0;
  resultFour = 0;


  printf("\n--RESULTS--");
  printf("\nPASSES: %d\nFAILS: %d\n", passes, fails);
  printf("\n---DONE TESTING gainCard FUNCTION ---\n\n");

}

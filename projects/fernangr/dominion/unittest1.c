#include <stdlib.h>
#include <stdio.h>
#include "assertFunction.h"
#include "dominion.h"
#include "dominion_helpers.h"

/*
  Test of isGameOver function.
*/

int main()
{
  printf("\n--- TESTING isGameOver FUNCTION ---\n");
  // Declare variables for pass/fail count
  int passes = 0;
  int fails = 0;

  // Setup test conditions
  struct gameState *testState = newGame();
  int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
  int randSeed = rand() % 10;
  int numPlayers = 2;
  // Initialize game
  initializeGame(numPlayers, cards, randSeed, testState);

  /*
    TEST CASE 1: Province pile is empty
    Expected outcome: Game should end
  */
  printf("\nTEST 1 - Testing that game ends when only Province pile is empty\n");

  // Set the Province pile to 0
  testState->supplyCount[province] = 0;

  // Test that isGameOver returns 1 for the current gameState and increment pass/fail
  if (assertTrue(isGameOver(testState)))
    passes++;
  else
    fails++;

  // Reset province supply to 8
  testState->supplyCount[province] = 8;

  /*
    TEST CASE 2: Three supply piles are depleted
    Expected outcome: Game should end
  */
  printf("\nTEST 2 - Testing that game ends when three supply piles are empty\n");

  // Set treause piles to 0
  testState->supplyCount[curse] = 0;
  testState->supplyCount[silver] = 0;
  testState->supplyCount[duchy] = 0;

  // Test that isGameOver returns 1 for the current gameState and increment pass/fail
  if (assertTrue(isGameOver(testState)))
    passes++;
  else
    fails++;

  // Reset treasure piles
  testState->supplyCount[curse] = 10;
  testState->supplyCount[silver] = 40;
  testState->supplyCount[duchy] = 8;

  /*
    TEST CASE 3: There are Province cards and 2 supply piles are depleted
    Expected outcome: Game should continue
  */
  printf("\nTEST 3 - Testing that game continues when neither three supply piles nor the Province pile are empty\n");

  // Set two supply piles to 0
  testState->supplyCount[copper] = 0;
  testState->supplyCount[gold] = 0;

  // Set the Province pile to 1
  testState->supplyCount[province] = 1;

  // Test that isGameOver returns 0 for the current gameState and increment pass/fail
  if (assertTrue(isGameOver(testState) == 0))
    passes++;
  else
    fails++;

  // Reset supply piles
  testState->supplyCount[copper] = 60 - (7 * numPlayers);
  testState->supplyCount[gold] = 30;

  // Reset the Province pile to 8
  testState->supplyCount[province] = 8;

  printf("\n--RESULTS--");
  printf("\nPASSES: %d\nFAILS: %d\n", passes, fails);
  printf("\n---DONE TESTING isGameOver FUNCTION ---\n\n");

}

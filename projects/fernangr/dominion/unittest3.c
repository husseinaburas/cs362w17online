#include <stdlib.h>
#include <stdio.h>
#include "assertFunction.h"
#include "dominion.h"
#include "dominion_helpers.h"

/*
  Test of updateCoins function.
*/

int main()
{
  printf("\n--- TESTING updateCoins FUNCTION ---\n");
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
  int coinsBeforeUpdate;
  int coinsAfterUpdate;
  int result = 0;
  int currentPlayer = 0;

  /*
    TEST CASE 1: Updating coins after initializing game
    Expected outcome: Player has 4 coins
  */
  printf("\nTEST 1 - Testing that starting a new game has player begin with 4 coins.\n");

  // Initialize value to 0
  coinsBeforeUpdate = 0;
  // Update coins on player's empty hand
  updateCoins(currentPlayer, &testState, 0);
  coinsAfterUpdate = testState.coins;

  // Compare and store result
  result = coinsAfterUpdate == coinsBeforeUpdate + 4;

  // Test result increment pass/fail
  if (assertTrue(result))
    passes++;
  else
    fails++;

  // Reset test variables
  result = 0;

  /*
    TEST CASE 2: Adding Treasure cards to the hand
    Expected outcome: Coin count should increment to match value of treasure cards added.
  */
  printf("\nTEST 2 - Testing that drawing Treasure cards increments coin count.\n");

  // Set proper value to before updating
  coinsBeforeUpdate = coinsAfterUpdate;

  // Draw one of each card then run a test
  gainCard(copper, &testState, 2, 0);
  gainCard(silver, &testState, 2, 0);
  gainCard(gold, &testState, 2, 0);

  // Call updateCoins on hand state
  updateCoins(currentPlayer, &testState, 0);
  coinsAfterUpdate = testState.coins;

  // See if coin count incremented by 6
  result = coinsAfterUpdate == coinsBeforeUpdate + 6;

  // Test result and increment pass/fail
  if (assertTrue(result))
    passes++;
  else
    fails++;

  result = 0;

  /*
    TEST CASE 3: Adding bonus coins from card effects
    Expected outcome: Coin total should increment by appropriate amount
  */
  printf("\nTEST 3 - Testing that coin bonuses increment the total correctly\n");

  // Set proper value to before updating
  coinsBeforeUpdate = coinsAfterUpdate;

  // Call updateCoins on hand state, with 3 bonus coins
  updateCoins(currentPlayer, &testState, 3);
  coinsAfterUpdate = testState.coins;

  // See if coin count incremented by 3
  result = coinsAfterUpdate == coinsBeforeUpdate + 3;

  // Test result and increment pass/fail
  if (assertTrue(result))
    passes++;
  else
    fails++;

  result = 0;

  printf("\n--RESULTS--");
  printf("\nPASSES: %d\nFAILS: %d\n", passes, fails);
  printf("\n---DONE TESTING updateCoins FUNCTION ---\n\n");

}

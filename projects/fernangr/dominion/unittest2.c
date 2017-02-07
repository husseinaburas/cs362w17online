#include <stdlib.h>
#include <stdio.h>
#include "assertFunction.h"
#include "dominion.h"
#include "dominion_helpers.h"

/*
  Test of discardCard function.
*/

int main()
{
  printf("\n--- TESTING discardCard FUNCTION ---\n");
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

  // Declare variables needed for tests
  int testFlag = 0;
  int countBeforePlaying = 0;
  int countAfterPlaying = 0;
  int result = 0;
  int handPos = 0;
  int currentPlayer = 0;

  /*
    TEST CASE 1: Trash flag not set
    Expected outcome: playedCardCount should increment.
  */
  printf("\nTEST 1 - Testing that playing card increments count.\n");

  // Set played cards to 3 (arbitrary) and store it
  testState->playedCardCount = 3;
  countBeforePlaying = testState->playedCardCount;

  // Call discardCard and store the count of played cards
  discardCard(handPos, 0, testState, testFlag);
  countAfterPlaying = testState->playedCardCount;

  // Compare and store result
  result = countAfterPlaying == (countBeforePlaying + 1);

  // Test result increment pass/fail
  if (assertTrue(result))
    passes++;
  else
    fails++;

  // Reset test variables
  countBeforePlaying = 0;
  countAfterPlaying = 0;
  result = 0;

  /*
    TEST CASE 2: Trash flag is set
    Expected outcome: playedCardCount should not increment.
  */
  printf("\nTEST 2 - Testing that trashing card does not increment count.\n");

  // Set trash flag to 1
  testFlag = 1;

  // Set played cards to 3 (arbitrary) and store it
  testState->playedCardCount = 3;
  countBeforePlaying = testState->playedCardCount;

  // Call discardCard and store the count of played cards
  discardCard(handPos, 0, testState, testFlag);
  countAfterPlaying = testState->playedCardCount;

  // Compare and store result
  result = countAfterPlaying == countBeforePlaying;

  // Test result and increment pass/fail
  if (assertTrue(result))
    passes++;
  else
    fails++;

  // Reset test variables
  testFlag = 0;
  countBeforePlaying = 0;
  countAfterPlaying = 0;
  result = 0;

  /*
    TEST CASE 3: Player has some number of cards (greater than 1) in hand.
    Expected outcome: Player should have one less card in hand.
  */
  printf("\nTEST 3 - Testing that number of cards in hand decrements correctly\n");

  testState->handCount[currentPlayer] = 3;

  // Set played cards to 3 (arbitrary) and store it
  countBeforePlaying = testState->handCount[currentPlayer];

  // Call discardCard and store the count of played cards
  discardCard(handPos, 0, testState, testFlag);
  countAfterPlaying = testState->handCount[currentPlayer];

  // Compare and store result
  result = countAfterPlaying == (countBeforePlaying - 1);

  // Test result and increment pass/fail
  if (assertTrue(result))
    passes++;
  else
    fails++;

  // Reset test variables
  testFlag = 0;
  countBeforePlaying = 0;
  countAfterPlaying = 0;
  result = 0;

  printf("\n--RESULTS--");
  printf("\nPASSES: %d\nFAILS: %d\n", passes, fails);
  printf("\n---DONE TESTING isGameOver FUNCTION ---\n\n");

}

#include <stdlib.h>
#include <stdio.h>
#include "assertFunction.h"
#include "dominion.h"
#include "dominion_helpers.h"

int nonTreasureCount(int player, struct gameState *state);
/*
  Test of adventurerCard function.
*/

int main()
{
  printf("\n--- TESTING adventurerCard FUNCTION ---\n");
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

  // Declare and initialize variables needed for tests
  int result = 0;
  int handBeforePlaying = 0;
  int handAfterPlaying = 0;
  int deckBeforePlaying = 0;
  int deckAfterPlaying = 0;
  int discardBeforePlaying = 0;
  int discardAfterPlaying = 0;
  int ntBeforePlaying = 0;
  int ntAfterPlaying = 0;
  int currentPlayer = 0;



  /*
    TEST CASE 1: Deck is empty
    Expected outcome: Adventurer card should trigger reshuffle
  */
  printf("\nTEST 1 - Testing that deck is reshuffled when it is empty\n");

  // Setup deck and discard pile
  testState.discardCount[currentPlayer] = 8;
  testState.deckCount[currentPlayer] = 0;
  testState.discard[currentPlayer][0] = copper;
  testState.discard[currentPlayer][1] = silver;
  testState.discard[currentPlayer][2] = gold;
  testState.discard[currentPlayer][3] = copper;
  testState.discard[currentPlayer][4] = silver;
  testState.discard[currentPlayer][5] = embargo;
  testState.discard[currentPlayer][6] = cutpurse;
  testState.discard[currentPlayer][7] = mine;

  // Store the number of cards in the deck and discard pile before playing the card
  deckBeforePlaying = testState.deckCount[currentPlayer];
  discardBeforePlaying = testState.discardCount[currentPlayer];

  // Play the adventurer card
  adventurerCard(&testState);

  // Store the number of cards in the deck and discard pile after playing the card
  deckAfterPlaying = testState.deckCount[currentPlayer];
  discardAfterPlaying = testState.discardCount[currentPlayer];

  // Check if discard pile was reshuffled into deck
  result = (discardAfterPlaying != discardBeforePlaying) && (deckAfterPlaying != deckBeforePlaying);

  // Run assertTrue on result
  if (assertTrue(result))
    passes++;
  else
    fails++;

  // Reset variables
  for (int i = 0; i < 8; i++)
  {
    testState.discard[currentPlayer][i] = 0;
    testState.deck[currentPlayer][i] = 0;
  }
  testState.discardCount[currentPlayer] = 0;
  testState.deckCount[currentPlayer] = 0;
  result = 0;

  /*
    TEST CASE 2: Adventurer card is played
    Expected outcome: Two treasure cards are added to the hand
  */
  printf("\nTEST 2 - Testing that 2 treasure cards are added to the hand\n");

  // Initialize new game
  initializeGame(numPlayers, cards, randSeed, &testState);

  // Set up the deck
  testState.deck[currentPlayer][0] = copper;
  testState.deck[currentPlayer][1] = silver;
  testState.deck[currentPlayer][2] = gold;
  testState.deck[currentPlayer][3] = copper;
  testState.deck[currentPlayer][4] = silver;
  testState.deck[currentPlayer][5] = embargo;
  testState.deck[currentPlayer][6] = cutpurse;
  testState.deck[currentPlayer][7] = mine;
  testState.deckCount[currentPlayer] = 8;

  // Store the number of cards in the hand before playing the card
  handBeforePlaying = testState.handCount[currentPlayer];

  // Play the adventurer card
  adventurerCard(&testState);

  // Store the number of cards in the hand after playing the card
  handAfterPlaying = testState.handCount[currentPlayer];

  // Check if discard pile was reshuffled into deck
  result = handAfterPlaying == handBeforePlaying + 2;
  printf("handAfterPlaying: %d; handBeforePlaying: %d\n", handAfterPlaying, handBeforePlaying);

  // Test that adventurerCard returns 1 for the current gameState and increment pass/fail
  if (assertTrue(result))
    passes++;
  else
    fails++;

  // Reset variables
  for (int i = 0; i < 8; i++)
  {
    testState.deck[currentPlayer][i] = 0;
  }
  testState.deckCount[currentPlayer] = 0;
  result = 0;

  /*
    TEST CASE 3: Number of non-Treasure cards
    Expected outcome: Should remain the same after playing
  */
  printf("\nTEST 3 - Testing that non-Treasure cards don't increase\n");
  // Initialize new game
  initializeGame(numPlayers, cards, randSeed, &testState);

  // Set up the deck
  testState.deck[currentPlayer][0] = copper;
  testState.deck[currentPlayer][1] = silver;
  testState.deck[currentPlayer][2] = gold;
  testState.deck[currentPlayer][3] = copper;
  testState.deck[currentPlayer][4] = silver;
  testState.deck[currentPlayer][5] = embargo;
  testState.deck[currentPlayer][6] = cutpurse;
  testState.deck[currentPlayer][7] = mine;
  testState.deckCount[currentPlayer] = 8;

  // Store the number of non-Treasure cards before playing
  ntBeforePlaying = nonTreasureCount(currentPlayer, &testState);

  // Play the adventurer card
  adventurerCard(&testState);

  // Store the number of non-Treasure cards after playing
  ntAfterPlaying = nonTreasureCount(currentPlayer, &testState);

  // Compare the number of non-Treasure cards before and after playing and store the result
  result = ntAfterPlaying == ntBeforePlaying;

  // Test that adventurerCard returns 0 for the current gameState and increment pass/fail
  if (assertTrue(result))
    passes++;
  else
    fails++;

  // Reset variables
  for (int i = 0; i < 8; i++)
  {
    testState.deck[currentPlayer][i] = 0;
  }
  testState.deckCount[currentPlayer] = 0;
  result = 0;

  printf("\n--RESULTS--");
  printf("\nPASSES: %d\nFAILS: %d\n", passes, fails);
  printf("\n---DONE TESTING adventurerCard FUNCTION ---\n\n");

}


int nonTreasureCount(int player, struct gameState *state)
{
  int count = 0;
  int handSize = state->handCount[player];

  for (int i = 0; i < handSize; i++)
  {
    if (state->hand[player][i] != copper && state->hand[player][i] != silver && state->hand[player][i] != gold)
    {
      count++;
    }
  }

  return count;
}

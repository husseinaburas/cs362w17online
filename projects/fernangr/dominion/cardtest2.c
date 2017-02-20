#include <stdlib.h>
#include <stdio.h>
#include "assertFunction.h"
#include "dominion.h"
#include "dominion_helpers.h"

/*
  Test of smithyCard function.
*/

int main()
{
  printf("\n--- TESTING smithyCard FUNCTION ---\n");
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
  int pcBeforePlaying = 0;
  int pcAfterPlaying = 0;
  int currentPlayer = 0;
  int handPos = 0;


  /*
    TEST CASE 1: Number of cards in hand
    Expected outcome: Should increase by 3 after playing smithy
  */
  printf("\nTEST 1 - Testing that cards in hand increase by 3\n");

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

  // Place the smithy card in the player's hand
  testState.hand[currentPlayer][handPos] = smithy;

  // Store the number of cards in the hand before playing the card
  handBeforePlaying = testState.handCount[currentPlayer];

  // Play the smithyCard card
  smithyCard(&testState, handPos);

  // Store the number of cards in the hand after playing the card
  handAfterPlaying = testState.handCount[currentPlayer];;

  // Check that the proper number of cards were added to the hand
  result = handAfterPlaying == handBeforePlaying + 3;
  printf("handAfterPlaying: %d; handBeforePlaying: %d\n", handAfterPlaying, handBeforePlaying);

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
    TEST CASE 2: Played pile after playing
    Expected outcome: Smithy card should be played, incrementing pile by 1
  */
  printf("\nTEST 2 - Testing that smithy card is added to played pile\n");

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
  testState.playedCards[testState.playedCardCount] = 0;

  // Store the number of cards in the played pile before playing the card
  pcBeforePlaying = testState.playedCards[testState.playedCardCount];

  // Place the smithy card in the player's hand
  testState.hand[currentPlayer][handPos] = smithy;

  // Play the adventurer card
  smithyCard(&testState, handPos);

  // Store the number of cards in the played pile after playing the card
  pcAfterPlaying = testState.playedCards[testState.playedCardCount];

  // Check that card was added to played pile
  result = pcAfterPlaying == pcBeforePlaying + 1;
  printf("pcAfterPlaying: %d; pcBeforePlaying: %d\n", pcAfterPlaying, pcBeforePlaying);

  // Test that smithyCard returns 1 for the current gameState and increment pass/fail
  if (assertTrue(result))
    passes++;
  else
    fails++;

  // Reset variables
  for (int i = 0; i < 8; i++)
  {
    testState.deck[currentPlayer][i] = 0;
  }
  testState.playedCards[testState.playedCardCount] = 0;
  testState.deckCount[currentPlayer] = 0;
  result = 0;

  printf("\n--RESULTS--");
  printf("\nPASSES: %d\nFAILS: %d\n", passes, fails);
  printf("\n---DONE TESTING smithyCard FUNCTION ---\n\n");

}

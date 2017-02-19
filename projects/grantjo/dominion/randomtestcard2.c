#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rngs.h"

#include <signal.h>
#include <unistd.h>
#include <execinfo.h>

#define TEST_NUM 1000
#define MAX_PLAYER 4
#define MIN_PLAYER 2
#define MAX_DECKSIZE 11 // limit decksize to ensure higher chance of 0 deck
#define MAX_DISCARD 20
#define MAX_HANDSIZE 10
#define MAX_TREASURE 4
#define NUM_CARDS 26

struct test {
  int testsPassed;
  int testsFailed;
};

struct greatHDetails {
  int currentPlayer;
  int shuffleOccurred;
  int tempHandCount;
};

int asserttrue(int condition, char* message)
{
  if (!condition) {
    printf("\t\t\tError: %s\n", message);
    return 1;
  }
  return 0;
}

// Reference adventurer logic
int refPlayGreatHall(struct gameState *state, struct greatHDetails *detail, int handPos) {
  detail->shuffleOccurred = 0;

  if (state->deckCount[detail->currentPlayer] == 0)
    detail->shuffleOccurred = 1;

  // Draw 1 Card from Deck and Add 1 Actions to currentPlayer
  //+1 Card
  drawCard(detail->currentPlayer, state);

  //+1 Actions
  state->numActions += 1;

  //discard played card from hand
  discardCard(handPos, detail->currentPlayer, state, 0);
}


int gameStateCorruption(struct gameState *ref, struct gameState *test, int numPlayers, int player) {
  int i = 0,
  j = 0,
  z = 0,
  error = 0;

  error += asserttrue(ref->numPlayers == test->numPlayers, "numPlayers mismatch");
  error += asserttrue(ref->outpostPlayed == test->outpostPlayed, "outpostPlayed mismatch");
  error += asserttrue(ref->outpostTurn == test->outpostTurn, "outpostTurn mismatch");
  error += asserttrue(ref->whoseTurn == test->whoseTurn, "whoseTurn mismatch");
  error += asserttrue(ref->phase == test->phase, "phase mismatch");
  error += asserttrue(ref->coins == test->coins, "coins mismatch");
  error += asserttrue(ref->numBuys == test->numBuys, "numBuys mismatch");

  // check supplyCounts match copy
  z = 0;	// z used to count matches
  for (i = 0; i < treasure_map+1; i++)
  if (ref->supplyCount[i] == test->supplyCount[i])
  z++;
  error += asserttrue(z == treasure_map+1, "supplyCount mismatch");

  // check embargoTokens match copy
  z = 0;	// z used to count matches
  for (i = 0; i < treasure_map+1; i++)
  if (ref->embargoTokens[i] == test->embargoTokens[i])
  z++;
  error += asserttrue(z == treasure_map+1, "embargoTokens mismatch");


  for (i = 0; i < numPlayers; i++) {
    if (i != player) {
      error += asserttrue(ref->deckCount[i] == test->deckCount[i], "deckCount mismatch");
      error += asserttrue(ref->handCount[i] == test->handCount[i], "handCount mismatch");
      error += asserttrue(ref->discardCount[i] == test->discardCount[i], "discardCount mismatch");

      // check altPlayers hand matches copy
      z = 0;	// z used to count matches
      for (j = 0; j < ref->handCount[i]; j++)
        if (ref->hand[i][j] == test->hand[i][j])
          z++;
      error += asserttrue(z == ref->handCount[i], "Adventurer changed another players hand");

      // check altPlayers deck matches copy
      z = 0;	// z used to count matches
      for (j= 0; j < ref->deckCount[i]; j++)
        if (ref->deck[i][j] == test->deck[i][j])
          z++;
      error += asserttrue(ref->deckCount[i] == z, "Adventurer changed another players deck");

      // check altPlayers discard matches copy
      z = 0;	// z used to count matches
      for (j = 0; j < ref->discardCount[i]; j++)
        if (ref->discard[i][j] == test->discard[i][j])
          z++;
      error += asserttrue(z == ref->discardCount[i], "Adventurer changed another players discard");
    }
  }
  return error;
}

void performRandomTest(struct test *totalTest, int test, int rand_seed) {

  struct test currTest;
  currTest.testsPassed = 0;
  currTest.testsFailed = 0;

  struct gameState testG,
                   refG,
                   refUnchanged;

  struct greatHDetails greatHDetails;

  int error = 0,
      errorTotal = 0,
      seed = rand_seed,
      success = 0,
      numPlayers,
      currentPlayer,
      handPos,
      deckSize,
      handSize,
      discardSize,
      choice1,
      choice2,
      choice3,
      bonus = 0,
      i = 0,
      k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                     sea_hag, great_hall, smithy, council_room},
      cardToTest = great_hall;

  char buffer[100],
       *cardName = "Great Hall";

  numPlayers = 1 + rand() % MAX_PLAYER;
  while (numPlayers < 2) numPlayers = 1 + rand() % MAX_PLAYER;

  currentPlayer = rand() % numPlayers;

  handSize = rand() % MAX_HANDSIZE;
  deckSize = rand() % MAX_DECKSIZE;
  discardSize = MAX_TREASURE + rand() % MAX_DISCARD;

  initializeGame(numPlayers, k, seed, &testG);

  testG.whoseTurn = currentPlayer;
  greatHDetails.currentPlayer = currentPlayer;
  testG.numPlayers = numPlayers;

  testG.handCount[currentPlayer] = handSize;

  if (handSize > 0) {
    handPos = rand() % handSize;
    for (i = 0; i < handSize; i++) {
      int card = rand() % NUM_CARDS;
      while (card == cardToTest) card = rand() % NUM_CARDS;
      testG.hand[currentPlayer][i] = card;
    }
    testG.hand[currentPlayer][handPos] = cardToTest;
  }
  else {
    handPos = 0;
    testG.hand[currentPlayer][testG.handCount[currentPlayer]++] = cardToTest;
  }

  testG.deckCount[currentPlayer] = deckSize;
  for (i = 0; i < deckSize; i++) {
      int card = rand() % NUM_CARDS;
      while (card == cardToTest) card = rand() % NUM_CARDS;
      testG.deck[currentPlayer][i] = card;
  }

  testG.discardCount[currentPlayer] = discardSize;
  for (i = 0; i < discardSize; i++) {
    int card = rand() % NUM_CARDS;
    while (card == cardToTest) card = rand() % NUM_CARDS;
    testG.discard[currentPlayer][i] = card;
  }

  printf("Test %d %s, Player %d, %d cards in deck, %d in discard and %d in hand\n",
            test, cardName, currentPlayer, deckSize, discardSize, handSize);
  printf("\tNumber of players: %d\n", numPlayers);

  // copy state variables into reference states
  memcpy(&refG, &testG, sizeof(struct gameState));
  memcpy(&refUnchanged, &testG, sizeof(struct gameState));

  greatHDetails.tempHandCount = refG.handCount[currentPlayer];
  // Call Reference Logic on reference state
  refPlayGreatHall(&refG, &greatHDetails, handPos);

  choice1 = rand() % 4;
  choice2 = rand() % 4;
  choice3 = rand() % 4;
  printf("\tCalling %s: Choice 1: %d, Choice 2: %d, Choce 3: %d\n", cardName,choice1, choice2, choice3);
  //call cardEffect for adventurer on player
  success = cardEffect(cardToTest, choice1, choice2, choice3, &testG, handPos, &bonus);

  // Ensure that game state corruption did not occurr
  sprintf(buffer, "Ensuring that reference %s logic did not corrupt game state", cardName);
  printf("\t%s\n", buffer);
  error += gameStateCorruption(&refUnchanged, &refG, numPlayers, currentPlayer);
  if (error == 0)
	  printf("\t\tSuccess: reference %s does not change irrelevant game state variables\n", cardName);
  errorTotal = error;
  error = 0;

  sprintf(buffer, "Ensuring that dominion.c %s logic did not corrupt game state", cardName);
  printf("\t%s\n", buffer);
  error += gameStateCorruption(&refUnchanged, &testG, numPlayers, currentPlayer);
  if (error == 0)
	  printf("\t\tSuccess: Dominion.c %s does not change irrelevant game state variables\n", cardName);
  errorTotal = error;
  error = 0;

  printf("\tChecking %s reference logic\n", cardName);
  // assert that reference Great Hall logic is working correctly.
    // Does not count towards error_count for dominion.c code
    asserttrue(refG.handCount[currentPlayer] == greatHDetails.tempHandCount, "Expected handCount to be the same after reference Great Hall logic, check test");
    asserttrue(refG.playedCards[refG.playedCardCount-1] == cardToTest, "Great Hall should be in played pile");
    // make sure Great Hall is not in hand
    seed = 0;
    for (i = 0; i < refG.handCount[currentPlayer]; i++ ) {
  	  if (refG.hand[currentPlayer][i] == cardToTest)
  		  seed++;
    }
    asserttrue(seed == 0, "Great Hall should not be in hand, check reference logic");
    asserttrue(refG.numActions == 2, "Num Actions should have increased by 2, check reference logic");
    // ********** End checking reference Great Hall logic

  if (error == 0)
    printf("\t\tNo Problems with Reference Logic Found\n");
  else
    printf("\t\t%d Problems with Reference Logic Found\n", error);
  error = 0;
  // ********** End checking reference adventurer logic

  // Check reference logic against game logic
  sprintf(buffer, "Check results of %s logic against dominion.c %s logic", cardName, cardName);
  printf("\t%s\n", buffer);

  error += asserttrue(success == 0, "Expected Function to return success");

  printf("\tExpecting 1 card to have been added to the hand, got %d\n", testG.handCount[currentPlayer]-(greatHDetails.tempHandCount-1));
  error += asserttrue(testG.handCount[currentPlayer]-(greatHDetails.tempHandCount-1) == 1,
        "Should have drawn 1 card");

  if (!greatHDetails.shuffleOccurred) {
    // Drawn card should wind up in handPos
    seed = 0;
    if (refG.hand[currentPlayer][handPos] == testG.hand[currentPlayer][handPos])
      seed++;

    // print expected result of reference comparison and assert it is as expected
    printf("\tNo Shuffle, Expects 1 if cards drawn in reference and returned are the same got %d\n", seed);
    error += asserttrue(seed == 1, "Reference and returned hand should match");
  } else {
    printf("\tShuffle Occurred, Expects 1 cards to have been added to the hand, got %d\n",
        testG.handCount[currentPlayer] - (greatHDetails.tempHandCount-1));
    error += asserttrue(testG.handCount[currentPlayer] - (greatHDetails.tempHandCount-1) == 1,
        "Should have drawn 1 card");
  }

  printf("\tExpecting handCount %d and received %d\n", refG.handCount[currentPlayer], testG.handCount[currentPlayer]);
  error += asserttrue(refG.handCount[currentPlayer] == testG.handCount[currentPlayer],
      "handCount does not match reference");

  printf("\tExpecting 1 if %s in played pile, got %d\n", cardName, testG.playedCards[testG.playedCardCount-1] == cardToTest);
  error += asserttrue((testG.playedCards[testG.playedCardCount-1] == cardToTest) == 1,
          "Expected Great Hall in played pile");

  // keep track of whether returned hand has Great Hall
  seed = 0;
  // Check returned hand doesnt have Great Hall
  for (i = 0; i < testG.handCount[currentPlayer]; i++) {
    if (testG.hand[currentPlayer][i] == cardToTest)
      seed++;
  }
  // print expected value of Great Hall card in hand
  printf("\tExpects 0 if returned hand doesnt have Great Hall card and got %d\n", seed);
  error += asserttrue(seed == 0, "Great Hall should not be in hand");

  printf("\tExpecting %d if numActions of returned to match reference, got %d\n", refG.numActions, testG.numActions);
  asserttrue(refG.numActions == testG.numActions, "numActions in returned should match reference");

  errorTotal += error;
  if (errorTotal == 0) {
    printf("%s Test %d Successful\n\n", cardName, test);
    totalTest->testsPassed++;
    return;
  }
  printf("%s Test %d Failed, %d comparisons failed\n\n", cardName, test, errorTotal);
  totalTest->testsFailed++;
  return;
}

void handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

int main(int argc, char **argv) {
  int seed,
      i = 0;
  signal(SIGFPE, handler);   // install our handler
  struct test total;
  total.testsPassed = 0;
  total.testsFailed = 0;

  if (argc < 2)
    seed = 10;
  else
    seed = atoi(argv[1]);

  srand(seed);

  printf("------------------------ Testing Great Hall Card ------------------------------\n");

  for (i = 0; i < TEST_NUM; i++)
    performRandomTest(&total, i+1, seed);

  if (total.testsFailed == 0)
      printf("ALL %d TESTS SUCCESSFUL, Great Hall\n", total.testsPassed);
  else
      printf("%d TESTS FAILED, %d TESTS PASSED Great Hall\n", total.testsFailed, total.testsPassed);
  printf("------------------------ END Test Great Hall Card ------------------------------\n\n");

  return 0;
}

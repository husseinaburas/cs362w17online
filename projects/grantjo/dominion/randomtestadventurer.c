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

struct adventurerDetails {
  int currentPlayer;
  int shuffleOccurred;
  int discardCount;
  int offsetDiscard;
  int drawntreasure;
  int temphand[MAX_HAND];
  int temphandCount;
};

int asserttrue(int condition, char* message)
{
  if (!condition) {
    printf("\t\t\tError: %s\n", message);
    return 1;
  }
  return 0;
}

// shuffle requires full deck
// moves all cards from discard to deck and clears discardCount
int shuffle_prepare(int player, struct gameState *state) {

    int i;
    //Move all cards from discard to deck
    for (i = 0; i < state->discardCount[player];i++){
      state->deck[player][i] = state->discard[player][i];
      state->discard[player][i] = -1;
    }

	// set deck size and clear discardCount
    state->deckCount[player] = state->discardCount[player];
    state->discardCount[player] = 0;

	return 0;
}

// Reference adventurer logic
int refPlayAdventurer(struct gameState *state, struct adventurerDetails *details) {

  details->temphandCount = 0;
  details->drawntreasure = 0;
  details->discardCount = state->discardCount[details->currentPlayer];
  details->offsetDiscard = 0;
  details->shuffleOccurred = 0;

  while(details->drawntreasure < 2)
  {
    if (state->deckCount[details->currentPlayer] < 1) //if the deck is empty we need to shuffle discard and add to deck
    {
      // if we haven't shuffled yet shuffle and set shuffled to true
      // If we dont have enough trasures after shuffling then you get only what
      // you have been able to draw
      if (details->shuffleOccurred == 0) {
        shuffle_prepare(details->currentPlayer, state);
        shuffle(details->currentPlayer, state);
        details->shuffleOccurred = 1;
      }
      else {
        // shuffle cards but break because we do not have enough treasures in
        // deck or discard
        shuffle_prepare(details->currentPlayer, state);
        shuffle(details->currentPlayer, state);
        break;
      }

    }
    // draw a card from the deck
    drawCard(details->currentPlayer, state);
    // store the card (now in hand)
    //top card of hand is most recently drawn card.
    int cardDrawn = state->hand[details->currentPlayer][state->handCount[details->currentPlayer]-1];
    // check if it is a currency, if so increment drawntreasure
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold )
      details->drawntreasure++;
    // if its not currency, add to temphand and remove from hand
    // do not add to discard as we dont want it reshuffled
    else
    {
      details->temphand[details->temphandCount]=cardDrawn;
      state->handCount[details->currentPlayer]--; //this should just remove the top card (the most recently drawn one).
      details->temphandCount++;
    }
  }
  // If shuffle never occurred add the number of cards in tempHand to shuffle_occurred
  if (details->shuffleOccurred == 0) {
    details->offsetDiscard = details->discardCount; // store size of discard to offset check of tempHand cards
    details->discardCount += details->temphandCount;
  }
  // Else, discard should have been cleared and the only cards to be placed in it are from tempHand
  else {
    details->offsetDiscard = 0; // make offset 0 because index in discard should match tempHand
    details->discardCount = details->temphandCount;
  }
  // discard everything in temphand
  while(details->temphandCount-1 >= 0)
  {
    // discard all cards in play that have been drawn
    state->discard[details->currentPlayer][state->discardCount[details->currentPlayer]++] =
                details->temphand[details->temphandCount-1];
    details->temphandCount--;
  }
}


int treasureCount(int player, struct gameState *state) {
  int i = 0,
      treasure = 0;

  for (i = 0; i < state->deckCount[player]; i++)
    if (state->deck[player][i] >= copper && state->deck[player][i] <= gold)
      treasure++;

  for (i = 0; i < state->discardCount[player]; i++)
    if (state->discard[player][i] >= copper && state->discard[player][i] <= gold)
      treasure++;

   if (treasure == 0)
    return -1;

   return treasure;
}

int topNCardsTreasure(int player, int numExpected, struct gameState *state) {
  int treasure = 0,
      i = state->handCount[player] - numExpected;

  for (; i < state->handCount[player]; i++)
    if (state->hand[player][i] >= copper && state->hand[player][i] <= gold)
      treasure++;

   if (treasure == numExpected)
    return 1;

    return 0;
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
  error += asserttrue(ref->numActions == test->numActions, "numActions mismatch");
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

  struct adventurerDetails advDetails;

  int error = 0,
      errorTotal = 0,
      seed = rand_seed,
      success = 0,
      numPlayers,
      currentPlayer,
      handPos,
      numTreasure,
      deckTreasure,
      discardTreasure,
      deckSize,
      handSize,
      discardSize,
      choice1,
      choice2,
      choice3,
      bonus = 0,
      i = 0,
      k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                     sea_hag, tribute, smithy, council_room},
      cardToTest = adventurer;

  char buffer[100],
       *cardName = "Adventurer";

  numPlayers = 1 + rand() % MAX_PLAYER;
  while (numPlayers < 2) numPlayers = 1 + rand() % MAX_PLAYER;

  currentPlayer = rand() % numPlayers;


  numTreasure = 1 + rand() % MAX_TREASURE;

  handSize = rand() % MAX_HANDSIZE;

  deckSize = rand() % MAX_DECKSIZE;
  discardSize = MAX_TREASURE + rand() % MAX_DISCARD;

  initializeGame(numPlayers, k, seed, &testG);

  testG.whoseTurn = currentPlayer;
  advDetails.currentPlayer = currentPlayer;
  testG.numPlayers = numPlayers;

  testG.handCount[currentPlayer] = handSize;

  if (handSize > 0) {
    handPos = rand() % handSize;
    for (i = 0; i < handSize; i++) {
      testG.hand[currentPlayer][i] = rand() & NUM_CARDS;
    }
    testG.hand[currentPlayer][handPos] = cardToTest;
  }
  else {
    handPos = 0;
    testG.hand[currentPlayer][testG.handCount[currentPlayer]++] = cardToTest;
  }
  testG.deckCount[currentPlayer] = deckSize;
  if (deckSize != 0) {
    //determin how to allocate treasure
    deckTreasure = rand() % numTreasure;
    while (deckTreasure > deckSize) deckTreasure = rand() % numTreasure;
    discardTreasure = numTreasure - deckTreasure;

    for (i = 0; i < deckSize; i++) {
      int card = rand() % NUM_CARDS;
      while (card >= copper && card <= gold) card = rand() % NUM_CARDS;
      testG.deck[currentPlayer][i] = card;
    }
    for (i = 0; i < deckTreasure; i++) {
      int card = rand() % 3 + copper;
      int index = rand() % deckSize;
      while (testG.deck[currentPlayer][index] >= copper &&
        testG.deck[currentPlayer][index] <= gold) {
          index = rand() % deckSize;
      }
      testG.deck[currentPlayer][index] = card;
    }
  } else {
    discardTreasure = numTreasure;
  }

  testG.discardCount[currentPlayer] = discardSize;
  for (i = 0; i < discardSize; i++) {
    int card = rand() % NUM_CARDS;
    while (card >= copper && card <= gold) card = rand() % NUM_CARDS;
    testG.discard[currentPlayer][i] = card;
  }
  for (i = 0; i < discardTreasure; i++) {
    int card = rand() % 3 + copper;
    int index = rand() % discardSize;
    while (testG.discard[currentPlayer][index] >= copper &&
           testG.discard[currentPlayer][index] <= gold) {
           index = rand() % discardSize;
    }
    testG.discard[currentPlayer][index] = card;
  }

  printf("Test %d %s, Player %d, %d cards in deck (%d treasure), %d in discard (%d treasure) and %d in hand\n",
            test, cardName, currentPlayer, deckSize, deckTreasure, discardSize, discardTreasure, handSize);
  printf("\tNumber of players: %d\n", numPlayers);

  seed = treasureCount(currentPlayer, &testG);

  asserttrue(seed == numTreasure, "Check random treasure logic, unexpected count in deck/discard");

  // copy state variables into reference states
  memcpy(&refG, &testG, sizeof(struct gameState));
  memcpy(&refUnchanged, &testG, sizeof(struct gameState));

  // Call Reference Logic on reference state
  refPlayAdventurer(&refG, &advDetails);

  choice1 = rand() % 4;
  choice2 = rand() % 4;
  choice3 = rand() % 4;
  printf("\tCalling %s: Choice 1: %d, Choice 2: %d, Choce 3: %d\n", cardName,choice1, choice2, choice3);
  //call cardEffect for adventurer on player
  success = cardEffect(cardToTest, choice1, choice2, choice3, &testG, 0, &bonus);

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


  // assert that reference adventurer logic is working correctly.
  // Does not count towards error_count for dominion.c code
  printf("\tChecking reference logic\n");
  error += asserttrue(advDetails.temphandCount == 0, "TempHand Count Should be 0, Check reference logic");
  error += asserttrue(advDetails.discardCount == refG.discardCount[currentPlayer],
    "Discard count does not match drawn cards, check reference logic");

  if (numTreasure == 1) {
    error += asserttrue(topNCardsTreasure(currentPlayer, 1, &refG), "Incorrect Treasure Count Drawn");
  }
  else {
    error += asserttrue(topNCardsTreasure(currentPlayer, 2, &refG), "Incorrect Treasure Count Drawn");
  }

  // walk backwards though discard and forwards through tempHand and confirm they match
  // (this is because tempHand is added to discard in revers order)
  // This makes sure that all drawn non-currency cards are added to discard.
  // Also assert that no currency cards were discarded
  seed = 0;  // use seed as a counter
  advDetails.temphandCount = 0;
  while (advDetails.discardCount > advDetails.offsetDiscard) {
	  if (refG.discard[currentPlayer][advDetails.discardCount-1] == advDetails.temphand[advDetails.temphandCount] &&
        (advDetails.temphand[advDetails.temphandCount] < copper || advDetails.temphand[advDetails.temphandCount] > gold)) {
		  seed++;
    }
	  advDetails.temphandCount++;
	  advDetails.discardCount--;
  }
  //printf("%d %d", seed, advDetails.temphandCount);
  error += asserttrue(seed == advDetails.temphandCount, "Cards added to discard should match non-currency cards drawn, check reference logic");
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

  if (numTreasure == 1)
    success = topNCardsTreasure(currentPlayer, 1, &testG);
  else
    success = topNCardsTreasure(currentPlayer, 2, &testG);

  printf("\t\tExpecting 1 if proper number of currency Cards Drawn, got %d\n", success);
  error += asserttrue(success, "Incorrect Treasure Count Drawn");

  printf("\t\tExpecting handCount %d and received %d\n", refG.handCount[currentPlayer], testG.handCount[currentPlayer]);
  error += asserttrue(refG.handCount[currentPlayer] == testG.handCount[currentPlayer],
      "handCount does not match reference");

  if (!advDetails.shuffleOccurred) {
    printf("\t\tNo Shuffle, Expects %d if reference discardCount matches returned got %d\n",
          refG.discardCount[currentPlayer], testG.discardCount[currentPlayer]);
    error += asserttrue(refG.discardCount[currentPlayer] == testG.discardCount[currentPlayer],
          "discardCount does not match reference");
    printf("\t\tNo Shuffle,Expects %d if reference deckCount matches returned got %d\n",
          refG.deckCount[currentPlayer], testG.deckCount[currentPlayer]);
    error += asserttrue(refG.deckCount[currentPlayer] == testG.deckCount[currentPlayer],
            "deckCount does not match reference");
  } else {
    printf("\t\tShuffle Occured: Expects %d if reference discardCount + deckCount matches returned got %d\n",
          refG.discardCount[currentPlayer]+refG.deckCount[currentPlayer],
          testG.discardCount[currentPlayer] + testG.deckCount[currentPlayer]);
    error += asserttrue(refG.discardCount[currentPlayer]+refG.deckCount[currentPlayer] ==
          testG.discardCount[currentPlayer] + testG.deckCount[currentPlayer],
          "sum of discardCount and deckCount should match after shuffle");
  }
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

  printf("------------------------ Testing Adventurer Card ------------------------------\n");

  for (i = 0; i < TEST_NUM; i++)
    performRandomTest(&total, i+1, seed);

  if (total.testsFailed == 0)
      printf("ALL %d TESTS SUCCESSFUL, Adventurer\n", total.testsPassed);
  else
      printf("%d TESTS FAILED, %d TESTS PASSED Adventurer\n", total.testsFailed, total.testsPassed);
  printf("------------------------ END Test Adventurer Card ------------------------------\n\n");

  return 0;
}

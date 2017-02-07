#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int asserttrue(int condition, char* message)
{
  if (!condition) {
    printf("\t\tError: %s\n", message);
    return 1;
  }

  return 0;
}


int main(int argc, char** argv)
{
  struct gameState G,		//used as reference Game state
                   testG;	//used as test Game state
  int i = 0,
      success = 1, 			//used to assert function returns success
      error_count = 0,		// used to count errors in current test
      error_total = 0,		// used to keep track of total errors in Unit test
      copper_count = 0,		// used to count copper in init game test
      estate_count = 0, 	// used to count estate in init game test
      seed = 0,				// used to seed init game at the beginning, used later as count variable for some tests
      k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, great_hall, tribute, smithy},
      bonus = 0,			// passed to initializeGame
      tempDeck[MAX_DECK],       // store deck to check that Great Hall cards come from there
      tempDeckCount,
      tempHandCount;

  // Great Hall reference logic helper variables
  int currentPlayer = 1,	// track current player
      z = 0,				     // track size of temphand
	    handPos = 0;			// position of Great Hall card


  //Variables to check alternate players deck remains intact and gameState.
  int alternatePlayer = 0,
	  altHandCount = 0,
	  altDeckCount = 0,
	  altDiscardCount = 0,
	  altHand[MAX_HAND],
	  altDeck[MAX_DECK],
	  altDiscard[MAX_DECK],
	  numPlayers, //number of players,
	  supplyCount[treasure_map+1],
	  embargoTokens[treasure_map+1],
	  outpostPlayed,
	  outpostTurn,
	  whoseTurn,
	  phase,
	  coins, /* Use as you see fit! */
	  numBuys; /* Starts at 1 each turn */

  printf("------------------------ Testing Great Hall Card ------------------------------\n");

  seed = 1 + rand() % 10;
  // BEGIN INITIALIZATION TEST to gameState is correct
  printf("\n------------------------ Initializing Game----------------------\n");
  // Make sure initialize game returns success, if not exit
  success = initializeGame(2, k, seed, &G);
  asserttrue(success == 0, "Failed to Initialize Game");
  if ( success == -1 ) return 1;

  // initialize game returns success, check values are what is expected

  // Make sure player count is correct
  error_count += asserttrue(G.numPlayers == 2, "Player Count Wrong");
  // Make sure supply counts are correct
  error_count += asserttrue(G.supplyCount[curse] == 10, "Curse Count Incorrect for 2 players");
  error_count += asserttrue(G.supplyCount[estate] == 8, "Estate Count Incorrect for 2 players");

  error_count += asserttrue(G.supplyCount[duchy] == 8, "Duchy Count Incorrect for 2 players");

  error_count += asserttrue(G.supplyCount[province] == 8, "Province Count Incorrect for 2 players");

  error_count += asserttrue(G.supplyCount[copper] == 46, "Copper Count Incorrect for 2 players");

  error_count += asserttrue(G.supplyCount[silver] == 40, "Silver Count Incorrect for 2 players");
  error_count += asserttrue(G.supplyCount[gold] == 30, "Gold Count Incorrect for 2 players");
  // Check Kingdom Card supply
  for (i = 0; i < 10; i++ ) {
    if (k[i] == great_hall || k[i] == gardens) {
      error_count += asserttrue(G.supplyCount[ k[i] ] == 8, "Deck Incorrect for 2 players");
    } else {
      error_count += asserttrue(G.supplyCount[ k[i] ] == 10, "Deck Incorrect for 2 players");
    }
  }

  // Make sure player deckcounts are correct
  // Player 1 is first so deckcount if 5 after drawing 5 cards, Player 2 should be 10
  error_count += asserttrue(G.deckCount[0] == 5 && G.deckCount[1] == 10,
      "Player Deck Counts Incorrect");
  // Player 1 handCount is 5 and player 2 handCount is 0
  error_count += asserttrue(G.handCount[0] == 5 && G.handCount[1] == 0, "Player Handcount Incorrect");

  // Count Player 1s starting cards in hand and deck. SHould be 7 copper and
  // 3 estate
  for (i = 0; i < 10; i++) {
    if (i < G.handCount[0]) {
      if (G.hand[0][i] == copper)
        copper_count++;
      else if (G.hand[0][i] == estate)
        estate_count++;
    }
    if (i < G.deckCount[0]) {
      if (G.deck[0][i] == copper)
        copper_count++;
      else if (G.deck[0][i] == estate)
        estate_count++;
    }
  }

  error_count += asserttrue(estate_count == 3 && copper_count == 7, "Player 1 starting Deck is Incorrect");
  estate_count = 0;
  copper_count = 0;
  // Count Player 2s starting cards, should be 7 copper and 3 estate
  for (i = 0; i < 10; i++) {
    if ( i < G.handCount[1] ) {
      if (G.hand[1][i] == copper)
        copper_count++;
      else if (G.hand[1][i] == estate)
        estate_count++;
    }
    if ( i < G.deckCount[1]) {
      if (G.deck[1][i] == copper)
        copper_count++;
      else if (G.deck[1][i] == estate)
        estate_count++;
    }
  }
  error_count += asserttrue(estate_count == 3 && copper_count == 7,
      "Player 2 starting Deck is incorrect");

  // Check that player 1s turn is initialized correctly
  error_count += asserttrue(G.outpostPlayed == 0 &&
      G.phase == 0 &&
      G.numActions == 1 &&
      G.numBuys == 1 &&
      G.playedCardCount == 0 &&
      G.whoseTurn == 0, "Player 1 Turn Initialized Incorrectly");

  // If error_count is still 0 then Game was initialized successfully
  if (error_count ==  0 )
    printf("Game Initiliazed Successfully\n");
  else
    printf("Game Initialization encountered %d errors\n", error_count);

  printf("------------------------ Finished Initialization Section ----------------------\n\n");

  error_count = 0;

//******************************* TEST 1 - Default Deck (Just Initialized) Great Hall on player 2 *********************************
  printf("Test 1 Great Hall, Player 2 default deck, 10 cards in deck, 0 in discard, and only Great Hall in hand\n");

  // Add Great Hall to player 2's hand
  G.hand[currentPlayer][0] = great_hall;
  G.handCount[currentPlayer] = 1;
  handPos = 0;
  tempHandCount = G.handCount[currentPlayer];

  G.whoseTurn = 1;  // mark it as player 2's turn
  memcpy(&testG, &G, sizeof(struct gameState));


  // Store altPlayers hand to check after call to Great Hall
  memcpy(&altDeck, &testG.deck[alternatePlayer], MAX_DECK * sizeof(int));
  memcpy(&altDiscard, &testG.discard[alternatePlayer], MAX_DECK * sizeof(int));
  memcpy(&altHand, &testG.hand[alternatePlayer], MAX_HAND * sizeof(int));
  //memcpy(&supplyCount, &testG.supplyCount, treasure_map+1 * sizeof(int));
  for (i = 0; i < treasure_map+1; i++)
	  supplyCount[i] = testG.supplyCount[i];
  memcpy(&embargoTokens, &testG.embargoTokens, treasure_map+1 * sizeof(int));
  altDeckCount = testG.deckCount[alternatePlayer];
  altHandCount = testG.handCount[alternatePlayer];
  altDiscardCount = testG.discardCount[alternatePlayer];
  numPlayers = testG.numPlayers;
  outpostPlayed = testG.outpostPlayed;
  outpostTurn = testG.outpostTurn;
  whoseTurn = testG.whoseTurn;
  phase = testG.phase;
  coins  = testG.coins;
  numBuys = testG.numBuys;

  //call cardEffect for Great Hall on player
  success = cardEffect(great_hall, -1, -1, -1, &testG, handPos, &bonus);

  //******************************* APPLY Great Hall LOGIC TO REFERENCE STATE *********************************
  // Here we implement the logic of Great Hall
  // Draw 1 Card from Deck and Add 1 Actions to currentPlayer
  //+1 Card
  drawCard(currentPlayer, &G);

  //+1 Actions
  G.numActions = G.numActions + 1;

  //discard played card from hand
  discardCard(handPos, currentPlayer, &G, 0);
  //******************************* END Great Hall LOGIC TO REFERENCE  *********************************

  // assert that reference Great Hall logic is working correctly.
  // Does not count towards error_count for dominion.c code
  asserttrue(G.handCount[currentPlayer] == 1, "Expected handCount to be 1 after reference Great Hall logic, check test");
  asserttrue(G.playedCards[G.playedCardCount-1] == great_hall, "Great Hall should be in played pile");
  // make sure Great Hall is not in hand
  z = 0;
  for (i = 0; i < G.handCount[currentPlayer]; i++ ) {
	  if (G.hand[currentPlayer][i] == great_hall)
		  z++;
  }
  asserttrue(z == 0, "Great Hall should not be in hand, check reference logic");
  asserttrue(G.numActions == 2, "Num Actions should have increased by 2, check reference logic");
  // ********** End checking reference Great Hall logic

  //*********************** LOGIC TO CHECK Great Hall doesnt effect other players deck or other gamestate vars **************/
  printf("\tExpecting Great Hall does not alter other players deck or irrelevent game state variables\n");
  // check altPlayers hand matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altHandCount; i++)
	  if (altHand[i] == testG.hand[alternatePlayer][i])
		  z++;
  error_count += asserttrue(z == altHandCount, "Great Hall changed another players hand");

  // check altPlayers deck matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altDeckCount; i++)
	  if (altDeck[i] == testG.deck[alternatePlayer][i])
		  z++;
  error_count += asserttrue(z == altDeckCount, "Great Hall changed another players deck");

  // check altPlayers discard matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altDiscardCount; i++)
	  if (altDiscard[i] == testG.discard[alternatePlayer][i])
		  z++;

  error_count += asserttrue(z == altDiscardCount, "Great Hall changed another players discard");

  // check supplyCounts match copy
  z = 0;	// z used to count matches
  for (i = 0; i < treasure_map+1; i++)
	  if (supplyCount[i] == testG.supplyCount[i])
		  z++;

  error_count += asserttrue(z == treasure_map+1, "Great Hall changed supplyCount");

  // check embargoTokens match copy
  z = 0;	// z used to count matches
  for (i = 0; i < treasure_map+1; i++)
	  if (embargoTokens[i] == testG.embargoTokens[i])
		  z++;

  error_count += asserttrue(z == treasure_map+1, "Great Hall changed embargoTokens");

  // Assert altHandCount, altDeckCount, and altDiscardCount match current alternate players counts
  error_count += asserttrue(testG.handCount[alternatePlayer] == altHandCount, "Great Hall changed another players handCount");
  error_count += asserttrue(testG.deckCount[alternatePlayer] == altDeckCount, "Great Hall changed another players deckCount");
  error_count += asserttrue(testG.discardCount[alternatePlayer] == altDiscardCount, "Great Hall changed another players handCount");
  // assert that other gameState variables have not changed
  error_count += asserttrue(numPlayers == testG.numPlayers, "Great Hall change numPlayers");
  error_count += asserttrue(outpostPlayed == testG.outpostPlayed, "Great Hall change outpostPlayed");
  error_count += asserttrue(outpostTurn == testG.outpostTurn, "Great Hall change outpostTurn");
  error_count += asserttrue(whoseTurn == testG.whoseTurn, "Great Hall change whoseTurn");
  error_count += asserttrue(phase == testG.phase, "Great Hall change phase");
  error_count += asserttrue(coins == testG.coins, "Great Hall change coins");
  error_count += asserttrue(numBuys == testG.numBuys, "Great Hall change numBuys");

  if (error_count == 0)
	  printf("\t\tSuccess: Great Hall does not change other players hand or irrelevant game state variables\n");
  //*********************** END OF LOGIC TO CHECK Great Hall doesnt effect other players deck **************/

  // assert cardEffect returns 0
  error_count += asserttrue(success == 0, "Call to cardEffect for Great Hall returned status failed");

  // assert handCounts matches reference
  printf("\tExpecting handCount %d and received %d\n", G.handCount[currentPlayer], testG.handCount[currentPlayer]);
  error_count += asserttrue(G.handCount[currentPlayer] == testG.handCount[currentPlayer],
      "handCount does not match reference");

  // test that 3 cards were drawn
  printf("\tExpecting 1 cards to have been added to the hand, got %d\n", testG.handCount[currentPlayer]-(tempHandCount-1));
  error_count += asserttrue(testG.handCount[currentPlayer]-(tempHandCount-1) == 1,
                    "Should have only drawn 1 card");

  printf("\tExpecting %d if numActions of returned to match reference, got %d\n", G.numActions, testG.numActions);
  asserttrue(G.numActions == testG.numActions, "numActions in returned should match reference");


  seed = 0;
  if (G.hand[currentPlayer][G.handCount[currentPlayer]-1] == testG.hand[currentPlayer][testG.handCount[currentPlayer]-1]) {
    seed++;
  }
  // print expected result of reference comparison and assert it is as expected
  printf("\tExpects 1 if card drawn in reference and returned are the same got %d\n", seed);
  error_count += asserttrue(seed == 1, "Reference and returned hand should match");

  // keep track of whether returned hand has Great Hall
  seed = 0;
  // Check returned hand doesnt have Great Hall
  for (i = 0; i < testG.handCount[currentPlayer]; i++) {
    if (testG.hand[currentPlayer][i] == great_hall)
      seed++;
  }
  // print expected value of Great Hall card in hand
  printf("\tExpects 0 if returned hand doesnt have Great Hall card and got %d\n", seed);
  error_count += asserttrue(seed == 0, "Great Hall should not be in hand");

  // keep track of whether returned deck matches reference
  seed = 0;
  // Check returned deck matches reference
  for (i = 0; i < testG.deckCount[currentPlayer]; i++) {
    if (testG.deck[currentPlayer][i] == G.deck[currentPlayer][i])
      seed++;
  }

  // print expected value of Great Hall card in hand
  printf("\tExpects %d if returned deck matches reference and got %d\n", G.deckCount[currentPlayer], seed);
  error_count += asserttrue(seed == G.deckCount[currentPlayer], "Reference deck should match returned");

  // print comparison of expected deckCount and reference and assert it is as expected
  printf("\tExpects %d if reference deckCount matches returned got %d\n",
      G.deckCount[currentPlayer], testG.deckCount[currentPlayer]);
  error_count += asserttrue(G.deckCount[currentPlayer] == testG.deckCount[currentPlayer],
      "deckCount does not match reference");

  // print comparison of expected discardCount and reference and assert it is as expected
  printf("\tExpects %d if reference discardCount matches returned got %d\n",
      G.discardCount[currentPlayer], testG.discardCount[currentPlayer]);
  error_count += asserttrue(G.discardCount[currentPlayer] == testG.discardCount[currentPlayer],
      "discardCount does not match reference");

  if (error_count == 0)
    printf("\n\tAll Tests Successful, Player 2 default deck\n\n");
  else
    printf("\n\t%d Tests Failed, Player 2 default deck\n\n", error_count);

  error_total += error_count;
  error_count = 0;

  //******************************* TEST 2 - Player1 deck empty, discard has 12 cards with, 3 copper in hand with Great Hall in pos 1 ***********************
  printf("Test 2 Great Hall, Player1 discard empty, deck has 12 cards with, 3 copper in hand with Great Hall in pos 1\n");

  // clear Great Hall variables and make currentPlayer player 1
  currentPlayer = 0;
  z = 0;

  // clear altPlayer variables
  alternatePlayer = 1;
  altHandCount = 0;
  altDeckCount = 0;
  altDiscardCount = 0;


  // make it player 1's turn
  G.whoseTurn = 0;
  // empty player 1 deck and fill discard with two copper
  G.deckCount[currentPlayer] = 0;
  G.discardCount[currentPlayer] = 0;
  G.handCount[currentPlayer] = 0;
  // add 10 non-currency cards
  for (i = 0; i < 12; i++)
      G.deck[currentPlayer][G.deckCount[currentPlayer]++] = i;

  G.hand[currentPlayer][G.handCount[currentPlayer]++] = copper;
  G.hand[currentPlayer][G.handCount[currentPlayer]++] = great_hall;
  G.hand[currentPlayer][G.handCount[currentPlayer]++] = copper;
  G.hand[currentPlayer][G.handCount[currentPlayer]++] = copper;
  handPos = 1;
  tempHandCount = G.handCount[currentPlayer];
  G.numActions = 1;

  // copy new player 1 state into
  memcpy(&testG, &G, sizeof(struct gameState));

  // Copy testG deck and discard into temp storage
  for (i = 0; i < testG.deckCount[currentPlayer]; i++)
    tempDeck[i] = testG.deck[currentPlayer][i];
  tempDeckCount = i;


  // Store altPlayers hand to check after call to Great Hall
  memcpy(&altDeck, &testG.deck[alternatePlayer], MAX_DECK * sizeof(int));
  memcpy(&altDiscard, &testG.discard[alternatePlayer], MAX_DECK * sizeof(int));
  memcpy(&altHand, &testG.hand[alternatePlayer], MAX_HAND * sizeof(int));
  //memcpy(&supplyCount, &testG.supplyCount, treasure_map+1 * sizeof(int));
  for (i = 0; i < treasure_map+1; i++)
	  supplyCount[i] = testG.supplyCount[i];
  memcpy(&embargoTokens, &testG.embargoTokens, treasure_map+1 * sizeof(int));
  altDeckCount = testG.deckCount[alternatePlayer];
  altHandCount = testG.handCount[alternatePlayer];
  altDiscardCount = testG.discardCount[alternatePlayer];
  numPlayers = testG.numPlayers;
  outpostPlayed = testG.outpostPlayed;
  outpostTurn = testG.outpostTurn;
  whoseTurn = testG.whoseTurn;
  phase = testG.phase;
  coins  = testG.coins;
  numBuys = testG.numBuys;

  //call cardEffect for Great Hall on player
  success = cardEffect(great_hall, -1, -1, -1, &testG, handPos, &bonus);

  //******************************* APPLY Great Hall LOGIC TO REFERENCE STATE *********************************
  // Here we implement the logic of Great Hall
  // Draw 1 Card from Deck and Add 1 Actions to currentPlayer
  //+1 Card
  drawCard(currentPlayer, &G);

  //+2 Actions
  G.numActions = G.numActions + 1;

  //discard played card from hand
  discardCard(handPos, currentPlayer, &G, 0);
  //******************************* END Great Hall LOGIC TO REFERENCE  *********************************


  // assert that reference Great Hall logic is working correctly.
  // Does not count towards error_count for dominion.c code
  asserttrue(G.handCount[currentPlayer] == tempHandCount, "Expected handCount to be the same after reference Great Hall logic, check test");
  asserttrue(G.playedCards[G.playedCardCount-1] == great_hall, "Great Hall should be in played pile");
  // make sure Great Hall is not in hand
  z = 0;
  for (i = 0; i < G.handCount[currentPlayer]; i++ ) {
	  if (G.hand[currentPlayer][i] == great_hall)
		  z++;
  }
  asserttrue(z == 0, "Great Hall should not be in hand, check reference logic");
  asserttrue(G.numActions == 2, "Num Actions should have increased by 1, check reference logic");
  // ********** End checking reference Great Hall logic
  //*********************** LOGIC TO CHECK Great Hall doesnt effect other players deck or other gamestate vars **************/
  printf("\tExpecting Great Hall does not alter other players deck or irrelevent game state variables\n");
  // check altPlayers hand matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altHandCount; i++)
	  if (altHand[i] == testG.hand[alternatePlayer][i])
		  z++;
  error_count += asserttrue(z == altHandCount, "Great Hall changed another players hand");

  // check altPlayers deck matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altDeckCount; i++)
	  if (altDeck[i] == testG.deck[alternatePlayer][i])
		  z++;
  error_count += asserttrue(z == altDeckCount, "Great Hall changed another players deck");

  // check altPlayers discard matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altDiscardCount; i++)
	  if (altDiscard[i] == testG.discard[alternatePlayer][i])
		  z++;

  error_count += asserttrue(z == altDiscardCount, "Great Hall changed another players discard");

  // check supplyCounts match copy
  z = 0;	// z used to count matches
  for (i = 0; i < treasure_map+1; i++)
	  if (supplyCount[i] == testG.supplyCount[i])
		  z++;

  error_count += asserttrue(z == treasure_map+1, "Great Hall changed supplyCount");

  // check embargoTokens match copy
  z = 0;	// z used to count matches
  for (i = 0; i < treasure_map+1; i++)
	  if (embargoTokens[i] == testG.embargoTokens[i])
		  z++;


  error_count += asserttrue(z == treasure_map+1, "Great Hall changed embargoTokens");

  // Assert altHandCount, altDeckCount, and altDiscardCount match current alternate players counts
  error_count += asserttrue(testG.handCount[alternatePlayer] == altHandCount, "Great Hall changed another players handCount");
  error_count += asserttrue(testG.deckCount[alternatePlayer] == altDeckCount, "Great Hall changed another players deckCount");
  error_count += asserttrue(testG.discardCount[alternatePlayer] == altDiscardCount, "Great Hall changed another players handCount");
  // assert that other gameState variables have not changed
  error_count += asserttrue(numPlayers == testG.numPlayers, "Great Hall change numPlayers");
  error_count += asserttrue(outpostPlayed == testG.outpostPlayed, "Great Hall change outpostPlayed");
  error_count += asserttrue(outpostTurn == testG.outpostTurn, "Great Hall change outpostTurn");
  error_count += asserttrue(whoseTurn == testG.whoseTurn, "Great Hall change whoseTurn");
  error_count += asserttrue(phase == testG.phase, "Great Hall change phase");
  error_count += asserttrue(coins == testG.coins, "Great Hall change coins");
  error_count += asserttrue(numBuys == testG.numBuys, "Great Hall change numBuys");

  if (error_count == 0)
	  printf("\t\tSuccess: Great Hall does not change irrelevant game state variables\n");
  //*********************** END OF LOGIC TO CHECK Great Hall doesnt effect other players deck **************/

  // assert cardEffect returns 0
  error_count += asserttrue(success == 0, "Call to cardEffect for Great Hall returned status failed");

  // assert handCounts matches reference
  printf("\tExpecting handCount %d and received %d\n", G.handCount[currentPlayer], testG.handCount[currentPlayer]);
  error_count += asserttrue(G.handCount[currentPlayer] == testG.handCount[currentPlayer],
      "handCount does not match reference");

  // test that 3 cards were drawn
  printf("\tExpecting 1 card to have been added to the hand, got %d\n", testG.handCount[currentPlayer]-(tempHandCount-1));
  error_count += asserttrue(testG.handCount[currentPlayer]-(tempHandCount-1) == 1,
                "Should have only drawn 1 card");
  // Drawn card should wind up in handPos
  seed = 0;
  if (G.hand[currentPlayer][handPos] == testG.hand[currentPlayer][handPos])
    seed++;

  // print expected result of reference comparison and assert it is as expected
  printf("\tExpects 1 if cards drawn in reference and returned are the same got %d\n", seed);
  error_count += asserttrue(seed == 1, "Reference and returned hand should match");

  seed = 0;
  // Make sure that cards added to hand come from deck
  // last card added is from the third to last position in tempdeck and is
  // swapped with Great Hall position
  if (tempDeck[tempDeckCount-1] == testG.hand[currentPlayer][handPos])
    seed++;

  printf("\tExpects 1 if the card drawn came from the top of the deck and got %d\n", seed);
  error_count += asserttrue(seed == 1, "Card should come from top of the deck.");

  printf("\tExpects %d if the numActions in the reference equals returned, got %d\n", G.numActions, testG.numActions);
  error_count += asserttrue(G.numActions == testG.numActions, "numActions should be equal between reference and returned");

  // keep track of whether returned hand has Great Hall
  seed = 0;
  // Check returned hand doesnt have Great Hall
  for (i = 0; i < testG.handCount[currentPlayer]; i++) {
    if (testG.hand[currentPlayer][i] == great_hall)
      seed++;
  }
  // print expected value of Great Hall card in hand
  printf("\tExpects 0 if returned hand doesnt have Great Hall card and got %d\n", seed);
  error_count += asserttrue(seed == 0, "Great Hall should not be in hand");

  // keep track of whether returned deck matches reference
  seed = 0;
  // Check returned deck matches reference
  for (i = 0; i < testG.deckCount[currentPlayer]; i++) {
    if (testG.deck[currentPlayer][i] == G.deck[currentPlayer][i])
      seed++;
  }

  // print expected value of Great Hall card in hand
  printf("\tExpects %d if returned deck matches reference and got %d\n", G.deckCount[currentPlayer], seed);
  error_count += asserttrue(seed == G.deckCount[currentPlayer], "Reference deck should match returned");

  // print comparison of expected deckCount and reference and assert it is as expected
  printf("\tExpects %d if reference deckCount matches returned got %d\n",
      G.deckCount[currentPlayer], testG.deckCount[currentPlayer]);
  error_count += asserttrue(G.deckCount[currentPlayer] == testG.deckCount[currentPlayer],
      "deckCount does not match reference");

  // print comparison of expected discardCount and reference and assert it is as expected
  printf("\tExpects %d if reference discardCount matches returned got %d\n",
      G.discardCount[currentPlayer], testG.discardCount[currentPlayer]);
  error_count += asserttrue(G.discardCount[currentPlayer] == testG.discardCount[currentPlayer],
      "discardCount does not match reference");

  if (error_count == 0)
    printf("\n\tAll Tests Successful, Test 2 Great Hall, Player1 discard empty, deck has 12 cards with, 3 copper in hand with Great Hall in pos 1\n\n");
  else
    printf("\n\t%d Tests Failed, Test 2 Great Hall, Player1 discard empty, deck has 12 cards with, 3 copper in hand with Great Hall in pos 1\n\n", error_count);

  error_total += error_count;
  error_count = 0;

  //******************************* TEST 3 - Great Hall, Player 2 empty deck, 12 cards in discard, hand has 2 silver with Great Hall on top ***********************
  printf("Test 3 Great Hall, Player 2 empty deck, 12 cards in discard, hand has 2 silver with Great Hall on top\n");

  // clear Great Hall variables and make currentPlayer player 1
  currentPlayer = 1;
  z = 0;

  // clear altPlayer variables
  alternatePlayer = 0;
  altHandCount = 0;
  altDeckCount = 0;
  altDiscardCount = 0;


  // make it player 1's turn
  G.whoseTurn = 1;
  // empty player 1 deck and fill discard with two copper
  G.deckCount[currentPlayer] = 0;
  G.discardCount[currentPlayer] = 0;
  G.handCount[currentPlayer] = 0;
  // add 10 non-currency cards
  for (i = 0; i < 12; i++)
      G.discard[currentPlayer][G.discardCount[currentPlayer]++] = i;

  G.hand[currentPlayer][G.handCount[currentPlayer]++] = silver;
  G.hand[currentPlayer][G.handCount[currentPlayer]++] = silver;
  G.hand[currentPlayer][G.handCount[currentPlayer]++] = great_hall;
  handPos = 2;
  tempHandCount = G.handCount[currentPlayer];
  G.numActions = 1;

  // copy new player 1 state into
  memcpy(&testG, &G, sizeof(struct gameState));

  // Store altPlayers hand to check after call to Great Hall
  memcpy(&altDeck, &testG.deck[alternatePlayer], MAX_DECK * sizeof(int));
  memcpy(&altDiscard, &testG.discard[alternatePlayer], MAX_DECK * sizeof(int));
  memcpy(&altHand, &testG.hand[alternatePlayer], MAX_HAND * sizeof(int));
  //memcpy(&supplyCount, &testG.supplyCount, treasure_map+1 * sizeof(int));
  for (i = 0; i < treasure_map+1; i++)
	  supplyCount[i] = testG.supplyCount[i];
  memcpy(&embargoTokens, &testG.embargoTokens, treasure_map+1 * sizeof(int));
  altDeckCount = testG.deckCount[alternatePlayer];
  altHandCount = testG.handCount[alternatePlayer];
  altDiscardCount = testG.discardCount[alternatePlayer];
  numPlayers = testG.numPlayers;
  outpostPlayed = testG.outpostPlayed;
  outpostTurn = testG.outpostTurn;
  whoseTurn = testG.whoseTurn;
  phase = testG.phase;
  coins  = testG.coins;
  numBuys = testG.numBuys;

  //call cardEffect for Great Hall on player
  success = cardEffect(great_hall, -1, -1, -1, &testG, handPos, &bonus);

  //******************************* APPLY Great Hall LOGIC TO REFERENCE STATE *********************************
  // Here we implement the logic of Great Hall
  // Draw 1 Card from Deck and Add 2 Actions to currentPlayer
  //+1 Card
  drawCard(currentPlayer, &G);

  //+2 Actions
  G.numActions = G.numActions + 1;

  //discard played card from hand
  discardCard(handPos, currentPlayer, &G, 0);
  //******************************* END Great Hall LOGIC TO REFERENCE  *********************************


  // assert that reference Great Hall logic is working correctly.
  // Does not count towards error_count for dominion.c code
  asserttrue(G.handCount[currentPlayer] == tempHandCount , "Expected handCount be the same after reference Great Hall logic, check test");
  asserttrue(G.playedCards[G.playedCardCount-1] == great_hall, "Great Hall should be in played pile");
  // make sure Great Hall is not in hand
  z = 0;
  for (i = 0; i < G.handCount[currentPlayer]; i++ ) {
	  if (G.hand[currentPlayer][i] == great_hall)
		  z++;
  }
  asserttrue(z == 0, "Great Hall should not be in hand, check reference logic");
  asserttrue(G.numActions == 2, "Num Actions should have increased by 1, check reference logic");
  // ********** End checking reference Great Hall logic

  //*********************** LOGIC TO CHECK Great Hall doesnt effect other players deck or other gamestate vars **************/
  printf("\tExpecting Great Hall does not alter other players deck or irrelevent game state variables\n");
  // check altPlayers hand matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altHandCount; i++)
	  if (altHand[i] == testG.hand[alternatePlayer][i])
		  z++;
  error_count += asserttrue(z == altHandCount, "Great Hall changed another players hand");

  // check altPlayers deck matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altDeckCount; i++)
	  if (altDeck[i] == testG.deck[alternatePlayer][i])
		  z++;
  error_count += asserttrue(z == altDeckCount, "Great Hall changed another players deck");

  // check altPlayers discard matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altDiscardCount; i++)
	  if (altDiscard[i] == testG.discard[alternatePlayer][i])
		  z++;

  error_count += asserttrue(z == altDiscardCount, "Great Hall changed another players discard");

  // check supplyCounts match copy
  z = 0;	// z used to count matches
  for (i = 0; i < treasure_map+1; i++)
	  if (supplyCount[i] == testG.supplyCount[i])
		  z++;

  error_count += asserttrue(z == treasure_map+1, "Great Hall changed supplyCount");

  // check embargoTokens match copy
  z = 0;	// z used to count matches
  for (i = 0; i < treasure_map+1; i++)
	  if (embargoTokens[i] == testG.embargoTokens[i])
		  z++;


  error_count += asserttrue(z == treasure_map+1, "Great Hall changed embargoTokens");

  // Assert altHandCount, altDeckCount, and altDiscardCount match current alternate players counts
  error_count += asserttrue(testG.handCount[alternatePlayer] == altHandCount, "Great Hall changed another players handCount");
  error_count += asserttrue(testG.deckCount[alternatePlayer] == altDeckCount, "Great Hall changed another players deckCount");
  error_count += asserttrue(testG.discardCount[alternatePlayer] == altDiscardCount, "Great Hall changed another players handCount");
  // assert that other gameState variables have not changed
  error_count += asserttrue(numPlayers == testG.numPlayers, "Great Hall change numPlayers");
  error_count += asserttrue(outpostPlayed == testG.outpostPlayed, "Great Hall change outpostPlayed");
  error_count += asserttrue(outpostTurn == testG.outpostTurn, "Great Hall change outpostTurn");
  error_count += asserttrue(whoseTurn == testG.whoseTurn, "Great Hall change whoseTurn");
  error_count += asserttrue(phase == testG.phase, "Great Hall change phase");
  error_count += asserttrue(coins == testG.coins, "Great Hall change coins");
  error_count += asserttrue(numBuys == testG.numBuys, "Great Hall change numBuys");

  if (error_count == 0)
	  printf("\t\tSuccess: Great Hall does not change irrelevant game state variables\n");
  //*********************** END OF LOGIC TO CHECK Great Hall doesnt effect other players deck **************/

  // assert cardEffect returns 0
  error_count += asserttrue(success == 0, "Call to cardEffect for Great Hall returned status failed");

  // assert handCounts matches reference
  printf("\tExpecting handCount %d and received %d\n", G.handCount[currentPlayer], testG.handCount[currentPlayer]);
  error_count += asserttrue(G.handCount[currentPlayer] == testG.handCount[currentPlayer],
      "handCount does not match reference");

  // test that 1 card were drawn
  printf("\tExpecting 1 cards to have been added to the hand, got %d\n", testG.handCount[currentPlayer]-(tempHandCount-1));
  error_count += asserttrue(testG.handCount[currentPlayer]-(tempHandCount-1) == 1,
                "Should have only drawn 1 cards");

  // keep track of whether returned hand has Great Hall
  seed = 0;
  // Check returned hand doesnt have Great Hall
  for (i = 0; i < testG.handCount[currentPlayer]; i++) {
    if (testG.hand[currentPlayer][i] == great_hall)
      seed++;
  }
  // print expected value of Great Hall card in hand
  printf("\tExpects 0 if returned hand doesnt have Great Hall card and got %d\n", seed);
  error_count += asserttrue(seed == 0, "Great Hall should not be in hand");

  printf("\tExpecting %d if numActions of returned to match reference, got %d\n", G.numActions, testG.numActions);
  asserttrue(G.numActions == testG.numActions, "numActions in returned should match reference");

  // print comparison of expected deckCount and reference and assert it is as expected
  printf("\tExpects deckCount to have been shuffled. Reference %d, Returned %d\n",
      G.deckCount[currentPlayer], testG.deckCount[currentPlayer]);
  error_count += asserttrue(G.deckCount[currentPlayer] == testG.deckCount[currentPlayer],
      "Discard should have been shuffled back into deck");

  // print comparison of expected discardCount and reference and assert it is as expected
  printf("\tExpects %d since discard should be empty after shuffle, got %d\n",
      0, testG.discardCount[currentPlayer]);
  error_count += asserttrue(0 == testG.discardCount[currentPlayer],
      "discardCount does not match reference");

  if (error_count == 0)
    printf("\n\tAll Tests Successful, Test 3 Great Hall, Player 2 empty deck, 12 cards in discard, hand has 2 silver with Great Hall on top\n\n");
  else
    printf("\n\t%d Tests Failed, Test 3 Great Hall, Player 2 empty deck, 12 cards in discard, hand has 2 silver with Great Hall on top\n\n", error_count);

  error_total += error_count;

  if (error_total == 0)
    printf("ALL TESTS SUCCESSFUL, Great Hall\n");
  else
    printf("%d TESTS FAILED, Great Hall\n", error_total);

  printf("------------------------ END Test Great Hall Card ------------------------------\n");

  return 0;
}

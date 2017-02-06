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
      k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy},
      bonus = 0;			// passed to initializeGame

  // Adventurer helper variables
  int currentPlayer = 1,	// track current player
		// track if shuffle occurred (adventurure should only shuffle once and if only 1 treasure if found abort)
      shuffle_occurred = 0, 
      drawntreasure = 0,	// increment drawn treasure
      cardDrawn,			// store card drawn into hand to check if currency
      z = 0,				// track size of temphand
      temphand[MAX_HAND],	// store non-currency cards drawn during adventurer
	  check_discard = 0,	// to test size of discard after adventurer agains size of temphand
	  count_discard_matches = 0; // used to compare reference discard pile to temphand to make sure its successful
	  
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
	  numActions, /* Starts at 1 each turn */
	  coins, /* Use as you see fit! */
	  numBuys; /* Starts at 1 each turn */
  
  printf("------------------------ Testing Adventurer Card ------------------------------\n");
  
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

//******************************* TEST 1 - Default Deck (Just Initialized) Adventurer on player 2 *********************************
  printf("Test 1 Adventurer, Player 2 default deck, 10 cards in deck, 0 in discard and hand\n");
  
  G.whoseTurn = 1;  // mark it as player 2's turn
  memcpy(&testG, &G, sizeof(struct gameState));
  
  // Store altPlayers hand to check after call to adventurer
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
  numActions = testG.numActions;
  coins  = testG.coins;
  numBuys = testG.numBuys;

  //call cardEffect for adventurer on player 2
  success = cardEffect(adventurer, -1, -1, -1, &testG, 0, &bonus);

  //******************************* APPLY ADVENTURER LOGIC TO REFERENCE STATE *********************************
  // Here we implement the logic of Adventurer
  // Draw from the deck until you have drawn 2 treasure cards. Discard all non
  // treasure cards
  check_discard = G.discardCount[currentPlayer];
  shuffle_occurred = 0;
  while(drawntreasure < 2)
  {
    if (G.deckCount[currentPlayer] < 1) //if the deck is empty we need to shuffle discard and add to deck
    {
      // if we haven't shuffled yet shuffle and set shuffled to true
      // If we dont have enough trasures after shuffling then you get only what
      // you have been able to draw
      if (shuffle_occurred == 0) {
		 shuffle_prepare(currentPlayer, &G);
        shuffle(currentPlayer, &G);
        shuffle_occurred = 1;
      }
      else {
        // shuffle cards but break because we do not have enough treasures in
        // deck or discard
		shuffle_prepare(currentPlayer, &G);
        shuffle(currentPlayer, &G);
        break;
      }

    }
    // draw a card from the deck
    drawCard(currentPlayer, &G);
    // store the card (now in hand)
    cardDrawn = G.hand[currentPlayer][G.handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
    // check if it is a currency, if so increment drawntreasure
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold )
      drawntreasure++;
    // if its not currency, add to temphand and remove from hand
    // do not add to discard as we dont want it reshuffled
    else
    {
      temphand[z]=cardDrawn;
      G.handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
      z++;
    }
  }
  // If shuffle never occurred add the number of cards in tempHand to shuffle_occurred
  if (shuffle_occurred == 0) {
    seed = check_discard; // store size of discard to offset check of tempHand cards
	check_discard += z;
  }
  // Else, discard should have been cleared and the only cards to be placed in it are from tempHand
  else {
	seed = 0; // make offset 0 because index in discard should match tempHand
	check_discard = z;
  }
  // discard everything in temphand
  while(z-1 >= 0)
  {
    G.discard[currentPlayer][G.discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
    z=z-1;
  }
  
  
  // assert that reference adventurer logic is working correctly. 
  // Does not count towards error_count for dominion.c code
  asserttrue(z == 0, "TempHand Should be 0, Check reference logic");
  asserttrue(check_discard == G.discardCount[currentPlayer], 
		"Discard count does not match drawn cards, check reference logic");
  // check that top of reference hand is drawntreasure amount of currency cards
  z = 0;
  for (i = G.handCount[currentPlayer]-1; i > G.handCount[currentPlayer]- (1 + drawntreasure); i--) {
	  if (G.hand[currentPlayer][i] >= 3 && G.hand[currentPlayer][i] <= 6)
		z++;
  }
  asserttrue(z == drawntreasure, "Reference adventurur logic drew non-currncy into hand, check reference logic");
  // walk backwards though discard and forwards through tempHand and confirm they match
  // (this is because tempHand is added to discard in revers order)
  // This makes sure that all drawn non-currency cards are added to discard.
  // Also assert that no currency cards were discarded
  z = 0;
  while (check_discard >= seed) {
	  if (G.discard[currentPlayer][check_discard-1] == temphand[z] && (temphand[z] < 4 || temphand[z] > 6))
		  count_discard_matches++;
	  z++;
	  check_discard--;
  } 
  asserttrue(count_discard_matches == z, "Cards added to discard should match non-currency cards drawn, check reference logic");
  // ********** End checking reference adventurer logic

  //*********************** LOGIC TO CHECK ADVENTURER doesnt effect other players deck or other gamestate vars **************/
  printf("\tExpecting Adventurer does not alter other players deck or irrelevent game state variables\n");
  // check altPlayers hand matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altHandCount; i++)
	  if (altHand[i] == testG.hand[alternatePlayer][i])
		  z++;
  error_count += asserttrue(z == altHandCount, "Adventurer changed another players hand");
  
  // check altPlayers deck matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altDeckCount; i++)
	  if (altDeck[i] == testG.deck[alternatePlayer][i])
		  z++;
  error_count += asserttrue(z == altDeckCount, "Adventurer changed another players deck");
  
  // check altPlayers discard matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altDiscardCount; i++)
	  if (altDiscard[i] == testG.discard[alternatePlayer][i])
		  z++;
	  
  error_count += asserttrue(z == altDiscardCount, "Adventurer changed another players discard");
  
  // check supplyCounts match copy
  z = 0;	// z used to count matches
  for (i = 0; i < treasure_map+1; i++) 
	  if (supplyCount[i] == testG.supplyCount[i])
		  z++;
  
  error_count += asserttrue(z == treasure_map+1, "Adventurer changed supplyCount");
  
  // check embargoTokens match copy
  z = 0;	// z used to count matches
  for (i = 0; i < treasure_map+1; i++) 
	  if (embargoTokens[i] == testG.embargoTokens[i])
		  z++;
	  
  error_count += asserttrue(z == treasure_map+1, "Adventurer changed embargoTokens");
  
  // Assert altHandCount, altDeckCount, and altDiscardCount match current alternate players counts
  error_count += asserttrue(testG.handCount[alternatePlayer] == altHandCount, "Adventurer changed another players handCount");
  error_count += asserttrue(testG.deckCount[alternatePlayer] == altDeckCount, "Adventurer changed another players deckCount");
  error_count += asserttrue(testG.discardCount[alternatePlayer] == altDiscardCount, "Adventurer changed another players handCount");
  // assert that other gameState variables have not changed
  error_count += asserttrue(numPlayers == testG.numPlayers, "Adventurer change numPlayers");
  error_count += asserttrue(outpostPlayed == testG.outpostPlayed, "Adventurer change outpostPlayed");
  error_count += asserttrue(outpostTurn == testG.outpostTurn, "Adventurer change outpostTurn");
  error_count += asserttrue(whoseTurn == testG.whoseTurn, "Adventurer change whoseTurn");
  error_count += asserttrue(phase == testG.phase, "Adventurer change phase");
  error_count += asserttrue(coins == testG.coins, "Adventurer change coins");
  error_count += asserttrue(numBuys == testG.numBuys, "Adventurer change numBuys");
  
  if (error_count == 0)
	  printf("\t\tSuccess: Adventurer does not change irrelevant game state variables\n");
  //*********************** END OF LOGIC TO CHECK ADVENTURER doesnt effect other players deck **************/
  
  // assert cardEffect returns 0
  error_count += asserttrue(success == 0, "Call to cardEffect for adventurer returned status failed");
  
  // assert handCounts matches reference
  printf("\tExpecting handCount %d and received %d\n", G.handCount[currentPlayer], testG.handCount[currentPlayer]);
  error_count += asserttrue(G.handCount[currentPlayer] == testG.handCount[currentPlayer], 
      "handCount does not match reference");
  
  // keep track of whether reference matches returned hand cards
  seed = 0;
  // keep track of whether returned cards in hand are currency
  copper_count = 0;
  // Check is top two cards in hand are the same as the reference and are
  // currency
  for (i = G.handCount[currentPlayer]-1; i > G.handCount[currentPlayer]-3; i--) {
    if (G.hand[currentPlayer][i] == testG.hand[currentPlayer][i])
      seed++;

    cardDrawn = testG.hand[currentPlayer][i];
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
      copper_count++;
  }
  
  // print expected result of reference comparison and assert it is as expected
  printf("\tExpects 2 if top two cards are same in reference and returned hand got%d\n", seed);
  error_count += asserttrue(seed == 2, "Top two cards in hand do not match reference");
  // print expected value of currncy cards obtained and assert it is as expected
  printf("\tExpects 2 if top two cards are currency in hand and got%d\n", copper_count);
  error_count += asserttrue(copper_count == 2, "Top two cards in hand are not currency");
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

  //******************************* TEST 2 - EMPTY DECK, 12 non-currency cards in Discard with 2 copper} ***********************
  printf("Test 2 Adventurer, Player1 deck empty, discard has 12 cards with 2 copper, 5 cards in hand\n");

  // clear adventurer variables and make currentPlayer player 1
  currentPlayer = 0;
  shuffle_occurred = 0;
  drawntreasure = 0;
  cardDrawn = -1;
  z = 0,
  check_discard = 0,
  count_discard_matches = 0;
  
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

  // add 10 non-currency cards
  for (i = 7; i < 17; i++) 
      G.discard[currentPlayer][G.discardCount[currentPlayer]++] = i;
  // add two copper
  G.discard[currentPlayer][G.discardCount[currentPlayer]++] = 4;
  G.discard[currentPlayer][G.discardCount[currentPlayer]++] = 4;
  
  // copy new player 1 state into
  memcpy(&testG, &G, sizeof(struct gameState));
  
  // Store altPlayers hand to check after call to adventurer
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
  numActions = testG.numActions;
  coins  = testG.coins;
  numBuys = testG.numBuys;
  
  //call cardEffect for adventurer on player 1
  success = cardEffect(adventurer, -1, -1, -1, &testG, 0, &bonus);

  //******************************* APPLY ADVENTURER LOGIC TO REFERENCE STATE *********************************
  // Here we implement the logic of Adventurer
  // Draw from the deck until you have drawn 2 treasure cards. Discard all non
  // treasure cards
  check_discard = G.discardCount[currentPlayer];
  shuffle_occurred = 0;
  while(drawntreasure < 2)
  {
    if (G.deckCount[currentPlayer] < 1) //if the deck is empty we need to shuffle discard and add to deck
    {
      // if we haven't shuffled yet shuffle and set shuffled to true
      // If we dont have enough trasures after shuffling then you get only what
      // you have been able to draw
      if (shuffle_occurred == 0) {
		 shuffle_prepare(currentPlayer, &G);
        shuffle(currentPlayer, &G);
        shuffle_occurred = 1;
      }
      else {
        // shuffle cards but break because we do not have enough treasures in
        // deck or discard
		shuffle_prepare(currentPlayer, &G);
        shuffle(currentPlayer, &G);
        break;
      }

    }
    // draw a card from the deck
    drawCard(currentPlayer, &G);
    // store the card (now in hand)
    cardDrawn = G.hand[currentPlayer][G.handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
    // check if it is a currency, if so increment drawntreasure
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold )
      drawntreasure++;
    // if its not currency, add to temphand and remove from hand
    // do not add to discard as we dont want it reshuffled
    else
    {
      temphand[z]=cardDrawn;
      G.handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
      z++;
    }
  }
  // If shuffle never occurred add the number of cards in tempHand to shuffle_occurred
  if (shuffle_occurred == 0) {
    seed = check_discard; // store size of discard to offset check of tempHand cards
	check_discard += z;
  }
  // Else, discard should have been cleared and the only cards to be placed in it are from tempHand
  else {
	seed = 0; // make offset 0 because index in discard should match tempHand
	check_discard = z;
  }
  // discard everything in temphand
  while(z-1 >= 0)
  {
    G.discard[currentPlayer][G.discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
    z=z-1;
  }
  
  
  // assert that reference adventurer logic is working correctly. 
  // Does not count towards error_count for dominion.c code
  asserttrue(z == 0, "TempHand Should be 0, Check reference logic");
  asserttrue(check_discard == G.discardCount[currentPlayer], 
		"Discard count does not match drawn cards, check reference logic");
  // check that top of reference hand is drawntreasure amount of currency cards
  z = 0;
  for (i = G.handCount[currentPlayer]-1; i > G.handCount[currentPlayer]- (1 + drawntreasure); i--) {
	  if (G.hand[currentPlayer][i] >= 3 && G.hand[currentPlayer][i] <= 6)
		z++;
  }
  asserttrue(z == drawntreasure, "Reference adventurur logic drew non-currncy into hand, check reference logic");
  // walk backwards though discard and forwards through tempHand and confirm they match
  // (this is because tempHand is added to discard in revers order)
  // This makes sure that all drawn non-currency cards are added to discard.
  // Also assert that no currency cards were discarded
  z = 0;
  while (check_discard >= seed) {
	  if (G.discard[currentPlayer][check_discard-1] == temphand[z] && (temphand[z] < 4 || temphand[z] > 6))
		  count_discard_matches++;
	  z++;
	  check_discard--;
  } 
  asserttrue(count_discard_matches == z, "Cards added to discard should match non-currency cards drawn, check reference logic");
  // ********** End checking reference adventurer logic
  
  //*********************** LOGIC TO CHECK ADVENTURER doesnt effect other players deck or other gamestate vars **************/
  printf("\tExpecting Adventurer does not alter other players deck or irrelevent game state variables\n");
  // check altPlayers hand matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altHandCount; i++)
	  if (altHand[i] == testG.hand[alternatePlayer][i])
		  z++;
  error_count += asserttrue(z == altHandCount, "Adventurer changed another players hand");
  
  // check altPlayers deck matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altDeckCount; i++)
	  if (altDeck[i] == testG.deck[alternatePlayer][i])
		  z++;
  error_count += asserttrue(z == altDeckCount, "Adventurer changed another players deck");
  
  // check altPlayers discard matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altDiscardCount; i++)
	  if (altDiscard[i] == testG.discard[alternatePlayer][i])
		  z++;
	  
  error_count += asserttrue(z == altDiscardCount, "Adventurer changed another players discard");
  
  // check supplyCounts match copy
  z = 0;	// z used to count matches
  for (i = 0; i < treasure_map+1; i++) 
	  if (supplyCount[i] == testG.supplyCount[i])
		  z++;
  
  error_count += asserttrue(z == treasure_map+1, "Adventurer changed supplyCount");
  
  // check embargoTokens match copy
  z = 0;	// z used to count matches
  for (i = 0; i < treasure_map+1; i++) 
	  if (embargoTokens[i] == testG.embargoTokens[i])
		  z++;
	  
    
  error_count += asserttrue(z == treasure_map+1, "Adventurer changed embargoTokens");
  
  // Assert altHandCount, altDeckCount, and altDiscardCount match current alternate players counts
  error_count += asserttrue(testG.handCount[alternatePlayer] == altHandCount, "Adventurer changed another players handCount");
  error_count += asserttrue(testG.deckCount[alternatePlayer] == altDeckCount, "Adventurer changed another players deckCount");
  error_count += asserttrue(testG.discardCount[alternatePlayer] == altDiscardCount, "Adventurer changed another players handCount");
  // assert that other gameState variables have not changed
  error_count += asserttrue(numPlayers == testG.numPlayers, "Adventurer change numPlayers");
  error_count += asserttrue(outpostPlayed == testG.outpostPlayed, "Adventurer change outpostPlayed");
  error_count += asserttrue(outpostTurn == testG.outpostTurn, "Adventurer change outpostTurn");
  error_count += asserttrue(whoseTurn == testG.whoseTurn, "Adventurer change whoseTurn");
  error_count += asserttrue(phase == testG.phase, "Adventurer change phase");
  error_count += asserttrue(coins == testG.coins, "Adventurer change coins");
  error_count += asserttrue(numBuys == testG.numBuys, "Adventurer change numBuys");
  
  if (error_count == 0)
	  printf("\t\tSuccess: Adventurer does not change irrelevant game state variables\n");
  //*********************** END OF LOGIC TO CHECK ADVENTURER doesnt effect other players deck **************/

   // assert cardEffect returns 0
  error_count += asserttrue(success == 0, "Call to cardEffect for adventurer returned status failed");
  // assert handCounts matches reference
  printf("\tExpecting handCount %d and received %d\n", G.handCount[currentPlayer], testG.handCount[currentPlayer]);
  error_count += asserttrue(G.handCount[currentPlayer] == testG.handCount[currentPlayer], 
      "handCount does not match reference");
  
  // keep track of whether reference matches returned hand cards
  seed = 0;
  // keep track of whether returned cards in hand are currency
  copper_count = 0;
  // Check is top two cards in hand are the same as the reference and are
  // currency
  for (i = G.handCount[currentPlayer]-1; i > G.handCount[currentPlayer]-3; i--) {
    if (G.hand[currentPlayer][i] == testG.hand[currentPlayer][i])
      seed++;

    cardDrawn = testG.hand[currentPlayer][i];
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
      copper_count++;
  }
  
  // print expected result of reference comparison and assert it is as expected
  printf("\tExpects 2 if top two cards are same in reference and returned hand got %d\n", seed);
  error_count += asserttrue(seed == 2, "Top two cards in hand do not match reference");
  // print expected value of currncy cards obtained and assert it is as expected
  printf("\tExpects 2 if top two cards are currency in returned hand and got %d\n", copper_count);
  error_count += asserttrue(copper_count == 2, "Top two cards in hand are not currency");
  // print comparison of expected discardCount and reference and assert it is as expected
  printf("\tExpects discardCount and deckCount sum to be %d got  %d\n", 
      G.discardCount[currentPlayer] + G.deckCount[currentPlayer], 
      testG.discardCount[currentPlayer] + testG.deckCount[currentPlayer]);
  error_count += asserttrue(G.discardCount[currentPlayer] + G.deckCount[currentPlayer] == 
      testG.discardCount[currentPlayer] + testG.deckCount[currentPlayer],
      "Two copper should have been placed in hand, sum of discard and deck counts should be equal");

  if (error_count == 0)
    printf("\n\tAll Tests Successful, Player 1 deck empty discard full, contains 2 copper\n\n");
  else
    printf("\n\t%d Tests Failed, Player 1 deck empty discard full, contains 2 copper\n\n", error_count);
  
  error_total += error_count;
  error_count = 0;

	//******************************* TEST 3 - Player2 10 cards in discard with 1 silver, 5 non-currency in deck, 0 in hand ***********************
  printf("Test 3 Adventurer, Player2 10 cards in discard with 1 silver, 5 non-currency in deck, 0 in hand\n");

  // clear adventurer variables and make currentPlayer player 2
  currentPlayer = 1;
  shuffle_occurred = 0;
  drawntreasure = 0;
  cardDrawn = -1;
  z = 0,
  check_discard = 0,
  count_discard_matches = 0;
  
  // clear altPlayer variables
  alternatePlayer = 0;
  altHandCount = 0;
  altDeckCount = 0;
  altDiscardCount = 0;
  
  // make it player 2's turn
  G.whoseTurn = 1;
  // empty player 2 deck and fill discard with two copper
  G.deckCount[currentPlayer] = 0;
  G.discardCount[currentPlayer] = 0;
  G.handCount[currentPlayer] = 0;

  // add 10 non-currency cards
  for (i = 7; i < 17; i++) 
      G.discard[currentPlayer][G.discardCount[currentPlayer]++] = i;
  // add one silver
  G.discard[currentPlayer][G.discardCount[currentPlayer]++] = 5;
  // add 5 non-currency cards to deck
  for (i = 20; i < 25; i++)
    G.deck[currentPlayer][G.deckCount[currentPlayer]++] = i;

  // copy new player 2 state into
  memcpy(&testG, &G, sizeof(struct gameState));
  
  // Store altPlayers hand to check after call to adventurer
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
  numActions = testG.numActions;
  coins  = testG.coins;
  numBuys = testG.numBuys;
  
  //call cardEffect for adventurer on player 1
  success = cardEffect(adventurer, -1, -1, -1, &testG, 0, &bonus);

  //******************************* APPLY ADVENTURER LOGIC TO REFERENCE STATE *********************************
  // Here we implement the logic of Adventurer
  // Draw from the deck until you have drawn 2 treasure cards. Discard all non
  // treasure cards
  check_discard = G.discardCount[currentPlayer];
  shuffle_occurred = 0;
  while(drawntreasure < 2)
  {
    if (G.deckCount[currentPlayer] < 1) //if the deck is empty we need to shuffle discard and add to deck
    {
      // if we haven't shuffled yet shuffle and set shuffled to true
      // If we dont have enough trasures after shuffling then you get only what
      // you have been able to draw
      if (shuffle_occurred == 0) {
		 shuffle_prepare(currentPlayer, &G);
        shuffle(currentPlayer, &G);
        shuffle_occurred = 1;
      }
      else {
        // shuffle cards but break because we do not have enough treasures in
        // deck or discard
		shuffle_prepare(currentPlayer, &G);
        shuffle(currentPlayer, &G);
        break;
      }

    }
    // draw a card from the deck
    drawCard(currentPlayer, &G);
    // store the card (now in hand)
    cardDrawn = G.hand[currentPlayer][G.handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
    // check if it is a currency, if so increment drawntreasure
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold )
      drawntreasure++;
    // if its not currency, add to temphand and remove from hand
    // do not add to discard as we dont want it reshuffled
    else
    {
      temphand[z]=cardDrawn;
      G.handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
      z++;
    }
  }
  // If shuffle never occurred add the number of cards in tempHand to shuffle_occurred
  if (shuffle_occurred == 0) {
    seed = check_discard; // store size of discard to offset check of tempHand cards
	check_discard += z;
  }
  // Else, discard should have been cleared and the only cards to be placed in it are from tempHand
  else {
	seed = 0; // make offset 0 because index in discard should match tempHand
	check_discard = z;
  }
  // discard everything in temphand
  while(z-1 >= 0)
  {
    G.discard[currentPlayer][G.discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
    z=z-1;
  }
  
  
  // assert that reference adventurer logic is working correctly. 
  // Does not count towards error_count for dominion.c code
  asserttrue(z == 0, "TempHand Should be 0, Check reference logic");
  asserttrue(check_discard == G.discardCount[currentPlayer], 
		"Discard count does not match drawn cards, check reference logic");
  // check that top of reference hand is drawntreasure amount of currency cards
  z = 0;
  for (i = G.handCount[currentPlayer]-1; i > G.handCount[currentPlayer]- (1 + drawntreasure); i--) {
	  if (G.hand[currentPlayer][i] >= 3 && G.hand[currentPlayer][i] <= 6)
		z++;
  }
  asserttrue(z == drawntreasure, "Reference adventurur logic drew non-currncy into hand, check reference logic");
  // walk backwards though discard and forwards through tempHand and confirm they match
  // (this is because tempHand is added to discard in revers order)
  // This makes sure that all drawn non-currency cards are added to discard.
  // Also assert that no currency cards were discarded
  z = 0;
  while (check_discard >= seed) {
	  if (G.discard[currentPlayer][check_discard-1] == temphand[z] && (temphand[z] < 4 || temphand[z] > 6))
		  count_discard_matches++;
	  z++;
	  check_discard--;
  } 
  asserttrue(count_discard_matches == z, "Cards added to discard should match non-currency cards drawn, check reference logic");
  // ********** End checking reference adventurer logic
  
  //*********************** LOGIC TO CHECK ADVENTURER doesnt effect other players deck or other gamestate vars **************/
  printf("\tExpecting Adventurer does not alter other players deck or irrelevent game state variables\n");
  // check altPlayers hand matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altHandCount; i++)
	  if (altHand[i] == testG.hand[alternatePlayer][i])
		  z++;
  error_count += asserttrue(z == altHandCount, "Adventurer changed another players hand");
  
  // check altPlayers deck matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altDeckCount; i++)
	  if (altDeck[i] == testG.deck[alternatePlayer][i])
		  z++;
  error_count += asserttrue(z == altDeckCount, "Adventurer changed another players deck");
  
  // check altPlayers discard matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altDiscardCount; i++)
	  if (altDiscard[i] == testG.discard[alternatePlayer][i])
		  z++;
	  
  error_count += asserttrue(z == altDiscardCount, "Adventurer changed another players discard");
  
  // check supplyCounts match copy
  z = 0;	// z used to count matches
  for (i = 0; i < treasure_map+1; i++) 
	  if (supplyCount[i] == testG.supplyCount[i])
		  z++;
  
  error_count += asserttrue(z == treasure_map+1, "Adventurer changed supplyCount");
  
  // check embargoTokens match copy
  z = 0;	// z used to count matches
  for (i = 0; i < treasure_map+1; i++) 
	  if (embargoTokens[i] == testG.embargoTokens[i])
		  z++;
	  
    
  error_count += asserttrue(z == treasure_map+1, "Adventurer changed embargoTokens");
  
  // Assert altHandCount, altDeckCount, and altDiscardCount match current alternate players counts
  error_count += asserttrue(testG.handCount[alternatePlayer] == altHandCount, "Adventurer changed another players handCount");
  error_count += asserttrue(testG.deckCount[alternatePlayer] == altDeckCount, "Adventurer changed another players deckCount");
  error_count += asserttrue(testG.discardCount[alternatePlayer] == altDiscardCount, "Adventurer changed another players handCount");
  // assert that other gameState variables have not changed
  error_count += asserttrue(numPlayers == testG.numPlayers, "Adventurer change numPlayers");
  error_count += asserttrue(outpostPlayed == testG.outpostPlayed, "Adventurer change outpostPlayed");
  error_count += asserttrue(outpostTurn == testG.outpostTurn, "Adventurer change outpostTurn");
  error_count += asserttrue(whoseTurn == testG.whoseTurn, "Adventurer change whoseTurn");
  error_count += asserttrue(phase == testG.phase, "Adventurer change phase");
  error_count += asserttrue(coins == testG.coins, "Adventurer change coins");
  error_count += asserttrue(numBuys == testG.numBuys, "Adventurer change numBuys");
  
  if (error_count == 0)
	  printf("\t\tSuccess: Adventurer does not change irrelevant game state variables\n");
  //*********************** END OF LOGIC TO CHECK ADVENTURER doesnt effect other players deck **************/

   // assert cardEffect returns 0
  error_count += asserttrue(success == 0, "Call to cardEffect for adventurer returned status failed");
  // assert handCounts matches reference
  printf("\tExpecting handCount %d and received %d\n", G.handCount[currentPlayer], testG.handCount[currentPlayer]);
  error_count += asserttrue(G.handCount[currentPlayer] == testG.handCount[currentPlayer], 
      "handCount does not match reference");
  
  // keep track of whether reference matches returned hand cards
  seed = 0;
  // keep track of whether returned cards in hand are currency
  copper_count = 0;
  // Check if top  cards in hand are the same as the reference and are
  // currency
  for (i = 0; i < testG.handCount[currentPlayer]; i++) {
    if (G.hand[currentPlayer][i] == testG.hand[currentPlayer][i])
      seed++;

    cardDrawn = testG.hand[currentPlayer][i];
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
      copper_count++;
  }
  
  // print expected result of reference comparison and assert it is as expected
  printf("\tExpects 1 if top cards are same in reference and returned hand got %d\n", seed);
  error_count += asserttrue(seed == 1, "top cards in hand do not match reference");
  // print expected value of currncy cards obtained and assert it is as expected
  printf("\tExpects 1 if top cards are currency in returned hand and got %d\n", copper_count);
  error_count += asserttrue(copper_count == 1, "Top two cards in hand are not currency");
  // print comparison of expected discardCount and reference and assert it is as expected
  printf("\tExpects discardCount and deckCount sum to be %d got  %d\n", 
      G.discardCount[currentPlayer] + G.deckCount[currentPlayer], 
      testG.discardCount[currentPlayer] + testG.deckCount[currentPlayer]);
  error_count += asserttrue(G.discardCount[currentPlayer] + G.deckCount[currentPlayer] == 
      testG.discardCount[currentPlayer] + testG.deckCount[currentPlayer],
      "Two copper should have been placed in hand, sum of discard and deck counts should be equal");

  if (error_count == 0)
    printf("\n\tAll Tests Successful,  Player2 only 1 currency (silver) in discard, none in deck\n\n");
  else
    printf("\n\t%d Tests Failed, Player2 only 1 currency (silver) in discard, none in deck\n\n", error_count);
  
  error_total += error_count;
  error_count = 0;
  
  
  //******************************* TEST 4 - EMPTY Discard, 12 non-currency cards in Deck with 2 gold} ***********************
  printf("Test 4 Adventurer, Player1 empty discard, 5 non-currency in hand, and 12 cards in deck with 2 gold at bottom\n");

  // clear adventurer variables and make currentPlayer player 1
  currentPlayer = 0;
  shuffle_occurred = 0;
  drawntreasure = 0;
  cardDrawn = -1;
  z = 0,
  check_discard = 0,
  count_discard_matches = 0;
  
  // clear altPlayer variables
  alternatePlayer = 1;
  altHandCount = 0;
  altDeckCount = 0;
  altDiscardCount = 0;
	  
	  
  // make it player 1's turn
  G.whoseTurn = 0;
  // empty player 1 discard and fill deck with 10 non currency and two gold
  G.deckCount[currentPlayer] = 0;
  G.discardCount[currentPlayer] = 0;
  // add 5 non-currency to hand
  for (i = 0; i < 5; i++)
	  G.hand[currentPlayer][i] = i+10; // add non-currency cards
  G.handCount[currentPlayer] = i;
  
  // add two gold to deck
  G.deck[currentPlayer][G.deckCount[currentPlayer]++] = 6;
  G.deck[currentPlayer][G.deckCount[currentPlayer]++] = 6;
  // add 10 non-currency cards
  for (i = 7; i < 17; i++) 
      G.deck[currentPlayer][G.deckCount[currentPlayer]++] = i;
  
  
  // copy new player 1 state into
  memcpy(&testG, &G, sizeof(struct gameState));
  
  // Store altPlayers hand to check after call to adventurer
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
  numActions = testG.numActions;
  coins  = testG.coins;
  numBuys = testG.numBuys;
  
  //call cardEffect for adventurer on player 1
  success = cardEffect(adventurer, -1, -1, -1, &testG, 0, &bonus);

  //******************************* APPLY ADVENTURER LOGIC TO REFERENCE STATE *********************************
  // Here we implement the logic of Adventurer
  // Draw from the deck until you have drawn 2 treasure cards. Discard all non
  // treasure cards
  check_discard = G.discardCount[currentPlayer];
  shuffle_occurred = 0;
  while(drawntreasure < 2)
  {
    if (G.deckCount[currentPlayer] < 1) //if the deck is empty we need to shuffle discard and add to deck
    {
      // if we haven't shuffled yet shuffle and set shuffled to true
      // If we dont have enough trasures after shuffling then you get only what
      // you have been able to draw
      if (shuffle_occurred == 0) {
		shuffle_prepare(currentPlayer, &G);
        shuffle(currentPlayer, &G);
        shuffle_occurred = 1;
      }
      else {
        // shuffle cards but break because we do not have enough treasures in
        // deck or discard
		shuffle_prepare(currentPlayer, &G);
        shuffle(currentPlayer, &G);
        break;
      }

    }
    // draw a card from the deck
    drawCard(currentPlayer, &G);
    // store the card (now in hand)
    cardDrawn = G.hand[currentPlayer][G.handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
    // check if it is a currency, if so increment drawntreasure
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold )
      drawntreasure++;
    // if its not currency, add to temphand and remove from hand
    // do not add to discard as we dont want it reshuffled
    else
    {
      temphand[z]=cardDrawn;
      G.handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
      z++;
    }
  }
  // If shuffle never occurred add the number of cards in tempHand to shuffle_occurred
  if (shuffle_occurred == 0) {
    seed = check_discard; // store size of discard to offset check of tempHand cards
	check_discard += z;
  }
  // Else, discard should have been cleared and the only cards to be placed in it are from tempHand
  else {
	seed = 0; // make offset 0 because index in discard should match tempHand
	check_discard = z;
  }
  // discard everything in temphand
  while(z-1 >= 0)
  {
    G.discard[currentPlayer][G.discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
    z=z-1;
  }
  
  
  // assert that reference adventurer logic is working correctly. 
  // Does not count towards error_count for dominion.c code
  asserttrue(z == 0, "TempHand Should be 0, Check reference logic");
  asserttrue(check_discard == G.discardCount[currentPlayer], 
		"Discard count does not match drawn cards, check reference logic");
  // check that top of reference hand is drawntreasure amount of currency cards
  z = 0;
  for (i = G.handCount[currentPlayer]-1; i > G.handCount[currentPlayer]- (1 + drawntreasure); i--) {
	  if (G.hand[currentPlayer][i] >= 3 && G.hand[currentPlayer][i] <= 6)
		z++;
  }
  asserttrue(z == drawntreasure, "Reference adventurur logic drew non-currncy into hand, check reference logic");
  // walk backwards though discard and forwards through tempHand and confirm they match
  // (this is because tempHand is added to discard in revers order)
  // This makes sure that all drawn non-currency cards are added to discard.
  // Also assert that no currency cards were discarded
  z = 0;
  while (check_discard > seed) {
	  if (G.discard[currentPlayer][check_discard-1] == temphand[z] && (temphand[z] < 4 || temphand[z] > 6))
		  count_discard_matches++;
	  z++;
	  check_discard--;
  } 
  asserttrue(count_discard_matches == z, "Cards added to discard should match non-currency cards drawn, check reference logic");
  // ********** End checking reference adventurer logic
  
  //*********************** LOGIC TO CHECK ADVENTURER doesnt effect other players deck or other gamestate vars **************/
  printf("\tExpecting Adventurer does not alter other players deck or irrelevent game state variables\n");
  // check altPlayers hand matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altHandCount; i++)
	  if (altHand[i] == testG.hand[alternatePlayer][i])
		  z++;
  error_count += asserttrue(z == altHandCount, "Adventurer changed another players hand");
  
  // check altPlayers deck matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altDeckCount; i++)
	  if (altDeck[i] == testG.deck[alternatePlayer][i])
		  z++;
  error_count += asserttrue(z == altDeckCount, "Adventurer changed another players deck");
  
  // check altPlayers discard matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altDiscardCount; i++)
	  if (altDiscard[i] == testG.discard[alternatePlayer][i])
		  z++;
	  
  error_count += asserttrue(z == altDiscardCount, "Adventurer changed another players discard");
  
  // check supplyCounts match copy
  z = 0;	// z used to count matches
  for (i = 0; i < treasure_map+1; i++) 
	  if (supplyCount[i] == testG.supplyCount[i])
		  z++;
  
  error_count += asserttrue(z == treasure_map+1, "Adventurer changed supplyCount");
  
  // check embargoTokens match copy
  z = 0;	// z used to count matches
  for (i = 0; i < treasure_map+1; i++) 
	  if (embargoTokens[i] == testG.embargoTokens[i])
		  z++;
	  
    
  error_count += asserttrue(z == treasure_map+1, "Adventurer changed embargoTokens");
  
  // Assert altHandCount, altDeckCount, and altDiscardCount match current alternate players counts
  error_count += asserttrue(testG.handCount[alternatePlayer] == altHandCount, "Adventurer changed another players handCount");
  error_count += asserttrue(testG.deckCount[alternatePlayer] == altDeckCount, "Adventurer changed another players deckCount");
  error_count += asserttrue(testG.discardCount[alternatePlayer] == altDiscardCount, "Adventurer changed another players handCount");
  // assert that other gameState variables have not changed
  error_count += asserttrue(numPlayers == testG.numPlayers, "Adventurer change numPlayers");
  error_count += asserttrue(outpostPlayed == testG.outpostPlayed, "Adventurer change outpostPlayed");
  error_count += asserttrue(outpostTurn == testG.outpostTurn, "Adventurer change outpostTurn");
  error_count += asserttrue(whoseTurn == testG.whoseTurn, "Adventurer change whoseTurn");
  error_count += asserttrue(phase == testG.phase, "Adventurer change phase");
  error_count += asserttrue(coins == testG.coins, "Adventurer change coins");
  error_count += asserttrue(numBuys == testG.numBuys, "Adventurer change numBuys");
  
  if (error_count == 0)
	  printf("\t\tSuccess: Adventurer does not change irrelevant game state variables\n");
  //*********************** END OF LOGIC TO CHECK ADVENTURER doesnt effect other players deck **************/

   // assert cardEffect returns 0
  error_count += asserttrue(success == 0, "Call to cardEffect for adventurer returned status failed");
  // assert handCounts matches reference
  printf("\tExpecting handCount %d and received %d\n", G.handCount[currentPlayer], testG.handCount[currentPlayer]);
  error_count += asserttrue(G.handCount[currentPlayer] == testG.handCount[currentPlayer], 
      "handCount does not match reference");
  
  // keep track of whether reference matches returned hand cards
  seed = 0;
  // keep track of whether returned cards in hand are currency
  copper_count = 0;
  // Check is top two cards in hand are the same as the reference and are
  // currency
  for (i = G.handCount[currentPlayer]-1; i > G.handCount[currentPlayer]-3; i--) {
    if (G.hand[currentPlayer][i] == testG.hand[currentPlayer][i])
      seed++;

    cardDrawn = testG.hand[currentPlayer][i];
    if (cardDrawn == gold)
      copper_count++;
  }
  
  // print expected result of reference comparison and assert it is as expected
  printf("\tExpects 2 if top two cards are same in reference and returned hand got %d\n", seed);
  error_count += asserttrue(seed == 2, "Top two cards in hand do not match reference");
  // print expected value of currncy cards obtained and assert it is as expected
  printf("\tExpects 2 if top two cards are currency in returned hand and got %d\n", copper_count);
  error_count += asserttrue(copper_count == 2, "Top two cards in hand are not currency");
  // print comparison of expected discardCount and reference and assert it is as expected
  printf("\tExpects discardCount to be %d got  %d\n", 
      G.discardCount[currentPlayer], testG.discardCount[currentPlayer]);
  error_count += asserttrue(G.discardCount[currentPlayer] == testG.discardCount[currentPlayer],
      "Returned discardCount should match reference discardCount");
	  
  printf("\tExpects deckCount to be %d got %d\n", 
      G.deckCount[currentPlayer], testG.deckCount[currentPlayer]);
  error_count += asserttrue(G.deckCount[currentPlayer] == testG.deckCount[currentPlayer],
      "Returned deckCount should match reference deckCount");
	  

  if (error_count == 0)
    printf("\n\tAll Tests Successful, Player1 empty discard, 5 non-currency in hand, and 12 cards in deck with 2 gold at bottom\n\n");
  else
    printf("\n\t%d Tests Failed, Player1 empty discard, 5 non-currency in hand, and 12 cards in deck with 2 gold at bottom\n\n", error_count);
  
  error_total += error_count;
  error_count = 0;


  error_total += error_count;

  if (error_total == 0)
    printf("ALL TESTS SUCCESSFUL, Adventurer\n");
  else
    printf("%d TESTS FAILED, Adventurer\n", error_total);

  printf("------------------------ END Test Adventurer Card ------------------------------\n");
  
  return 0; 
}



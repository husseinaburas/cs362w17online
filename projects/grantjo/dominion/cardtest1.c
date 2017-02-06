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
  struct gameState G,
                   testG;
  int i = 0,
      success = 1, 
      error_count = 0,
      error_total = 0,
      copper_count = 0,
      estate_count = 0, 
      seed = 0,
      k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy},
      bonus = 0;

  // Adventurer helper variables
  int currentPlayer = 1,
      shuffle_occurred = 0,
      drawntreasure = 0,
      cardDrawn,
      z = 0,
      temphand[MAX_HAND];

  
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


  printf("Testing Adventurer, Player 2 default deck\n");
  
  G.whoseTurn = 1;  // mark it as player 2's turn
  memcpy(&testG, &G, sizeof(struct gameState));

  //call cardEffect for adventurer on player 2
  success = cardEffect(adventurer, -1, -1, -1, &testG, 0, &bonus);

  // Here we implement the logic of Adventurer
  // Draw from the deck until you have drawn 2 treasure cards. Discard all non
  // treasure cards
  shuffle_occurred = 0;
  while(drawntreasure < 2)
  {
    if (G.deckCount[currentPlayer] < 1) //if the deck is empty we need to shuffle discard and add to deck
    {
      // if we haven't shuffled yet shuffle and set shuffled to true
      // If we dont have enough trasures after shuffling then you get only what
      // you have been able to draw
      if (shuffle_occurred == 0) {
        shuffle(currentPlayer, &G);
        shuffle_occurred = 1;
      }
      else {
        // shuffle cards but break because we do not have enough treasures in
        // deck or discard
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
  // discard everything in temphand
  while(z-1 >= 0)
  {
    G.discard[currentPlayer][G.discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
    z=z-1;
  }


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
  printf("\tExcpects %d if reference discardCount matches returned got %d\n", 
      G.discardCount[currentPlayer], testG.discardCount[currentPlayer]);
  error_count += asserttrue(G.discardCount[currentPlayer] == testG.discardCount[currentPlayer],
      "discardCount does not match reference");

  if (error_count == 0)
    printf("\n\tAll Tests Successful, Player 2 default deck\n\n");
  else
    printf("\n\t%d Tests Failed, Player 2 default deck\n\n", error_count);
  
  error_total += error_count;
  error_count = 0;

  printf("Testing Adventurer, Player1 deck empty discard full, contains 2 copper\n");

  // clear adventurer variables and make currentPlayer player 1
  currentPlayer = 0;
  shuffle_occurred = 0;
  drawntreasure = 0;
  cardDrawn = -1;
  z = 0;
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
  
  //call cardEffect for adventurer on player 1
  success = cardEffect(adventurer, -1, -1, -1, &testG, 0, &bonus);

  // Here we implement the logic of Adventurer
  // Draw from the deck until you have drawn 2 treasure cards. Discard all non
  // treasure cards
  shuffle_occurred = 0;
  while(drawntreasure < 2)
  {
    if (G.deckCount[currentPlayer] < 1) //if the deck is empty we need to shuffle discard and add to deck
    {
      // if we haven't shuffled yet shuffle and set shuffled to true
      // If we dont have enough trasures after shuffling then you get only what
      // you have been able to draw
      if (shuffle_occurred == 0) {
        shuffle(currentPlayer, &G);
        shuffle_occurred = 1;
      }
      else {
        // shuffle cards but break because we do not have enough treasures in
        // deck or discard
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
  // discard everything in temphand
  while(z-1 >= 0)
  {
    G.discard[currentPlayer][G.discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
    z=z-1;
  }

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


  printf("Testing Adventurer, Player2 only 1 currency (silver) in discard, none in deck\n");

  // clear adventurer variables and make currentPlayer player 2
  currentPlayer = 1;
  shuffle_occurred = 0;
  drawntreasure = 0;
  cardDrawn = -1;
  z = 0;
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
  
  //call cardEffect for adventurer on player 1
  success = cardEffect(adventurer, -1, -1, -1, &testG, 0, &bonus);

  // Here we implement the logic of Adventurer
  // Draw from the deck until you have drawn 2 treasure cards. Discard all non
  // treasure cards
  shuffle_occurred = 0;
  while(drawntreasure < 2)
  {
    if (G.deckCount[currentPlayer] < 1) //if the deck is empty we need to shuffle discard and add to deck
    {
      // if we haven't shuffled yet shuffle and set shuffled to true
      // If we dont have enough trasures after shuffling then you get only what
      // you have been able to draw
      if (shuffle_occurred == 0) {
        shuffle(currentPlayer, &G);
        shuffle_occurred = 1;
      }
      else {
        // shuffle cards but break because we do not have enough treasures in
        // deck or discard
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
  // discard everything in temphand
  while(z-1 >= 0)
  {
    G.discard[currentPlayer][G.discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
    z=z-1;
  }

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


  error_total += error_count;

  if (error_total == 0)
    printf("ALL TESTS SUCCESSFUL, Adventurer\n");
  else
    printf("%d TESTS FAILED, Adventurer\n", error_total);

  printf("------------------------ END Test Adventurer Card ------------------------------\n");
  
  return 0; 
}



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int asserttrue(int condition, char* message)
{
  if (!condition) {
    printf("\tError: %s\n", message);
    return 1;
  }

  return 0;
}


int main(int argc, char** argv) 
{
  // Unit Test for drawCard
  // Test Suite:
  // 1) Draw Card From Non-empty deck
  // 2) 
  struct gameState G,
				   testG;
  int i = 0,
      counter = 0,
      deckCount,
      handCount,
      deckTop,
      handTop,
      success = 1, 
      error_count = 0,
      error_total = 0, 
      seed = 0,
      tempDeck[MAX_DECK],
      k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	  
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
	  numBuys,/* Starts at 1 each turn */
	  z = 0; // counter for tests

  seed = 1 + rand() % 10;
  // BEGIN INITIALIZATION TEST to gameState is correct
  printf("------------------------ Test drawCard Function ----------------------\n");
  // Make sure initialize game returns success, if not exit
  success = initializeGame(2, k, seed, &G);
  asserttrue(success == 0, "Failed to Initialize Game");
  if ( success == -1 ) return 1; 

  printf("Testing call to drawCard with nonempty deck\n");
  // Add a card that would not typically be in starting deck to top of player
  // 1 deck and post-increment deckCount
  G.deck[0][G.deckCount[0]++] = sea_hag;

  // Store values for handCount, deckCount, top of hand, and top of deck card
  deckCount = G.deckCount[0];
  handCount = G.handCount[0];
  deckTop = G.deck[0][G.deckCount[0]-1];
  handTop = G.hand[0][G.handCount[0]-1];
  
  alternatePlayer = 1;
  // Store altPlayers hand to check after call to adventurer
  memcpy(&altDeck, &G.deck[alternatePlayer], MAX_DECK * sizeof(int));
  memcpy(&altDiscard, &G.discard[alternatePlayer], MAX_DECK * sizeof(int));
  memcpy(&altHand, &G.hand[alternatePlayer], MAX_HAND * sizeof(int));
  //memcpy(&supplyCount, &G.supplyCount, treasure_map+1 * sizeof(int));
  for (i = 0; i < treasure_map+1; i++)
	  supplyCount[i] = G.supplyCount[i];
  memcpy(&embargoTokens, &G.embargoTokens, treasure_map+1 * sizeof(int));
  altDeckCount = G.deckCount[alternatePlayer];
  altHandCount = G.handCount[alternatePlayer];
  altDiscardCount = G.discardCount[alternatePlayer];
  numPlayers = G.numPlayers;
  outpostPlayed = G.outpostPlayed;
  outpostTurn = G.outpostTurn;
  whoseTurn = G.whoseTurn;
  phase = G.phase;
  numActions = G.numActions;
  coins  = G.coins;
  numBuys = G.numBuys;
  
  // call drawCard
  success = drawCard(0, &G);
  
  //*********************** LOGIC TO CHECK drawCard doesnt effect other players deck or other gamestate vars **************/
  printf("\tExpecting drawCard does not alter other players deck or irrelevent game state variables\n");
  // check altPlayers hand matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altHandCount; i++)
	  if (altHand[i] == G.hand[alternatePlayer][i])
		  z++;
  error_count += asserttrue(z == altHandCount, "drawCard changed another players hand");

  // check altPlayers deck matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altDeckCount; i++)
	  if (altDeck[i] == G.deck[alternatePlayer][i])
		  z++;
  error_count += asserttrue(z == altDeckCount, "drawCard changed another players deck");

  // check altPlayers discard matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altDiscardCount; i++)
	  if (altDiscard[i] == G.discard[alternatePlayer][i])
		  z++;

  error_count += asserttrue(z == altDiscardCount, "drawCard changed another players discard");

  // check supplyCounts match copy
  z = 0;	// z used to count matches
  for (i = 0; i < treasure_map+1; i++)
	  if (supplyCount[i] == G.supplyCount[i])
		  z++;

  error_count += asserttrue(z == treasure_map+1, "drawCard changed supplyCount");

  // check embargoTokens match copy
  z = 0;	// z used to count matches
  for (i = 0; i < treasure_map+1; i++)
	  if (embargoTokens[i] == G.embargoTokens[i])
		  z++;

  error_count += asserttrue(z == treasure_map+1, "drawCard changed embargoTokens");

  // Assert altHandCount, altDeckCount, and altDiscardCount match current alternate players counts
  error_count += asserttrue(G.handCount[alternatePlayer] == altHandCount, "drawCard changed another players handCount");
  error_count += asserttrue(G.deckCount[alternatePlayer] == altDeckCount, "drawCard changed another players deckCount");
  error_count += asserttrue(G.discardCount[alternatePlayer] == altDiscardCount, "drawCard changed another players handCount");
  // assert that other gameState variables have not changed
  error_count += asserttrue(numPlayers == G.numPlayers, "drawCard change numPlayers");
  error_count += asserttrue(outpostPlayed == G.outpostPlayed, "drawCard change outpostPlayed");
  error_count += asserttrue(outpostTurn == G.outpostTurn, "drawCard change outpostTurn");
  error_count += asserttrue(whoseTurn == G.whoseTurn, "drawCard change whoseTurn");
  error_count += asserttrue(phase == G.phase, "drawCard change phase");
  error_count += asserttrue(coins == G.coins, "drawCard change coins");
  error_count += asserttrue(numBuys == G.numBuys, "drawCard change numBuys");
  error_count += asserttrue(numActions == G.numActions, "drawCard change numActions");

  if (error_count == 0)
	  printf("\t\tSuccess: drawCard does not change irrelevant game state variables\n");
  //*********************** END OF LOGIC TO CHECK DrawCard doesnt effect other players deck **************/

  // assert that handCount is incremented, deckCount decremented, and top of
  // deck added to hand
  error_count += asserttrue(deckCount-1 == G.deckCount[0], "deckCount not decremented");
  error_count += asserttrue(handCount+1 == G.handCount[0], "handCount not incremented");
  error_count += asserttrue(deckTop == G.hand[0][G.handCount[0]-1], "Top of player1 hand is not sea hag");
  error_count += asserttrue(handTop != G.hand[0][G.handCount[0]-1], "Top of player1 hand unchanged");

  if (error_count == 0)
    printf("\tAll 20 Tests Completed Successfully: Card Draw (deck not empty)\n\n");
  else
    printf("\t%d Tests failed: Card Draw (deck not empty)\n\n)", error_count);
  
  G.deckCount[1] = 0;
  G.discardCount[1] = 0;
  // Fill Player 1 discard with different cards
  for (i = 0; i < 10; i++) {
    G.discard[1][G.discardCount[1]++] = i;
  }
  //copy discard pile into tempDeck hand and store size of discard in deckCount
  //the discard pile should be shuffled into deck after call to drawCard
  memcpy(&tempDeck, &G.discard[1], sizeof(int)*MAX_DECK); 
  deckCount = G.discardCount[1];
  
  // save error_total and clear error_count
  error_total += error_count;
  error_count = 0;

  printf("Testing call to drawCard with empty deck\n");
  
  alternatePlayer = 0;
  // Store altPlayers hand to check after call to adventurer
  memcpy(&altDeck, &G.deck[alternatePlayer], MAX_DECK * sizeof(int));
  memcpy(&altDiscard, &G.discard[alternatePlayer], MAX_DECK * sizeof(int));
  memcpy(&altHand, &G.hand[alternatePlayer], MAX_HAND * sizeof(int));
  //memcpy(&supplyCount, &G.supplyCount, treasure_map+1 * sizeof(int));
  for (i = 0; i < treasure_map+1; i++)
	  supplyCount[i] = G.supplyCount[i];
  memcpy(&embargoTokens, &G.embargoTokens, treasure_map+1 * sizeof(int));
  altDeckCount = G.deckCount[alternatePlayer];
  altHandCount = G.handCount[alternatePlayer];
  altDiscardCount = G.discardCount[alternatePlayer];
  numPlayers = G.numPlayers;
  outpostPlayed = G.outpostPlayed;
  outpostTurn = G.outpostTurn;
  whoseTurn = G.whoseTurn;
  phase = G.phase;
  numActions = G.numActions;
  coins  = G.coins;
  numBuys = G.numBuys;
  
  // get starting handCount
  handCount = G.handCount[1];
  
  success = drawCard(1, &G);
  
    //*********************** LOGIC TO CHECK drawCard doesnt effect other players deck or other gamestate vars **************/
  printf("\tExpecting drawCard does not alter other players deck or irrelevent game state variables\n");
  // check altPlayers hand matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altHandCount; i++)
	  if (altHand[i] == G.hand[alternatePlayer][i])
		  z++;
  error_count += asserttrue(z == altHandCount, "drawCard changed another players hand");

  // check altPlayers deck matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altDeckCount; i++)
	  if (altDeck[i] == G.deck[alternatePlayer][i])
		  z++;
  error_count += asserttrue(z == altDeckCount, "drawCard changed another players deck");

  // check altPlayers discard matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altDiscardCount; i++)
	  if (altDiscard[i] == G.discard[alternatePlayer][i])
		  z++;

  error_count += asserttrue(z == altDiscardCount, "drawCard changed another players discard");

  // check supplyCounts match copy
  z = 0;	// z used to count matches
  for (i = 0; i < treasure_map+1; i++)
	  if (supplyCount[i] == G.supplyCount[i])
		  z++;

  error_count += asserttrue(z == treasure_map+1, "drawCard changed supplyCount");

  // check embargoTokens match copy
  z = 0;	// z used to count matches
  for (i = 0; i < treasure_map+1; i++)
	  if (embargoTokens[i] == G.embargoTokens[i])
		  z++;

  error_count += asserttrue(z == treasure_map+1, "drawCard changed embargoTokens");

  // Assert altHandCount, altDeckCount, and altDiscardCount match current alternate players counts
  error_count += asserttrue(G.handCount[alternatePlayer] == altHandCount, "drawCard changed another players handCount");
  error_count += asserttrue(G.deckCount[alternatePlayer] == altDeckCount, "drawCard changed another players deckCount");
  error_count += asserttrue(G.discardCount[alternatePlayer] == altDiscardCount, "drawCard changed another players handCount");
  // assert that other gameState variables have not changed
  error_count += asserttrue(numPlayers == G.numPlayers, "drawCard change numPlayers");
  error_count += asserttrue(outpostPlayed == G.outpostPlayed, "drawCard change outpostPlayed");
  error_count += asserttrue(outpostTurn == G.outpostTurn, "drawCard change outpostTurn");
  error_count += asserttrue(whoseTurn == G.whoseTurn, "drawCard change whoseTurn");
  error_count += asserttrue(phase == G.phase, "drawCard change phase");
  error_count += asserttrue(coins == G.coins, "drawCard change coins");
  error_count += asserttrue(numBuys == G.numBuys, "drawCard change numBuys");
  error_count += asserttrue(numActions == G.numActions, "drawCard change numActions");

  if (error_count == 0)
	  printf("\t\tSuccess: drawCard does not change irrelevant game state variables\n");
  //*********************** END OF LOGIC TO CHECK DrawCard doesnt effect other players deck **************/

  // get the top of Player 1's hand after drawCard
  handTop = G.hand[1][G.handCount[1]-1];
  
  error_count += asserttrue(success == 0, "Draw Card Failed");
  // Check that handCount increased
  error_count += asserttrue(handCount + 1 == G.handCount[1], "Hand Count not incremented");
  // check that discard is now empty after shuffle to deck
  error_count += asserttrue(G.discardCount[1] == 0, "Discard not cleared after deck shuffle");
  // check that deckCount is 1 less than before (9 as player 1 starts with 10
  // cards)
  error_count += asserttrue(G.deckCount[1] == 9, "Deck size incorrect after drawCard, should be 9");
  
  // See if cards from old discard pile exactly match the ordering in current
  // deck. If so, shuffling did not work correctly
  counter = 0;
  seed = 0;
  // check if cards were shuffled from discard to deck. If they match tempDeck
  // then it wasnt shuffled
  for (i = 0; i < G.deckCount[1]; i++) {
    if ( tempDeck[i] == G.deck[1][i] )
      seed++;
  }
  // see if top of hand actually came from shuffled discard pile
  for (i = 0; i < deckCount; i++) {
    if (tempDeck[i] == handTop)
      counter++;
  }
  // assert that deck was shuffled
  error_count += asserttrue(seed != deckCount-1, "Deck not shuffled from discard");
  
  // assert that the card was in the discard pile before it was shuffled into
  // the deck
  error_count += asserttrue(counter == 1, "Drawn card did not come from old discard pile");

  if (error_count == 0)
    printf("\tAll 22 Tests Completed Successfully: Card Draw (deck empty)\n\n");
  else
    printf("\t%d Tests failed: Card Draw (deck empty)\n\n", error_count);

  error_total += error_count;
  error_count = 0;
  
  printf("Test Invalid Input (both deck and discard empty\n");
  
  // Set deck and discard counts to 0
  G.discardCount[0] = 0;
  G.deckCount[0] = 0;
  
  alternatePlayer = 1;
  // Store altPlayers hand to check after call to adventurer
  memcpy(&altDeck, &G.deck[alternatePlayer], MAX_DECK * sizeof(int));
  memcpy(&altDiscard, &G.discard[alternatePlayer], MAX_DECK * sizeof(int));
  memcpy(&altHand, &G.hand[alternatePlayer], MAX_HAND * sizeof(int));
  //memcpy(&supplyCount, &G.supplyCount, treasure_map+1 * sizeof(int));
  for (i = 0; i < treasure_map+1; i++)
	  supplyCount[i] = G.supplyCount[i];
  memcpy(&embargoTokens, &G.embargoTokens, treasure_map+1 * sizeof(int));
  altDeckCount = G.deckCount[alternatePlayer];
  altHandCount = G.handCount[alternatePlayer];
  altDiscardCount = G.discardCount[alternatePlayer];
  numPlayers = G.numPlayers;
  outpostPlayed = G.outpostPlayed;
  outpostTurn = G.outpostTurn;
  whoseTurn = G.whoseTurn;
  phase = G.phase;
  numActions = G.numActions;
  coins  = G.coins;
  numBuys = G.numBuys;
  
  // copy game state into temp variable
  memcpy(&testG, &G, sizeof(struct gameState));

  success = drawCard(0, &G);
  
    //*********************** LOGIC TO CHECK drawCard doesnt effect other players deck or other gamestate vars **************/
  printf("\tExpecting drawCard does not alter other players deck or irrelevent game state variables\n");
  // check altPlayers hand matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altHandCount; i++)
	  if (altHand[i] == G.hand[alternatePlayer][i])
		  z++;
  error_count += asserttrue(z == altHandCount, "drawCard changed another players hand");

  // check altPlayers deck matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altDeckCount; i++)
	  if (altDeck[i] == G.deck[alternatePlayer][i])
		  z++;
  error_count += asserttrue(z == altDeckCount, "drawCard changed another players deck");

  // check altPlayers discard matches copy
  z = 0;	// z used to count matches
  for (i = 0; i < altDiscardCount; i++)
	  if (altDiscard[i] == G.discard[alternatePlayer][i])
		  z++;

  error_count += asserttrue(z == altDiscardCount, "drawCard changed another players discard");

  // check supplyCounts match copy
  z = 0;	// z used to count matches
  for (i = 0; i < treasure_map+1; i++)
	  if (supplyCount[i] == G.supplyCount[i])
		  z++;

  error_count += asserttrue(z == treasure_map+1, "drawCard changed supplyCount");

  // check embargoTokens match copy
  z = 0;	// z used to count matches
  for (i = 0; i < treasure_map+1; i++)
	  if (embargoTokens[i] == G.embargoTokens[i])
		  z++;

  error_count += asserttrue(z == treasure_map+1, "drawCard changed embargoTokens");

  // Assert altHandCount, altDeckCount, and altDiscardCount match current alternate players counts
  error_count += asserttrue(G.handCount[alternatePlayer] == altHandCount, "drawCard changed another players handCount");
  error_count += asserttrue(G.deckCount[alternatePlayer] == altDeckCount, "drawCard changed another players deckCount");
  error_count += asserttrue(G.discardCount[alternatePlayer] == altDiscardCount, "drawCard changed another players handCount");
  // assert that other gameState variables have not changed
  error_count += asserttrue(numPlayers == G.numPlayers, "drawCard change numPlayers");
  error_count += asserttrue(outpostPlayed == G.outpostPlayed, "drawCard change outpostPlayed");
  error_count += asserttrue(outpostTurn == G.outpostTurn, "drawCard change outpostTurn");
  error_count += asserttrue(whoseTurn == G.whoseTurn, "drawCard change whoseTurn");
  error_count += asserttrue(phase == G.phase, "drawCard change phase");
  error_count += asserttrue(coins == G.coins, "drawCard change coins");
  error_count += asserttrue(numBuys == G.numBuys, "drawCard change numBuys");
  error_count += asserttrue(numActions == G.numActions, "drawCard change numActions");

  if (error_count == 0)
	  printf("\t\tSuccess: drawCard does not change irrelevant game state variables\n");
  //*********************** END OF LOGIC TO CHECK DrawCard doesnt effect other players deck **************/

  error_count += asserttrue(memcmp(&testG, &G, sizeof(struct gameState)) == 0, "Game State should not be altered on invalid call");
  
  // assert that drawCard returns a -1 when it catches invalid input
  error_count += asserttrue(success == -1, "Failed to catch invalid input");
  
  if (error_count == 0)
    printf("\tAll 18 Tests Completed Successfully: Card Draw (invalid input)\n\n");
  else
    printf("\t%d Tests failed: Card Draw (invalid input)\n\n", error_count);

  error_total += error_count;

  if (error_total == 0)
    printf("ALL 60 TESTS SUCCESSFUL drawCard\n");
  else
    printf("%d TESTS FAILED drawCard\n", error_total);



  printf("------------------------ END Test drawCard ----------------------\n");

  return 0; 
}



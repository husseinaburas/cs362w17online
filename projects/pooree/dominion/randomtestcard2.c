/* -----------------------------------------------------------------------
 *
 *          randomtestcard2.c
 *          Random Testing of Sea Hag Card 
 * 
 *      
 * -----------------------------------------------------------------------
 */


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"

// To see all print statements for value comparisons, set NOISY to 1
#define NOISY 0 
//#define NOISY 1


void assertTrue(int test, char *errorMsg)
{
  if (!test) {
    printf ("*****FAILED TEST*****\n");
    printf("%s\n", errorMsg);
  }
  return;
}



int main (int argc, char** argv) {

  int i, n, x, r, p, numPlayers;

  struct gameState G, preG;

  if (!argv[1]) {
    PutSeed((long)1);
  } else {
    PutSeed((long)atoi(argv[1]));
  }
  
  printf ("################Testing Sea Hag################\n");

  

  for (x = 0; x < 1000; x++) {   
    printf ("***************************Test %d***************************\n", x);

    numPlayers = floor(Random() * 3) + 2;             // Determine a random number of players for game
    // Initialize supply count of curse cards so that the supply count change can be tested
    G.numPlayers = numPlayers;
    G.supplyCount[0] = 10;
    
    for (n=0; n<numPlayers; n++) {
      G.deckCount[n] = floor(Random() * MAX_DECK);      // Use Random() from rngs.h because mod 0 illegal operation in C
      G.discardCount[n] = floor(Random() * MAX_DECK);
      G.handCount[n] = floor(Random() * MAX_HAND);
      
      // Add cards to hand and piles at random (for our purposes, doesn't matter which cards)
      for (i=0; i<G.handCount[n]; i++) {
        G.hand[n][i] = floor(Random()*treasure_map);
      }

      for (i=0; i<G.deckCount[n]; i++) {
        G.deck[n][i] = floor(Random()*treasure_map);
      }

      for (i=0; i<G.discardCount[n]; i++) {
        G.discard[n][i] = floor(Random()*treasure_map);
      }
    } 


    p = floor(Random() * numPlayers);                 // Randomly select a player 
    G.whoseTurn = p;  
    G.playedCardCount = 0;                            // Initialize to 0                                
    r = floor(Random()*G.handCount[p]);               // Randomly place a Sea Hag card in player's hand
    G.hand[p][r] = sea_hag;


    memcpy(&preG, &G, sizeof(struct gameState)); // Copy game state prior to playing card for comparisons
    
    // Play the card from the proper hand position
    cardEffect(sea_hag, 0, 0, 0, &G, r, 0);

    // Test hand count decreases by 1 indicating the card was discarded
    if (NOISY == 1) printf("hand count = %d, expected = %d\n", G.handCount[p], preG.handCount[p] - 1);
    assertTrue(G.handCount[p] == preG.handCount[p] - 1, "Current player hand count error");

    // Test discard count increases by 1
    if (NOISY == 1) printf("discard count = %d, expected = %d\n", G.discardCount[p], preG.discardCount[p] + 1);
    assertTrue(G.discardCount[p] == preG.discardCount[p] + 1, "Current player discard count error");

    // Test played card in hand has been replaced
    if (NOISY == 1) printf("card now where sea_hag was=%d expect in most cases to !=sea_hag\n", G.hand[p][r]);
    assertTrue(G.hand[p][r] != sea_hag, "Current player card replacement error");

    // Test sea_hag added to discard pile
    if (NOISY == 1) printf("most recent discard card = %d, expected = %d\n", G.discard[p][G.discardCount[p]-1], sea_hag);
    assertTrue(G.discard[p][G.discardCount[p]-1] == sea_hag, "Error: Sea Hag not at top of discard pile");

    // Test other player's hand / piles 
    for(i=0; i<numPlayers; i++) {
      if (i != p) {
        // Overall hand count should remain the same
        if (NOISY == 1) printf("player %d hand count = %d, expected = %d\n", i, G.handCount[i], preG.handCount[i]);
        assertTrue(G.handCount[i] == preG.handCount[i], "Error: other player hand count");
        
        // Overall deck count should remain the same
        if (NOISY == 1) printf("player %d deck count = %d, expected = %d\n", i, G.deckCount[i], preG.deckCount[i]);
        assertTrue(G.deckCount[i] == preG.deckCount[i], "Error: other player deck count");

        //The top card of the deck should be a curse card
        if (NOISY == 1) printf("player %d top deck card = %d, expected = %d\n", i, G.deck[i][G.deckCount[i]-1], curse);
        assertTrue(G.deck[i][G.deckCount[i] -1] == curse, "Error: top card in deck not curse");

        // Discard count should increase by 1
        if (NOISY == 1) printf("player %d discard count = %d, expected = %d\n", i, G.discardCount[i], preG.discardCount[i] + 1);
        assertTrue(G.discardCount[i] == preG.discardCount[i] + 1, "Error: other player discard count");

        // Top card in discard pile should be previous top card of deck
        if (NOISY == 1) printf("player %d top discard card = %d, expected = %d\n", i, G.discard[i][G.discardCount[i]--], preG.deck[i][preG.deckCount[i]--]);
        assertTrue(G.discard[i][G.discardCount[i]--] == preG.deck[i][preG.deckCount[i]--], "Error: other player discard count");
      } 
    }


    // Test there is no change to supply piles other than curse cards
    for (i=1; i<sizeof(G.supplyCount)/sizeof(int); i++) {
      if (NOISY == 1) printf("supply %d count = %d, expected %d\n", i, G.supplyCount[i], preG.supplyCount[i]);
      assertTrue(G.supplyCount[i] == preG.supplyCount[i], "Error: supply card count");
    }

    // Test that the supply count of curse cards decreases by numPlayers - 1
    if (NOISY == 1) printf("num curse cards = %d, expected %d\n", G.supplyCount[0], preG.supplyCount[0] - numPlayers + 1);
    assertTrue(G.supplyCount[0] == preG.supplyCount[0] - numPlayers + 1, "Error: supply card count");

    // Test other general game state qualities are uneffected
    if (NOISY == 1) printf("Num players = %d, expected = %d\n", G.numPlayers, preG.numPlayers);
    assertTrue(G.numPlayers == preG.numPlayers, "Error: number of players in game changed");
    
    if (NOISY == 1) printf("Whose turn = %d, expected = %d\n", G.whoseTurn, preG.whoseTurn);
    assertTrue(G.whoseTurn == preG.whoseTurn, "Error: whose turn changed");  // Playing the card doesn't end the turn thus whose turn should remain the same
    
    if (NOISY == 1) printf("Phase number = %d, expected = %d\n", G.phase, preG.phase);
    assertTrue(G.phase == preG.phase, "Error: phase number changed");
    
    if (NOISY == 1) printf("Number of actions = %d, expected = %d\n", G.numActions, preG.numActions);
    assertTrue(G.numActions == preG.numActions, "Error: number of actions changed"); // playCard decrements numActions, but outside of this function. Smithy does not increase numActions, thus should be unchanged.
    
    if (NOISY == 1) printf("Number of coins = %d, expected = %d\n", G.coins, preG.coins);
    assertTrue(G.coins == preG.coins, "Error: number of coins changed");
    
    if (NOISY == 1) printf("Number of buys = %d, expected = %d\n", G.numBuys, preG.numBuys);
    assertTrue(G.numBuys == preG.numBuys, "Error: number of buys changed");
   }

  printf ("################Testing of Sea Hag Complete################\n");

  return 0;
}



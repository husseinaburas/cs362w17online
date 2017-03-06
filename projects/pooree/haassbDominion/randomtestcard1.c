/* -----------------------------------------------------------------------
 *
 *          randomtestcard1.c
 *          Random Testing of Smithy Card 
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
//#define NOISY 1 
#define NOISY 0


void assertTrue(int test, char *errorMsg)
{
  if (!test) {
    printf ("*****FAILED TEST*****\n");
    printf("%s\n", errorMsg);
  }
  return;
}



int main (int argc, char** argv) {

  int i, n, r, p, numPlayers;

  struct gameState G, preG;

  // If a command line argument is given, assign to default seed otherwise
  if (!argv[1]) {
    PutSeed((long)1);
  } else {
    PutSeed((long)atoi(argv[1]));
  }

  printf ("################Testing Smithy################\n");

  

  for (n = 0; n < 1000; n++) {   
    printf ("***************************Test %d***************************\n", n);

    numPlayers = floor(Random() * 3) + 2;             // Determine a random number of players for game
    G.numPlayers = numPlayers;
    p = floor(Random() * numPlayers);                 // Randomly select a player 
    G.whoseTurn = p;  
    G.playedCardCount = 0;                            // Initialize to 0                                
    G.deckCount[p] = floor(Random() * MAX_DECK);      // Use Random() from rngs.h because mod 0 illegal operation in C
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);

    
    // Add cards to hand and piles at random (for our purposes, doesn't matter which cards)
    for (i=0; i<G.handCount[p]; i++) {
      G.hand[p][i] = floor(Random()*treasure_map);
    }

    for (i=0; i<G.deckCount[p]; i++) {
      G.deck[p][i] = floor(Random()*treasure_map);
    }

    for (i=0; i<G.discardCount[p]; i++) {
      G.discard[p][i] = floor(Random()*treasure_map);
    }

    r = floor(Random()*G.handCount[p]);   // Randomly place Smithy card in player's hand
    G.hand[p][r] = smithy;


    memcpy(&preG, &G, sizeof(struct gameState)); // Copy game state prior to playing card for comparisons
    
    // Play the card from the function created outside of cardEffect
    playSmithy(&G, r);

    // Test hand count increases by 2 overall (3 new cards - 1 discard)
    if (NOISY == 1) printf("hand count = %d, expected = %d\n", G.handCount[p], preG.handCount[p] + 2);
    assertTrue(G.handCount[p] == preG.handCount[p] + 2, "Current player hand count error");

    // Test discard count increases by 1
    if (NOISY == 1) printf("discard count = %d, expected = %d\n", G.discardCount[p], preG.discardCount[p] + 1);
    assertTrue(G.discardCount[p] == preG.discardCount[p] + 1, "Current player discard count error");

    // Test played card in hand has been replaced
    if (NOISY == 1) printf("card now where smithy was=%d expect in most cases to !=smithy\n", G.hand[p][r]);
    assertTrue(G.hand[p][r] != smithy, "Current player card replacement error");

    // Test smithy added to discard pile
    if (NOISY == 1) printf("most recent discard card = %d, expected = %d\n", G.discard[p][G.discardCount[p]-1], smithy);
    assertTrue(G.discard[p][G.discardCount[p]-1] == smithy, "Error: Smithy not at top of discard pile");

    // Test other player's hand / piles are uneffected 
    for(i=0; i<numPlayers; i++) {
      if (i != p) {
        if (NOISY == 1) printf("player %d hand count = %d, expected = %d\n", i, G.handCount[i], preG.handCount[i]);
        assertTrue(G.handCount[i] == preG.handCount[i], "Error: other player hand count");
        
        if (NOISY == 1) printf("player %d deck count = %d, expected = %d\n", i, G.deckCount[i], preG.deckCount[i]);
        assertTrue(G.deckCount[i] == preG.deckCount[i], "Error: other player deck count");
        
        if (NOISY == 1) printf("player %d discard count = %d, expected = %d\n", i, G.discardCount[i], preG.discardCount[i]);
        assertTrue(G.discardCount[i] == preG.discardCount[i], "Error: other player discard count");
      } 
    }


    // Test there is no change to supply piles
    for (i=0; i<sizeof(G.supplyCount)/sizeof(int); i++) {
      if (NOISY == 1) printf("supply %d count = %d, expected %d\n", i, G.supplyCount[i], preG.supplyCount[i]);
      assertTrue(G.supplyCount[i] == preG.supplyCount[i], "Error: supply card count");
    }

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

  printf ("################Testing of Smithy Complete################\n");

  return 0;
}



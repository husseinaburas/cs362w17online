#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include "assert_custom.h"
#include "string.h"

#define TEST_RUNS 28

int testCardAdventurer(struct gameState *G, struct gameState *copyG, int player) {


   // test player hand card count increase
   int hCntDiff = G->handCount[player] - copyG->handCount[player];
   assert_custom(hCntDiff > 0, "test handCount increased");
   assert_custom(hCntDiff == 2, "test handCount increase by 2 cards");

   // test deckCount decrease
   int deckCntDiff = G->deckCount[player] - copyG->deckCount[player];
   assert_custom(deckCntDiff < 0, "test deckCount decreased");

   // test discardCount increase
   int disCntDiff = G->discardCount[player] - copyG->discardCount[player];
   assert_custom(disCntDiff > 0, "test discardCount increase");
    
   // test playedCardCount increase
   int playedCardDiff = G->playedCardCount - copyG->playedCardCount;
   assert_custom(playedCardDiff > 0, "test playedCardCount increase");

   // test deckcount decreased by same amout as increase in discard count plus player hand count increase
   int noDiffTest = deckCntDiff + disCntDiff + hCntDiff;
   assert_custom(noDiffTest == 0, "test deckCount decrease is equal to increase in discardCount plus handCount"); 

   return 0;
}

int main (int argc, char *argv[]) {

   int seed = 738;

   if (argv[1] == NULL)
   {
      seed = 738;
      printf("No argument passed, seed set to: %i\n", seed);
   } else {
      seed = atoi(argv[1]);
      printf("Seed set to: %i\n", seed);
   }

   // seed random number generator
   srand(seed);

   struct gameState G, copyG;
   int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
   int p = 0, handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

   int i = 0;
   for(i = 0; i < TEST_RUNS; i++)
   {
      printf("---------------- Adventurer Card Test Run# %i ----------------\n", i);

      // Generate randomly between 2 and 4 players
      p = (rand() % 3) + 2;
      initializeGame(p, k, seed, &G);
      printf("number of players: %i\n", p);

      // Randomly choose a player to play card
      int player = rand() % p;
      
      // End turns until its the chosen players turn to initialize players hand
      while(G.whoseTurn != player){ endTurn(&G); }
      
      printf("whoseTurn: %i\n", G.whoseTurn);
      printf("player: %i\n", player);

      // Radomly choose hand position of card
      int handCt = G.handCount[player];
      if( handCt < 1 )
      {
         handPos = 0;
      } else {
         handPos = rand() % handCt;
      }
      printf("handPos: %i\n", handPos);

      // place card in player hand 
      G.hand[player][handPos] = adventurer;

      // confirm adventurer card is in hand
      assert_custom(G.hand[player][handPos] == adventurer, "test adventurer card is in hand");

      // randomly generate the number of cards deck available to player
      G.deckCount[player] = rand() % (MAX_DECK + 1);
      printf("deckCount: %i\n", G.deckCount[player]);

      // save initial state
      memcpy(&copyG, &G, sizeof(struct gameState));

      cardEffect(adventurer, choice1, choice2, choice3, &G, handPos, &bonus);

      // run testCard function comparing initial game state to game state after playing card
      testCardAdventurer(&G, &copyG, player);

      printf("---------------- End of Adventurer Card Test Run# %i ----------------\n", i);
   }



   return 0;
}

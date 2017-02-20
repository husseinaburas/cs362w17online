/* *****************************************************************************
 * Nicholas Wong
 * OSU CS 362 Winter 2017
 * Assignment 4 Random Tester for Smithy Card
 * randomtestcard1.c
 *
 * Randomly tests smithyCall() in dominion.c
 * ************************************************************************** */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"



int checkSmithyCall(int n, int i, int handPos, int currentPlayer, struct gameState *post) {
   struct gameState pre;
   memcpy(&pre, post, sizeof(struct gameState));
   int tempHand = pre.handCount[currentPlayer], tempDeck = pre.deckCount[currentPlayer];

   int r = smithyCall(i, handPos, currentPlayer, post);       //function call

   //this is what I assume the Smithy card function is doing
   for(i=0; i<3; i++){      //simply draw 3 cards
      drawCard(currentPlayer, &pre);
   }


   printf("Iteration: %d\n", n);
   assert (r == 0);

   //check that both gamestate's handcounts ++ three times
   if(pre.handCount[currentPlayer]-3 == tempHand && post->handCount[currentPlayer]-3 == tempHand)
      printf("PASSED: Hand count increased by 3\n");
   else printf("FAILED: Hand count did not increase by 3; Pre: %d, Post: %d\n", tempHand, post->handCount[currentPlayer]);
   //check that both gamestate's deck has decreased by 3 (including the smithy card itself)
   if(post->deckCount[currentPlayer] == tempDeck-4)
      printf("PASSED: Deck count decreased\n");
   else printf("FAILED: Deck count did not decrease; Pre: %d, Post: %d\n", tempDeck, post->deckCount[currentPlayer]);

}


int main (int argc, char** argv) {
   struct gameState G;
   int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy};

   int i, j, n, p;
   int temphand[MAX_HAND];
   int drawntreasure=0, smithyPos;
   int cardDrawn;
   int z = 0;   // this is the counter for the temp hand
   int currentPlayer = whoseTurn(&G);
   int nextPlayer = currentPlayer + 1;
   if (nextPlayer > (G.numPlayers - 1)){
      nextPlayer = 0;
   }

   for(i=0; i<2000; i++){
      memset(&G, 23, sizeof(struct gameState));   // clear the game state
      initializeGame(2, k, i, &G); // initialize a new game with seed i (this makes the game random from others)
      p = floor(Random() * 2);
      G.deckCount[p] = floor(Random() * MAX_DECK);    //generate a random deck count
      G.handCount[p] = floor(Random() * MAX_HAND);    //generate a random hand count
      //choose a random pos in hand to be smithy card
      smithyPos = floor(Random() * G.handCount[p]);
	  checkSmithyCall(i, j, smithyPos, p, &G);
    }



   return 0;
}

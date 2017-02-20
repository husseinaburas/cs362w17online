/* *****************************************************************************
 * Nicholas Wong
 * OSU CS 362 Winter 2017
 * Assignment 4 Random Tester for Adventurer Card
 * randomtestadventurer.c
 *
 * Randomly tests adventurerCall() in dominion.c
 * ************************************************************************** */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"



int checkAdventurerCall(int n, int drawntreasure, struct gameState *post, int currentPlayer, int cardDrawn, int z, int temphand[MAX_HAND]) {
   struct gameState pre;
   int i, tempHand = pre.handCount[currentPlayer], tempDeck = pre.deckCount[currentPlayer];
   memcpy(&pre, post, sizeof(struct gameState));

   int r = adventurerCall(drawntreasure, post, currentPlayer, cardDrawn, z, temphand); //THIS IS THE SEGFAULT

   //this is what I assume the callAdventurer function is doing
   for(i=0; i<2; i++){
      drawCard(currentPlayer, &pre);
      cardDrawn = pre.hand[currentPlayer][pre.handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
      if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
	 drawntreasure++;
      else{
	 temphand[z]=cardDrawn;
	 pre.handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
	 z++;
      }
   }

   printf("Iteration: %d\n", n);
   assert (r == 0);

   //check that both gamestate's handcounts ++ twice
   if(pre.handCount[currentPlayer]-2 == tempHand && post->handCount[currentPlayer]-2 == tempHand)
      printf("PASSED: Hand count increased by 2\n");
   else printf("FAILED: Hand count did not increase by 2; Pre: %d, Post: %d\n", tempHand, post->handCount[currentPlayer]);
   //check that both gamestate's deck has decreased some amount
   if(post->deckCount[currentPlayer] < tempDeck)
      printf("PASSED: Deck count decreased\n");
   else printf("FAILED: Deck count did not decrease; Pre: %d, Post: %d\n", tempDeck, post->deckCount[currentPlayer]);

}


int main (int argc, char** argv) {
   struct gameState G;
   int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy};

   int i, n, p;
   int temphand[MAX_HAND];
   int drawntreasure=0;
   int cardDrawn;
   int z = 0;   // this is the counter for the temp hand
   int currentPlayer = whoseTurn(&G);
   int nextPlayer = currentPlayer + 1;
   if (nextPlayer > (G.numPlayers - 1)){
      nextPlayer = 0;
   }

   for(i=0; i<2000; i++){
      memset(&G, 23, sizeof(struct gameState));   // clear the game state
      initializeGame(2, k, i, &G); // initialize a new game
      p = floor(Random() * 2);
      G.deckCount[p] = floor(Random() * MAX_DECK);
      G.handCount[p] = floor(Random() * MAX_HAND);
      checkAdventurerCall(i, drawntreasure, &G, currentPlayer, cardDrawn, z, temphand);

   }


   /*for (n = 0; n < 2000; n++) {
     for (i = 0; i < sizeof(struct gameState); i++) {
     ((char*)&G)[i] = floor(Random() * 256);
     }
     p = floor(Random() * 2);
     G.deckCount[p] = floor(Random() * MAX_DECK);
     G.discardCount[p] = floor(Random() * MAX_DECK);
     G.handCount[p] = floor(Random() * MAX_HAND);
     checkAdventurerCall(drawntreasure, &G, currentPlayer, cardDrawn, z, temphand); //SEGFAULT
     }*/


   return 0;
}

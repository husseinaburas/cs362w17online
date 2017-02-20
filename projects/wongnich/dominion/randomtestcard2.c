

/* *****************************************************************************
 * Nicholas Wong
 * OSU CS 362 Winter 2017
 * Assignment 4 Random Tester for Village Card
 * randomtestcard2.c
 *
 * Randomly tests villageCall() in dominion.c
 * ************************************************************************** */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"



int checkVillageCall(int n, int currentPlayer, struct gameState *post, int handPos) {
   struct gameState pre;
   memcpy(&pre, post, sizeof(struct gameState));
   int tempHand = pre.handCount[currentPlayer], tempNumActions = pre.numActions;
   int r = villageCall(currentPlayer, post, handPos);       //function call

   //this is what I assume the Village card function is doing

      drawCard(currentPlayer, &pre);    //draw 1 card
      pre.numActions = pre.numActions + 2;  //add 2 actions points

      discardCard(handPos, currentPlayer, &pre, 0); //discard that village card


   printf("Iteration: %d\n", n);
   assert (r == 0);

   //check that both gamestate's handcounts ++ once means card count should equal (discard one, add one)
   if(pre.handCount[currentPlayer] == tempHand && post->handCount[currentPlayer] == tempHand)
      printf("PASSED: Hand count increased by 1\n");
   else printf("FAILED: Hand count did not increase by 1; Pre: %d, Post: %d\n", tempHand, post->handCount[currentPlayer]);
   //check that gamestate's numActions has increased by 2
   if(post->numActions == pre.numActions && post->numActions == tempNumActions + 2)
      printf("PASSED: Both numActions increased by 2\n");
   else printf("FAILED: numActions did not increase by 2; Pre: %d, Post: %d\n", tempNumActions, post->numActions);
}


int main (int argc, char** argv) {
   struct gameState G;
   int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy};

   int i, j, n, p, seed;
   int temphand[MAX_HAND];
   int drawntreasure=0, handPos;
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
      //choose a random pos in hand to be village card
      handPos = floor(Random() * G.handCount[p]);
	  checkVillageCall(i, p, &G, handPos);
    }



   return 0;
}

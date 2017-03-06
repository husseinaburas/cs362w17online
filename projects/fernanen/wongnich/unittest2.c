/* -----------------------------------------------------------------------
* Unit test of function gainCard() from dominion.c
* Will output into unittestresults.out along with other unit tests
* We want to check if gain card function works for:
*   specfic cards
*   what happens with each "toFlag"
*
* to see if the function properly returns the state of the game
* 2/1/17
* -----------------------------------------------------------------------
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0

int main() {
  int i;
  int seed = 1000;
  int numPlayer = 2;
  int p, r, handCount=5, tempCount, tempDeck, tempDiscard;
  //int bonus;
  int k[10] = {adventurer, council_room, feast, gardens, mine
    , remodel, smithy, village, baron, great_hall};

    int cardtoTest = 0;      //this will be our card to "gain"
    struct gameState G;
    //int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    //int coppers[MAX_HAND];
    //int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
      //coppers[i] = copper;
      //silvers[i] = silver;
      golds[i] = gold;
    }

    printf ("TESTING gainCard():\n");
    for (p = 1; p < numPlayer; p++){
      for(i=0; i<3; i++){     //iterates through "toFlag" 0: discard, 1: deck, 2:hand

          memset(&G, 23, sizeof(struct gameState));   // clear the game state
          r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
          G.handCount[p] = handCount;                 // set the number of cards on hand
          memcpy(G.hand[p], golds, sizeof(int) * handCount); // set all the cards to gold rich man
          tempCount = G.handCount[p];
          G.deckCount[p] = 499;   //because we add 1 for toflag==1
          tempDeck = G.deckCount[p];
          tempDiscard = G.discardCount[p];
          gainCard(cardtoTest, &G, i, p);

          if(i==0){ // check what happens when toFlag is 0 (should add card to discard, discardCount should ++)
            if(tempDiscard == G.discardCount[p]-1)  printf("gainCard(): PASS when testing %d toFlag, init discardCount: %d, final discardCount: %d\n", i, tempDiscard, G.discardCount[p]);
            else  printf("gainCard(): FAIL when testing %d toFlag, init discardCount: %d, final discardCount: %d\n", i, tempDiscard, G.discardCount[p]);
          }
          if(i==1){   //check what happens when toFlag is 1 (should add card to deck)
            if(tempDeck == G.deckCount[p]-1)  printf("gainCard(): PASS when testing %d toFlag, init deckCount: %d, final deckCount: %d\n", i, tempDeck, G.deckCount[p]);
            else  printf("gainCard(): FAIL when testing %d toFlag, init deckCount: %d, final deckCount: %d\n", i, tempDeck, G.deckCount[p]);

          }
          if(i==2){   //check what happens when toFlag is 2 (should add card to hand)
            if(tempCount == G.handCount[p]-1)  printf("gainCard(): PASS when testing %d toFlag, init handCount: %d, final handCount: %d\n", i, tempCount, G.handCount[p]);
            else  printf("gainCard(): FAIL when testing %d toFlag, init handCount: %d, final handCount: %d\n", i, tempCount, G.handCount[p]);

          }
      }
    }

    return 0;
  }

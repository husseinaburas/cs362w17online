//
//  unittest3.c
//  
//
//  Created by Jeanvally Galing Beato on 2/4/17.
//
//  unitTest #3 = fullDeckCount()
//
//

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

    /*******************
     
     ORIGINAL METHOD:  fullDeckCount()
     Description:  Returns the count of a specific card in a specific player's discard deck and hand.
     
     int fullDeckCount(int player, int card, struct gameState *state) {
         int i;
         int count = 0;
         
         for (i = 0; i < state->deckCount[player]; i++)
         {
         if (state->deck[player][i] == card) count++;
         }
         
         for (i = 0; i < state->handCount[player]; i++)
         {
         if (state->hand[player][i] == card) count++;
         }
         
         for (i = 0; i < state->discardCount[player]; i++)
         {
         if (state->discard[player][i] == card) count++;
         }
         
         return count;
     }
     
    *******************/

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {

    int seed = 1000;
    int numPlayer = 2;
    struct gameState gameS;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    
    //Clear game state
    memset(&gameS, 23, sizeof(struct gameState));
    //Initialize new game
    initializeGame(numPlayer, k, seed, &gameS);
    
    printf("**************************\n");
    printf("*                        *\n");
    printf("*                        *\n");
    printf("*     UNIT TEST #3       *\n");
    printf("*                        *\n");
    printf("*                        *\n");
    printf("*TESTING: fullDeckCount()*\n");
    printf("**************************\n\n");
    
#if (NOISY_TEST == 1)
    //Test counting # of ____ cards in Player _____'s deck, hand, and discard pile
    printf("------------------------------------------------------------------------------------\n");
    printf("COUNT HOW MANY OF A CERTAIN CARD ARE IN CURRENT PLAYER'S DECK, HAND, & DISCARD PILE.\n");
    printf("------------------------------------------------------------------------------------\n\n");
#endif
                
#if (NOISY_TEST == 1)
        //***********
        //
        //TEST 1:  Check # of baron cards
        //
        //*************

        printf("Test #1: Count # of BARON cards...\n");
        printf("----------------------------------\n");
        int a = fullDeckCount(gameS.whoseTurn, baron, &gameS);
        printf("BARON cards:        %i\n\n", a);
#endif
                
#if (NOISY_TEST == 1)
        //***********
        //
        //TEST 2:  Check # of estate cards
        //
        //*************
        
        printf("Test #2: Count # of ESTATE cards...\n");
        printf("----------------------------------\n");
        int b = fullDeckCount(gameS.whoseTurn, estate, &gameS);
        printf("ESTATE cards:        %i\n\n", b);
#endif
    
#if (NOISY_TEST == 1)
        //***********
        //
        //TEST 3:  Check # of copper cards
        //
        //*************
        
        printf("Test #3: Count # of COPPER cards...\n");
        printf("----------------------------------\n");
        int c = fullDeckCount(gameS.whoseTurn, copper, &gameS);
        printf("COPPER cards:        %i\n\n", c);
#endif
    
#if (NOISY_TEST == 1)
        //***********
        //
        //TEST 4:  Check # of adventurer cards
        //
        //*************
        
        printf("Test #4: Count # of ADVENTURER cards...\n");
        printf("----------------------------------\n");
        int d = fullDeckCount(gameS.whoseTurn, adventurer, &gameS);
        printf("ADVENTURER cards:        %i\n\n", d);
#endif

    
    printf("--------------------------\n");
    printf("ALL UNIT #3 TESTS PASSED! \n\n");
    
    return 0;

}
//
//  unittest1.c
//  
//
//  Created by Jeanvally Galing Beato on 2/4/17.
//
//  unitTest #1 = isGameOver()
//
//

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

    /*******************
     
     ORIGINAL METHOD:  isGameOver()
     Description:  Checks the number of provinces or if three supply piles are empty to determine if
     the game is over.
     
     int isGameOver(struct gameState *state) {
         int i;
         int j;
            
         //if stack of Province cards is empty, the game ends
         if (state->supplyCount[province] == 0)
         {
         return 1;
         }
         
         //if three supply pile are at 0, the game ends
         j = 0;
         for (i = 0; i < 25; i++)
         {
         if (state->supplyCount[i] == 0)
            {
         j++;
            }
         }
         if ( j >= 3)
         {
         return 1;
         }
         
         return 0;
     }
    *******************/

int main() {
    
    int seed = 1000;
    int numPlayer = 2;
    struct gameState gameS;
    
    int k[10] = {smithy, adventurer, baron, feast, gardens, mine, remodel, great_hall, village, council_room};
    
    //Initialize game
    initializeGame(numPlayer, k, seed, &gameS);
    
#if (NOISY_TEST == 1)
    printf("************************\n");
    printf("*                      *\n");
    printf("*                      *\n");
    printf("*    UNIT TEST #1      *\n");
    printf("*                      *\n");
    printf("*                      *\n");
    printf("*TESTING: isGameOver() *\n");
    printf("************************\n\n");
#endif

#if (NOISY_TEST == 1)
    //***********
    //
    //TEST 1:  Empty Province Cards
    //
    //*************
    
    //Setting Province stack to zero
    printf("Test #1: Setting Province supply count to 0...\n");
    printf("----------------------------------------------\n");

    gameS.supplyCount[province] = 0;
    

    //Check if stack of Province cards is empty, after setting it to empty
    //If empty, error message shows, game ends
    if(isGameOver(&gameS))
    {
        assert(isGameOver(&gameS) == 1);
        printf("Testing for empty Province Cards:    PASSED - EMPTY\n");
        printf("Game Over Due to:                    Empty Province Cards\n\n");
    }
    else
    {
        printf("Testing for empty Province Cards:    FAILED - NOT EMPTY\n\n");
    }

    
    //Change Province stack back to non-zero
    gameS.supplyCount[province] = 1;
#endif

#if (NOISY_TEST == 1)
    //***********
    //
    //TEST 2:  3 Supply Piles are Empty
    //
    //*************
    
    //Setting 3 Supply Piles to Empty
    gameS.supplyCount[village] = 0;
    gameS.supplyCount[adventurer] = 0;
    gameS.supplyCount[smithy] = 0;
    
    printf("Test #2: Setting 3 Supply Piles to Empty...\n");
    printf("-------------------------------------------\n");
    
    if(isGameOver(&gameS))
    {
        assert(isGameOver(&gameS) == 1);
        printf("Testing for 3 Empty Supply Piles:   PASSED - EMPTY\n");
        printf("Game Over Due to:                   3 Supply Piles are Empty\n\n");
    }
    else
    {
        printf("Testing for 3 Empty Supply Piles:   FAILED - NOT EMPTY\n\n");
    }
#endif
    
#if (NOISY_TEST == 1)
    //***********
    //
    //TEST 3:  Check who's turn it is
    //
    //*************
    
    //Who's turn it is, should not affect whether or not isGameOver result true
    printf("Test #3: Check who's turn it is............\n");
    printf("-------------------------------------------\n");
    printf("Player #'s Turn:   %d\n\n", whoseTurn(&gameS));
#endif
    
#if (NOISY_TEST == 1)
    //Print statement that all tests passed
    printf("ALL UNIT #1 TESTS PASSED! \n\n");
#endif

    return 0;
}
//
//  unittest2.c
//  
//
//  Created by Jeanvally Galing Beato on 2/4/17.
//
//  unitTest #2 = updateCoins()
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
     
     ORIGINAL METHOD:  updateCoins()
     Description:  Returns the count of a specific card in a specific player’s discard deck and hand.
     
     int updateCoins(int player, struct gameState *state, int bonus)
     {
         int i;
         
         //reset coin count
         state->coins = 0;
         
         //add coins for each Treasure card in player's hand
         for (i = 0; i < state->handCount[player]; i++)
         {
         if (state->hand[player][i] == copper)
         {
         state->coins += 1;
         }
         else if (state->hand[player][i] == silver)
         {
         state->coins += 2;
         }
         else if (state->hand[player][i] == gold)
         {
         state->coins += 3;
         }
         }	
         
         //add bonus
         state->coins += bonus;
         
         return 0;
     }
    *******************/

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    
    int bonus, i, p, r, handCount;
    int maxBonus = 10;
    int maxHandCount = 5;
    int seed = 1000;
    int numPlayer = 2;
    struct gameState gameS;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    
    //Setup array of copper, silver, gold
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
    
    printf("************************\n");
    printf("*                      *\n");
    printf("*                      *\n");
    printf("*    UNIT TEST #2      *\n");
    printf("*                      *\n");
    printf("*                      *\n");
    printf("*TESTING: updateCoins()*\n");
    printf("************************\n\n");
    
    for( p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for (bonus = 0; bonus <= maxBonus; bonus++)
            {
#if (NOISY_TEST == 1)
                //Test Player #___ with ___treasure cards and ___ bonus
                printf("-----------------------------------------------------\n");
                printf("TEST PLAYER %d WITH %d TREASURE CARD(S) AND %d BONUS.\n", p, handCount, bonus);
                printf("-----------------------------------------------------\n\n");
                //Clear game state
                memset(&gameS, 23, sizeof(struct gameState));
                //Initialize new game
                initializeGame(numPlayer, k, seed, &gameS);
                //Set current player's number of cards on hand
                gameS.handCount[p] = handCount;
#endif
                
#if (NOISY_TEST == 1)
                //***********
                //
                //TEST 1:  Check if # of copper coins is correct
                //
                //*************
                
                //Set all cards to copper
                printf("Test #1: Setting all cards to copper...\n");
                printf("---------------------------------------\n");
                memcpy(gameS.hand[p], coppers, sizeof(int) * handCount);
                updateCoins(p, &gameS, bonus);
                printf("COINS = %d, EXPECTED = %d\n", gameS.coins, handCount * 1 + bonus);
                if(gameS.coins == (handCount * 1 + bonus)){
                    printf("Test: PASSED!\n\n");
                }
                else
                {
                    printf("Test: FAILED!\n\n");
                }
                //Check if # of copper coins is correct
                assert(gameS.coins == handCount * 1 + bonus);
#endif
                
#if (NOISY_TEST == 1)
                //***********
                //
                //TEST 2:  Check if # of silver coins is correct
                //
                //*************
                
                //Set all cards to silver
                printf("Test #2: Setting all cards to silver...\n");
                printf("---------------------------------------\n");
                memcpy(gameS.hand[p], silvers, sizeof(int) * handCount);
                updateCoins(p, &gameS, bonus);
                printf("COINS = %d, EXPECTED = %d\n", gameS.coins, handCount * 2 + bonus);
                if(gameS.coins == (handCount * 2 + bonus)){
                    printf("Test: PASSED!\n\n");
                }
                else
                {
                    printf("Test: FAILED!\n\n");
                }
                //Check if # of silver coins is correct
                assert(gameS.coins == handCount * 2 + bonus);
#endif
                
#if (NOISY_TEST == 1)
                //***********
                //
                //TEST 3:  Check if # of gold coins is correct
                //
                //*************
                
                //Set all cards to gold
                printf("Test #3: Setting all cards to gold...\n");
                printf("---------------------------------------\n");
                memcpy(gameS.hand[p], golds, sizeof(int) * handCount);
                updateCoins(p, &gameS, bonus);
                printf("COINS = %d, EXPECTED = %d\n", gameS.coins, handCount * 3 + bonus);
                if(gameS.coins == (handCount * 3 + bonus)){
                    printf("Test: PASSED!\n\n");
                }
                else
                {
                    printf("Test: FAILED!\n\n");
                }
                //Check if # of gold coins is correct
                assert(gameS.coins == handCount * 3 + bonus);
#endif
                
            }
        }
    }
    
    printf("--------------------------\n");
    printf("ALL UNIT #2 TESTS PASSED! \n\n");
    
    return 0;

}
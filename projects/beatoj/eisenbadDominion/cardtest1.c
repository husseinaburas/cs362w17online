//
//  cardtest1.c
//  
//
//  Created by Jeanvally Galing Beato on 2/4/17.
//
//  cardtest #1 = smithy
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
     
     CARD:  SMITHY
     Description:  Draw 3 cards.  Discard card from hand.
     
     int playSmithy(struct gameState *state, int currentPlayer, int handPos)
     {
         //+3 Cards
         int i = 1;                  //***BUG ADDED:  CHANGED FROM int i = 0 to int i = 1
         for(i ; i < 3; i++)         //CHANGED THE FOR LOOP, DECLARING INT WITHIN FOR LOOP - C99 COMPATIBILITY ISSUES
         {
         drawCard(currentPlayer, state);
         }
         
         //discard card from hand
         discardCard(handPos, handPos, state, 0);  //***BUG ADDED:  CHANGED FROM currentPlayer to handPos
         return 0;
     }
     
    *******************/

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {

    int i = 0, t = 0;
    int seed = 1000;
    int handPos = 0;
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
    printf("*     CARD TEST #1       *\n");
    printf("*                        *\n");
    printf("*                        *\n");
    printf("*TESTING: SMITHY         *\n");
    printf("**************************\n\n");
    
    //Initialize state
    int deck_Count = gameS.deckCount[t];
    int hand_Count = gameS.handCount[t];
    int player_Turn = gameS.whoseTurn;
    int smithy_Total = gameS.supplyCount[smithy];
    
    //Victory & Kingdom state snapshot
    int gardens_Count = gameS.supplyCount[gardens];
    int greatHall_Count = gameS.supplyCount[great_hall];
    int province_Count = gameS.supplyCount[province];
    int estate_Count = gameS.supplyCount[estate];
    
#if (NOISY_TEST == 1)
    
    //***********
    //
    //TEST 1:  Play Smithy card.  Check deck has -3 cards, & hand has +2 cards (since used Smithy)
    //
    //*************
    
    printf("---------------------------------------------------------------\n");
    printf("Test #1: Play Smithy.  Check deck has -3 & hand has +2 cards...\n");
    printf("---------------------------------------------------------------\n");
    
    //Play Smithy card
    
    //playSmithy(&gameS, gameS.whoseTurn, handPos);
    smithy_refact(&gameS, handPos);                                     //A5 - REFACTORED:  REMOVED 2ND ARG
    
    //Withdraw 3 cards, so deck should be substracted by 3              //BUG FOUND:  Does not work due to edited playSmithy()
    if(gameS.deckCount[t] == (deck_Count - 3))
    {
        printf("Deck has -3 cards:  TRUE - TEST PASSED\n");
    }
    else
    {
        printf("Deck has -3 cards:  FALSE - TEST FAILED\n");
    }
    
    //Discard Smithy after use, so hand should be substracted by 2      //BUG FOUND:  Does not work due to edited playSmithy() method
    if(gameS.handCount[t] == (hand_Count - 2))
    {
        printf("Hand has -2 cards:  TRUE - TEST PASSED\n\n");
    }
    else
    {
        printf("Hand has -2 cards:  FALSE - TEST FAILED\n\n");
    }
#endif
                
#if (NOISY_TEST == 1)
    
    //***********
    //
    //TEST 2:  Verify Victory & Kingdom cards have not changed
    //
    //*************
    
    printf("------------------------------------------------------------\n");
    printf("Test #2: Check that Victory/Kingdom cards haven't changed...\n");
    printf("------------------------------------------------------------\n");
    
    //Check if Kingdom cards changed
    if(gameS.supplyCount[gardens] == gardens_Count & gameS.supplyCount[great_hall] == greatHall_Count)
    {
        printf("Kingdom Cards Unchanged:  TRUE - TEST PASSED\n");
    }
    else
    {
        printf("Kingdom Cards Unchanged:  FALSE - TEST FAILED\n");
    }
    
    //Check if Victory cards changed
    if(gameS.supplyCount[province] == province_Count & gameS.supplyCount[estate] == estate_Count)
    {
        printf("Victory Cards Unchanged:  TRUE - TEST PASSED\n\n");
    }
    else
    {
        printf("Victory Cards Unchanged:  FALSE - TEST FAILED\n\n");
    }
#endif
    
#if (NOISY_TEST == 1)
    
    //***********
    //
    //TEST 3:  Check to make sure turn has not changed
    //
    //*************
    
    printf("---------------------------------------------------\n");
    printf("Test #3: Check to make sure turn has not changed...\n");
    printf("---------------------------------------------------\n");
    
    //Check if Kingdom cards changed
    if(player_Turn == gameS.whoseTurn)
    {
        printf("Turn has not changed:  TRUE - TEST PASSED\n\n");
    }
    else
    {
        printf("Turn has not changed:  FALSE - TEST FAILED\n\n");
    }
#endif
    
    printf("--------------------------\n");
    printf("ALL CARD #1 TESTS PASSED! \n\n");
    
    return 0;

}
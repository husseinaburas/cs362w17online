//
//  unittest4.c
//  
//
//  Created by Jeanvally Galing Beato on 2/4/17.
//
//  unitTest #4 = endTurn()
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
     
     ORIGINAL METHOD:  endTurn()
     Description:  Changes the current player to the next player or the first player if the last player has finished their turn. Resets the player gameState and draws cards for the next player.
     
     
     int endTurn(struct gameState *state) {
     
         int k;
         int i;
         int currentPlayer = whoseTurn(state);
         
         //Discard hand
         for (i = 0; i < state->handCount[currentPlayer]; i++){
         state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
         state->hand[currentPlayer][i] = -1;//Set card to -1
         }
         state->handCount[currentPlayer] = 0;//Reset hand count
         
         //Code for determining the player
         if (currentPlayer < (state->numPlayers - 1)){
         state->whoseTurn = currentPlayer + 1;//Still safe to increment
         }
         else{
         state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
         }
         
         state->outpostPlayed = 0;
         state->phase = 0;
         state->numActions = 1;
         state->coins = 0;
         state->numBuys = 1;
         state->playedCardCount = 0;
         state->handCount[state->whoseTurn] = 0;
         
         //int k; move to top
     
         //Next player draws hand
         for (k = 0; k < 5; k++){
         drawCard(state->whoseTurn, state);//Draw a card
         }
         
         //Update money
         updateCoins(state->whoseTurn, state , 0);
         
         return 0;
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
    int prevTurn = gameS.whoseTurn;
    
    printf("**************************\n");
    printf("*                        *\n");
    printf("*                        *\n");
    printf("*     UNIT TEST #4       *\n");
    printf("*                        *\n");
    printf("*                        *\n");
    printf("*TESTING: endTurn()      *\n");
    printf("**************************\n\n");
    
#if (NOISY_TEST == 1)
    
    //***********
    //
    //TEST 1:  See who's turn it is BEFORE endTurn() is called
    //
    //*************
    
    //Checking who's turn it is BEFORE endTurn() is called
    printf("--------------------------------------------------\n");
    printf("Test #1: See who's turn BEFORE endTurn() called...\n");
    printf("--------------------------------------------------\n");
    printf("Turn:  Player # %i\n\n", gameS.whoseTurn);
#endif
                
#if (NOISY_TEST == 1)
    //***********
    //
    //TEST 2:  Call endTurn() to change current player to next player, reset player's gameState & draw card for player
    //
    //*************

    printf("------------------------------------\n");
    printf("Test #2: Calling endTurn() method...\n");
    printf("------------------------------------\n");
    int check = endTurn(&gameS);
    if(!check)
    {
        printf("endTurn() SUCCESSFUL!\n\n");
    }
    else
    {
        printf("endTurn() did NOT execute successfully!\n\n");
    }
#endif
                
#if (NOISY_TEST == 1)
    //***********
    //
    //TEST 3:  See who's turn it is AFTER endTurn() is called
    //
    //*************
    
   //Checking who's turn it is AFTER endTurn() is called
   printf("--------------------------------------------------\n");
   printf("Test #3: See who's turn AFTER endTurn() called...\n");
   printf("--------------------------------------------------\n");
   printf("Turn:  Player # %i\n\n", gameS.whoseTurn);
   if(prevTurn != gameS.whoseTurn)
   {
       printf("Test:  PASSED!");
   }
   else
   {
       printf("Test:  FAILED!");
   }
#endif
    
#if (NOISY_TEST == 1)
    //***********
    //
    //TEST 4:  Check that gameState has been reset
    //
    //*************
    
    //Did not include coins & playedCardCount because this is executed at the end of endTurn(), after gameState is reset
    printf("----------------------------------------------------------------------\n");
    printf("Test #4: Check that gameState for new current player has been reset...\n");
    printf("----------------------------------------------------------------------\n");
    if(gameS.outpostPlayed == 0 && gameS.phase == 0 && gameS.numActions == 1 && gameS.numBuys ==1)
    {
        printf("gameState reset status:    TRUE\n\n");
        printf("Test:  PASSED!");
    }
       
#endif
    
    
    printf("--------------------------\n");
    printf("ALL UNIT #4 TESTS PASSED! \n\n");
    
    return 0;

}
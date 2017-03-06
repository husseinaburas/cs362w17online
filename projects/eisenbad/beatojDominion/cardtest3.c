//
//  cardtest3.c
//  
//
//  Created by Jeanvally Galing Beato on 2/4/17.
//
//  cardtest #3 = councilRoom
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
     
     CARD:  COUNCIL ROOM
     Description:  Draw 4 cards, increase buys by 1, each other player draws a card, put played card in discard pile.
     
     int playCouncil_Room(struct gameState *state, int currentPlayer, int handPos)
     {
         //+4 Cards
         int i = 0;
         for (i ; i < 4; i++)
         {
         drawCard(currentPlayer, state);
         }
         
         //+1 Buy
         state->numBuys++;
         
         //Each other player draws a card
         for (i = 0; i < state->numPlayers; i++)
         {
         if ( i != currentPlayer )
         {
         drawCard(i, state);
         }
         }
         
         //put played card in played card pile
         discardCard(handPos, currentPlayer, state, 0);
         
         return 0;
     }
     
    *******************/


// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {

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
    printf("*     CARD TEST #3       *\n");
    printf("*                        *\n");
    printf("*                        *\n");
    printf("*TESTING: COUNCIL ROOM   *\n");
    printf("**************************\n\n");
    
    //Initialize state
    int deck1Prev, deck2Prev;
    int deck1New, deck2New;
    int buyNumPrev = gameS.numBuys;
    int buyNumNew;
    
    //Save old deck state
    deck1Prev = gameS.deckCount[0];
    deck2Prev = gameS.deckCount[1];
    
    //PLAY COUNCIL ROOM CARD
    playCouncil_Room(&gameS, gameS.whoseTurn, handPos);
    
    deck1New = gameS.deckCount[0];      //Save new deck state
    deck2New = gameS.deckCount[1];      //Save new deck state
    buyNumNew = gameS.numBuys;          //Save new num_buys
    
#if (NOISY_TEST == 1)
    
    //***********
    //
    //TEST 1:  Player 1 Deck should have -4 less cards
    //
    //*************
    
    printf("---------------------------------------------------\n");
    printf("Test #1: Player 1 deck should have -4 less cards...\n");
    printf("---------------------------------------------------\n");
    
    //After Council Room card is played, deck should have -4 cards
    if(deck1New == (deck1Prev - 4))
    {
        printf("Player 1 Deck has -4 cards:  TRUE - TEST PASSED\n\n");
    }
    else
    {
        printf("Player 1 Deck has -4 cards:  FALSE - TEST FAILED\n\n");
    }
#endif
    
#if (NOISY_TEST == 1)
    
    //***********
    //
    //TEST 2:  Player 2 Deck should have -1 less cards
    //
    //*************
    
    printf("---------------------------------------------------\n");
    printf("Test #2: Player 2 deck should have -1 less cards...\n");
    printf("---------------------------------------------------\n");
    
    //After Council Room card is played, deck should have -4 cards
    if(deck2New == (deck2Prev - 1))
    {
        printf("Player 1 Deck has -1 cards:  TRUE - TEST PASSED\n\n");
    }
    else
    {
        printf("Player 2 Deck has -1 cards:  FALSE - TEST FAILED\n\n");
    }
#endif
    
#if (NOISY_TEST == 1)
    
    //***********
    //
    //TEST 3:  Check to see if buys increased by +1
    //
    //*************
    
    printf("------------------------------------------------\n");
    printf("Test #3: Check to see if buys increased by +1...\n");
    printf("------------------------------------------------\n");
    
    //After Council Room card is played, deck should have -4 cards
    if(buyNumNew == (buyNumPrev + 1))
    {
        printf("Num Buys increased by +1:  TRUE - TEST PASSED\n\n");
    }
    else
    {
        printf("Num Buys increased by +1:  FALSE - TEST FAILED\n\n");
    }
#endif
    
    printf("--------------------------\n");
    printf("ALL CARD #3 TESTS PASSED! \n\n");
    
    return 0;
    
}

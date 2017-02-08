//
//  cardtest2.c
//  
//
//  Created by Jeanvally Galing Beato on 2/4/17.
//
//  cardtest #2 = adventurer
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
     
     CARD:  ADVENTURER
     Description:  Reveal cards from your deck until you reveal 2 Treasure cards. Put those Treasure cards in your hand and discard the other revealed cards.
     
     int playAdventurer(int drawntreasure, struct gameState *state, int currentPlayer, int cardDrawn, int *temphand, int z)
    {
     
         while(drawntreasure<2){
            if (state->deckCount[currentPlayer] <1)
            {  //if the deck is empty we need to shuffle discard and add to deck
                shuffle(currentPlayer, state);
            }
     
            drawCard(currentPlayer, state);
            cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];     //top card of hand is most recently drawn card.
            if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
                drawntreasure++;
            else
            {
                temphand[z]=cardDrawn;
                state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
                z++;
            }
         }
         
         while(z-2>=0){              //***BUG ADDED:  CHANGED FROM Z-1 TO Z-2
            state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
            z=z-1;
         }
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
    printf("*     CARD TEST #2       *\n");
    printf("*                        *\n");
    printf("*                        *\n");
    printf("*TESTING: ADVENTURER     *\n");
    printf("**************************\n\n");
    
    //Initialize state
    int deck_Count = gameS.deckCount[t];
    int hand_Count = gameS.handCount[t];
    int player_Turn = gameS.whoseTurn;
    int cardDrawn;
    int *temp;
    
    //PLAY ADVENTURER CARD
    playAdventurer(0, &gameS, player_Turn, cardDrawn, temp ,0);
    
#if (NOISY_TEST == 1)
    
    //***********
    //
    //TEST 1:  Deck should have -2 less cards
    //
    //*************
    
    printf("------------------------------------------\n");
    printf("Test #1: Deck should have -2 less cards...\n");
    printf("------------------------------------------\n");
    
    //After Adventurer card is played, deck should have at least 2 less cards
    if(gameS.deckCount[t] <= (deck_Count - 2))
    {
        printf("Deck has -2 cards:  TRUE - TEST PASSED\n\n");
    }
    else
    {
        printf("Deck has -2 cards:  FALSE - TEST FAILED\n\n");
    }
#endif
    
#if (NOISY_TEST == 1)
    
    //***********
    //
    //TEST 2:  Hand should have +2 less cards
    //
    //*************
    
    printf("------------------------------------------\n");
    printf("Test #1: Hand should have +2 more cards...\n");
    printf("------------------------------------------\n");
    
    //After Adventurer card is played, deck should have at least 2 less cards
    if(gameS.deckCount[t] <= (deck_Count - 2))
    {
        printf("Hand has +2 cards:  TRUE - TEST PASSED\n\n");
    }
    else
    {
        printf("Hand has +2 cards:  FALSE - TEST FAILED\n\n");
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
    printf("ALL CARD #2 TESTS PASSED! \n\n");
    
    return 0;
    
}

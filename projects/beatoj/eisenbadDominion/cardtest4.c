//
//  cardtest4.c
//  
//
//  Created by Jeanvally Galing Beato on 2/4/17.
//
//  cardtest #4 = steward
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

    CARD:  STEWARD
    Description:  Draw 2 cards from deck or add 2 coins, otherwise trash 2 hand cards.  Discard steward card from hand.


        case steward:
            if (choice1 == 1)
            {
                //+2 cards
                drawCard(currentPlayer, state);
                drawCard(currentPlayer, state);
            }
            else if (choice1 == 2)
            {
                //+2 coins
                state->coins = state->coins + 2;
            }
            else
            {
                //trash 2 cards in hand
                discardCard(choice2, currentPlayer, state, 1);
                discardCard(choice3, currentPlayer, state, 1);
            }

            //discard card from hand
            discardCard(handPos, currentPlayer, state, 0);
            return 0;

******************/


// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    
    int seed = 1000;
    int handPos = 0;
    int numPlayer = 2;
    int *bonus = 0;
    int current_player = 0;
    struct gameState gameS1;
    struct gameState gameS2;
    struct gameState gameS3;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    
    printf("**************************\n");
    printf("*                        *\n");
    printf("*                        *\n");
    printf("*     CARD TEST #4       *\n");
    printf("*                        *\n");
    printf("*                        *\n");
    printf("*TESTING: STEWARD        *\n");
    printf("**************************\n\n");
    
    
#if (NOISY_TEST == 1)
    
    printf("---------------------------------------------------\n");
    printf("Test #1: Player 1 deck should have -2 less cards...\n");
    printf("---------------------------------------------------\n");
    
    //Clear game state
    memset(&gameS1, 23, sizeof(struct gameState));
    //Initialize new game
    int true = initializeGame(numPlayer, k, seed, &gameS1);
    assert(true == 0);
    
    //Save old state deck, hand, numActions
    int deck1Prev = gameS1.deckCount[current_player];
    int hand1Prev = gameS1.handCount[current_player];
    int coins1Prev = gameS1.coins;
    printf("PREVIOUS:  Deck %i, Hand %i, Coins %i\n", deck1Prev, hand1Prev, coins1Prev);
    
    //PLAY STEWARD CARD
    cardEffect(steward, 1, 0, 0, &gameS1, handPos, &bonus);             //A5 - REFACTORED:  Didn't have to refactor anything, this is part of original switch statement in cardEffect.  There is not a separate function outside of the switch statement that was refactored.  
    
    //TESTING ONLY
    //drawCard(current_player, &gameS);
    //drawCard(current_player, &gameS);
    //discardCard(handPos, current_player, &gameS, 0);
    
    int deck1New = gameS1.deckCount[current_player];          //Save new deck state
    int coins1New = gameS1.coins;                              //Save new numActions
    int hand1New = gameS1.handCount[current_player];           //Save new hand state
    
    //TESTING ONLY
    printf("AFTER:  Deck %i, Hand %i, Coins %i\n", deck1New, hand1New, coins1New);
    
    //***********
    //
    //TEST 1:  Player 1 Deck should have -1 less cards
    //
    //*************
    
    
    //After steward card is played, deck should have -2 cards
    if(deck1New == (deck1Prev - 2))
    {
        printf("Player 1 Deck has -2 cards:  TRUE - TEST PASSED\n\n");
    }
    else
    {
        printf("Player 1 Deck has -2 cards:  FALSE - TEST FAILED\n\n");
    }
#endif

#if (NOISY_TEST == 1)
    
    printf("--------------------------------------------\n");
    printf("Test #2: coins should increase by +2...\n");
    printf("--------------------------------------------\n");
    
    //Clear game state
    memset(&gameS2, 23, sizeof(struct gameState));
    //Initialize new game
    true = initializeGame(numPlayer, k, seed, &gameS2);
    assert(true == 0);
    
    //Save old state deck, hand, numActions
    int deck2Prev = gameS2.deckCount[current_player];
    int hand2Prev = gameS2.handCount[current_player];
    int coins2Prev = gameS2.coins;
    printf("PREVIOUS:  Deck %i, Hand %i, Coins %i\n", deck2Prev, hand2Prev, coins2Prev);
    
    //PLAY STEWARD CARD
    cardEffect(steward, 2, 0, 0, &gameS2, handPos, &bonus);
    
    //TESTING ONLY
    //drawCard(current_player, &gameS);
    //drawCard(current_player, &gameS);
    //discardCard(handPos, current_player, &gameS, 0);
    
    int deck2New = gameS2.deckCount[current_player];          //Save new deck state
    int coins2New = gameS2.coins;                              //Save new numActions
    int hand2New = gameS2.handCount[current_player];           //Save new hand state
    
    //TESTING ONLY
    printf("AFTER:  Deck %i, Hand %i, Coins %i\n", deck2New, hand2New, coins2New);

    
    //***********
    //
    //TEST 2:  numActions should increase by +1
    //
    //*************
    
    //After steward is played, coins should increase by 2
    if(coins2New == (coins2Prev + 2))
    {
        printf("Coins Increased by +2:  TRUE - TEST PASSED\n\n");
    }
    else
    {
        printf("Coins Increased by +2:  FALSE - TEST FAILED\n\n");
    }
#endif
    
#if (NOISY_TEST == 1)
    
    printf("-----------------------------------------\n");
    printf("Test #3: Hand should decrease by -3...\n");
    printf("-----------------------------------------\n");
    
    //Clear game state
    memset(&gameS3, 23, sizeof(struct gameState));
    //Initialize new game
    true = initializeGame(numPlayer, k, seed, &gameS3);
    assert(true == 0);
    
    //Save old state deck, hand, numActions
    int deck3Prev = gameS3.deckCount[current_player];
    int hand3Prev = gameS3.handCount[current_player];
    int coins3Prev = gameS3.coins;
    printf("PREVIOUS:  Deck %i, Hand %i, Coins %i\n", deck3Prev, hand3Prev, coins3Prev);
    
    //PLAY STEWARD CARD
    cardEffect(steward, 3, 0, 0, &gameS3, handPos, &bonus);
    
    //TESTING ONLY
    //drawCard(current_player, &gameS);
    //drawCard(current_player, &gameS);
    //discardCard(handPos, current_player, &gameS, 0);
    
    int deck3New = gameS3.deckCount[current_player];          //Save new deck state
    int coins3New = gameS3.coins;                              //Save new numActions
    int hand3New = gameS3.handCount[current_player];           //Save new hand state
    
    //TESTING ONLY
    printf("AFTER:  Deck %i, Hand %i, Coins %i\n", deck3New, hand3New, coins3New);
    
    //***********
    //
    //TEST 3:  Hand should decrease by -2
    //
    //*************
    
    //After great_hall card is played, hand should have -1 cards
    if(hand3New == (hand3Prev - 3))
    {
        printf("Hand decreased by -3:  TRUE - TEST PASSED\n\n");
    }
    else
    {
        printf("Hand decreased by -3:  FALSE - TEST FAILED\n\n");
    }
#endif
    
    printf("--------------------------\n");
    printf("ALL CARD #4 TESTS PASSED! \n\n");
    
    return 0;
    
}



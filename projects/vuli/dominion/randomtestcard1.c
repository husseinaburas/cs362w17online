/* randomtestcard1.c
Card tested: Village

General requirements:
-- Successful execution (return value 0)
-- Decreases Hand+Deck+Discard count by 1
-- Increases playedCardCount by 1
-- Adds card previously at handPos to playedCards
-- Removes card previously at handPos from hand
    Caveat: A new card might have been drawn that is the same as card previously 
        at handPos
-- Does not change game state except for current player
-- Does not change Hand+Deck+Discard for current player, except removing played card

Specific requirements:
-- If Deck+Discard previously has 1+ cards:
    +) Does not change Hand count (1 card drawn - 1 card played)
    +) Decreases Deck+Discard count by 1
    +) 1 card is added to Hand and 1 card is removed from Deck+Discard.
    Caveat: If card removed from Deck+Discard is same as played card, Hand
    would look the same as before
-- If Deck+Discard previously has no card:
    +) Hand count decreased by 1 (- 1 card played)
    +) Deck+Discard count unchanged
    +) No card is added to Hand and no card is removed from Deck+Discard
-- The card added to hand is the card removed from Deck+Discard
-- Increases number of actions by 2
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tests_helpers.h"

#define CARD_NAME "Village"


/*********************************************************************
* testCardVillage()
* Executes the following tests for Village
* -- All general requirements
* -- If Deck+Discard previously has 1+ cards:
*    +) Does not change Hand count (1 card drawn - 1 card played)
*    +) Decreases Deck+Discard count by 1
*    +) 1 card is added to Hand and 1 card is removed from Deck+Discard
* -- If Deck+Discard previously has no card:
*    +) Hand count decreased by 1 (- 1 card played)
*    +) Deck+Discard count unchanged
*    +) No card is added to Hand and no card is removed from Deck+Discard
* -- The card added to hand is the card removed from Deck+Discard
* -- Increases number of actions by 2
*********************************************************************/

void testCardVillage(int* caseCount, int* testCount, int* r_main,
    int card, int choice1, int choice2, int choice3, int handPos, int* bonus,
    struct gameState* G, struct gameState* preG)
{
    struct gameState G_mod, preG_mod;
    int player = G->whoseTurn;
    int count1, count2, i, j;
    int G_DeckDiscard[2*MAX_DECK], preG_DeckDiscard[2*MAX_DECK];
    int G_DeckDiscardCount, preG_DeckDiscardCount;

    char casename[500];
    int playedCardCrossed = -1;
    int playedCardsRemovedFromDeckDiscard = 0;  // is played card (village in this case) removed/drawn from Deck+Discard


    /*-------------------------------------------------------------------------*/
    (*caseCount)++;
    sprintf(casename, "Hand count=%d, Deck count=%d, Discard count=%d, handPos=%d", G->handCount[player], G->deckCount[player], G->discardCount[player], handPos);

    testCardGeneralRequirements(caseCount, casename, testCount, r_main,
        card, choice1, choice2, choice3, handPos, bonus,
        G, preG);

    memcpy(&G_mod, G, sizeof(struct gameState));  // make a copy of G & preG that can be modified
    memcpy(&preG_mod, preG, sizeof(struct gameState));


    /*-------------------------------------------------------------------------*/
    /* If Deck + Discard previously has 1+ cards */
    if (preG->deckCount[player] + preG->discardCount[player] >= 1) {
        printf("---------CASE %d: %s -- TEST %d: Hand count unchanged\n", *caseCount, casename, ++(*testCount));
        count1 = preG->handCount[player];
        count2 = G->handCount[player];
        if (NOISY_TEST) printf("Hand count before: %d\nHand count after: %d\n", count1, count2);
        asserttrue(count2==count1, r_main);

        /*********/
        printf("---------CASE %d: %s -- TEST %d: Deck+Discard count decreased by 1\n", *caseCount, casename, ++(*testCount));
        count1 = preG->deckCount[player] + preG->discardCount[player];
        count2 = G->deckCount[player] + G->discardCount[player];
        if (NOISY_TEST) printf("Deck+Discard count before: %d\nDeck+Discard count after: %d\n", count1, count2);
        asserttrue(count2==count1-1, r_main);

        /*********/
        printf("---------CASE %d: %s -- TEST %d: 1 card removed from Deck+Discard\n", *caseCount, casename, ++(*testCount));    
        // Copy Deck+Discards before execution to preG_DeckDiscard
        preG_DeckDiscardCount = 0;
        for (i=0; i<preG_mod.deckCount[player]; i++) {
            preG_DeckDiscard[preG_DeckDiscardCount] = preG_mod.deck[player][i];
            preG_DeckDiscardCount++;
        }
        for (i=0; i<preG_mod.discardCount[player]; i++) {
            preG_DeckDiscard[preG_DeckDiscardCount] = preG_mod.discard[player][i];
            preG_DeckDiscardCount++;
        }
        // Copy Deck+Discards after execution to G_DeckDiscard
        G_DeckDiscardCount = 0;
        for (i=0; i<G_mod.deckCount[player]; i++) {
            G_DeckDiscard[G_DeckDiscardCount] = G_mod.deck[player][i];
            G_DeckDiscardCount++;
        }
        for (i=0; i<G_mod.discardCount[player]; i++) {
            G_DeckDiscard[G_DeckDiscardCount] = G_mod.discard[player][i];
            G_DeckDiscardCount++;
        }
        // What cards are removed from Deck+Discards?
        for (i=0; i<preG_DeckDiscardCount; i++) {
            for (j=0; j<G_DeckDiscardCount; j++) {
                if (preG_DeckDiscard[i] == G_DeckDiscard[j] && preG_DeckDiscard[i] != -1) {
                    preG_DeckDiscard[i] = -1;
                    G_DeckDiscard[j] = -1;
                    break;
                }
            }
        }
        // Added cards are those uncrossed in preG_DeckDiscard
        count2 = 0;
        for (i=0; i<preG_DeckDiscardCount; i++) {
            if (preG_DeckDiscard[i] > -1) {
                count2++;
                if (NOISY_TEST) printf("Card removed from Deck+Discard #%d: %s\n", count2, getCardName(preG_DeckDiscard[i]));
                if (preG_DeckDiscard[i] == card) {
                    playedCardsRemovedFromDeckDiscard++;
                }
            }
        }
        asserttrue(count2==1, r_main);        


        /*********/
        printf("---------CASE %d: %s -- TEST %d: 1 new card added to Hand\n", *caseCount, casename, ++(*testCount));
        assert(G->handCount[player] >= 1);  // hand should have 1+ cards
        // What cards are added to Hand?
        for (i=0; i<G_mod.handCount[player]; i++) {
            if (G_mod.hand[player][i] == card && playedCardCrossed < 0 && playedCardsRemovedFromDeckDiscard == 0) {
                G_mod.hand[player][i] = -1;  // first Played card
                playedCardCrossed = 1;
            }
            for (j=0; j<preG_mod.handCount[player]; j++) {
                if (G_mod.hand[player][i] == preG_mod.hand[player][j] && G_mod.hand[player][i] != -1) {
                    G_mod.hand[player][i] = -1;  // cross out cards that appear in both G_mod.hand and preG_mod.hand
                    preG_mod.hand[player][j] = -1;
                    break;
                }
            }
        }
        // Caveat: If at least one played Card was removed from Deck+Discard, Hand should be the same as before
        if (playedCardsRemovedFromDeckDiscard > 0) {
            for (i=0; i<G_mod.handCount[player]; i++) {
                if (G_mod.hand[player][i] == -1) {
                    G_mod.hand[player][i] = card;
                    break;
                }
            }
        }

        // Added cards are those uncrossed in G_mod.hand
        count1 = 0;
        for (i=0; i<G_mod.handCount[player]; i++) {
            if (G_mod.hand[player][i] > -1) {
                count1++;  // how many new cards in Hand?
                if (NOISY_TEST) printf("Card added to Hand #%d: %s\n", count1, getCardName(G_mod.hand[player][i]));
            }
        }
        asserttrue(count1==1, r_main);

    }



    /*-------------------------------------------------------------------------*/
    /* If Deck + Discard previously has 0 cards */
    else if (preG->deckCount[player] + preG->discardCount[player] == 0) {
        printf("---------CASE %d: %s -- TEST %d: Hand count decreased by 1\n", *caseCount, casename, ++(*testCount));
        count1 = preG->handCount[player];
        count2 = G->handCount[player];
        if (NOISY_TEST) printf("Hand count before: %d\nHand count after: %d\n", count1, count2);
        asserttrue(count2==count1-1, r_main);

        /*********/
        printf("---------CASE %d: %s -- TEST %d: Deck+Discard count unchanged\n", *caseCount, casename, ++(*testCount));
        count1 = preG->deckCount[player] + preG->discardCount[player];
        count2 = G->deckCount[player] + G->discardCount[player];
        if (NOISY_TEST) printf("Deck+Discard count before: %d\nDeck+Discard count after: %d\n", count1, count2);
        asserttrue(count2==count1, r_main);

        /*********/
        printf("---------CASE %d: %s -- TEST %d: No card removed from Deck+Discard\n", *caseCount, casename, ++(*testCount));    
        // Copy Deck+Discards before execution to preG_DeckDiscard
        preG_DeckDiscardCount = 0;
        for (i=0; i<preG_mod.deckCount[player]; i++) {
            preG_DeckDiscard[preG_DeckDiscardCount] = preG_mod.deck[player][i];
            preG_DeckDiscardCount++;
        }
        for (i=0; i<preG_mod.discardCount[player]; i++) {
            preG_DeckDiscard[preG_DeckDiscardCount] = preG_mod.discard[player][i];
            preG_DeckDiscardCount++;
        }
        // Copy Deck+Discards after execution to G_DeckDiscard
        G_DeckDiscardCount = 0;
        for (i=0; i<G_mod.deckCount[player]; i++) {
            G_DeckDiscard[G_DeckDiscardCount] = G_mod.deck[player][i];
            G_DeckDiscardCount++;
        }
        for (i=0; i<G_mod.discardCount[player]; i++) {
            G_DeckDiscard[G_DeckDiscardCount] = G_mod.discard[player][i];
            G_DeckDiscardCount++;
        }
        // What cards are removed from Deck+Discards?
        for (i=0; i<preG_DeckDiscardCount; i++) {
            for (j=0; j<G_DeckDiscardCount; j++) {
                if (preG_DeckDiscard[i] == G_DeckDiscard[j] && preG_DeckDiscard[i] != -1) {
                    preG_DeckDiscard[i] = -1;
                    G_DeckDiscard[j] = -1;
                    break;
                }
            }
        }
        // Added cards are those uncrossed in preG_DeckDiscard
        count2 = 0;
        for (i=0; i<preG_DeckDiscardCount; i++) {
            if (preG_DeckDiscard[i] > -1) {
                count2++;
                if (NOISY_TEST) printf("Card removed from Deck+Discard #%d: %s\n", count2, getCardName(preG_DeckDiscard[i]));
                if (preG_DeckDiscard[i] == card) {
                    playedCardsRemovedFromDeckDiscard++;
                }
            }
        }
        asserttrue(count2==0, r_main);        


        /*********/
        printf("---------CASE %d: %s -- TEST %d: No new card added to Hand\n", *caseCount, casename, ++(*testCount));
        // What cards are added to Hand?
        for (i=0; i<G_mod.handCount[player]; i++) {
            if (G_mod.hand[player][i] == card && playedCardCrossed < 0 && playedCardsRemovedFromDeckDiscard == 0) {
                G_mod.hand[player][i] = -1;  // first Played card
                playedCardCrossed = 1;
            }
            for (j=0; j<preG_mod.handCount[player]; j++) {
                if (G_mod.hand[player][i] == preG_mod.hand[player][j] && G_mod.hand[player][i] != -1) {
                    G_mod.hand[player][i] = -1;  // cross out cards that appear in both G_mod.hand and preG_mod.hand
                    preG_mod.hand[player][j] = -1;
                    break;
                }
            }
        }
        // Caveat: If at least one played Card was removed from Deck+Discard, Hand should be the same as before
        if (playedCardsRemovedFromDeckDiscard > 0) {
            for (i=0; i<G_mod.handCount[player]; i++) {
                if (G_mod.hand[player][i] == -1) {
                    G_mod.hand[player][i] = card;
                    break;
                }
            }
        }

        // Added cards are those uncrossed in G_mod.hand
        count1 = 0;
        for (i=0; i<G_mod.handCount[player]; i++) {
            if (G_mod.hand[player][i] > -1) {
                count1++;  // how many new cards in Hand?
                if (NOISY_TEST) printf("Card added to Hand #%d: %s\n", count1, getCardName(G_mod.hand[player][i]));
            }
        }
        asserttrue(count1==0, r_main);

    }


    /*-------------------------------------------------------------------------*/
    printf("---------CASE %d: %s -- TEST %d: Cards added to Hand were the same as cards removed from Deck+Discard\n", *caseCount, casename, ++(*testCount));
    // What cards added to Hand are not removed from Deck+Discard?
    for (i=0; i<G_mod.handCount[player]; i++) {
        for (j=0; j<preG_DeckDiscardCount; j++) {
            if (G_mod.hand[player][i] == preG_DeckDiscard[j] && G_mod.hand[player][i] != -1) {
                G_mod.hand[player][i] = -1;
                preG_DeckDiscard[j] = -1;
                count1--;
                count2--;
            }
        }
    }
    // What cards added to Hand are not removed from Deck+Discard?
    for (j=0; j<preG_DeckDiscardCount; j++) {
        for (i=0; i<G_mod.handCount[player]; i++) {
             if (G_mod.hand[player][i] == preG_DeckDiscard[j] && G_mod.hand[player][i] != -1) {
                G_mod.hand[player][i] = -1;
                preG_DeckDiscard[j] = -1;
                count1--;
                count2--;
            }           
        }
    }
    if (NOISY_TEST) {
        if (count1>0) {
            printf("Cards added to Hand but not removed from Deck+Discard: ");
            for (i=0; i<G_mod.handCount[player]; i++) {
                if (G_mod.hand[player][i] > -1) printf("%s\t", getCardName(G_mod.hand[player][i]));
            }
            printf("\n");
        }
        if (count2>0) {
            printf("Cards removed from Deck+Discard but not added to Hand: ");
            for (j=0; j<preG_DeckDiscardCount; j++) {
                if (preG_DeckDiscard[j] > -1) printf("%s\t", getCardName(preG_DeckDiscard[j]));
            }
            printf("\n");
        }
    }
    asserttrue(count1==0 && count2==0, r_main);


    /*-------------------------------------------------------------------------*/
    printf("---------CASE %d: %s -- TEST %d: Number of actions increased by 2\n", *caseCount, casename, ++(*testCount));
    count1 = preG->numActions;
    count2 = G->numActions;
    if (NOISY_TEST) printf("Action count before: %d\nAction count after: %d\n", count1, count2);
    asserttrue(count2==count1+2, r_main);

}





/*********************************************************************/
/* Main */
int main(int argc, char* argv[]) {
    struct gameState G, preG;
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;  // dummy parameters; won't be used for this card
    int seed, player, handPos, i, j;
    int testCount = 0, caseCount = 0;
    int card = village;
    int r_main = 0;

    /* Get seed from cmd line args to start random number generator */
    if (argc > 1) {
        seed = atoi(argv[1]);      
    } else {
        printf("Format: %s [seed]\n", argv[0]);
        exit(1);
    }
    SelectStream(2);
    PutSeed(seed);


/*-------------------------------------------------------------------------*/
    printf("**********************************************************\n");
    printf("BEGIN random test %s\n", CARD_NAME);

    /* Perform NUM_RANDOM_TESTS random tests */
    for (i=0; i<NUM_RANDOM_TESTS; i++) {
        /* Construct game state */
        G = randomGameState(1, 0, 0);
        player = G.whoseTurn;
        handPos = randomInRange(G.handCount[player]-1);
        G.hand[player][handPos] = card;  

        /* Copy game state to preG */
        memcpy(&preG, &G, sizeof(struct gameState));

        /*********/
        testCardVillage(&caseCount, &testCount, &r_main,
            card, choice1, choice2, choice3, handPos, &bonus,
            &G, &preG);       
    }

    /* Perform NUM_RANDOM_TESTS random tests where Deck is empty */
    for (i=0; i<NUM_RANDOM_TESTS; i++) {
        /* Construct game state */
        G = randomGameState(1, 0, 0);
        player = G.whoseTurn;
        handPos = randomInRange(G.handCount[player]-1);
        G.hand[player][handPos] = card;  
        
        for (j=0; j<MAX_DECK; j++) G.deck[player][j] = -1;
        G.deckCount[player] = 0;

        /* Copy game state to preG */
        memcpy(&preG, &G, sizeof(struct gameState));

        /*********/
        testCardVillage(&caseCount, &testCount, &r_main,
            card, choice1, choice2, choice3, handPos, &bonus,
            &G, &preG);       
    }

    /* Perform NUM_RANDOM_TESTS random tests where Discard is empty */
    for (i=0; i<NUM_RANDOM_TESTS; i++) {
        /* Construct game state */
        G = randomGameState(1, 0, 0);
        player = G.whoseTurn;
        handPos = randomInRange(G.handCount[player]-1);
        G.hand[player][handPos] = card;  
        
        for (j=0; j<MAX_DECK; j++) G.discard[player][j] = -1;
        G.discardCount[player] = 0;

        /* Copy game state to preG */
        memcpy(&preG, &G, sizeof(struct gameState));

        /*********/
        testCardVillage(&caseCount, &testCount, &r_main,
            card, choice1, choice2, choice3, handPos, &bonus,
            &G, &preG);       
    }

    /* Perform NUM_RANDOM_TESTS random tests where Deck and Discard both empty */
    for (i=0; i<NUM_RANDOM_TESTS; i++) {
        /* Construct game state */
        G = randomGameState(1, 0, 0);
        player = G.whoseTurn;
        handPos = randomInRange(G.handCount[player]-1);
        G.hand[player][handPos] = card;  

        for (j=0; j<MAX_DECK; j++) G.deck[player][j] = -1;
        G.deckCount[player] = 0;        
        for (j=0; j<MAX_DECK; j++) G.discard[player][j] = -1;
        G.discardCount[player] = 0;

        /* Copy game state to preG */
        memcpy(&preG, &G, sizeof(struct gameState));

        /*********/
        testCardVillage(&caseCount, &testCount, &r_main,
            card, choice1, choice2, choice3, handPos, &bonus,
            &G, &preG);       
    }


    /* Perform NUM_RANDOM_TESTS random tests where Hand only has card being played */
    for (i=0; i<NUM_RANDOM_TESTS; i++) {
        /* Construct game state */
        G = randomGameState(1, 0, 0);
        player = G.whoseTurn;
        for (j=0; j<MAX_HAND; j++) G.hand[player][j] = -1;
        G.hand[player][0] = card;
        G.handCount[player] = 1;        
        handPos = 0;

        /* Copy game state to preG */
        memcpy(&preG, &G, sizeof(struct gameState));

        /*********/
        testCardVillage(&caseCount, &testCount, &r_main,
            card, choice1, choice2, choice3, handPos, &bonus,
            &G, &preG);       
    }



/*-------------------------------------------------------------------------*/
    printf("---------\n");
    printf("Card %s passed %d/%d tests.\n", CARD_NAME, r_main, testCount);
    printf("END random test %s\n", CARD_NAME);
    printf("**********************************************************\n\n");

    return 0;
}


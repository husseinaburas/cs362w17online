/* randomtestadventurer.c
Card tested: Adventurer

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
-- If Deck+Discard previously has 2+ Treasure:
    +) Hand count increased by 1 (2 Treasure drawn - 1 card played)
    +) Deck+Discard count decreased by 2
    +) 2 new Treasure added to Hand
    +) 2 Treasure removed from Deck+Discard
-- If Deck+Discard previously has 1 Treasure:
    +) Hand count unchanged (1 Treasure drawn - 1 card played)
    +) Deck+Discard count decreased by 1
    +) 1 new Treasure added to Hand
    +) 1 Treasure removed from Deck+Discard
-- If Deck+Discard previously has 0 Treasure:
    +) Hand count decreased by 1 (- 1 card played)
    +) Deck+Discard count unchanged
    +) Hand unchanged except removing played card
    +) Deck+Discard unchanged
-- The cards added to hand are the same as the cards removed from Deck+Discard

The following cases are tests:
-- 2+ Treasure in Deck, no Treasure in Discard
-- No Treasure in Deck, 2 Treasure in Discard
-- 1 Treasure in Deck, 1 Treasure in Discard
-- 1 Treasure in Deck, no Treasure in Discard
-- No Treasure in Deck, 1 Treasure in Discard
-- No Treasure in Deck, no Treasure in Discard

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

#define CARD_NAME "Adventurer"


/*********************************************************************
* testCardAdventurer()
*********************************************************************/

void testCardAdventurer(int* caseCount, int* testCount, int* r_main,
    int card, int choice1, int choice2, int choice3, int handPos, int* bonus,
    struct gameState* G, struct gameState* preG)
{

    struct gameState G_mod, preG_mod;
    int player = G->whoseTurn;
    int count1, count2, i, j, numTreasureDeck, numTreasureDiscard, count1_Treasure, count2_Treasure;
    int G_DeckDiscard[2*MAX_DECK], preG_DeckDiscard[2*MAX_DECK];
    int G_DeckDiscardCount, preG_DeckDiscardCount;

    char casename[500];
    int playedCardCrossed = -1;
    int playedCardsRemovedFromDeckDiscard = 0;  // is played card removed/drawn from Deck+Discard


    /*-------------------------------------------------------------------------*/
    (*caseCount)++;
    numTreasureDeck = getNumCardsDeck(player, copper, G) + getNumCardsDeck(player, silver, G) + getNumCardsDeck(player, gold, G);
    numTreasureDiscard = getNumCardsDiscard(player, copper, G) + getNumCardsDiscard(player, silver, G) + getNumCardsDiscard(player, gold, G);
    sprintf(casename, "Hand count=%d, Deck count=%d, Discard count=%d, Treasure count in Deck=%d,  Treasure count in Discard=%d", G->handCount[player], G->deckCount[player], G->discardCount[player], numTreasureDeck, numTreasureDiscard);

    testCardGeneralRequirements(caseCount, casename, testCount, r_main,
        card, choice1, choice2, choice3, handPos, bonus,
        G, preG);

    memcpy(&G_mod, G, sizeof(struct gameState));  // make a copy of G & preG that can be modified
    memcpy(&preG_mod, preG, sizeof(struct gameState));


    /*-------------------------------------------------------------------------*/
    /* If Deck + Discard previously has 2+ Treasure */
    if (numTreasureDeck + numTreasureDiscard >= 2) {
        printf("---------CASE %d: %s -- TEST %d: Hand count increased by 1\n", *caseCount, casename, ++(*testCount));
        count1 = preG->handCount[player];
        count2 = G->handCount[player];
        if (NOISY_TEST) printf("Hand count before: %d\nHand count after: %d\n", count1, count2);
        asserttrue(count2==count1+1, r_main);

        /*********/
        printf("---------CASE %d: %s -- TEST %d: Deck+Discard count decreased by 2\n", *caseCount, casename, ++(*testCount));
        count1 = preG->deckCount[player] + preG->discardCount[player];
        count2 = G->deckCount[player] + G->discardCount[player];
        if (NOISY_TEST) printf("Deck+Discard count before: %d\nDeck+Discard count after: %d\n", count1, count2);
        asserttrue(count2==count1-2, r_main);

        /*********/
        printf("---------CASE %d: %s -- TEST %d: 2 Treasure removed from Deck+Discard\n", *caseCount, casename, ++(*testCount));    
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
        count2_Treasure = 0;
        for (i=0; i<preG_DeckDiscardCount; i++) {
            if (preG_DeckDiscard[i] > -1) {
                count2++;
                if (preG_DeckDiscard[i] == copper || preG_DeckDiscard[i] == silver || preG_DeckDiscard[i] == gold ) {
                    count2_Treasure++;
                }
                if (NOISY_TEST) printf("Card removed from Deck+Discard #%d: %s\n", count2, getCardName(preG_DeckDiscard[i]));
                if (preG_DeckDiscard[i] == card) {
                    playedCardsRemovedFromDeckDiscard++;
                }
            }
        }
        asserttrue(count2==2 && count2_Treasure==2, r_main);        


        /*********/
        printf("---------CASE %d: %s -- TEST %d: 2 new Treasure added to Hand\n", *caseCount, casename, ++(*testCount));
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
        count1_Treasure = 0;
        for (i=0; i<G_mod.handCount[player]; i++) {
            if (G_mod.hand[player][i] > -1) {
                count1++;  // how many new cards in Hand?
                if (G_mod.hand[player][i] == copper || G_mod.hand[player][i] == silver || G_mod.hand[player][i] == gold) {
                    count1_Treasure++;
                }
                if (NOISY_TEST) printf("Card added to Hand #%d: %s\n", count1, getCardName(G_mod.hand[player][i]));
            }
        }
        asserttrue(count1==2 && count1_Treasure==2, r_main);

    }


    /*-------------------------------------------------------------------------*/
    /* If Deck + Discard previously has 1 Treasure */
    else if (numTreasureDeck + numTreasureDiscard == 1) {
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
        printf("---------CASE %d: %s -- TEST %d: 1 Treasure removed from Deck+Discard\n", *caseCount, casename, ++(*testCount));    
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
        count2_Treasure = 0;
        for (i=0; i<preG_DeckDiscardCount; i++) {
            if (preG_DeckDiscard[i] > -1) {
                count2++;
                if (preG_DeckDiscard[i] == copper || preG_DeckDiscard[i] == silver || preG_DeckDiscard[i] == gold ) {
                    count2_Treasure++;
                }
                if (NOISY_TEST) printf("Card removed from Deck+Discard #%d: %s\n", count2, getCardName(preG_DeckDiscard[i]));
                if (preG_DeckDiscard[i] == card) {
                    playedCardsRemovedFromDeckDiscard++;
                }
            }
        }
        asserttrue(count2==1 && count2_Treasure==1, r_main);        


        /*********/
        printf("---------CASE %d: %s -- TEST %d: 1 new Treasure added to Hand\n", *caseCount, casename, ++(*testCount));
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
        count1_Treasure = 0;
        for (i=0; i<G_mod.handCount[player]; i++) {
            if (G_mod.hand[player][i] > -1) {
                count1++;  // how many new cards in Hand?
                if (G_mod.hand[player][i] == copper || G_mod.hand[player][i] == silver || G_mod.hand[player][i] == gold) {
                    count1_Treasure++;
                }
                if (NOISY_TEST) printf("Card added to Hand #%d: %s\n", count1, getCardName(G_mod.hand[player][i]));
            }
        }
        asserttrue(count1==1 && count1_Treasure==1, r_main);

    }


    /*-------------------------------------------------------------------------*/
    /* If Deck + Discard previously has 0 Treasure */
    else if (numTreasureDeck + numTreasureDiscard == 1) {
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
        printf("---------CASE %d: %s -- TEST %d: No Treasure removed from Deck+Discard\n", *caseCount, casename, ++(*testCount));    
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
        count2_Treasure = 0;
        for (i=0; i<preG_DeckDiscardCount; i++) {
            if (preG_DeckDiscard[i] > -1) {
                count2++;
                if (preG_DeckDiscard[i] == copper || preG_DeckDiscard[i] == silver || preG_DeckDiscard[i] == gold ) {
                    count2_Treasure++;
                }
                if (NOISY_TEST) printf("Card removed from Deck+Discard #%d: %s\n", count2, getCardName(preG_DeckDiscard[i]));
                if (preG_DeckDiscard[i] == card) {
                    playedCardsRemovedFromDeckDiscard++;
                }
            }
        }
        asserttrue(count2==0 && count2_Treasure==0, r_main);        


        /*********/
        printf("---------CASE %d: %s -- TEST %d: No new Treasure added to Hand\n", *caseCount, casename, ++(*testCount));
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
        count1_Treasure = 0;
        for (i=0; i<G_mod.handCount[player]; i++) {
            if (G_mod.hand[player][i] > -1) {
                count1++;  // how many new cards in Hand?
                if (G_mod.hand[player][i] == copper || G_mod.hand[player][i] == silver || G_mod.hand[player][i] == gold) {
                    count1_Treasure++;
                }
                if (NOISY_TEST) printf("Card added to Hand #%d: %s\n", count1, getCardName(G_mod.hand[player][i]));
            }
        }
        asserttrue(count1==0 && count1_Treasure==0, r_main);

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

}





/*********************************************************************/
/* Main */
int main(int argc, char* argv[]) {
    struct gameState G, preG;
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;  // dummy parameters; won't be used for this card
    int seed, player, handPos, i, j, randPos;
    int testCount = 0, caseCount = 0;
    int card = adventurer;
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


// Specific requirements:
// -- If Deck+Discard previously has 2+ Treasure:
//     +) Hand count increased by 1 (2 Treasure drawn - 1 card played)
//     +) Deck+Discard count decreased by 2
//     +) 2 new Treasure added to Hand
//     +) 2 Treasure removed from Deck+Discard
// -- If Deck+Discard previously has 1 Treasure:
//     +) Hand count unchanged (1 Treasure drawn - 1 card played)
//     +) Deck+Discard count decreased by 1
//     +) 1 new Treasure added to Hand
//     +) 1 Treasure removed from Deck+Discard
// -- If Deck+Discard previously has 0 Treasure:
//     +) Hand count decreased by 1 (- 1 card played)
//     +) Deck+Discard count unchanged
//     +) Hand unchanged except removing played card
//     +) Deck+Discard unchanged
// -- The cards added to hand are the same as the cards removed from Deck+Discard

// The following cases are tests:
// -- 1 Treasure in Deck, no Treasure in Discard
// -- No Treasure in Deck, 1 Treasure in Discard
// -- No Treasure in Deck, no Treasure in Discard

    /* Perform NUM_RANDOM_TESTS random tests */
    for (i=0; i<NUM_RANDOM_TESTS; i++) {
        printf("Iter=%d\n", i);

        /* Construct game state */
        G = randomGameState();
        player = G.whoseTurn;
        handPos = randomInRange(G.handCount[player]-1);
        G.hand[player][handPos] = card;  

        /* Copy game state to preG */
        memcpy(&preG, &G, sizeof(struct gameState));

        /*********/
        testCardAdventurer(&caseCount, &testCount, &r_main,
            card, choice1, choice2, choice3, handPos, &bonus,
            &G, &preG);       
    }


    // /* Perform NUM_RANDOM_TESTS random tests with 2+ Treasure in Deck, 0 Treasure in Discard */
    // for (i=0; i<NUM_RANDOM_TESTS; i++) {
    //     /* Construct game state */
    //     G = randomGameState();
    //     player = G.whoseTurn;
    //     handPos = randomInRange(G.handCount[player]-1);
    //     G.hand[player][handPos] = card;
    //     for (j=0; j<5; j++) {
    //         randPos = randomInRange(G.deckCount[player]-1);
    //         G.deck[player][randPos] = copper;
    //     }
    //     for (j=0; j<G.discardCount[player]; j++) {
    //         if (G.discard[player][j] == copper || G.discard[player][j] == silver || G.discard[player][j] == gold) {
    //             G.discard[player][j] = baron;
    //         }
    //     }

    //     /* Copy game state to preG */
    //     memcpy(&preG, &G, sizeof(struct gameState));

    //     /*********/
    //     testCardAdventurer(&caseCount, &testCount, &r_main,
    //         card, choice1, choice2, choice3, handPos, &bonus,
    //         &G, &preG);       
    // }


    // /* Perform NUM_RANDOM_TESTS random tests with 1 Treasure in Deck, 1+ Treasure in Discard */
    // for (i=0; i<NUM_RANDOM_TESTS; i++) {
    //     /* Construct game state */
    //     G = randomGameState();
    //     player = G.whoseTurn;
    //     handPos = randomInRange(G.handCount[player]-1);
    //     G.hand[player][handPos] = card;
    //     for (j=0; j<G.deckCount[player]; j++) {
    //         if (G.deck[player][j] == copper || G.deck[player][j] == silver || G.deck[player][j] == gold) {
    //             G.deck[player][j] = baron;
    //         }
    //     }
    //     randPos = randomInRange(G.deckCount[player]-1);
    //     G.deck[player][randPos] = copper;
    //     for (j=0; j<5; j++) {
    //         randPos = randomInRange(G.discardCount[player]-1);
    //         G.discard[player][randPos] = copper;
    //     }

    //     /* Copy game state to preG */
    //     memcpy(&preG, &G, sizeof(struct gameState));

    //     /*********/
    //     testCardAdventurer(&caseCount, &testCount, &r_main,
    //         card, choice1, choice2, choice3, handPos, &bonus,
    //         &G, &preG);       
    // }


    // /* Perform NUM_RANDOM_TESTS random tests with 0 Treasure in Deck, 2+ Treasure in Discard */
    // for (i=0; i<NUM_RANDOM_TESTS; i++) {
    //     /* Construct game state */
    //     G = randomGameState();
    //     player = G.whoseTurn;
    //     handPos = randomInRange(G.handCount[player]-1);
    //     G.hand[player][handPos] = card;
    //     for (j=0; j<G.deckCount[player]; j++) {
    //         if (G.deck[player][j] == copper || G.deck[player][j] == silver || G.deck[player][j] == gold) {
    //             G.deck[player][j] = baron;
    //         }
    //     }
    //     for (j=0; j<5; j++) {
    //         randPos = randomInRange(G.discardCount[player]-1);
    //         G.discard[player][randPos] = copper;
    //     }

    //     /* Copy game state to preG */
    //     memcpy(&preG, &G, sizeof(struct gameState));

    //     /*********/
    //     testCardAdventurer(&caseCount, &testCount, &r_main,
    //         card, choice1, choice2, choice3, handPos, &bonus,
    //         &G, &preG);       
    // }


    // /* Perform NUM_RANDOM_TESTS random tests with 1 Treasure in Deck, 0 Treasure in Discard */
    // for (i=0; i<NUM_RANDOM_TESTS; i++) {
    //     /* Construct game state */
    //     G = randomGameState();
    //     player = G.whoseTurn;
    //     handPos = randomInRange(G.handCount[player]-1);
    //     G.hand[player][handPos] = card;
    //     for (j=0; j<G.deckCount[player]; j++) {
    //         if (G.deck[player][j] == copper || G.deck[player][j] == silver || G.deck[player][j] == gold) {
    //             G.deck[player][j] = baron;
    //         }
    //     }
    //     randPos = randomInRange(G.deckCount[player]-1);
    //     G.deck[player][randPos] = copper;
    //     for (j=0; j<G.discardCount[player]; j++) {
    //         if (G.discard[player][j] == copper || G.discard[player][j] == silver || G.discard[player][j] == gold) {
    //             G.discard[player][j] = baron;
    //         }
    //     }

    //     /* Copy game state to preG */
    //     memcpy(&preG, &G, sizeof(struct gameState));

    //     /*********/
    //     testCardAdventurer(&caseCount, &testCount, &r_main,
    //         card, choice1, choice2, choice3, handPos, &bonus,
    //         &G, &preG);       
    // }


    // /* Perform NUM_RANDOM_TESTS random tests with 0 Treasure in Deck, 1 Treasure in Discard */
    // for (i=0; i<NUM_RANDOM_TESTS; i++) {
    //     /* Construct game state */
    //     G = randomGameState();
    //     player = G.whoseTurn;
    //     handPos = randomInRange(G.handCount[player]-1);
    //     G.hand[player][handPos] = card;
    //     for (j=0; j<G.deckCount[player]; j++) {
    //         if (G.deck[player][j] == copper || G.deck[player][j] == silver || G.deck[player][j] == gold) {
    //             G.deck[player][j] = baron;
    //         }
    //     }
    //     for (j=0; j<G.discardCount[player]; j++) {
    //         if (G.discard[player][j] == copper || G.discard[player][j] == silver || G.discard[player][j] == gold) {
    //             G.discard[player][j] = baron;
    //         }
    //     }
    //     randPos = randomInRange(G.discardCount[player]-1);
    //     G.discard[player][randPos] = copper;

    //     /* Copy game state to preG */
    //     memcpy(&preG, &G, sizeof(struct gameState));

    //     /*********/
    //     testCardAdventurer(&caseCount, &testCount, &r_main,
    //         card, choice1, choice2, choice3, handPos, &bonus,
    //         &G, &preG);       
    // }


    // /* Perform NUM_RANDOM_TESTS random tests with 0 Treasure in Deck, 0 Treasure in Discard */
    // for (i=0; i<NUM_RANDOM_TESTS; i++) {
    //     /* Construct game state */
    //     G = randomGameState();
    //     player = G.whoseTurn;
    //     handPos = randomInRange(G.handCount[player]-1);
    //     G.hand[player][handPos] = card;
    //     for (j=0; j<G.deckCount[player]; j++) {
    //         if (G.deck[player][j] == copper || G.deck[player][j] == silver || G.deck[player][j] == gold) {
    //             G.deck[player][j] = baron;
    //         }
    //     }
    //     for (j=0; j<G.discardCount[player]; j++) {
    //         if (G.discard[player][j] == copper || G.discard[player][j] == silver || G.discard[player][j] == gold) {
    //             G.discard[player][j] = baron;
    //         }
    //     }

    //     /* Copy game state to preG */
    //     memcpy(&preG, &G, sizeof(struct gameState));

    //     /*********/
    //     testCardAdventurer(&caseCount, &testCount, &r_main,
    //         card, choice1, choice2, choice3, handPos, &bonus,
    //         &G, &preG);       
    // }


/*-------------------------------------------------------------------------*/
    printf("---------\n");
    printf("Card %s passed %d/%d tests.\n", CARD_NAME, r_main, testCount);
    printf("END random test %s\n", CARD_NAME);
    printf("**********************************************************\n\n");

    return 0;
}


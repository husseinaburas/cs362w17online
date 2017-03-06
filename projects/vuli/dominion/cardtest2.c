/* cardtest1.c
Card tested: Smithy

General requirements:
-- Successful execution (return value 0)
-- Decreases Hand+Deck+Discard count by 1
-- Increases playedCardCount by 1
-- Adds card previously at handPos to playedCards
-- Removes card previously at handPos from hand
-- Does not change game state except for current player
-- Does not change Hand+Deck+Discard for current player, except removing played card

Specific requirements:
-- If Deck+Discard previously has 3+ cards:
    +) Increases Hand count by 2 (3 cards drawn - 1 card played)
    +) Decreases Deck+Discard count by 3
    +) 3 cards are added to Hand and 3 cards are removed from Deck+Discard
-- If Deck+Discard previously has 2 cards:
    +) Increases Hand count by 1 (2 cards drawn - 1 card played)
    +) Decreases Deck+Discard count by 2
    +) 2 cards are added to Hand and 2 cards are removed from Deck+Discard
-- If Deck+Discard previously has 1 card:
    +) Hand count unchanged (1 card drawn - 1 card played)
    +) Decreases Deck+Discard count by 1
    +) 1 card is added to Hand and 1 card is removed from Deck+Discard
-- If Deck+Discard previously has no card:
    +) Hand count decreased by 1 (- 1 card played)
    +) Deck+Discard count unchanged
    +) No card is added to Hand and no card is removed from Deck+Discard
-- The cards added to hand are the same as the cards removed from Deck+Discard

The following cases are tested:
-- 3+ cards in Deck, empty Discard
-- 2 cards in Deck, non-empty Discard
-- Empty Deck, 3+ cards in Discard
-- 2 cards in Deck, empty Discard
-- 1 card in Deck, 1 card in Discard
-- Empty Deck, 1 card in Discard
-- Empty Deck, empty Discard
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

#define CARD_NAME "Smithy"




/*********************************************************************/
/* Main */
int main() {
    int seed = 1000;
    struct gameState G, preG, G_mod, preG_mod;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine, 
      remodel, smithy, village, baron, great_hall};
    int r_main = 0;
    int testCount = 0, caseCount = 0;

    int handPos = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;  // dummy parameters; won't be used for this card
    int player, card, i, j;
    int count1, count2;

    char* casename;
    int G_DeckDiscard[2*MAX_DECK], preG_DeckDiscard[2*MAX_DECK];
    int G_DeckDiscardCount, preG_DeckDiscardCount;

    printf("**********************************************************\n");
    printf("BEGIN unit testing %s\n", CARD_NAME);
    

/*-------------------------------------------------------------------------*/
    casename = "3+ cards in Deck, empty Discard";
    caseCount++;
    initializeGame(numPlayer, k, seed, &G);
    player = G.whoseTurn;
    G.hand[player][handPos] = smithy; // make current card smithy
    card = G.hand[player][handPos];  // card previously at handPos
    assert(G.deckCount[player] >=3); // Deck should have 5 cards after initialization
    memcpy(&preG, &G, sizeof(struct gameState));  // save gameState to preG

    /*********/
    testCardGeneralRequirements(&caseCount, casename, &testCount, &r_main,
        card, choice1, choice2, choice3, handPos, &bonus,
        &G, &preG);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Hand count increased by 2\n", caseCount, casename, ++testCount);
    count1 = preG.handCount[player];
    count2 = G.handCount[player];
    if (NOISY_TEST) printf("Hand count before: %d\nHand count after: %d\n", count1, count2);
    asserttrue(count2==count1+2, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Deck+Discard count decreased by 3\n", caseCount, casename, ++testCount);
    count1 = preG.deckCount[player] + preG.discardCount[player];
    count2 = G.deckCount[player] + G.discardCount[player];
    if (NOISY_TEST) printf("Deck+Discard count before: %d\nDeck+Discard count after: %d\n", count1, count2);
    asserttrue(count2==count1-3, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: 3 new cards added to Hand\n", caseCount, casename, ++testCount);
    assert(G.handCount[player] >= 3);  // hand should have 3+ cards
    memcpy(&G_mod, &G, sizeof(struct gameState));  // make a copy of G & preG that can be modified
    memcpy(&preG_mod, &preG, sizeof(struct gameState));
    // What cards are added to Hand?
    for (i=0; i<G_mod.handCount[player]; i++) {
        if (G_mod.hand[player][i] == smithy) {
            G_mod.hand[player][i] = -1;  // cross out Smithy as it'd be moved to played
        }
        for (j=0; j<preG_mod.handCount[player]; j++) {
            if (G_mod.hand[player][i] == preG_mod.hand[player][j] && G_mod.hand[player][i] != -1) {
                G_mod.hand[player][i] = -1;  // cross out cards that appear in both G_mod.hand and preG_mod.hand
                preG_mod.hand[player][j] = -1;
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
    asserttrue(count1==3, &r_main);


    /*********/
    printf("---------CASE %d: %s -- TEST %d: 3 cards removed from Deck+Discard\n", caseCount, casename, ++testCount);    
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
            count2++;  // how many new cards in Hand?
            if (NOISY_TEST) printf("Card removed from Deck+Discard #%d: %s\n", count2, getCardName(preG_DeckDiscard[i]));
        }
    }
    asserttrue(count2==3, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Cards added to Hand were the same as cards removed from Deck+Discard\n", caseCount, casename, ++testCount); 
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
    // What cards removed from Deck+Discard are not added to Hand?
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
    asserttrue(count1==0 && count2==0, &r_main);


/*-------------------------------------------------------------------------*/
    casename = "2 cards in Deck, non-empty Discard";  // to test shuffle
    caseCount++;
    initializeGame(numPlayer, k, seed, &G);
    player = G.whoseTurn;
    G.hand[player][handPos] = smithy; // make current card smithy
    card = G.hand[player][handPos];  // card previously at handPos

    /* Construct Deck with 2 cards, Discard with 4 cards */
    G.deckCount[player] = 2;
    G.deck[player][0] = gold;
    G.deck[player][1] = silver;
    G.discardCount[player] = 4;
    G.discard[player][0] = adventurer;
    G.discard[player][1] = council_room;
    G.discard[player][2] = feast;
    G.discard[player][3] = gardens;

    memcpy(&preG, &G, sizeof(struct gameState));  // save gameState to preG

    /*********/
    testCardGeneralRequirements(&caseCount, casename, &testCount, &r_main,
        card, choice1, choice2, choice3, handPos, &bonus,
        &G, &preG);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Hand count increased by 2\n", caseCount, casename, ++testCount);
    count1 = preG.handCount[player];
    count2 = G.handCount[player];
    if (NOISY_TEST) printf("Hand count before: %d\nHand count after: %d\n", count1, count2);
    asserttrue(count2==count1+2, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Deck+Discard count decreased by 3\n", caseCount, casename, ++testCount);
    count1 = preG.deckCount[player] + preG.discardCount[player];
    count2 = G.deckCount[player] + G.discardCount[player];
    if (NOISY_TEST) printf("Deck+Discard count before: %d\nDeck+Discard count after: %d\n", count1, count2);
    asserttrue(count2==count1-3, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: 3 new cards added to Hand\n", caseCount, casename, ++testCount);
    assert(G.handCount[player] >= 3);  // hand should have 3+ cards
    memcpy(&G_mod, &G, sizeof(struct gameState));  // make a copy of G & preG that can be modified
    memcpy(&preG_mod, &preG, sizeof(struct gameState));
    // What cards are added to Hand?
    for (i=0; i<G_mod.handCount[player]; i++) {
        if (G_mod.hand[player][i] == smithy) {
            G_mod.hand[player][i] = -1;  // cross out Smithy as it'd be moved to played
        }
        for (j=0; j<preG_mod.handCount[player]; j++) {
            if (G_mod.hand[player][i] == preG_mod.hand[player][j] && G_mod.hand[player][i] != -1) {
                G_mod.hand[player][i] = -1;  // cross out cards that appear in both G_mod.hand and preG_mod.hand
                preG_mod.hand[player][j] = -1;
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
    asserttrue(count1==3, &r_main);


    /*********/
    printf("---------CASE %d: %s -- TEST %d: 3 cards removed from Deck+Discard\n", caseCount, casename, ++testCount);    
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
            count2++;  // how many new cards in Hand?
            if (NOISY_TEST) printf("Card removed from Deck+Discard #%d: %s\n", count2, getCardName(preG_DeckDiscard[i]));
        }
    }
    asserttrue(count2==3, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Cards added to Hand were the same as cards removed from Deck+Discard\n", caseCount, casename, ++testCount); 
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
    // What cards removed from Deck+Discard are not added to Hand?
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
    asserttrue(count1==0 && count2==0, &r_main);


/*-------------------------------------------------------------------------*/
    casename = "Empty Deck, 3+ cards in Discard";  // to test shuffle
    caseCount++;
    initializeGame(numPlayer, k, seed, &G);
    player = G.whoseTurn;
    G.hand[player][handPos] = smithy; // make current card smithy
    card = G.hand[player][handPos];  // card previously at handPos

    /* Construct empty Deck and Discard with 4 cards */
    for (i=0; i<G.deckCount[player]; i++) {
        G.deck[player][i] = -1;
    }
    G.deckCount[player] = 0;
    G.discardCount[player] = 4;
    G.discard[player][0] = adventurer;
    G.discard[player][1] = council_room;
    G.discard[player][2] = feast;
    G.discard[player][3] = gardens;

    memcpy(&preG, &G, sizeof(struct gameState));  // save gameState to preG

    /*********/
    testCardGeneralRequirements(&caseCount, casename, &testCount, &r_main,
        card, choice1, choice2, choice3, handPos, &bonus,
        &G, &preG);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Hand count increased by 2\n", caseCount, casename, ++testCount);
    count1 = preG.handCount[player];
    count2 = G.handCount[player];
    if (NOISY_TEST) printf("Hand count before: %d\nHand count after: %d\n", count1, count2);
    asserttrue(count2==count1+2, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Deck+Discard count decreased by 3\n", caseCount, casename, ++testCount);
    count1 = preG.deckCount[player] + preG.discardCount[player];
    count2 = G.deckCount[player] + G.discardCount[player];
    if (NOISY_TEST) printf("Deck+Discard count before: %d\nDeck+Discard count after: %d\n", count1, count2);
    asserttrue(count2==count1-3, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: 3 new cards added to Hand\n", caseCount, casename, ++testCount);
    assert(G.handCount[player] >= 3);  // hand should have 3+ cards
    memcpy(&G_mod, &G, sizeof(struct gameState));  // make a copy of G & preG that can be modified
    memcpy(&preG_mod, &preG, sizeof(struct gameState));
    // What cards are added to Hand?
    for (i=0; i<G_mod.handCount[player]; i++) {
        if (G_mod.hand[player][i] == smithy) {
            G_mod.hand[player][i] = -1;  // cross out Smithy as it'd be moved to played
        }
        for (j=0; j<preG_mod.handCount[player]; j++) {
            if (G_mod.hand[player][i] == preG_mod.hand[player][j] && G_mod.hand[player][i] != -1) {
                G_mod.hand[player][i] = -1;  // cross out cards that appear in both G_mod.hand and preG_mod.hand
                preG_mod.hand[player][j] = -1;
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
    asserttrue(count1==3, &r_main);


    /*********/
    printf("---------CASE %d: %s -- TEST %d: 3 cards removed from Deck+Discard\n", caseCount, casename, ++testCount);    
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
            count2++;  // how many new cards in Hand?
            if (NOISY_TEST) printf("Card removed from Deck+Discard #%d: %s\n", count2, getCardName(preG_DeckDiscard[i]));
        }
    }
    asserttrue(count2==3, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Cards added to Hand were the same as cards removed from Deck+Discard\n", caseCount, casename, ++testCount); 
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
    // What cards removed from Deck+Discard are not added to Hand?
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
    asserttrue(count1==0 && count2==0, &r_main);

/*-------------------------------------------------------------------------*/
    casename = "2 cards in Deck, empty Discard";  // to test Deck+Discard count < 3
    caseCount++;
    initializeGame(numPlayer, k, seed, &G);
    player = G.whoseTurn;
    G.hand[player][handPos] = smithy; // make current card smithy
    card = G.hand[player][handPos];  // card previously at handPos

    /* Construct Deck with 2 cards and empty Discard */
    for (i=0; i<G.deckCount[player]; i++) {
        G.deck[player][i] = -1;
    }
    G.deckCount[player] = 2;
    G.deck[player][0] = gold;
    G.deck[player][1] = gardens;
    G.discardCount[player] = 0;

    memcpy(&preG, &G, sizeof(struct gameState));  // save gameState to preG

    /*********/
    testCardGeneralRequirements(&caseCount, casename, &testCount, &r_main,
        card, choice1, choice2, choice3, handPos, &bonus,
        &G, &preG);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Hand count increased by 1\n", caseCount, casename, ++testCount);
    count1 = preG.handCount[player];
    count2 = G.handCount[player];
    if (NOISY_TEST) printf("Hand count before: %d\nHand count after: %d\n", count1, count2);
    asserttrue(count2==count1+1, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Deck+Discard count decreased by 2\n", caseCount, casename, ++testCount);
    count1 = preG.deckCount[player] + preG.discardCount[player];
    count2 = G.deckCount[player] + G.discardCount[player];
    if (NOISY_TEST) printf("Deck+Discard count before: %d\nDeck+Discard count after: %d\n", count1, count2);
    asserttrue(count2==count1-2, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: 2 new cards added to Hand\n", caseCount, casename, ++testCount);
    assert(G.handCount[player] >= 2);  // hand should have 2+ cards
    memcpy(&G_mod, &G, sizeof(struct gameState));  // make a copy of G & preG that can be modified
    memcpy(&preG_mod, &preG, sizeof(struct gameState));
    // What cards are added to Hand?
    for (i=0; i<G_mod.handCount[player]; i++) {
        if (G_mod.hand[player][i] == smithy) {
            G_mod.hand[player][i] = -1;  // cross out Smithy as it'd be moved to played
        }
        for (j=0; j<preG_mod.handCount[player]; j++) {
            if (G_mod.hand[player][i] == preG_mod.hand[player][j] && G_mod.hand[player][i] != -1) {
                G_mod.hand[player][i] = -1;  // cross out cards that appear in both G_mod.hand and preG_mod.hand
                preG_mod.hand[player][j] = -1;
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
    asserttrue(count1==2, &r_main);


    /*********/
    printf("---------CASE %d: %s -- TEST %d: 2 cards removed from Deck+Discard\n", caseCount, casename, ++testCount);    
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
            count2++;  // how many new cards in Hand?
            if (NOISY_TEST) printf("Card removed from Deck+Discard #%d: %s\n", count2, getCardName(preG_DeckDiscard[i]));
        }
    }
    asserttrue(count2==2, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Cards added to Hand were the same as cards removed from Deck+Discard\n", caseCount, casename, ++testCount); 
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
    // What cards removed from Deck+Discard are not added to Hand?
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
    asserttrue(count1==0 && count2==0, &r_main);


/*-------------------------------------------------------------------------*/
    casename = "1 card in Deck, 1 card in Discard";  // to test shuffle and Deck+Discard count < 3
    caseCount++;
    initializeGame(numPlayer, k, seed, &G);
    player = G.whoseTurn;
    G.hand[player][handPos] = smithy; // make current card smithy
    card = G.hand[player][handPos];  // card previously at handPos

    /* Construct Deck with 1 card and Discard with 1 card */
    for (i=0; i<G.deckCount[player]; i++) {
        G.deck[player][i] = -1;
    }
    G.deckCount[player] = 1;
    G.deck[player][0] = gold;
    G.discardCount[player] = 1;
    G.discard[player][0] = gardens;

    memcpy(&preG, &G, sizeof(struct gameState));  // save gameState to preG

    /*********/
    testCardGeneralRequirements(&caseCount, casename, &testCount, &r_main,
        card, choice1, choice2, choice3, handPos, &bonus,
        &G, &preG);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Hand count increased by 1\n", caseCount, casename, ++testCount);
    count1 = preG.handCount[player];
    count2 = G.handCount[player];
    if (NOISY_TEST) printf("Hand count before: %d\nHand count after: %d\n", count1, count2);
    asserttrue(count2==count1+1, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Deck+Discard count decreased by 2\n", caseCount, casename, ++testCount);
    count1 = preG.deckCount[player] + preG.discardCount[player];
    count2 = G.deckCount[player] + G.discardCount[player];
    if (NOISY_TEST) printf("Deck+Discard count before: %d\nDeck+Discard count after: %d\n", count1, count2);
    asserttrue(count2==count1-2, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: 2 new cards added to Hand\n", caseCount, casename, ++testCount);
    assert(G.handCount[player] >= 2);  // hand should have 2+ cards
    memcpy(&G_mod, &G, sizeof(struct gameState));  // make a copy of G & preG that can be modified
    memcpy(&preG_mod, &preG, sizeof(struct gameState));
    // What cards are added to Hand?
    for (i=0; i<G_mod.handCount[player]; i++) {
        if (G_mod.hand[player][i] == smithy) {
            G_mod.hand[player][i] = -1;  // cross out Smithy as it'd be moved to played
        }
        for (j=0; j<preG_mod.handCount[player]; j++) {
            if (G_mod.hand[player][i] == preG_mod.hand[player][j] && G_mod.hand[player][i] != -1) {
                G_mod.hand[player][i] = -1;  // cross out cards that appear in both G_mod.hand and preG_mod.hand
                preG_mod.hand[player][j] = -1;
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
    asserttrue(count1==2, &r_main);


    /*********/
    printf("---------CASE %d: %s -- TEST %d: 2 cards removed from Deck+Discard\n", caseCount, casename, ++testCount);    
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
            count2++;  // how many new cards in Hand?
            if (NOISY_TEST) printf("Card removed from Deck+Discard #%d: %s\n", count2, getCardName(preG_DeckDiscard[i]));
        }
    }
    asserttrue(count2==2, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Cards added to Hand were the same as cards removed from Deck+Discard\n", caseCount, casename, ++testCount); 
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
    // What cards removed from Deck+Discard are not added to Hand?
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
    asserttrue(count1==0 && count2==0, &r_main);

/*-------------------------------------------------------------------------*/
    casename = "Empty Deck, 1 card in Discard";  // to test shuffle and Deck+Discard count < 3
    caseCount++;
    initializeGame(numPlayer, k, seed, &G);
    player = G.whoseTurn;
    G.hand[player][handPos] = smithy; // make current card smithy
    card = G.hand[player][handPos];  // card previously at handPos

    /* Construct empty Deck and Discard with 1 card */
    for (i=0; i<G.deckCount[player]; i++) {
        G.deck[player][i] = -1;
    }
    G.deckCount[player] = 0;
    G.discardCount[player] = 1;
    G.discard[player][0] = gardens;

    memcpy(&preG, &G, sizeof(struct gameState));  // save gameState to preG

    /*********/
    testCardGeneralRequirements(&caseCount, casename, &testCount, &r_main,
        card, choice1, choice2, choice3, handPos, &bonus,
        &G, &preG);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Hand count unchanged\n", caseCount, casename, ++testCount);
    count1 = preG.handCount[player];
    count2 = G.handCount[player];
    if (NOISY_TEST) printf("Hand count before: %d\nHand count after: %d\n", count1, count2);
    asserttrue(count2==count1, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Deck+Discard count decreased by 1\n", caseCount, casename, ++testCount);
    count1 = preG.deckCount[player] + preG.discardCount[player];
    count2 = G.deckCount[player] + G.discardCount[player];
    if (NOISY_TEST) printf("Deck+Discard count before: %d\nDeck+Discard count after: %d\n", count1, count2);
    asserttrue(count2==count1-1, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: 1 new card added to Hand\n", caseCount, casename, ++testCount);
    assert(G.handCount[player] >= 1);  // hand should have 1+ cards
    memcpy(&G_mod, &G, sizeof(struct gameState));  // make a copy of G & preG that can be modified
    memcpy(&preG_mod, &preG, sizeof(struct gameState));
    // What cards are added to Hand?
    for (i=0; i<G_mod.handCount[player]; i++) {
        if (G_mod.hand[player][i] == smithy) {
            G_mod.hand[player][i] = -1;  // cross out Smithy as it'd be moved to played
        }
        for (j=0; j<preG_mod.handCount[player]; j++) {
            if (G_mod.hand[player][i] == preG_mod.hand[player][j] && G_mod.hand[player][i] != -1) {
                G_mod.hand[player][i] = -1;  // cross out cards that appear in both G_mod.hand and preG_mod.hand
                preG_mod.hand[player][j] = -1;
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
    asserttrue(count1==1, &r_main);


    /*********/
    printf("---------CASE %d: %s -- TEST %d: 1 card removed from Deck+Discard\n", caseCount, casename, ++testCount);    
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
            count2++;  // how many new cards in Hand?
            if (NOISY_TEST) printf("Card removed from Deck+Discard #%d: %s\n", count2, getCardName(preG_DeckDiscard[i]));
        }
    }
    asserttrue(count2==1, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Cards added to Hand were the same as cards removed from Deck+Discard\n", caseCount, casename, ++testCount); 
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
    // What cards removed from Deck+Discard are not added to Hand?
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
    asserttrue(count1==0 && count2==0, &r_main);

/*-------------------------------------------------------------------------*/
    casename = "Empty Deck, empty Discard";
    caseCount++;
    initializeGame(numPlayer, k, seed, &G);
    player = G.whoseTurn;
    G.hand[player][handPos] = smithy; // make current card smithy
    card = G.hand[player][handPos];  // card previously at handPos

    /* Construct empty Deck and empty Discard */
    for (i=0; i<G.deckCount[player]; i++) {
        G.deck[player][i] = -1;
    }
    G.deckCount[player] = 0;
    G.discardCount[player] = 0;

    memcpy(&preG, &G, sizeof(struct gameState));  // save gameState to preG

    /*********/
    testCardGeneralRequirements(&caseCount, casename, &testCount, &r_main,
        card, choice1, choice2, choice3, handPos, &bonus,
        &G, &preG);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Hand count decreased by 1\n", caseCount, casename, ++testCount);
    count1 = preG.handCount[player];
    count2 = G.handCount[player];
    if (NOISY_TEST) printf("Hand count before: %d\nHand count after: %d\n", count1, count2);
    asserttrue(count2==count1-1, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Deck+Discard count unchanged\n", caseCount, casename, ++testCount);
    count1 = preG.deckCount[player] + preG.discardCount[player];
    count2 = G.deckCount[player] + G.discardCount[player];
    if (NOISY_TEST) printf("Deck+Discard count before: %d\nDeck+Discard count after: %d\n", count1, count2);
    asserttrue(count2==count1, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: No new card added to Hand\n", caseCount, casename, ++testCount);
    assert(G.handCount[player] >= 0);
    memcpy(&G_mod, &G, sizeof(struct gameState));  // make a copy of G & preG that can be modified
    memcpy(&preG_mod, &preG, sizeof(struct gameState));
    // What cards are added to Hand?
    for (i=0; i<G_mod.handCount[player]; i++) {
        if (G_mod.hand[player][i] == smithy) {
            G_mod.hand[player][i] = -1;  // cross out Smithy as it'd be moved to played
        }
        for (j=0; j<preG_mod.handCount[player]; j++) {
            if (G_mod.hand[player][i] == preG_mod.hand[player][j] && G_mod.hand[player][i] != -1) {
                G_mod.hand[player][i] = -1;  // cross out cards that appear in both G_mod.hand and preG_mod.hand
                preG_mod.hand[player][j] = -1;
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
    asserttrue(count1==0, &r_main);


    /*********/
    printf("---------CASE %d: %s -- TEST %d: No card removed from Deck+Discard\n", caseCount, casename, ++testCount);    
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
            count2++;  // how many new cards in Hand?
            if (NOISY_TEST) printf("Card removed from Deck+Discard #%d: %s\n", count2, getCardName(preG_DeckDiscard[i]));
        }
    }
    asserttrue(count2==0, &r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Cards added to Hand were the same as cards removed from Deck+Discard\n", caseCount, casename, ++testCount); 
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
    // What cards removed from Deck+Discard are not added to Hand?
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
    asserttrue(count1==0 && count2==0, &r_main);

/*-------------------------------------------------------------------------*/
    /******** Result */
    printf("---------\n");
    printf("Card %s passed %d/%d tests.\n", CARD_NAME, r_main, testCount);
    printf("END unit testing %s\n", CARD_NAME);
    printf("**********************************************************\n\n");

    return 0;
}


/* cardtest1.c
Card tested: Adventurer

Requirements:
-- Decreases Hand+Deck+Discard count by 1
-- Increases playedCardCount by 1
-- Adds card previously at handPos to playedCards
-- Removes card previously at handPos from hand
-- Does not change game state except for current player
-- Does not change Hand+Deck+Discard for current player, except removing played card

-- If deck+discard previously has 2+ Treasure:
    +) Increases handCount by 1 (2 Treasure drawn - 1 card played)
    +) hand contains 2 new Treasure
-- If deck+discard previously has 1 Treasure:
    +) handCount unchanged (1 Treasure drawn - 1 card played)
    +) hand contains 1 new Treasure
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define CARD_NAME "Adventurer"
#define NOISY_TEST 1


/* Function to test general requirements that apply to most cards and Deck+Hand+Discard scenarios:
-- Decreases Hand+Deck+Discard count by 1
-- Increases playedCardCount by 1
-- Adds card previously at handPos to playedCards
-- Removes card previously at handPos from hand
-- Does not change game state except for current player
 */
void testGeneralRequirements(int caseCount, char* casename, int* testCount, int* r_main,
    int card, int choice1, int choice2, int choice3, int handPos, int* bonus,
    struct gameState* G, struct gameState* preG) 
{
    int count1, count2, r, i, j;
    struct gameState preG_mod;
    int player = G->whoseTurn;
    int G_HandDeckDiscard[2*MAX_DECK + MAX_HAND], preG_HandDeckDiscard[2*MAX_DECK + MAX_HAND];
    int G_HandDeckDiscardCount, preG_HandDeckDiscardCount;

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Successful execution\n", caseCount, casename, ++(*testCount));
    r = cardEffect(card, choice1, choice2, choice3, G, handPos, bonus);
    asserttrue(r==0, r_main); 
    if (NOISY_TEST) {
        printf("Before execution:\n");
        printCurrentPlayer(player, preG);
        printf("After execution:\n");
        printCurrentPlayer(player, G);
    }   

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Hand+Deck+Discard count decreased by 1\n", caseCount, casename, ++(*testCount));
    count1 = preG->handCount[player] + preG->discardCount[player] + preG->deckCount[player];
    count2 = G->handCount[player] + G->discardCount[player] + G->deckCount[player];
    asserttrue(count1==count2+1, r_main);
    if (NOISY_TEST) printf("Count before: %d\nCount after: %d\n", count1, count2);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Played card count increased by 1\n", caseCount, casename, ++(*testCount));
    count1 = preG->playedCardCount;
    count2 = G->playedCardCount;
    asserttrue(count2==count1+1, r_main);
    if (NOISY_TEST) printf("Played count before: %d\nPlayed count after: %d\n", count1, count2);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Card at handPos added to playedCards\n", caseCount, casename, ++(*testCount));
    asserttrue(G->playedCards[G->playedCardCount-1] == preG->hand[player][handPos], r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Card at handPos removed from current player's hand\n", caseCount, casename, ++(*testCount));
    count1 = getNumCardsHand(player, card, preG);
    count2 = getNumCardsHand(player, card, G);
    asserttrue(count2==count1-1, r_main);
    if (NOISY_TEST) printf("Card at handPos: %s\nCard count before: %d\nCard count after: %d\n", 
        getCardName(preG->hand[player][handPos]), count1, count2);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Game state unchanged except for played card and current player\n", caseCount, casename, ++(*testCount));
    memcpy(&preG_mod, G, sizeof(struct gameState));
    preG_mod.handCount[player] = G->handCount[player];  // make current player's hand, deck, discard before execution equal after execution
    for (i=0; i<MAX_HAND; i++) preG_mod.hand[player][i] = G->hand[player][i];
    preG_mod.deckCount[player] = G->deckCount[player];
    for (i=0; i<MAX_DECK; i++) preG_mod.deck[player][i] = G->deck[player][i];
    preG_mod.discardCount[player] = G->discardCount[player];
    for (i=0; i<MAX_DECK; i++) preG_mod.discard[player][i] = G->discard[player][i];
    preG_mod.playedCardCount = G->playedCardCount;
    for (i=0; i<MAX_DECK; i++) preG_mod.playedCards[i] = G->playedCards[i];
    asserttrue(memcmp(G, &preG_mod, sizeof(struct gameState))==0, r_main);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Cards in Hand+Deck+Discard unchanged except removing played card\n", caseCount, casename, ++(*testCount));
    // Copy Hand+Deck+Discard before execution to preG_HandDeckDiscard
    preG_HandDeckDiscardCount = 0;
    for (i=0; i<preG->handCount[player]; i++) {
        preG_HandDeckDiscard[preG_HandDeckDiscardCount] = preG->hand[player][i];
        preG_HandDeckDiscardCount++;
    }
    for (i=0; i<preG->deckCount[player]; i++) {
        preG_HandDeckDiscard[preG_HandDeckDiscardCount] = preG->deck[player][i];
        preG_HandDeckDiscardCount++;
    }
    for (i=0; i<preG->discardCount[player]; i++) {
        preG_HandDeckDiscard[preG_HandDeckDiscardCount] = preG->discard[player][i];
        preG_HandDeckDiscardCount++;
    }
    // Copy Hand+Deck+Discard after execution to G_HandDeckDiscard
    G_HandDeckDiscardCount = 0;
    for (i=0; i<G->handCount[player]; i++) {
        G_HandDeckDiscard[G_HandDeckDiscardCount] = G->hand[player][i];
        G_HandDeckDiscardCount++;
    }
    for (i=0; i<G->deckCount[player]; i++) {
        G_HandDeckDiscard[G_HandDeckDiscardCount] = G->deck[player][i];
        G_HandDeckDiscardCount++;
    }
    for (i=0; i<G->discardCount[player]; i++) {
        G_HandDeckDiscard[G_HandDeckDiscardCount] = G->discard[player][i];
        G_HandDeckDiscardCount++;
    }
    // Make -1 all cards in preG_HandDeckDiscard that appear in G_HandDeckDiscard, and vice versa
    for (i=0; i<preG_HandDeckDiscardCount; i++) {
        for (j=0; j<G_HandDeckDiscardCount; j++) {
            if (preG_HandDeckDiscard[i] == G_HandDeckDiscard[j] && preG_HandDeckDiscard[i] != -1) {
                preG_HandDeckDiscard[i] = -1;
                G_HandDeckDiscard[j] = -1;
                break;
            }
        }
    }
    for (i=0; i<G_HandDeckDiscardCount; i++) {
        for (j=0; j<preG_HandDeckDiscardCount; j++) {
            if (G_HandDeckDiscard[i] == preG_HandDeckDiscard[j] && G_HandDeckDiscard[i] != -1) {
                G_HandDeckDiscard[i] = -1;
                preG_HandDeckDiscard[j] = -1;
                break;
            }
        }
    }
    // There should be no -1 cards in preG_HandDeckDiscard and G_HandDeckDiscard now (except played card)
    count1 = 0;
    for (i=0; i<preG_HandDeckDiscardCount; i++) {
        if (preG_HandDeckDiscard[i] > -1 && preG_HandDeckDiscard[i] != card) {
            count1++;
            if (NOISY_TEST) printf("Card in Hand+Deck+Discard before but not after #%d: %s\n", count1, getCardName(preG_HandDeckDiscard[i]));
        }
    }
    count2 = 0;
    for (i=0; i<G_HandDeckDiscardCount; i++) {
        if (G_HandDeckDiscard[i] > -1) {
            count2++;
            if (NOISY_TEST) printf("Card in Hand+Deck+Discard after but not before #%d: %s\n", count2, getCardName(G_HandDeckDiscard[i]));
        }
    }
    asserttrue(count1==0 && count2==0, r_main);
}



/*********************************************************************/
/* Main */
int main() {
    int seed = 1000;
    struct gameState G, preG;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine, 
      remodel, smithy, village, baron, great_hall};
    int r_main = 0;
    int testCount = 0, caseCount = 0;

    int handPos = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;  // dummy parameters; won't be used for this card
    int player, card, iterCard, i;
    int count1, count2;
    char* casename;

    printf("**********************************************************\n");
    printf("BEGIN testing %s\n", CARD_NAME);
    

/*-------------------------------------------------------------------------*/
    casename = "3 Treasure in Deck, empty Discard";
    caseCount++;
    initializeGame(numPlayer, k, seed, &G);
    player = G.whoseTurn;
    G.hand[player][handPos] = adventurer; // make current card adventurer
    card = G.hand[player][handPos];  // card previously at handPos
    
    /* Construct Deck with 1 Treasure in beginning, 1 Treasure in middle, 1 Treasure in end */
    iterCard = council_room;
    for (i=0; i<G.deckCount[player]; i++) {
        if (G.deck[player][i] == copper || G.deck[player][i] == silver || G.deck[player][i] == gold) {
            G.deck[player][i] = iterCard++;
        }
    }
    G.deck[player][0] = copper;
    G.deck[player][G.deckCount[player]/2] = silver;
    G.deck[player][G.deckCount[player]-1] = gold;

    memcpy(&preG, &G, sizeof(struct gameState));  // save gameState to preG

    /*********/
    testGeneralRequirements(caseCount, casename, &testCount, &r_main,
        card, choice1, choice2, choice3, handPos, &bonus,
        &G, &preG);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Hand count increased by 1\n", caseCount, casename, ++testCount);
    count1 = preG.handCount[player];
    count2 = G.handCount[player];
    asserttrue(count2==count1+1, &r_main);
    if (NOISY_TEST) printf("Hand count before: %d\nHand count after: %d\n", count1, count2);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Hand contains 2 more Treasure\n", caseCount, casename, ++testCount);
    count1 = getNumCardsHand(player, copper, &preG) + getNumCardsHand(player, silver, &preG) + getNumCardsHand(player, gold, &preG);
    count2 = getNumCardsHand(player, copper, &G) + getNumCardsHand(player, silver, &G) + getNumCardsHand(player, gold, &G);
    asserttrue(count1==count2-2, &r_main);
    if (NOISY_TEST) printf("Treasure count before: %d\nTreasure count after: %d\n", count1, count2);


/*-------------------------------------------------------------------------*/
    casename = "1 Treasure in Deck, 1 Treasure in Discard";
    caseCount++;
    initializeGame(numPlayer, k, seed, &G);
    player = G.whoseTurn;
    G.hand[player][handPos] = adventurer; // make current card adventurer
    card = G.hand[player][handPos];  // card previously at handPos
    
    /* Construct Deck with 1 Treasure in middle, Discard with 1 Treasure in middle */
    iterCard = council_room;
    for (i=0; i<G.deckCount[player]; i++) {
        if (G.deck[player][i] == copper || G.deck[player][i] == silver || G.deck[player][i] == gold) {
            G.deck[player][i] = iterCard++;
        }
    }
    G.deck[player][G.deckCount[player]/2] = silver;
    G.discardCount[player] = 3;
    G.discard[player][0] = iterCard++;
    G.discard[player][1] = silver;
    G.discard[player][2] = iterCard++;

    memcpy(&preG, &G, sizeof(struct gameState));  // save gameState to preG

    /*********/
    testGeneralRequirements(caseCount, casename, &testCount, &r_main,
        card, choice1, choice2, choice3, handPos, &bonus,
        &G, &preG);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Hand count increased by 1\n", caseCount, casename, ++testCount);
    count1 = preG.handCount[player];
    count2 = G.handCount[player];
    asserttrue(count2==count1+1, &r_main);
    if (NOISY_TEST) printf("Hand count before: %d\nHand count after: %d\n", count1, count2);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Hand contains 2 more Treasure\n", caseCount, casename, ++testCount);
    count1 = getNumCardsHand(player, copper, &preG) + getNumCardsHand(player, silver, &preG) + getNumCardsHand(player, gold, &preG);
    count2 = getNumCardsHand(player, copper, &G) + getNumCardsHand(player, silver, &G) + getNumCardsHand(player, gold, &G);
    asserttrue(count1==count2-2, &r_main);
    if (NOISY_TEST) printf("Treasure count before: %d\nTreasure count after: %d\n", count1, count2);


/*-------------------------------------------------------------------------*/
    casename = "1 Treasure in Deck, empty Discard";
    caseCount++;
    initializeGame(numPlayer, k, seed, &G);
    player = G.whoseTurn;
    G.hand[player][handPos] = adventurer; // make current card adventurer
    card = G.hand[player][handPos];  // card previously at handPos

    /* Construct Deck with 1 Treasure in middle */
    iterCard = council_room;
    for (i=0; i<G.deckCount[player]; i++) {
        if (G.deck[player][i] == copper || G.deck[player][i] == silver || G.deck[player][i] == gold) {
            G.deck[player][i] = iterCard++;
        }
    }
    G.deck[player][G.deckCount[player]/2] = silver;
    memcpy(&preG, &G, sizeof(struct gameState));  // save gameState to preG

    /*********/
    testGeneralRequirements(caseCount, casename, &testCount, &r_main,
        card, choice1, choice2, choice3, handPos, &bonus,
        &G, &preG);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Hand count unchanged\n", caseCount, casename, ++testCount);
    count1 = preG.handCount[player];
    count2 = G.handCount[player];
    asserttrue(count2==count1, &r_main);
    if (NOISY_TEST) printf("Hand count before: %d\nHand count after: %d\n", count1, count2);

    /*********/
    printf("---------CASE %d: %s -- TEST %d: Hand contains 1 more Treasure\n", caseCount, casename, ++testCount);
    count1 = getNumCardsHand(player, copper, &preG) + getNumCardsHand(player, silver, &preG) + getNumCardsHand(player, gold, &preG);
    count2 = getNumCardsHand(player, copper, &G) + getNumCardsHand(player, silver, &G) + getNumCardsHand(player, gold, &G);
    asserttrue(count1==count2-1, &r_main);
    if (NOISY_TEST) printf("Treasure count before: %d\nTreasure count after: %d\n", count1, count2);


    /*-------------------------------------------------------------------------*/
    /******** Result */
    printf("---------\n");
    printf("Card %s passed %d/%d tests.\n", CARD_NAME, r_main, testCount);
    printf("END testing %s\n", CARD_NAME);
    printf("**********************************************************\n");

    return 0;
}


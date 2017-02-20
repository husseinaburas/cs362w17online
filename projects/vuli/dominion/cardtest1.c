/* cardtest1.c
Card tested: Adventurer

General requirements:
-- Successful execution (return value 0)
-- Decreases Hand+Deck+Discard count by 1
-- Increases playedCardCount by 1
-- Adds card previously at handPos to playedCards
-- Removes card previously at handPos from hand
-- Does not change game state except for current player
-- Does not change Hand+Deck+Discard for current player, except removing played card

Specific requirements:
-- If Deck+Discard previously has 2+ Treasure:
    +) Increases Hand count by 1 (2 Treasure drawn - 1 card played)
    +) Hand contains 2 new Treasure
-- If Deck+Discard previously has 1 Treasure:
    +) Hand count unchanged (1 Treasure drawn - 1 card played)
    +) Hand contains 1 new Treasure
-- If Deck+Discard previously has 0 Treasure:
    +) Decreases Hand count by 1 (- 1 card played)
    +) Hand contains the same number of Treasure as before

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
    printf("BEGIN unit testing %s\n", CARD_NAME);
    

/*-------------------------------------------------------------------------*/
    casename = "2+ Treasure in Deck, no Treasure in Discard";
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
    printf("---------CASE %d: %s -- TEST %d: Hand contains 2 more Treasure\n", caseCount, casename, ++testCount);
    count1 = getNumCardsHand(player, copper, &preG) + getNumCardsHand(player, silver, &preG) + getNumCardsHand(player, gold, &preG);
    count2 = getNumCardsHand(player, copper, &G) + getNumCardsHand(player, silver, &G) + getNumCardsHand(player, gold, &G);
    if (NOISY_TEST) printf("Treasure count before: %d\nTreasure count after: %d\n", count1, count2);
    asserttrue(count1==count2-2, &r_main);


/*-------------------------------------------------------------------------*/
    casename = "No Treasure in Deck, 2 Treasure in Discard";
    caseCount++;
    initializeGame(numPlayer, k, seed, &G);
    player = G.whoseTurn;
    G.hand[player][handPos] = adventurer; // make current card adventurer
    card = G.hand[player][handPos];  // card previously at handPos
    
    /* Construct Deck with no Treasure and Discard with 1 Treasure in beginning, 1 Treasure in middle */
    iterCard = council_room;
    for (i=0; i<G.deckCount[player]; i++) {
        if (G.deck[player][i] == copper || G.deck[player][i] == silver || G.deck[player][i] == gold) {
            G.deck[player][i] = iterCard++;
        }
    }
    G.discardCount[player] = 2;
    G.discard[player][0] = copper;
    G.discard[player][G.discardCount[player]/2] = silver;

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
    printf("---------CASE %d: %s -- TEST %d: Hand contains 2 more Treasure\n", caseCount, casename, ++testCount);
    count1 = getNumCardsHand(player, copper, &preG) + getNumCardsHand(player, silver, &preG) + getNumCardsHand(player, gold, &preG);
    count2 = getNumCardsHand(player, copper, &G) + getNumCardsHand(player, silver, &G) + getNumCardsHand(player, gold, &G);
    if (NOISY_TEST) printf("Treasure count before: %d\nTreasure count after: %d\n", count1, count2);
    asserttrue(count1==count2-2, &r_main);



/*-------------------------------------------------------------------------*/
    casename = "1 Treasure in Deck, 1 Treasure in Discard";  // test shuffle
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
    printf("---------CASE %d: %s -- TEST %d: Hand contains 2 more Treasure\n", caseCount, casename, ++testCount);
    count1 = getNumCardsHand(player, copper, &preG) + getNumCardsHand(player, silver, &preG) + getNumCardsHand(player, gold, &preG);
    count2 = getNumCardsHand(player, copper, &G) + getNumCardsHand(player, silver, &G) + getNumCardsHand(player, gold, &G);
    if (NOISY_TEST) printf("Treasure count before: %d\nTreasure count after: %d\n", count1, count2);
    asserttrue(count1==count2-2, &r_main);


/*-------------------------------------------------------------------------*/
    casename = "1 Treasure in Deck, no Treasure in Discard";  // test shuffle and <1 Treasure
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
    printf("---------CASE %d: %s -- TEST %d: Hand contains 1 more Treasure\n", caseCount, casename, ++testCount);
    count1 = getNumCardsHand(player, copper, &preG) + getNumCardsHand(player, silver, &preG) + getNumCardsHand(player, gold, &preG);
    count2 = getNumCardsHand(player, copper, &G) + getNumCardsHand(player, silver, &G) + getNumCardsHand(player, gold, &G);
    if (NOISY_TEST) printf("Treasure count before: %d\nTreasure count after: %d\n", count1, count2);
    asserttrue(count1==count2-1, &r_main);


/*-------------------------------------------------------------------------*/
    casename = "No Treasure in Deck, 1 Treasure in Discard";  // test shuffle and <1 Treasure
    caseCount++;
    initializeGame(numPlayer, k, seed, &G);
    player = G.whoseTurn;
    G.hand[player][handPos] = adventurer; // make current card adventurer
    card = G.hand[player][handPos];  // card previously at handPos

    /* Construct Deck with no Treasure and Discard with 1 Treasure in middle */
    iterCard = council_room;
    for (i=0; i<G.deckCount[player]; i++) {
        if (G.deck[player][i] == copper || G.deck[player][i] == silver || G.deck[player][i] == gold) {
            G.deck[player][i] = iterCard++;
        }
    }
    G.discardCount[player] = 1;
    G.discard[player][G.discardCount[player]/2] = silver;
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
    printf("---------CASE %d: %s -- TEST %d: Hand contains 1 more Treasure\n", caseCount, casename, ++testCount);
    count1 = getNumCardsHand(player, copper, &preG) + getNumCardsHand(player, silver, &preG) + getNumCardsHand(player, gold, &preG);
    count2 = getNumCardsHand(player, copper, &G) + getNumCardsHand(player, silver, &G) + getNumCardsHand(player, gold, &G);
    if (NOISY_TEST) printf("Treasure count before: %d\nTreasure count after: %d\n", count1, count2);
    asserttrue(count1==count2-1, &r_main);

/*-------------------------------------------------------------------------*/
    casename = "No Treasure in Deck, no Treasure in Discard";  // test 0 Treasure
    caseCount++;
    initializeGame(numPlayer, k, seed, &G);
    player = G.whoseTurn;
    G.hand[player][handPos] = adventurer; // make current card adventurer
    card = G.hand[player][handPos];  // card previously at handPos

    /* Construct Deck with no Treasure and Discard with no Treasure */
    iterCard = council_room;
    for (i=0; i<G.deckCount[player]; i++) {
        if (G.deck[player][i] == copper || G.deck[player][i] == silver || G.deck[player][i] == gold) {
            G.deck[player][i] = iterCard++;
        }
    }
    G.discardCount[player] = 2;
    G.discard[player][0] = smithy;
    G.discard[player][1] = cutpurse;
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
    printf("---------CASE %d: %s -- TEST %d: Hand contains the same number of Treasure\n", caseCount, casename, ++testCount);
    count1 = getNumCardsHand(player, copper, &preG) + getNumCardsHand(player, silver, &preG) + getNumCardsHand(player, gold, &preG);
    count2 = getNumCardsHand(player, copper, &G) + getNumCardsHand(player, silver, &G) + getNumCardsHand(player, gold, &G);
    if (NOISY_TEST) printf("Treasure count before: %d\nTreasure count after: %d\n", count1, count2);
    asserttrue(count1==count2, &r_main);


/*-------------------------------------------------------------------------*/
    /******** Result */
    printf("---------\n");
    printf("Card %s passed %d/%d tests.\n", CARD_NAME, r_main, testCount);
    printf("END unit testing %s\n", CARD_NAME);
    printf("**********************************************************\n\n");

    return 0;
}


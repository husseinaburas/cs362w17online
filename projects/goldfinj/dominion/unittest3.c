#include <string.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testUtil.h"

int main(void) {
    char *testFunc = "gainCard()";
    int seed = 8442;
    int numPlayers = 2;
    int kCards[10] = { council_room, feast, mine, smithy, village,
                       baron, minion, tribute, outpost, sea_hag };
    struct gameState G, testG;
    int currentPlayer;

    int gainedCard; /* enum of card to gain from supply pile */
    int whereTo;    /* 0 = discard pile, 1 = deck, 2 = hand */

    int beforeDeckCount,    afterDeckCount;
    int beforeDiscardCount, afterDiscardCount;
    int beforeHandCount,    afterHandCount;
    int beforeSupplyCount,  afterSupplyCount;

    int i;

    printf("################ TESTING %s ################\n", testFunc);

    /* create reference state */
    initializeGame(numPlayers, kCards, seed, &G);

    printf("\nTEST 1: Gain to discard pile, card in supply\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up */
    gainedCard = council_room;
    whereTo = 0;

    /* record original state */
    beforeDeckCount =       testG.deckCount[currentPlayer];
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeHandCount =       testG.handCount[currentPlayer];
    beforeSupplyCount =     testG.supplyCount[gainedCard];

    /* attempt the gain */
    gainCard(gainedCard, &testG, whereTo, currentPlayer);

    /* record altered state */
    afterDeckCount =        testG.deckCount[currentPlayer];
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterHandCount =        testG.handCount[currentPlayer];
    afterSupplyCount =      testG.supplyCount[gainedCard];

    /* examine the state */
    printTest("Number of cards in discard pile increased by 1",
        beforeDiscardCount + 1, afterDiscardCount);

    printTest("Gained card added to end (top) of discard pile",
        gainedCard, testG.discard[currentPlayer][afterDiscardCount - 1]);

    printTest("Number of cards in deck does not change",
        beforeDeckCount, afterDeckCount);

    printTest("Number of cards in hand does not change",
        beforeHandCount, afterHandCount);

    printTest("Supply pile card count decreased by 1",
        beforeSupplyCount - 1, afterSupplyCount);


    printf("\nTEST 2: Gain to discard pile, 1 card in supply\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up */
    gainedCard = council_room;
    whereTo = 0;
    testG.supplyCount[gainedCard] = 1;

    /* record original state */
    beforeDeckCount =       testG.deckCount[currentPlayer];
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeHandCount =       testG.handCount[currentPlayer];
    beforeSupplyCount =     testG.supplyCount[gainedCard];

    /* attempt the gain */
    gainCard(gainedCard, &testG, whereTo, currentPlayer);

    /* record altered state */
    afterDeckCount =        testG.deckCount[currentPlayer];
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterHandCount =        testG.handCount[currentPlayer];
    afterSupplyCount =      testG.supplyCount[gainedCard];

    /* examine the state */
    printTest("Number of cards in discard pile increased by 1",
        beforeDiscardCount + 1, afterDiscardCount);

    printTest("Gained card added to end (top) of discard pile",
        gainedCard, testG.discard[currentPlayer][afterDiscardCount - 1]);

    printTest("Number of cards in deck does not change",
        beforeDeckCount, afterDeckCount);

    printTest("Number of cards in hand does not change",
        beforeHandCount, afterHandCount);

    printTest("Supply pile card count is 0",
        beforeSupplyCount - 1, afterSupplyCount);


    printf("\nTEST 3: Gain to discard pile, card supply is empty\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up */
    gainedCard = council_room;
    whereTo = 0;
    testG.supplyCount[gainedCard] = 0;

    /* record original state */
    beforeDeckCount =       testG.deckCount[currentPlayer];
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeHandCount =       testG.handCount[currentPlayer];
    beforeSupplyCount =     testG.supplyCount[gainedCard];

    /* attempt the gain */
    gainCard(gainedCard, &testG, whereTo, currentPlayer);

    /* record altered state */
    afterDeckCount =        testG.deckCount[currentPlayer];
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterHandCount =        testG.handCount[currentPlayer];
    afterSupplyCount =      testG.supplyCount[gainedCard];

    /* examine the state */
    printTest("Number of cards in discard pile does not change",
        beforeDiscardCount, afterDiscardCount);

    printTest("Number of cards in deck does not change",
        beforeDeckCount, afterDeckCount);

    printTest("Number of cards in hand does not change",
        beforeHandCount, afterHandCount);

    printTest("Supply pile card count is 0",
        beforeSupplyCount, afterSupplyCount);


    printf("\nTEST 4: Gain to discard pile, card not in game\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up */
    gainedCard = cutpurse;
    whereTo = 0;
    testG.supplyCount[gainedCard] = -1;

    /* record original state */
    beforeDeckCount =       testG.deckCount[currentPlayer];
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeHandCount =       testG.handCount[currentPlayer];
    beforeSupplyCount =     testG.supplyCount[gainedCard];

    /* attempt the gain */
    gainCard(gainedCard, &testG, whereTo, currentPlayer);

    /* record altered state */
    afterDeckCount =        testG.deckCount[currentPlayer];
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterHandCount =        testG.handCount[currentPlayer];
    afterSupplyCount =      testG.supplyCount[gainedCard];

    /* examine the state */
    printTest("Number of cards in discard pile does not change",
        beforeDiscardCount, afterDiscardCount);

    printTest("Number of cards in deck does not change",
        beforeDeckCount, afterDeckCount);

    printTest("Number of cards in hand does not change",
        beforeHandCount, afterHandCount);

    printTest("Supply pile card count is -1",
        beforeSupplyCount, afterSupplyCount);


    printf("\nTEST 5: Gain to deck, card in supply\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up */
    gainedCard = council_room;
    whereTo = 1;

    /* record original state */
    beforeDeckCount =       testG.deckCount[currentPlayer];
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeHandCount =       testG.handCount[currentPlayer];
    beforeSupplyCount =     testG.supplyCount[gainedCard];

    /* attempt the gain */
    gainCard(gainedCard, &testG, whereTo, currentPlayer);

    /* record altered state */
    afterDeckCount =        testG.deckCount[currentPlayer];
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterHandCount =        testG.handCount[currentPlayer];
    afterSupplyCount =      testG.supplyCount[gainedCard];

    /* examine the state */
    printTest("Number of cards in discard pile does not change",
        beforeDiscardCount, afterDiscardCount);

    printTest("Number of cards in deck increased by 1",
        beforeDeckCount + 1, afterDeckCount);

    printTest("Gained card added to end (top) of deck",
        gainedCard, testG.deck[currentPlayer][afterDeckCount - 1]);

    printTest("Number of cards in hand does not change",
        beforeHandCount, afterHandCount);

    printTest("Supply pile card count decreased by 1",
        beforeSupplyCount - 1, afterSupplyCount);


    printf("\nTEST 6: Gain to hand, card in supply\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up */
    gainedCard = council_room;
    whereTo = 2;

    /* record original state */
    beforeDeckCount =       testG.deckCount[currentPlayer];
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeHandCount =       testG.handCount[currentPlayer];
    beforeSupplyCount =     testG.supplyCount[gainedCard];

    /* attempt the gain */
    gainCard(gainedCard, &testG, whereTo, currentPlayer);

    /* record altered state */
    afterDeckCount =        testG.deckCount[currentPlayer];
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterHandCount =        testG.handCount[currentPlayer];
    afterSupplyCount =      testG.supplyCount[gainedCard];

    /* examine the state */
    printTest("Number of cards in discard pile does not change",
        beforeDiscardCount, afterDiscardCount);

    printTest("Number of cards in deck does not change",
        beforeDeckCount, afterDeckCount);

    printTest("Number of cards in hand increased by 1",
        beforeHandCount + 1, afterHandCount);

    printTest("Gained card added to end (back) of hand",
        gainedCard, testG.hand[currentPlayer][afterHandCount - 1]);

    printTest("Supply pile card count decreased by 1",
        beforeSupplyCount - 1, afterSupplyCount);

    printf("Hand before: ");
    for (i = 0; i != beforeHandCount; ++i) {
        printf("%d ", G.hand[currentPlayer][i]);
    }
    printf("\nHand after: ");
    for (i = 0; i != afterHandCount; ++i) {
        printf("%d ", testG.hand[currentPlayer][i]);
    }
    printf("\n");

    printf("\n################ END %s TEST ################\n\n", testFunc);

    return 0;
}
#include <string.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testUtil.h"

int main(void) {
    char *testFunc = "playAdventurer()";
    int seed = 8544;
    int numPlayers = 2;
    int kCards[10] = { adventurer, feast, mine, smithy, village,
                       baron, minion, tribute, outpost, sea_hag };
    struct gameState G, testG;
    int currentPlayer;

    int beforeDiscardCount, afterDiscardCount;
    int beforeDeckCount,    afterDeckCount;
    int beforeHandCount,    afterHandCount;
    int beforePlayedCount,  afterPlayedCount;
    int expectedFirst,      actualFirst;
    int expectedSecond,     actualSecond;


    printf("################ TESTING %s ################\n", testFunc);

    /* create reference state */
    initializeGame(numPlayers, kCards, seed, &G);

    printf("\nTEST 1: Two treasure cards in deck\n\n");

    /* NOTE: previously caused segmentation fault due to infinite loop,
       playAdventurer() updated to have a less severe bug */

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the deck */
    testG.deck[currentPlayer][0] = gold;
    testG.deck[currentPlayer][1] = smithy;
    testG.deck[currentPlayer][2] = smithy;
    testG.deck[currentPlayer][3] = smithy;
    testG.deck[currentPlayer][4] = silver;
    testG.deck[currentPlayer][5] = smithy; /* top */
    testG.deckCount[currentPlayer] = 6;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeDeckCount =       testG.deckCount[currentPlayer];
    beforeHandCount =       testG.handCount[currentPlayer];
    beforePlayedCount =     testG.playedCardCount;
    expectedFirst =         testG.deck[currentPlayer][4];
    expectedSecond =        testG.deck[currentPlayer][0];

    /* play the card */
    playAdventurer(&testG);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterDeckCount =        testG.deckCount[currentPlayer];
    afterHandCount =        testG.handCount[currentPlayer];
    afterPlayedCount =      testG.playedCardCount;
    actualFirst =           testG.hand[currentPlayer][afterHandCount - 2];
    actualSecond =          testG.hand[currentPlayer][afterHandCount - 1];

    /* examine the state */
    printTest("Number of cards in discard pile is correct",
        beforeDiscardCount + 5, afterDiscardCount);

    printTest("Number of cards in hand increased by 2",
        beforeHandCount + 2, afterHandCount);

    printTest("Second to last card in hand is correct",
        expectedFirst, actualFirst);

    printTest("Last card in hand is correct",
        expectedSecond, actualSecond);

    printTest("Number of cards in deck is correct",
        beforeDeckCount - 6, afterDeckCount);

    printTest("Played count increased by 1",
        beforePlayedCount + 1, afterPlayedCount);

    printTest("Last played card was Adventurer",
        adventurer, testG.playedCards[afterPlayedCount - 1]);


    printf("\nTEST 2: Entire deck is treasure cards\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the deck */
    testG.deck[currentPlayer][0] = gold;
    testG.deck[currentPlayer][1] = copper;
    testG.deck[currentPlayer][2] = copper;
    testG.deck[currentPlayer][3] = copper;
    testG.deck[currentPlayer][4] = silver;
    testG.deck[currentPlayer][5] = copper; /* top */
    testG.deckCount[currentPlayer] = 6;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeDeckCount =       testG.deckCount[currentPlayer];
    beforeHandCount =       testG.handCount[currentPlayer];
    beforePlayedCount =     testG.playedCardCount;
    expectedFirst =         testG.deck[currentPlayer][5];
    expectedSecond =        testG.deck[currentPlayer][4];

    /* play the card */
    playAdventurer(&testG);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterDeckCount =        testG.deckCount[currentPlayer];
    afterHandCount =        testG.handCount[currentPlayer];
    afterPlayedCount =      testG.playedCardCount;
    actualFirst =           testG.hand[currentPlayer][afterHandCount - 2];
    actualSecond =          testG.hand[currentPlayer][afterHandCount - 1];

    /* examine the state */
    printTest("Number of cards in discard pile increased by 1",
        beforeDiscardCount + 1, afterDiscardCount);

    printTest("Number of cards in hand increased by 2",
        beforeHandCount + 2, afterHandCount);

    printTest("Second to last card in hand is correct",
        expectedFirst, actualFirst);

    printTest("Last card in hand is correct",
        expectedSecond, actualSecond);

    printTest("Number of cards in deck is correct",
        beforeDeckCount - 2, afterDeckCount);

    printTest("Played count increased by 1",
        beforePlayedCount + 1, afterPlayedCount);

    printTest("Last played card was Adventurer",
        adventurer, testG.playedCards[afterPlayedCount - 1]);


    printf("\nTEST 3: No treasure cards in deck, ");
    printf("two in discard pile\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the deck */
    testG.deck[currentPlayer][0] = smithy;
    testG.deck[currentPlayer][1] = adventurer;
    testG.deck[currentPlayer][2] = smithy;
    testG.deck[currentPlayer][3] = smithy;
    testG.deck[currentPlayer][4] = smithy;
    testG.deck[currentPlayer][5] = adventurer;
    testG.deckCount[currentPlayer] = 6;

    /* set up the discard pile */
    testG.discard[currentPlayer][0] = copper;
    testG.discard[currentPlayer][1] = silver;
    testG.discard[currentPlayer][2] = smithy;
    testG.discardCount[currentPlayer] = 3;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeDeckCount =       testG.deckCount[currentPlayer];
    beforeHandCount =       testG.handCount[currentPlayer];
    beforePlayedCount =     testG.playedCardCount;
    expectedFirst =         testG.discard[currentPlayer][0];
    expectedSecond =        testG.discard[currentPlayer][1];

    /* play the card */
    playAdventurer(&testG);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterDeckCount =        testG.deckCount[currentPlayer];
    afterHandCount =        testG.handCount[currentPlayer];
    afterPlayedCount =      testG.playedCardCount;
    actualFirst =           testG.hand[currentPlayer][afterHandCount - 2];
    actualSecond =          testG.hand[currentPlayer][afterHandCount - 1];

    /* examine the state */
    printTest("Number of cards in discard pile and deck decreased by 1",
        beforeDiscardCount + beforeDeckCount - 2 + 1,
        afterDiscardCount + afterDeckCount);

    printTest("Number of cards in hand increased by 2",
        beforeHandCount + 2, afterHandCount);

    printTest("Second to last card in hand is correct",
        1, (expectedFirst == actualFirst) ||
           (expectedFirst == actualSecond));

    printTest("Last card in hand is correct",
        1, (expectedSecond == actualFirst) ||
           (expectedSecond == actualSecond));

    printTest("Played count increased by 1",
        beforePlayedCount + 1, afterPlayedCount);

    printTest("Last played card was Adventurer",
        adventurer, testG.playedCards[afterPlayedCount - 1]);


    printf("\nTEST 4: 1 treasure card in deck, 1 in discard pile\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the deck */
    testG.deck[currentPlayer][0] = smithy;
    testG.deck[currentPlayer][1] = adventurer;
    testG.deck[currentPlayer][2] = smithy;
    testG.deck[currentPlayer][3] = gold;
    testG.deck[currentPlayer][4] = smithy;
    testG.deck[currentPlayer][5] = adventurer;
    testG.deckCount[currentPlayer] = 6;

    /* set up the discard pile */
    testG.discard[currentPlayer][0] = copper;
    testG.discard[currentPlayer][1] = curse;
    testG.discard[currentPlayer][2] = smithy;
    testG.discardCount[currentPlayer] = 3;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeDeckCount =       testG.deckCount[currentPlayer];
    beforeHandCount =       testG.handCount[currentPlayer];
    beforePlayedCount =     testG.playedCardCount;
    expectedFirst =         testG.deck[currentPlayer][3];
    expectedSecond =        testG.discard[currentPlayer][0];

    /* play the card */
    playAdventurer(&testG);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterDeckCount =        testG.deckCount[currentPlayer];
    afterHandCount =        testG.handCount[currentPlayer];
    afterPlayedCount =      testG.playedCardCount;
    actualFirst =           testG.hand[currentPlayer][afterHandCount - 2];
    actualSecond =          testG.hand[currentPlayer][afterHandCount - 1];

    /* examine the state */
    printTest("Number of cards in discard pile and deck decreased by 1",
        beforeDiscardCount + beforeDeckCount - 2 + 1,
        afterDiscardCount + afterDeckCount);

    printTest("Number of cards in hand increased by 2",
        beforeHandCount + 2, afterHandCount);

    printTest("Second to last card in hand is correct",
        expectedFirst, actualFirst);

    printTest("Last card in hand is correct",
        expectedSecond, actualSecond);

    printTest("Played count increased by 1",
        beforePlayedCount + 1, afterPlayedCount);

    printTest("Last played card was Adventurer",
        adventurer, testG.playedCards[afterPlayedCount - 1]);


    printf("\nTEST 5: No treasure in deck or discard piles\n\n");

    printf("ERROR: Test code not run because it would cause an infinite ");
    printf("loop.\n");

    printf("\n################ END %s TEST ################\n\n", testFunc);

    return 0;
}
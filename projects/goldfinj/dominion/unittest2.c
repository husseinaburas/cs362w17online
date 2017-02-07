#include <string.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testUtil.h"

int main(void) {
    char *testFunc = "discardCard()";
    int seed = 8443;
    int numPlayers = 2;
    int kCards[10] = { council_room, feast, mine, smithy, village,
                       baron, minion, tribute, outpost, sea_hag };
    struct gameState G, testG;
    int currentPlayer;

    int handPos;        /* position of card to discard */
    int discardedCard;  /* enum value of card */
    int trashFlag;      /* 0 = discarded, 1 = trashed */

    int beforeDiscardCount, afterDiscardCount;
    int beforePlayedCount,  afterPlayedCount;
    int beforeHandCount,    afterHandCount;

    int i;


    printf("################ TESTING %s ################\n", testFunc);

    /* create reference state */
    initializeGame(numPlayers, kCards, seed, &G);

    printf("\nTEST 1: Discard first card in hand\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the discard */
    handPos = 0;
    trashFlag = 0;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforePlayedCount =     testG.playedCardCount;
    beforeHandCount =       testG.handCount[currentPlayer];
    discardedCard =         testG.hand[currentPlayer][handPos];

    /* attempt the discard */
    discardCard(handPos, currentPlayer, &testG, trashFlag);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterPlayedCount =      testG.playedCardCount;
    afterHandCount =        testG.handCount[currentPlayer];

    /* examine the state */
    printTest("Number of cards in discard pile increased by 1",
        beforeDiscardCount + 1, afterDiscardCount);

    printTest("Discarded card added to end (top) of discard pile",
        discardedCard, testG.discard[currentPlayer][afterDiscardCount - 1]);

    printTest("Number of played cards did not change",
        beforePlayedCount, afterPlayedCount);

    printTest("Number of cards in player's hand decreased by 1",
        beforeHandCount - 1, afterHandCount);

    printf("Hand before: ");
    for (i = 0; i != beforeHandCount; ++i) {
        printf("%d ", G.hand[currentPlayer][i]);
    }
    printf("\nHand after: ");
    for (i = 0; i != afterHandCount; ++i) {
        printf("%d ", testG.hand[currentPlayer][i]);
    }
    printf("\n\n");


    printf("\nTEST 2: Discard last card in hand\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the discard */
    handPos = testG.handCount[currentPlayer] - 1;
    trashFlag = 0;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforePlayedCount =     testG.playedCardCount;
    beforeHandCount =       testG.handCount[currentPlayer];
    discardedCard =         testG.hand[currentPlayer][handPos];

    /* attempt the discard */
    discardCard(handPos, currentPlayer, &testG, trashFlag);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterPlayedCount =      testG.playedCardCount;
    afterHandCount =        testG.handCount[currentPlayer];

    /* examine the state */
    printTest("Number of cards in discard pile increased by 1",
        beforeDiscardCount + 1, afterDiscardCount);

    printTest("Discarded card added to end (top) of discard pile",
        discardedCard, testG.discard[currentPlayer][afterDiscardCount - 1]);

    printTest("Number of played cards did not change",
        beforePlayedCount, afterPlayedCount);

    printTest("Number of cards in player's hand decreased by 1",
        beforeHandCount - 1, afterHandCount);

    printf("Hand before: ");
    for (i = 0; i != beforeHandCount; ++i) {
        printf("%d ", G.hand[currentPlayer][i]);
    }
    printf("\nHand after: ");
    for (i = 0; i != afterHandCount; ++i) {
        printf("%d ", testG.hand[currentPlayer][i]);
    }
    printf("\n\n");


    printf("\nTEST 3: Discard from hand with 1 card\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the discard */
    for (i = 1; i != testG.handCount[currentPlayer]; ++i) {
        testG.hand[currentPlayer][i] = -1;
    }
    testG.handCount[currentPlayer] = 1;
    handPos = 0;
    trashFlag = 0;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforePlayedCount =     testG.playedCardCount;
    beforeHandCount =       testG.handCount[currentPlayer];
    discardedCard =         testG.hand[currentPlayer][handPos];

    /* attempt the discard */
    discardCard(handPos, currentPlayer, &testG, trashFlag);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterPlayedCount =      testG.playedCardCount;
    afterHandCount =        testG.handCount[currentPlayer];

    /* examine the state */
    printTest("Number of cards in discard pile increased by 1",
        beforeDiscardCount + 1, afterDiscardCount);

    printTest("Discarded card added to end (top) of discard pile",
        discardedCard, testG.discard[currentPlayer][afterDiscardCount - 1]);

    printTest("Number of played cards did not change",
        beforePlayedCount, afterPlayedCount);

    printTest("Number of cards in player's hand is 0",
        beforeHandCount - 1, afterHandCount);

    printf("Hand before: ");
    for (i = 0; i != beforeHandCount; ++i) {
        printf("%d ", G.hand[currentPlayer][i]);
    }
    printf("\nHand after: ");
    for (i = 0; i != afterHandCount; ++i) {
        printf("%d ", testG.hand[currentPlayer][i]);
    }
    printf("\n\n");


    printf("\nTEST 4: Discard from empty hand\n\n");

    printf("ERROR: Test code not run because it would crash the program.\n\n");


    printf("\nTEST 5: Trash first card in hand\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the discard */
    handPos = 0;
    trashFlag = 1;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforePlayedCount =     testG.playedCardCount;
    beforeHandCount =       testG.handCount[currentPlayer];
    discardedCard =         testG.hand[currentPlayer][handPos];

    /* attempt the trash */
    discardCard(handPos, currentPlayer, &testG, trashFlag);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterPlayedCount =      testG.playedCardCount;
    afterHandCount =        testG.handCount[currentPlayer];

    /* examine the state */
    printTest("Number of cards in discard pile did not change",
        beforeDiscardCount, afterDiscardCount);

    printTest("Number of played cards did not change",
        beforePlayedCount, afterPlayedCount);

    printTest("Number of cards in player's hand decreased by 1",
        beforeHandCount - 1, afterHandCount);

    printf("Hand before: ");
    for (i = 0; i != beforeHandCount; ++i) {
        printf("%d ", G.hand[currentPlayer][i]);
    }
    printf("\nHand after: ");
    for (i = 0; i != afterHandCount; ++i) {
        printf("%d ", testG.hand[currentPlayer][i]);
    }
    printf("\n\n");

    printf("\n################ END %s TEST ################\n", testFunc);

    return 0;
}
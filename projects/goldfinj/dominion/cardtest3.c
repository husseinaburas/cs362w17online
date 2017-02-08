#include <string.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testUtil.h"

int main(void) {
    char *testFunc = "playSalvager()";
    int seed = 8546;
    int numPlayers = 2;
    int kCards[10] = { salvager, feast, mine, smithy, village,
                       baron, minion, tribute, outpost, sea_hag };
    struct gameState G, testG;
    int currentPlayer;

    int beforeDiscardCount, afterDiscardCount;
    int beforeDeckCount,    afterDeckCount;
    int beforeHandCount,    afterHandCount;
    int beforePlayedCount,  afterPlayedCount;
    int beforeNumBuys,      afterNumBuys;
    int beforeCoins,        afterCoins;

    int trashPos;
    int cardPos;    /* test card hand position */
    int stillInHand;

    int i;


    printf("################ TESTING %s ################\n", testFunc);

    /* create reference state */
    initializeGame(numPlayers, kCards, seed, &G);

    printf("\nTEST 1: Trash a Gold, three cards in hand\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the hand */
    testG.hand[currentPlayer][1] = gold;
    testG.hand[currentPlayer][2] = smithy;
    testG.hand[currentPlayer][3] = curse;
    testG.handCount[currentPlayer] = 4;
    trashPos = 1;
    cardPos = 0;    /* Salvager */
    
    /* put test card in hand */
    testG.hand[currentPlayer][0] = salvager;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeDeckCount =       testG.deckCount[currentPlayer];
    beforeHandCount =       testG.handCount[currentPlayer];
    beforePlayedCount =     testG.playedCardCount;
    beforeNumBuys =         testG.numBuys;
    beforeCoins =           testG.coins;

    /* play the card */
    playSalvager(&testG, trashPos, cardPos);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterDeckCount =        testG.deckCount[currentPlayer];
    afterHandCount =        testG.handCount[currentPlayer];
    afterPlayedCount =      testG.playedCardCount;
    afterNumBuys =          testG.numBuys;
    afterCoins =            testG.coins;

    /* examine the state */
    printTest("Number of cards in discard pile increased by 1",
        beforeDiscardCount + 1, afterDiscardCount);

    printTest("Number of cards in hand decreased by 2",
        beforeHandCount - 2, afterHandCount);

    printTest("Number of cards in deck does not change",
        beforeDeckCount, afterDeckCount);

    printTest("Played count increased by 1",
        beforePlayedCount + 1, afterPlayedCount);

    printTest("Last played card was Salvager",
        salvager, testG.playedCards[afterPlayedCount - 1]);

    printTest("Number of Buys increased by 1",
        beforeNumBuys + 1, afterNumBuys);

    printTest("Number of Coins increased by 6",
        beforeCoins + 6, afterCoins);

    for (i = 0; i != afterHandCount; ++i) {
        if (testG.hand[currentPlayer][i] == salvager) {
            stillInHand = 1;
        }
    }

    printTest("Salvager removed from hand", 1, !stillInHand);

    for (i = 0; i != afterHandCount; ++i) {
        if (testG.hand[currentPlayer][i] == gold) {
            stillInHand = 1;
        }
    }

    printTest("Gold removed from hand", 1, !stillInHand);
    
    printf("Hand after: ");
    for (i = 0; i != afterHandCount; ++i) {
        printf("%d ", testG.hand[currentPlayer][i]);
    }
    printf("\n");
    

    printf("\nTEST 2: Trash a Smithy, three cards in hand\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the hand */
    testG.hand[currentPlayer][1] = gold;
    testG.hand[currentPlayer][2] = smithy;
    testG.hand[currentPlayer][3] = curse;
    testG.handCount[currentPlayer] = 4;
    trashPos = 2;
    cardPos = 0;    /* Salvager */
    
    /* put test card in hand */
    testG.hand[currentPlayer][0] = salvager;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeDeckCount =       testG.deckCount[currentPlayer];
    beforeHandCount =       testG.handCount[currentPlayer];
    beforePlayedCount =     testG.playedCardCount;
    beforeNumBuys =         testG.numBuys;
    beforeCoins =           testG.coins;

    /* play the card */
    playSalvager(&testG, trashPos, cardPos);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterDeckCount =        testG.deckCount[currentPlayer];
    afterHandCount =        testG.handCount[currentPlayer];
    afterPlayedCount =      testG.playedCardCount;
    afterNumBuys =          testG.numBuys;
    afterCoins =            testG.coins;

    /* examine the state */
    printTest("Number of cards in discard pile increased by 1",
        beforeDiscardCount + 1, afterDiscardCount);

    printTest("Number of cards in hand decreased by 2",
        beforeHandCount - 2, afterHandCount);

    printTest("Number of cards in deck does not change",
        beforeDeckCount, afterDeckCount);

    printTest("Played count increased by 1",
        beforePlayedCount + 1, afterPlayedCount);

    printTest("Last played card was Salvager",
        salvager, testG.playedCards[afterPlayedCount - 1]);

    printTest("Number of Buys increased by 1",
        beforeNumBuys + 1, afterNumBuys);

    printTest("Number of Coins increased by 4",
        beforeCoins + 4, afterCoins);

    for (i = 0; i != afterHandCount; ++i) {
        if (testG.hand[currentPlayer][i] == salvager) {
            stillInHand = 1;
        }
    }

    printTest("Salvager removed from hand", 1, !stillInHand);

    for (i = 0; i != afterHandCount; ++i) {
        if (testG.hand[currentPlayer][i] == smithy) {
            stillInHand = 1;
        }
    }

    printTest("Smithy removed from hand", 1, !stillInHand);
    
    printf("Hand after: ");
    for (i = 0; i != afterHandCount; ++i) {
        printf("%d ", testG.hand[currentPlayer][i]);
    }
    printf("\n");
    

    printf("\nTEST 3: Trash a Curse, three cards in hand\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the hand */
    testG.hand[currentPlayer][1] = gold;
    testG.hand[currentPlayer][2] = smithy;
    testG.hand[currentPlayer][3] = curse;
    testG.handCount[currentPlayer] = 4;
    trashPos = 3;
    cardPos = 0;    /* Salvager */
    
    /* put test card in hand */
    testG.hand[currentPlayer][0] = salvager;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeDeckCount =       testG.deckCount[currentPlayer];
    beforeHandCount =       testG.handCount[currentPlayer];
    beforePlayedCount =     testG.playedCardCount;
    beforeNumBuys =         testG.numBuys;
    beforeCoins =           testG.coins;

    /* play the card */
    playSalvager(&testG, trashPos, cardPos);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterDeckCount =        testG.deckCount[currentPlayer];
    afterHandCount =        testG.handCount[currentPlayer];
    afterPlayedCount =      testG.playedCardCount;
    afterNumBuys =          testG.numBuys;
    afterCoins =            testG.coins;

    /* examine the state */
    printTest("Number of cards in discard pile increased by 1",
        beforeDiscardCount + 1, afterDiscardCount);

    printTest("Number of cards in hand decreased by 2",
        beforeHandCount - 2, afterHandCount);

    printTest("Number of cards in deck does not change",
        beforeDeckCount, afterDeckCount);

    printTest("Played count increased by 1",
        beforePlayedCount + 1, afterPlayedCount);

    printTest("Last played card was Salvager",
        salvager, testG.playedCards[afterPlayedCount - 1]);

    printTest("Number of Buys increased by 1",
        beforeNumBuys + 1, afterNumBuys);

    printTest("Number of Coins does not change",
        beforeCoins, afterCoins);

    for (i = 0; i != afterHandCount; ++i) {
        if (testG.hand[currentPlayer][i] == salvager) {
            stillInHand = 1;
        }
    }

    printTest("Salvager removed from hand", 1, !stillInHand);

    for (i = 0; i != afterHandCount; ++i) {
        if (testG.hand[currentPlayer][i] == curse) {
            stillInHand = 1;
        }
    }

    printTest("Curse removed from hand", 1, !stillInHand);

    printf("Hand after: ");
    for (i = 0; i != afterHandCount; ++i) {
        printf("%d ", testG.hand[currentPlayer][i]);
    }
    printf("\n");
    

    printf("\nTEST 4: Empty hand, don't trash anything\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the hand */
    testG.handCount[currentPlayer] = 1;
    trashPos = 0;
    cardPos = 0;    /* Salvager */
    
    /* put test card in hand */
    testG.hand[currentPlayer][0] = salvager;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeDeckCount =       testG.deckCount[currentPlayer];
    beforeHandCount =       testG.handCount[currentPlayer];
    beforePlayedCount =     testG.playedCardCount;
    beforeNumBuys =         testG.numBuys;
    beforeCoins =           testG.coins;

    /* play the card */
    playSalvager(&testG, trashPos, cardPos);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterDeckCount =        testG.deckCount[currentPlayer];
    afterHandCount =        testG.handCount[currentPlayer];
    afterPlayedCount =      testG.playedCardCount;
    afterNumBuys =          testG.numBuys;
    afterCoins =            testG.coins;

    /* examine the state */
    printTest("Number of cards in discard pile increased by 1",
        beforeDiscardCount + 1, afterDiscardCount);

    printTest("Number of cards in hand decreased by 1",
        beforeHandCount - 1, afterHandCount);

    printTest("Number of cards in deck does not change",
        beforeDeckCount, afterDeckCount);

    printTest("Played count increased by 1",
        beforePlayedCount + 1, afterPlayedCount);

    printTest("Last played card was Salvager",
        salvager, testG.playedCards[afterPlayedCount - 1]);

    printTest("Number of Buys increased by 1",
        beforeNumBuys + 1, afterNumBuys);

    printTest("Number of Coins does not change",
        beforeCoins, afterCoins);

    for (i = 0; i != afterHandCount; ++i) {
        if (testG.hand[currentPlayer][i] == salvager) {
            stillInHand = 1;
        }
    }

    printTest("Salvager removed from hand", 1, !stillInHand);
    
    printf("Hand after: ");
    for (i = 0; i != afterHandCount; ++i) {
        printf("%d ", testG.hand[currentPlayer][i]);
    }
    printf("\n");

    printf("\n################ END %s TEST ################\n\n", testFunc);

    return 0;
}
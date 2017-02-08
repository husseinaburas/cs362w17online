#include <string.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testUtil.h"

int main(void) {
    char *testFunc = "playSeaHag()";
    int seed = 8547;
    int numPlayers = 3;
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

    int p1beforeDiscardCount, p1afterDiscardCount;
    int p1beforeDeckCount,    p1afterDeckCount;
    int p2beforeDiscardCount, p2afterDiscardCount;
    int p2beforeDeckCount,    p2afterDeckCount;

    int stillInHand;

    int i;


    printf("################ TESTING %s ################\n", testFunc);

    /* create reference state */
    initializeGame(numPlayers, kCards, seed, &G);

    printf("\nTEST 1: All players have full decks, Curse in supply\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the hand */
    testG.hand[currentPlayer][0] = sea_hag;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeDeckCount =       testG.deckCount[currentPlayer];
    beforeHandCount =       testG.handCount[currentPlayer];
    beforePlayedCount =     testG.playedCardCount;
    beforeNumBuys =         testG.numBuys;
    beforeCoins =           testG.coins;
    p1beforeDiscardCount =  testG.discardCount[1];
    p1beforeDeckCount =     testG.deckCount[1];
    p2beforeDiscardCount =  testG.discardCount[2];
    p2beforeDeckCount =     testG.deckCount[2];

    /* play the card */
    playSeaHag(&testG);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterDeckCount =        testG.deckCount[currentPlayer];
    afterHandCount =        testG.handCount[currentPlayer];
    afterPlayedCount =      testG.playedCardCount;
    afterNumBuys =          testG.numBuys;
    afterCoins =            testG.coins;
    p1afterDiscardCount =   testG.discardCount[1];
    p1afterDeckCount =      testG.deckCount[1];
    p2afterDiscardCount =   testG.discardCount[2];
    p2afterDeckCount =      testG.deckCount[2];

    /* examine the state */
    printTest("Number of cards in discard pile increased by 1",
        beforeDiscardCount + 1, afterDiscardCount);

    printTest("Number of cards in hand decreased by 1",
        beforeHandCount - 1, afterHandCount);

    printTest("Number of cards in deck does not change",
        beforeDeckCount, afterDeckCount);

    printTest("Played count increased by 1",
        beforePlayedCount + 1, afterPlayedCount);

    printTest("Last played card was Sea Hag",
        sea_hag, testG.playedCards[afterPlayedCount - 1]);

    printTest("Number of Buys did not change",
        beforeNumBuys, afterNumBuys);

    printTest("Number of Coins did not change",
        beforeCoins, afterCoins);

    for (i = 0; i != afterHandCount; ++i) {
        if (testG.hand[currentPlayer][i] == sea_hag) {
            stillInHand = 1;
        }
    }

    printTest("Sea Hag removed from hand", 1, !stillInHand);

    printTest("Player 1's deck size did not change",
        p1beforeDeckCount, p1afterDeckCount);

    printTest("Player 1's discard pile size increased by 1",
        p1beforeDiscardCount + 1, p1afterDiscardCount);

    printTest("Player 1's top deck card is a Curse",
        curse, testG.deck[1][p1afterDeckCount - 1]);

    printTest("Player 2's deck size did not change",
        p2beforeDeckCount, p2afterDeckCount);

    printTest("Player 2's discard pile size increased by 1",
        p2beforeDiscardCount + 1, p2afterDiscardCount);

    printTest("Player 2's top deck card is a Curse",
        curse, testG.deck[2][p2afterDeckCount - 1]);
    
    printf("Hand after: ");
    for (i = 0; i != afterHandCount; ++i) {
        printf("%d ", testG.hand[currentPlayer][i]);
    }
    printf("\n");


    printf("\nTEST 2: All players have full decks, 2 Curses in supply\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the hand */
    testG.hand[currentPlayer][0] = sea_hag;

    /* set up the Curse supply */
    testG.supplyCount[curse] = 2;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeDeckCount =       testG.deckCount[currentPlayer];
    beforeHandCount =       testG.handCount[currentPlayer];
    beforePlayedCount =     testG.playedCardCount;
    beforeNumBuys =         testG.numBuys;
    beforeCoins =           testG.coins;
    p1beforeDiscardCount =  testG.discardCount[1];
    p1beforeDeckCount =     testG.deckCount[1];
    p2beforeDiscardCount =  testG.discardCount[2];
    p2beforeDeckCount =     testG.deckCount[2];

    /* play the card */
    playSeaHag(&testG);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterDeckCount =        testG.deckCount[currentPlayer];
    afterHandCount =        testG.handCount[currentPlayer];
    afterPlayedCount =      testG.playedCardCount;
    afterNumBuys =          testG.numBuys;
    afterCoins =            testG.coins;
    p1afterDiscardCount =   testG.discardCount[1];
    p1afterDeckCount =      testG.deckCount[1];
    p2afterDiscardCount =   testG.discardCount[2];
    p2afterDeckCount =      testG.deckCount[2];

    /* examine the state */
    printTest("Number of cards in discard pile increased by 1",
        beforeDiscardCount + 1, afterDiscardCount);

    printTest("Number of cards in hand decreased by 1",
        beforeHandCount - 1, afterHandCount);

    printTest("Number of cards in deck does not change",
        beforeDeckCount, afterDeckCount);

    printTest("Played count increased by 1",
        beforePlayedCount + 1, afterPlayedCount);

    printTest("Last played card was Sea Hag",
        sea_hag, testG.playedCards[afterPlayedCount - 1]);

    printTest("Number of Buys did not change",
        beforeNumBuys, afterNumBuys);

    printTest("Number of Coins did not change",
        beforeCoins, afterCoins);

    for (i = 0; i != afterHandCount; ++i) {
        if (testG.hand[currentPlayer][i] == sea_hag) {
            stillInHand = 1;
        }
    }

    printTest("Sea Hag removed from hand", 1, !stillInHand);

    printTest("Player 1's deck size did not change",
        p1beforeDeckCount, p1afterDeckCount);

    printTest("Player 1's discard pile size increased by 1",
        p1beforeDiscardCount + 1, p1afterDiscardCount);

    printTest("Player 1's top deck card is a Curse",
        curse, testG.deck[1][p1afterDeckCount - 1]);

    printTest("Player 2's deck size did not change",
        p2beforeDeckCount, p2afterDeckCount);

    printTest("Player 2's discard pile size increased by 1",
        p2beforeDiscardCount + 1, p2afterDiscardCount);

    printTest("Player 2's top deck card is a Curse",
        curse, testG.deck[2][p2afterDeckCount - 1]);

    printTest("Curse supply is now empty", 0, testG.supplyCount[curse]);
    
    printf("Hand after: ");
    for (i = 0; i != afterHandCount; ++i) {
        printf("%d ", testG.hand[currentPlayer][i]);
    }
    printf("\n");


    printf("\nTEST 3: All players have full decks, 1 Curse in supply\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the hand */
    testG.hand[currentPlayer][0] = sea_hag;

    /* set up the Curse supply */
    testG.supplyCount[curse] = 1;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeDeckCount =       testG.deckCount[currentPlayer];
    beforeHandCount =       testG.handCount[currentPlayer];
    beforePlayedCount =     testG.playedCardCount;
    beforeNumBuys =         testG.numBuys;
    beforeCoins =           testG.coins;
    p1beforeDiscardCount =  testG.discardCount[1];
    p1beforeDeckCount =     testG.deckCount[1];
    p2beforeDiscardCount =  testG.discardCount[2];
    p2beforeDeckCount =     testG.deckCount[2];

    /* play the card */
    playSeaHag(&testG);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterDeckCount =        testG.deckCount[currentPlayer];
    afterHandCount =        testG.handCount[currentPlayer];
    afterPlayedCount =      testG.playedCardCount;
    afterNumBuys =          testG.numBuys;
    afterCoins =            testG.coins;
    p1afterDiscardCount =   testG.discardCount[1];
    p1afterDeckCount =      testG.deckCount[1];
    p2afterDiscardCount =   testG.discardCount[2];
    p2afterDeckCount =      testG.deckCount[2];

    /* examine the state */
    printTest("Number of cards in discard pile increased by 1",
        beforeDiscardCount + 1, afterDiscardCount);

    printTest("Number of cards in hand decreased by 1",
        beforeHandCount - 1, afterHandCount);

    printTest("Number of cards in deck does not change",
        beforeDeckCount, afterDeckCount);

    printTest("Played count increased by 1",
        beforePlayedCount + 1, afterPlayedCount);

    printTest("Last played card was Sea Hag",
        sea_hag, testG.playedCards[afterPlayedCount - 1]);

    printTest("Number of Buys did not change",
        beforeNumBuys, afterNumBuys);

    printTest("Number of Coins did not change",
        beforeCoins, afterCoins);

    for (i = 0; i != afterHandCount; ++i) {
        if (testG.hand[currentPlayer][i] == sea_hag) {
            stillInHand = 1;
        }
    }

    printTest("Sea Hag removed from hand", 1, !stillInHand);

    printTest("Player 1's deck size did not change",
        p1beforeDeckCount, p1afterDeckCount);

    printTest("Player 1's discard pile size increased by 1",
        p1beforeDiscardCount + 1, p1afterDiscardCount);

    printTest("Player 1's top deck card is a Curse",
        curse, testG.deck[1][p1afterDeckCount - 1]);

    printTest("Player 2's deck size decreased by 1",
        p2beforeDeckCount - 1, p2afterDeckCount);

    printTest("Player 2's discard pile size increased by 1",
        p2beforeDiscardCount + 1, p2afterDiscardCount);

    printTest("Player 2's top deck card is not a Curse",
        1, curse != testG.deck[2][p2afterDeckCount - 1]);

    printTest("Curse supply is now empty", 0, testG.supplyCount[curse]);
    
    printf("Hand after: ");
    for (i = 0; i != afterHandCount; ++i) {
        printf("%d ", testG.hand[currentPlayer][i]);
    }
    printf("\n");


    printf("\nTEST 4: All players have full decks, Curse supply empty\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the hand */
    testG.hand[currentPlayer][0] = sea_hag;

    /* set up the Curse supply */
    testG.supplyCount[curse] = 0;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeDeckCount =       testG.deckCount[currentPlayer];
    beforeHandCount =       testG.handCount[currentPlayer];
    beforePlayedCount =     testG.playedCardCount;
    beforeNumBuys =         testG.numBuys;
    beforeCoins =           testG.coins;
    p1beforeDiscardCount =  testG.discardCount[1];
    p1beforeDeckCount =     testG.deckCount[1];
    p2beforeDiscardCount =  testG.discardCount[2];
    p2beforeDeckCount =     testG.deckCount[2];

    /* play the card */
    playSeaHag(&testG);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterDeckCount =        testG.deckCount[currentPlayer];
    afterHandCount =        testG.handCount[currentPlayer];
    afterPlayedCount =      testG.playedCardCount;
    afterNumBuys =          testG.numBuys;
    afterCoins =            testG.coins;
    p1afterDiscardCount =   testG.discardCount[1];
    p1afterDeckCount =      testG.deckCount[1];
    p2afterDiscardCount =   testG.discardCount[2];
    p2afterDeckCount =      testG.deckCount[2];

    /* examine the state */
    printTest("Number of cards in discard pile increased by 1",
        beforeDiscardCount + 1, afterDiscardCount);

    printTest("Number of cards in hand decreased by 1",
        beforeHandCount - 1, afterHandCount);

    printTest("Number of cards in deck does not change",
        beforeDeckCount, afterDeckCount);

    printTest("Played count increased by 1",
        beforePlayedCount + 1, afterPlayedCount);

    printTest("Last played card was Sea Hag",
        sea_hag, testG.playedCards[afterPlayedCount - 1]);

    printTest("Number of Buys did not change",
        beforeNumBuys, afterNumBuys);

    printTest("Number of Coins did not change",
        beforeCoins, afterCoins);

    for (i = 0; i != afterHandCount; ++i) {
        if (testG.hand[currentPlayer][i] == sea_hag) {
            stillInHand = 1;
        }
    }

    printTest("Sea Hag removed from hand", 1, !stillInHand);

    printTest("Player 1's deck size decreased by 1",
        p1beforeDeckCount - 1, p1afterDeckCount);

    printTest("Player 1's discard pile size increased by 1",
        p1beforeDiscardCount + 1, p1afterDiscardCount);

    printTest("Player 1's top deck card is not a Curse",
        1, curse != testG.deck[1][p1afterDeckCount - 1]);

    printTest("Player 2's deck size decreased by 1",
        p2beforeDeckCount - 1, p2afterDeckCount);

    printTest("Player 2's discard pile size increased by 1",
        p2beforeDiscardCount + 1, p2afterDiscardCount);

    printTest("Player 2's top deck card is not a Curse",
        1, curse != testG.deck[2][p2afterDeckCount - 1]);

    printTest("Curse supply remains empty", 0, testG.supplyCount[curse]);
    
    printf("Hand after: ");
    for (i = 0; i != afterHandCount; ++i) {
        printf("%d ", testG.hand[currentPlayer][i]);
    }
    printf("\n");


    printf("\nTEST 5: Player 1 has just 1 card in deck, Player 2 has ");
    printf("empty deck but some discards, Curse in supply\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the hand */
    testG.hand[currentPlayer][0] = sea_hag;

    /* set up Player 1 */
    testG.deckCount[1] = 1;

    /* set up Player 2 */
    testG.deckCount[2] = 0;
    testG.discard[2][0] = copper;
    testG.discard[2][1] = smithy;
    testG.discardCount[2] = 2;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeDeckCount =       testG.deckCount[currentPlayer];
    beforeHandCount =       testG.handCount[currentPlayer];
    beforePlayedCount =     testG.playedCardCount;
    beforeNumBuys =         testG.numBuys;
    beforeCoins =           testG.coins;
    p1beforeDiscardCount =  testG.discardCount[1];
    p1beforeDeckCount =     testG.deckCount[1];
    p2beforeDiscardCount =  testG.discardCount[2];
    p2beforeDeckCount =     testG.deckCount[2];

    /* play the card */
    playSeaHag(&testG);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterDeckCount =        testG.deckCount[currentPlayer];
    afterHandCount =        testG.handCount[currentPlayer];
    afterPlayedCount =      testG.playedCardCount;
    afterNumBuys =          testG.numBuys;
    afterCoins =            testG.coins;
    p1afterDiscardCount =   testG.discardCount[1];
    p1afterDeckCount =      testG.deckCount[1];
    p2afterDiscardCount =   testG.discardCount[2];
    p2afterDeckCount =      testG.deckCount[2];

    /* examine the state */
    printTest("Number of cards in discard pile increased by 1",
        beforeDiscardCount + 1, afterDiscardCount);

    printTest("Number of cards in hand decreased by 1",
        beforeHandCount - 1, afterHandCount);

    printTest("Number of cards in deck does not change",
        beforeDeckCount, afterDeckCount);

    printTest("Played count increased by 1",
        beforePlayedCount + 1, afterPlayedCount);

    printTest("Last played card was Sea Hag",
        sea_hag, testG.playedCards[afterPlayedCount - 1]);

    printTest("Number of Buys did not change",
        beforeNumBuys, afterNumBuys);

    printTest("Number of Coins did not change",
        beforeCoins, afterCoins);

    for (i = 0; i != afterHandCount; ++i) {
        if (testG.hand[currentPlayer][i] == sea_hag) {
            stillInHand = 1;
        }
    }

    printTest("Sea Hag removed from hand", 1, !stillInHand);

    printTest("Player 1's deck size did not change",
        p1beforeDeckCount, p1afterDeckCount);

    printTest("Player 1's discard pile size increased by 1",
        p1beforeDiscardCount + 1, p1afterDiscardCount);

    printTest("Player 1's top deck card is a Curse",
        curse, testG.deck[1][p1afterDeckCount - 1]);

    printTest("Player 2's deck size is now 1",
        1, p2afterDeckCount);

    printTest("Player 2's discard pile size is now 1",
        1, p2afterDiscardCount);

    printTest("Player 2's top deck card is a Curse",
        curse, testG.deck[2][p2afterDeckCount - 1]);
    
    printf("Hand after: ");
    for (i = 0; i != afterHandCount; ++i) {
        printf("%d ", testG.hand[currentPlayer][i]);
    }
    printf("\n");

    printf("\n################ END %s TEST ################\n\n", testFunc);

    return 0;
}
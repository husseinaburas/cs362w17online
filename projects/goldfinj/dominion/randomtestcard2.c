#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testUtil.h"

void testSalvager(int *testArr, int seed) {
    int numPlayers;
    int kCards[10] = { salvager, feast, mine, smithy, village,
                       baron, minion, tribute, outpost, sea_hag };
    struct gameState G, testG;
    int currentPlayer;
    const int INIT_HAND_MIN = 2;
    const int INIT_HAND_MAX = 20;
    const int INIT_DECK_MIN = 0;
    const int INIT_DECK_MAX = 100;

    int beforeDiscardCount[MAX_PLAYERS],    afterDiscardCount[MAX_PLAYERS];
    int beforeDeckCount[MAX_PLAYERS],       afterDeckCount[MAX_PLAYERS];
    int beforeHandCount,                    afterHandCount;
    int beforePlayedCount,                  afterPlayedCount;
    int beforeNumBuys,                      afterNumBuys;
    int beforeCoins,                        afterCoins;
    int expected,                           actual;
    int i, j;

    int testNo = 1;
    int trashPos;
    int cardCost;

    numPlayers = rand() % (MAX_PLAYERS - 2) + 2;

    /* create reference state */
    initializeGame(numPlayers, kCards, seed, &G);

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn = rand() % numPlayers;

    /* set up players' decks and discard piles */
    for (i = 0; i != numPlayers; ++i) {
        beforeDeckCount[i] = testG.deckCount[i] = rand() % INIT_DECK_MAX;
        for (j = 0; j != beforeDeckCount[i]; ++j) {
            testG.deck[i][j] = rand() % (treasure_map + 1);
        }

        beforeDiscardCount[i] = testG.discardCount[i] = rand() % INIT_DECK_MAX;
        for (j = 0; j != beforeDiscardCount[i]; ++j) {
            testG.discard[i][j] = rand() % (treasure_map + 1);
        }
    }

    /* set up current player's hand */
    testG.handCount[currentPlayer] = rand() % (INIT_HAND_MAX - 1) + INIT_HAND_MIN;
    beforeHandCount = testG.handCount[currentPlayer];

    testG.hand[currentPlayer][0] = salvager;
    for (i = 1; i != beforeHandCount; ++i) {
        testG.hand[currentPlayer][i] = rand() % (treasure_map + 1);
    }

    trashPos = rand() % (beforeHandCount - 1) + 1;
    cardCost = getCost(testG.hand[currentPlayer][trashPos]);

    /* record original state */
    testG.playedCardCount = rand() % (beforeDiscardCount[currentPlayer] + 1);
    beforePlayedCount =     testG.playedCardCount;
    beforeNumBuys =         testG.numBuys;
    beforeCoins =           testG.coins;

    /* play the card */
    playSalvager(&testG, trashPos, 0);

    /* record altered state */
    for (i = 0; i != numPlayers; ++i) {
        afterDeckCount[i] =     testG.deckCount[i];
        afterDiscardCount[i] =  testG.discardCount[i];
    }
    afterHandCount =        testG.handCount[currentPlayer];
    afterPlayedCount =      testG.playedCardCount;
    afterNumBuys =          testG.numBuys;
    afterCoins =            testG.coins;

    /* record info about players' decks and discard piles */
    for (i = 0; i != numPlayers; ++i) {
        afterDeckCount[i] = testG.deckCount[i];
        afterDiscardCount[i] = testG.discardCount[i];
    }

    /* examine the state */
    testArr[testNo++] += printTest("Number of cards in hand is correct",
        beforeHandCount - 2, afterHandCount);

    testArr[testNo++] += printTest("Played count increased by 1",
        beforePlayedCount + 1, afterPlayedCount);

    testArr[testNo++] += printTest("Last played card was Salvager",
        salvager, testG.playedCards[afterPlayedCount - 1]);

    testArr[testNo++] += printTest("Number of Buys increased by 1",
        beforeNumBuys + 1, afterNumBuys);

    testArr[testNo++] += printTest("Number of Coins increased by correct amount",
        beforeCoins + cardCost, afterCoins);

    expected = actual = 0;
    for (i = 0; i != numPlayers; ++i) {
        if (afterDeckCount[i] != beforeDeckCount[i]) {
            ++actual;
        }
    }
    testArr[testNo++] += printTest("Number of players' deck counts changed",
        expected, actual);

    expected = actual = 0;
    for (i = 0; i != numPlayers; ++i) {
        if (afterDiscardCount[i] != beforeDiscardCount[i]) {
            ++actual;
        }
    }
    testArr[testNo++] += printTest("Number of players' discard counts changed",
        expected, actual);
}

int main(int argc, char *argv[]) {
    const int ITERS = 10000;
    const int NUM_TESTS = 7;
    int seed = time(0);
    char *testFunc = "playSalvager()";
    int testSuccesses[NUM_TESTS + 1];
    int i;

    if (argc > 2) {
        seed = atoi(argv[1]);
        printf("%d", seed);
    }

    for (i = 0; i != NUM_TESTS + 1; ++i) {
        testSuccesses[i] = 0;
    }

    srand(seed);

    printf("################ TESTING %s ################\n\n", testFunc);
    
    for (i = 0; i != ITERS; ++i) {
        testSalvager(testSuccesses, seed);
        printf("\n");
    }

    printf("\nTotal Iterations: %d\n\n", ITERS);
    for (i = 1; i != NUM_TESTS + 1; ++i) {
        printf("Test %d: %d Successes\n", i, testSuccesses[i]);
    }

    printf("\n################ END %s TEST ################\n\n", testFunc);

    return 0;
}
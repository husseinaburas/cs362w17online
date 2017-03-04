#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testUtil.h"

void testAdventurer(int *testArr, int seed) {
    int numPlayers;
    int kCards[10] = { adventurer, feast, mine, smithy, village,
                       baron, minion, tribute, outpost, sea_hag };
    struct gameState G, testG;
    int currentPlayer;
    const int INIT_HAND_MIN = 1;
    const int INIT_HAND_MAX = 20;
    const int INIT_DECK_MIN = 0;
    const int INIT_DECK_MAX = 100;

    int beforeDiscardCount[MAX_PLAYERS],    afterDiscardCount[MAX_PLAYERS];
    int beforeDeckCount[MAX_PLAYERS],       afterDeckCount[MAX_PLAYERS];
    int beforeHandCount,                    afterHandCount;
    int beforePlayedCount,                  afterPlayedCount;
    int beforeDeckTreasureCount,            afterDeckTreasureCount;
    int beforeDiscardTreasureCount,         afterDiscardTreasureCount;
    int beforeHandTreasureCount,            afterHandTreasureCount;
    int expected,                           actual;
    int i, j;

    int testNo = 1;

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

    testG.hand[currentPlayer][0] = adventurer;
    for (i = 1; i != beforeHandCount; ++i) {
        testG.hand[currentPlayer][i] = rand() % (treasure_map + 1);
    }

    /* determine number of treasure cards in current player's deck and discard pile */
    beforeDeckTreasureCount = 0;
    for (i = 0; i != beforeDeckCount[currentPlayer]; ++i) {
        j = testG.deck[currentPlayer][i];
        if (j >= copper && j <= gold) {
            ++beforeDeckTreasureCount;
        }
    }

    beforeDiscardTreasureCount = 0;
    for (i = 0; i != beforeDiscardCount[currentPlayer]; ++i) {
        j = testG.discard[currentPlayer][i];
        if (j >= copper && j <= gold) {
            ++beforeDiscardTreasureCount;
        }
    }

    beforeHandTreasureCount = 0;
    for (i = 0; i != beforeHandCount; ++i) {
        j = testG.hand[currentPlayer][i];
        if (j >= copper && j <= gold) {
            ++beforeHandTreasureCount;
        }
    }

    /* record original state */
    testG.playedCardCount = rand() % (beforeDiscardCount[currentPlayer] + 1);
    beforePlayedCount =     testG.playedCardCount;

    /* play the card */
    playAdventurer(&testG, 0);

    /* record altered state */
    for (i = 0; i != numPlayers; ++i) {
        afterDeckCount[i] =     testG.deckCount[i];
        afterDiscardCount[i] =  testG.discardCount[i];
    }
    afterHandCount =        testG.handCount[currentPlayer];
    afterPlayedCount =      testG.playedCardCount;

    /* determine number of treasure cards in current player's deck and discard pile */
    afterDeckTreasureCount = 0;
    for (i = 0; i != afterDeckCount[currentPlayer]; ++i) {
        j = testG.deck[currentPlayer][i];
        if (j >= copper && j <= gold) {
            ++afterDeckTreasureCount;
        }
    }

    afterDiscardTreasureCount = 0;
    for (i = 0; i != afterDiscardCount[currentPlayer]; ++i) {
        j = testG.discard[currentPlayer][i];
        if (j >= copper && j <= gold) {
            ++afterDiscardTreasureCount;
        }
    }

    afterHandTreasureCount = 0;
    for (i = 0; i != afterHandCount; ++i) {
        j = testG.hand[currentPlayer][i];
        if (j >= copper && j <= gold) {
            ++afterHandTreasureCount;
        }
    }

    if (beforeDeckTreasureCount + beforeDiscardTreasureCount >= 2) {
        expected = 2;
    } else {
        expected = beforeDeckTreasureCount + beforeDiscardTreasureCount;
    }

    /* examine the state */
    testArr[testNo++] += printTest("Number of treasure cards in hand is correct",
        beforeHandTreasureCount + expected, afterHandTreasureCount);

    testArr[testNo++] += printTest("Number of cards in hand is correct",
        beforeHandCount + expected - 1, afterHandCount);

    testArr[testNo++] += printTest("Played count increased by 1",
        beforePlayedCount + 1, afterPlayedCount);

    testArr[testNo++] += printTest("Last played card was Adventurer",
        adventurer, testG.playedCards[afterPlayedCount - 1]);

    if (beforeDeckTreasureCount >= 2) {
        expected = beforeDeckTreasureCount - 2;
    } else if (beforeDeckTreasureCount == 1 && beforeDiscardTreasureCount >= 1) {
        expected = beforeDiscardTreasureCount - 1;
    } else if (beforeDeckTreasureCount == 0 && beforeDiscardTreasureCount >= 2) {
        expected = beforeDiscardTreasureCount - 2;
    } else {
        expected = 0;
    }

    testArr[testNo++] += printTest("Number of treasure cards in deck is correct",
        expected, afterDeckTreasureCount);

    if (beforeDeckTreasureCount >= 2) {
        expected = beforeDiscardTreasureCount;
    } else if (beforeDiscardTreasureCount >= 2) {
        expected = 0;
    }

    testArr[testNo++] += printTest("Number of treasure cards in discard pile is correct",
        expected, afterDiscardTreasureCount);

    expected = actual = 0;
    for (i = 0; i != numPlayers; ++i) {
        if (i != currentPlayer) {
            if (afterDeckCount[i] != beforeDeckCount[i]) {
                ++actual;
            }
        }
    }
    testArr[testNo++] += printTest("Number of other players' deck counts changed",
        expected, actual);

    expected = actual = 0;
    for (i = 0; i != numPlayers; ++i) {
        if (i != currentPlayer) {
            if (afterDiscardCount[i] != beforeDiscardCount[i]) {
                ++actual;
            }
        }
    }
    testArr[testNo++] += printTest("Number of other players' discard counts changed",
        expected, actual);
}

int main(int argc, char *argv[]) {
    const int ITERS = 10000;
    const int NUM_TESTS = 8;
    int seed = time(0);
    char *testFunc = "playAdventurer()";
    int testSuccesses[NUM_TESTS + 1];
    int i;

    if (argc > 1) {
        seed = atoi(argv[1]);
        printf("%d", seed);
    }

    for (i = 0; i != NUM_TESTS + 1; ++i) {
        testSuccesses[i] = 0;
    }

    srand(seed);

    printf("################ TESTING %s ################\n\n", testFunc);
    
    for (i = 0; i != ITERS; ++i) {
        testAdventurer(testSuccesses, seed);
        printf("\n");
    }

    printf("\nTotal Iterations: %d\n\n", ITERS);
    for (i = 1; i != NUM_TESTS + 1; ++i) {
        printf("Test %d: %d Successes\n", i, testSuccesses[i]);
    }

    printf("\n################ END %s TEST ################\n\n", testFunc);

    return 0;
}
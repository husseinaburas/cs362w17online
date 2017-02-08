#include <string.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testUtil.h"

int main(void) {
    char *testFunc = "playSmithy()";
    int seed = 8545;
    int numPlayers = 2;
    int kCards[10] = { council_room, feast, mine, smithy, village,
                       baron, minion, tribute, outpost, sea_hag };
    struct gameState G, testG;
    int currentPlayer;

    int beforeDiscardCount, afterDiscardCount;
    int beforeDeckCount,    afterDeckCount;
    int beforeHandCount,    afterHandCount;
    int beforePlayedCount,  afterPlayedCount;


    printf("################ TESTING %s ################\n", testFunc);

    /* create reference state */
    initializeGame(numPlayers, kCards, seed, &G);

    printf("\nTEST 1: Deck contains 3 cards\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the deck */
    testG.deck[currentPlayer][0] = gold;
    testG.deck[currentPlayer][1] = smithy;
    testG.deck[currentPlayer][2] = smithy; /* top */
    testG.deckCount[currentPlayer] = 3;
    
    /* put test card in hand */
    testG.hand[currentPlayer][0] = smithy;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeDeckCount =       testG.deckCount[currentPlayer];
    beforeHandCount =       testG.handCount[currentPlayer];
    beforePlayedCount =     testG.playedCardCount;

    /* play the card */
    playSmithy(&testG, 0);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterDeckCount =        testG.deckCount[currentPlayer];
    afterHandCount =        testG.handCount[currentPlayer];
    afterPlayedCount =      testG.playedCardCount;

    /* examine the state */
    printTest("Number of cards in discard pile increased by 1",
        beforeDiscardCount + 1, afterDiscardCount);

    printTest("Number of cards in hand increased by 2",
        beforeHandCount + 2, afterHandCount);

    printTest("Number of cards in deck decreased by 3",
        beforeDeckCount - 3, afterDeckCount);

    printTest("Played count increased by 1",
        beforePlayedCount + 1, afterPlayedCount);

    printTest("Last played card was Smithy",
        smithy, testG.playedCards[afterPlayedCount - 1]);


    printf("\nTEST 2: Deck contains 2 cards\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the deck */
    testG.deck[currentPlayer][0] = smithy;
    testG.deck[currentPlayer][1] = smithy; /* top */
    testG.deckCount[currentPlayer] = 2;
    
    /* put test card in hand */
    testG.hand[currentPlayer][0] = smithy;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeDeckCount =       testG.deckCount[currentPlayer];
    beforeHandCount =       testG.handCount[currentPlayer];
    beforePlayedCount =     testG.playedCardCount;

    /* play the card */
    playSmithy(&testG, 0);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterDeckCount =        testG.deckCount[currentPlayer];
    afterHandCount =        testG.handCount[currentPlayer];
    afterPlayedCount =      testG.playedCardCount;

    /* examine the state */
    printTest("Number of cards in discard pile increased by 1",
        beforeDiscardCount + 1, afterDiscardCount);

    printTest("Number of cards in hand increased by 1",
        beforeHandCount + 1, afterHandCount);

    printTest("Number of cards in deck decreased by 2",
        beforeDeckCount - 2, afterDeckCount);

    printTest("Played count increased by 1",
        beforePlayedCount + 1, afterPlayedCount);

    printTest("Last played card was Smithy",
        smithy, testG.playedCards[afterPlayedCount - 1]);


    printf("\nTEST 3: Deck and discard pile are empty\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the deck */
    testG.deckCount[currentPlayer] = 0;
    
    /* put test card in hand */
    testG.hand[currentPlayer][0] = smithy;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeDeckCount =       testG.deckCount[currentPlayer];
    beforeHandCount =       testG.handCount[currentPlayer];
    beforePlayedCount =     testG.playedCardCount;

    /* play the card */
    playSmithy(&testG, 0);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterDeckCount =        testG.deckCount[currentPlayer];
    afterHandCount =        testG.handCount[currentPlayer];
    afterPlayedCount =      testG.playedCardCount;

    /* examine the state */
    printTest("Number of cards in discard pile increased by 1",
        beforeDiscardCount + 1, afterDiscardCount);

    printTest("Number of cards in hand decreased by 1",
        beforeHandCount - 1, afterHandCount);

    printTest("Number of cards in deck remained 0",
        beforeDeckCount, afterDeckCount);

    printTest("Played count increased by 1",
        beforePlayedCount + 1, afterPlayedCount);

    printTest("Last played card was Smithy",
        smithy, testG.playedCards[afterPlayedCount - 1]);


    printf("\nTEST 4: Deck and discard pile each have 1 card\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the deck and discard piles */
    testG.deck[currentPlayer][0] = copper;
    testG.deckCount[currentPlayer] = 1;
    testG.discard[currentPlayer][0] = silver;
    testG.discardCount[currentPlayer] = 1;
    
    /* put test card in hand */
    testG.hand[currentPlayer][0] = smithy;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeDeckCount =       testG.deckCount[currentPlayer];
    beforeHandCount =       testG.handCount[currentPlayer];
    beforePlayedCount =     testG.playedCardCount;

    /* play the card */
    playSmithy(&testG, 0);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterDeckCount =        testG.deckCount[currentPlayer];
    afterHandCount =        testG.handCount[currentPlayer];
    afterPlayedCount =      testG.playedCardCount;

    /* examine the state */
    printTest("Number of cards in discard pile remained the same",
        beforeDiscardCount, afterDiscardCount);

    printTest("Number of cards in hand increased by 1",
        beforeHandCount + 1, afterHandCount);

    printTest("Number of cards in deck decreased by 1",
        beforeDeckCount - 1, afterDeckCount);

    printTest("Played count increased by 1",
        beforePlayedCount + 1, afterPlayedCount);

    printTest("Last played card was Smithy",
        smithy, testG.playedCards[afterPlayedCount - 1]);

    printf("\n################ END %s TEST ################\n\n", testFunc);

    return 0;
}
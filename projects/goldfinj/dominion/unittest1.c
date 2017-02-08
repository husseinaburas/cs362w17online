#include <string.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testUtil.h"

int main(void) {
    char *testFunc = "buyCard()";
    int seed = 8444;
    int numPlayers = 2;
    int kCards[10] = { council_room, feast, mine, smithy, village,
                       baron, minion, tribute, outpost, sea_hag };
    struct gameState G, testG;
    int currentPlayer;

    int purchaseCard;
    int cardCost;

    int beforeDiscardCount, afterDiscardCount;
    int beforeSupplyCount,  afterSupplyCount;
    int beforeNumBuys,      afterNumBuys;
    int beforeNumCoins,     afterNumCoins;


    printf("################ TESTING %s ################\n", testFunc);

    /* create reference state */
    initializeGame(numPlayers, kCards, seed, &G);

    printf("\nTEST 1: Player has more than 1 Buy, can afford card, card in supply\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the purchase */
    testG.numBuys = 2;
    testG.coins = 10;
    purchaseCard = council_room;
    cardCost = 5;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeSupplyCount =     testG.supplyCount[purchaseCard];
    beforeNumBuys =         testG.numBuys;
    beforeNumCoins =        testG.coins;

    /* attempt the purchase */
    buyCard(purchaseCard, &testG);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterSupplyCount =      testG.supplyCount[purchaseCard];
    afterNumBuys =          testG.numBuys;
    afterNumCoins =         testG.coins;

    /* examine the state */
    printTest("Number of cards in discard pile increased by 1",
        beforeDiscardCount + 1, afterDiscardCount);

    printTest("Purchased card added to end (top) of discard pile",
        purchaseCard, testG.discard[currentPlayer][afterDiscardCount - 1]);

    printTest("Supply pile card count decreased by 1",
        beforeSupplyCount - 1, afterSupplyCount);

    printTest("Player's number of Buys decreased by 1",
        beforeNumBuys - 1, afterNumBuys);

    printTest("Player's number of Coins decreased by correct amount",
        beforeNumCoins - cardCost, afterNumCoins);


    printf("\nTEST 2: Player has 1 Buy, can afford card, card in supply\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the purchase */
    testG.numBuys = 1;
    testG.coins = 10;
    purchaseCard = council_room;
    cardCost = 5;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeSupplyCount =     testG.supplyCount[purchaseCard];
    beforeNumBuys =         testG.numBuys;
    beforeNumCoins =        testG.coins;

    /* attempt the purchase */
    buyCard(purchaseCard, &testG);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterSupplyCount =      testG.supplyCount[purchaseCard];
    afterNumBuys =          testG.numBuys;
    afterNumCoins =         testG.coins;

    /* examine the state */
    printTest("Number of cards in discard pile increased by 1",
        beforeDiscardCount + 1, afterDiscardCount);

    printTest("Purchased card added to end (top) of discard pile",
        purchaseCard, testG.discard[currentPlayer][afterDiscardCount - 1]);

    printTest("Supply pile card count decreased by 1",
        beforeSupplyCount - 1, afterSupplyCount);

    printTest("Player's number of Buys is 0",
        beforeNumBuys - 1, afterNumBuys);

    printTest("Player's number of Coins decreased by correct amount",
        beforeNumCoins - cardCost, afterNumCoins);


    printf("\nTEST 3: Player has no Buys, can afford card, card in supply\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the purchase */
    testG.numBuys = 0;
    testG.coins = 10;
    purchaseCard = council_room;
    cardCost = 5;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeSupplyCount =     testG.supplyCount[purchaseCard];
    beforeNumBuys =         testG.numBuys;
    beforeNumCoins =        testG.coins;

    /* attempt the purchase */
    buyCard(purchaseCard, &testG);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterSupplyCount =      testG.supplyCount[purchaseCard];
    afterNumBuys =          testG.numBuys;
    afterNumCoins =         testG.coins;

    /* examine the state */
    printTest("Number of cards in discard pile does not change",
        beforeDiscardCount, afterDiscardCount);

    printTest("Supply pile card count does not change",
        beforeSupplyCount, afterSupplyCount);

    printTest("Player's number of Buys remains 0",
        beforeNumBuys, afterNumBuys);

    printTest("Player's number of Coins does not change",
        beforeNumCoins, afterNumCoins);


    printf("\nTEST 4: Player has 1 Buy, cannot afford card, card in supply\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the purchase */
    testG.numBuys = 1;
    testG.coins = 4;
    purchaseCard = council_room;
    cardCost = 5;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeSupplyCount =     testG.supplyCount[purchaseCard];
    beforeNumBuys =         testG.numBuys;
    beforeNumCoins =        testG.coins;

    /* attempt the purchase */
    buyCard(purchaseCard, &testG);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterSupplyCount =      testG.supplyCount[purchaseCard];
    afterNumBuys =          testG.numBuys;
    afterNumCoins =         testG.coins;

    /* examine the state */
    printTest("Number of cards in discard pile does not change",
        beforeDiscardCount, afterDiscardCount);

    printTest("Supply pile card count does not change",
        beforeSupplyCount, afterSupplyCount);

    printTest("Player's number of Buys remains 0",
        beforeNumBuys, afterNumBuys);

    printTest("Player's number of Coins does not change",
        beforeNumCoins, afterNumCoins);


    printf("\nTEST 5: Player has 1 Buy, can afford card, supply pile empty\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the purchase */
    testG.numBuys = 1;
    testG.coins = 5;
    purchaseCard = council_room;
    cardCost = 5;
    testG.supplyCount[purchaseCard] = 0;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeSupplyCount =     testG.supplyCount[purchaseCard];
    beforeNumBuys =         testG.numBuys;
    beforeNumCoins =        testG.coins;

    /* attempt the purchase */
    buyCard(purchaseCard, &testG);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterSupplyCount =      testG.supplyCount[purchaseCard];
    afterNumBuys =          testG.numBuys;
    afterNumCoins =         testG.coins;

    /* examine the state */
    printTest("Number of cards in discard pile does not change",
        beforeDiscardCount, afterDiscardCount);

    printTest("Supply pile card count remains 0",
        beforeSupplyCount, afterSupplyCount);

    printTest("Player's number of Buys remains 0",
        beforeNumBuys, afterNumBuys);

    printTest("Player's number of Coins does not change",
        beforeNumCoins, afterNumCoins);


    printf("\nTEST 6: Player has 1 Buy, can afford card, card not in game at all\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the purchase */
    testG.numBuys = 1;
    testG.coins = 4;
    purchaseCard = cutpurse;
    cardCost = 4;
    testG.supplyCount[purchaseCard] = 0;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeSupplyCount =     testG.supplyCount[purchaseCard];
    beforeNumBuys =         testG.numBuys;
    beforeNumCoins =        testG.coins;

    /* attempt the purchase */
    buyCard(purchaseCard, &testG);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterSupplyCount =      testG.supplyCount[purchaseCard];
    afterNumBuys =          testG.numBuys;
    afterNumCoins =         testG.coins;

    /* examine the state */
    printTest("Number of cards in discard pile does not change",
        beforeDiscardCount, afterDiscardCount);

    printTest("Supply pile card count remains 0",
        beforeSupplyCount, afterSupplyCount);

    printTest("Player's number of Buys remains 0",
        beforeNumBuys, afterNumBuys);

    printTest("Player's number of Coins does not change",
        beforeNumCoins, afterNumCoins);


    printf("\nTEST 7: Player has 1 Buy, can afford card, supply pile has 1 ");
    printf("card\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    currentPlayer = testG.whoseTurn;

    /* set up the purchase */
    testG.numBuys = 1;
    testG.coins = 4;
    purchaseCard = cutpurse;
    cardCost = 4;
    testG.supplyCount[purchaseCard] = 1;

    /* record original state */
    beforeDiscardCount =    testG.discardCount[currentPlayer];
    beforeSupplyCount =     testG.supplyCount[purchaseCard];
    beforeNumBuys =         testG.numBuys;
    beforeNumCoins =        testG.coins;

    /* attempt the purchase */
    buyCard(purchaseCard, &testG);

    /* record altered state */
    afterDiscardCount =     testG.discardCount[currentPlayer];
    afterSupplyCount =      testG.supplyCount[purchaseCard];
    afterNumBuys =          testG.numBuys;
    afterNumCoins =         testG.coins;

    /* examine the state */
    printTest("Number of cards in discard pile increased by 1",
        beforeDiscardCount + 1, afterDiscardCount);

    printTest("Purchased card added to end (top) of discard pile",
        purchaseCard, testG.discard[currentPlayer][afterDiscardCount - 1]);

    printTest("Supply pile card count is 0",
        beforeSupplyCount - 1, afterSupplyCount);

    printTest("Player's number of Buys is 0",
        beforeNumBuys - 1, afterNumBuys);

    printTest("Player's number of Coins decreased by correct amount",
        beforeNumCoins - cardCost, afterNumCoins);

    printf("\n################ END %s TEST ################\n\n", testFunc);

    return 0;
}
#include <string.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testUtil.h"

int main(void) {
    char *testFunc = "isGameOver()";
    int seed = 8441;
    int numPlayers = 2;
    int kCards[10] = { council_room, feast, mine, smithy, village,
                       baron, minion, tribute, outpost, sea_hag };
    struct gameState G, testG;


    printf("################ TESTING %s ################\n", testFunc);

    /* create reference state */
    initializeGame(numPlayers, kCards, seed, &G);

    printf("\nTEST 1: Two supply piles empty, Province pile not empty\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    /* set up the situation */
    testG.supplyCount[council_room] = 0;
    testG.supplyCount[feast] = 0;

    /* check whether game ended */
    printTest("Game is not over", 0, isGameOver(&testG));

    /* create reference state */
    initializeGame(numPlayers, kCards, seed, &G);


    printf("\nTEST 2: Three supply piles empty, Province pile not empty\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    /* set up the situation */
    testG.supplyCount[council_room] = 0;
    testG.supplyCount[feast] = 0;
    testG.supplyCount[mine] = 0;

    /* check whether game ended */
    printTest("Game is over", 1, isGameOver(&testG));


    printf("\nTEST 3: Four supply piles empty, Province pile not empty\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    /* set up the situation */
    testG.supplyCount[council_room] = 0;
    testG.supplyCount[feast] = 0;
    testG.supplyCount[mine] = 0;
    testG.supplyCount[smithy] = 0;

    /* check whether game ended */
    printTest("Game is over", 1, isGameOver(&testG));


    printf("\nTEST 4: Two supply piles empty, Province pile empty\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    /* set up the situation */
    testG.supplyCount[council_room] = 0;
    testG.supplyCount[feast] = 0;
    testG.supplyCount[province] = 0;

    /* check whether game ended */
    printTest("Game is over", 1, isGameOver(&testG));


    printf("\nTEST 5: Only Province pile empty\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    /* set up the situation */
    testG.supplyCount[province] = 0;

    /* check whether game ended */
    printTest("Game is over", 1, isGameOver(&testG));


    printf("\nTEST 6: Three treasure piles empty, Province pile not empty\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    /* set up the situation */
    testG.supplyCount[copper] = 0;
    testG.supplyCount[silver] = 0;
    testG.supplyCount[gold] = 0;

    /* check whether game ended */
    printTest("Game is over", 1, isGameOver(&testG));


    printf("\nTEST 7: Three supply piles of different types empty\n\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    /* set up the situation */
    testG.supplyCount[copper] = 0;
    testG.supplyCount[curse] = 0;
    testG.supplyCount[council_room] = 0;

    /* check whether game ended */
    printTest("Game is over", 1, isGameOver(&testG));

    printf("\n################ END %s TEST ################\n\n", testFunc);

    return 0;
}
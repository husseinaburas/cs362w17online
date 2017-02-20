//random test card smithy which I did unit test in assignment2
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "rngs.h"

#define NUM_TESTS 10000

void randomtest(int *pass, int *fail)
{
    int i, j;
    int outcome;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                    remodel, smithy, village, baron, great_hall};

    seed = rand() % 1000 + 1;

    numPlayers = rand() % 5 + 1;

    printf("seed = %d, numPlayers = %d\n", seed, numPlayers);

    outcome = initializeGame(numPlayers, k, seed, &G);
    if (outcome == -1)
    {
        printf("Failed - Game initialization failed.\n");
        (*fail)++;
        return;
    }
    memcpy(&testG, &G, sizeof(struct gameState));

    testG.hand[thisPlayer][testG.handCount[thisPlayer]] = smithy;
    testG.handCount[thisPlayer]++;
    if (G.handCount[thisPlayer] + 1 == testG.handCount[thisPlayer])
    {
        printf("pass,Smithy card given to player.\n");
    }
    else
    {
        printf("Failed,Smithy card not given.\n");
        (*fail)++;
        return;
    }


    DoSmithy(thisPlayer, &testG, 0);
    if (G.handCount[thisPlayer] + 3 == testG.handCount[thisPlayer])
    {
        printf("pass,Player gained 3 new cards, discarded 1.\n");
    }
    else
    {
        printf("Failed,Player did not gain/discard correct # of cards.\n");
        (*fail)++;
        return;
    }


    if (G.supplyCount[estate] == testG.supplyCount[estate])
    {
        printf("Pass,Player gained 3 new cards, discarded 1.\n");
    }
    else
    {
       printf("Failed, Count of estate cards has changed.\n");
       (*fail)++;
       return;
    }
    if (G.supplyCount[duchy] == testG.supplyCount[duchy])
    {

    }
    else
    {
       printf("Failed,Count of duchy cards has changed.\n");
       (*fail)++;
       return;
    }
    if (G.supplyCount[province] == testG.supplyCount[province])
    {
       printf("Pass, Count of province cards unchanged.\n");
    }
    else
    {
       printf("Failed, Count of province cards has changed.\n");
       (*fail)++;
       return;
    }

    printf("TEST Done\n\n");

    (*pass)++;
    return;
}
int main()
{
    int i;
    int pass = 0, fail = 0;

    srand(time(NULL));

    for (i = 0; i < NUM_TESTS; i++)
    {
        randomtest(&pass, &fail);
    }
    return 0;
}

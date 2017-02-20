/*-----------------------------------------------
* Christopher Grant
* CS-362
* Winter 2017
* Assignment-3
* Unit Test 2 - test for ()
------------------------------------------------*/

/*
1. if three piles are empty the game is over
2. if Province pile is gone the game is over
3. if 2 or less are empty the game is still going.
*/



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main(void)
{
    int returnValue;
    int i, j, k;
    int errorCount = 0;
    int seed = 123456;
    int handCount = 0;
    struct gameState game, preGame;
    int kingdom[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    printf("***START OF ISGAMEOVER TESTS***\n");

    for (i = 2; i <= MAX_PLAYERS; i++)
    {
        returnValue = initializeGame(i, kingdom, seed, &game);
        game.supplyCount[province] = 0;
        returnValue = isGameOver(&game);

        if (returnValue != 1)
        {
            errorCount++;
            printf("isGameOver() error %d\n", errorCount);
            printf("Province pile is gone but game did not end\n\n");
        }
    }


    for (i = 2; i <= MAX_PLAYERS; i++)
    {
        for (j = 0; j < 22; j++ )
        {
            returnValue = initializeGame(i, kingdom, seed, &game);
            game.supplyCount[0 + j] = 0;
            game.supplyCount[1 + j] = 0;
            game.supplyCount[2 + j] = 0;
            returnValue = isGameOver(&game);

            if (returnValue != 1)
            {
                errorCount++;
                printf("isGameOver() error %d\n", errorCount);
                printf("Pile's %d, %d, %d are gone but game did not end\n\n", j, j + 1, j + 2);
            }
        }

    }

    for (i = 2; i <= MAX_PLAYERS; i++)
    {
        for (j = 0; j < 22; j++ )
        {
            returnValue = initializeGame(i, kingdom, seed, &game);
            if (j != province)
            {
                game.supplyCount[0 + j] = 0;
            }


            //game.supplyCount[1 + j] = 0;
            //game.supplyCount[2 + j] = 0;
            returnValue = isGameOver(&game);

            if (returnValue != 0)
            {
                errorCount++;
                printf("isGameOver() error %d\n", errorCount);
                printf("Pile %d are gone but game did end\n\n", j);
            }
        }
    }

    for (i = 2; i <= MAX_PLAYERS; i++)
    {
        for (j = 0; j < 22; j++ )
        {
            returnValue = initializeGame(i, kingdom, seed, &game);
            if (j != province)
            {
                game.supplyCount[0 + j] = 0;
            }

            if (j + 1 != province)
            {
                game.supplyCount[1 + j] = 0;
            }

            //game.supplyCount[1 + j] = 0;
            //game.supplyCount[2 + j] = 0;
            returnValue = isGameOver(&game);

            if (returnValue != 0)
            {
                errorCount++;
                printf("isGameOver() error %d\n", errorCount);
                printf("Piles %d, %d are gone but game did end\n\n", j, j + 1);
            }
        }

    }
    if (errorCount == 0)
    {
        printf("ALL TESTS PASSED FOR ISGAMEOVER\n");
    }
    printf("***END OF ISGAMEOVER TESTS***\n\n");
    return 0;
}

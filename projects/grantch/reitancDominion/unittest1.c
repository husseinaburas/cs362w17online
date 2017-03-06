/*-----------------------------------------------
* Christopher Grant
* CS-362
* Winter 2017
* Assignment-5
* Unit Test 1 - test for updatecoins()
* Testing dominion.c code from Craig Allan Reitan (reitanc).
------------------------------------------------*/

/*
1. does not change the other players hands. checked
2. does not change the other players decks. checked
3. adds up the tresure cards in the current players hand and adds them to coins. checked
4. adds bonus to total coins. checked
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

    printf("***START OF UPDATECOINS TESTS***\n");

    for (i = 0; i < 3; i++)
    {
        returnValue = initializeGame(2, kingdom, seed, &game);
        memcpy (&preGame, &game, sizeof(struct gameState));
        //printHand(0, &game);
        for (j = 0; j < 5; j++)
        {
            if (i == 0)
            {
                game.hand[0][j] = copper;
            }
            else if (i == 1)
            {
                game.hand[0][j] = silver;
            }
            else if (i == 2)
            {
                game.hand[0][j] = gold;
            }
        }

        updateCoins(0, &game, 0);
        if (!memcmp(&game.hand[1][0], &preGame.hand[1][0], sizeof(game.hand[1])) == 0)
        {
            errorCount++;
            printf("updateCoins() error %d\n", errorCount);
            printf("moded another players hand\n\n");
        }

        if (!memcmp(&game.deck[1][0], &preGame.deck[1][0], sizeof(game.deck[1])) == 0)
        {
            errorCount++;
            printf("updateCoins() error %d\n", errorCount);
            printf("moded another players deck\n\n");
        }

        if (i == 0)
        {

            //printHand(0, &game);
            if(game.coins != 5)
            {
                errorCount++;
                printf("updateCoins() error %d\n", errorCount);
                printf("Coins should be 5 but are at %d\n\n", game.coins);
            }
        }
        else if (i == 1)
        {
            if(game.coins != 10)
            {
                errorCount++;
                printf("updateCoins() error %d\n", errorCount);
                printf("Coins should be 10 but are at %d\n\n", game.coins);
            }
        }
        else if (i == 2)
        {
            if(game.coins != 15)
            {
                errorCount++;
                printf("updateCoins() error %d\n", errorCount);
                printf("Coins should be 15 but are at %d\n\n", game.coins);
            }
        }
    }


    for (i = 0; i < 100; i++)
    {
        returnValue = initializeGame(2, kingdom, seed, &game);
        memcpy (&preGame, &game, sizeof(struct gameState));

        for (j = 0; j < 5; j++)
        {
            game.hand[0][j] = copper;
        }

        updateCoins(0, &game, i);

        if (!memcmp(&game.hand[1][0], &preGame.hand[1][0], sizeof(game.hand[1])) == 0)
        {
            printf("updateCoins() error %d\n", errorCount);
            printf("moded another players hand\n\n");
        }

        if (!memcmp(&game.deck[1][0], &preGame.deck[1][0], sizeof(game.deck[1])) == 0)
        {
            printf("updateCoins() error %d\n", errorCount);
            printf("moded another players deck\n\n");
        }

        if (game.coins != 5 + i)
        {
            printf("updateCoins() error %d\n", errorCount);
            printf("Coins should be %d but are at %d\n\n", 5 + i, game.coins);
        }
    }
    if (errorCount == 0)
    {
        printf("ALL TESTS PASSED FOR UPDATECOINS\n");
    }
    printf("***END OF UPDATECOINS TESTS***\n\n");
    return 0;
}

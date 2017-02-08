/*-----------------------------------------------
* Christopher Grant
* CS-362
* Winter 2017
* Assignment-3
* Card Test 4 - test for cardAdventurer()
------------------------------------------------*/

/*
Card rules.
1. current player gets +2 coin. Checked!
2. other players with copper in hands lose 1 copper. Checked!
3. players that lose copper goes into their dicard pile. Checked!
4. if a player has no copper cards nothing happens to their hand. checked!
5.
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
    int i, j, l;
    int errorCount = 0;
    int seed = 123456;
    int handCount = 0;
    struct gameState game, preGame;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    printf("***START OF CUTPURSE TESTS***\n");
    for (i = 2; i <= MAX_PLAYERS; i++)
    {
        returnValue = initializeGame(i, k, seed, &game);
        game.hand[0][0] = cutpurse;
        memcpy (&preGame, &game, sizeof(struct gameState));
        handCount = numHandCards(&game);


        //adding cards to other players hands
        for (j = 1; j < 4; j++)
        {
            for (l = 0; l < 5; l++)
            {
                game.hand[j][l] = smithy;
                game.handCount[j]++;
            }
        }

        game.hand[1][0] = copper; //adding copper to players 2 hand
        game.hand[2][2] = copper; //adding copper to players 3 hand
        game.hand[3][1] = copper; //adding copper to players 4 hand
        updateCoins(0, &preGame, 0);
        //printHand(1, &game);
        cardCutpurse(&game, 0); //setup preGame coin count for compare

        //printHand(0, &preGame);
        //printf("%d %d\n", preGame.coins, game.coins);
        if (preGame.coins + 2 != game.coins)
        {
            errorCount++;
            printf("cardCutpurse() error %d\n", errorCount);
            printf("player 0 did not get +2 coins\n");
            printf("Num of Players: %d\n", i);
            printf("\n");
        }

        if (i >= 2)
        {
            //printDiscard(1, &game);
            //printHand(1, &game);
            if (game.hand[1][0] == copper)
            {
                errorCount++;
                printf("cardCutpurse() error %d\n", errorCount);
                printf("player 2's copper not taken\n");
                printf("Num of Players: %d\n", i);
                printf("\n");
            }

            if(game.playedCards[0] != copper)
            {
                errorCount++;
                printf("cardCutpurse() error %d\n", errorCount);
                printf("player 2's copper not in discard\n");
                printf("Num of Players: %d\n", i);
                printf("\n");
            }
        }

        if (i >= 3)
        {
            if (game.hand[2][2] == copper)
            {
                errorCount++;
                printf("cardCutpurse() error %d\n", errorCount);
                printf("player 3's copper not taken\n");
                printf("Num of Players: %d\n", i);
                printf("\n");
            }

            if(game.playedCards[1] != copper)
            {
                errorCount++;
                printf("cardCutpurse() error %d\n", errorCount);
                printf("player 3's copper not in discard\n");
                printf("Num of Players: %d\n", i);
                printf("\n");
            }
        }

        if (i >= 4)
        {
            if (game.hand[3][1] == copper)
            {
                errorCount++;
                printf("cardCutpurse() error %d\n", errorCount);
                printf("player 4's copper not taken\n");
                printf("Num of Players: %d\n", i);
                printf("\n");
            }

            if(game.playedCards[2] != copper)
            {
                errorCount++;
                printf("cardCutpurse() error %d\n", errorCount);
                printf("player 2's copper not in discard\n");
                printf("Num of Players: %d\n", i);
                printf("\n");
            }
        }
    }

    for (i = 2; i <= MAX_PLAYERS; i++)
    {
        returnValue = initializeGame(i, k, seed, &game);
        game.hand[0][0] = cutpurse;

        //adding cards to other players hands
        for (j = 1; j < 4; j++)
        {
            for (l = 0; l < 5; l++)
            {
                game.hand[j][l] = smithy;
                game.handCount[j]++;
            }
        }

        memcpy (&preGame, &game, sizeof(struct gameState));
        handCount = numHandCards(&game);

        //game.hand[1][0] = copper; //adding copper to players 2 hand
        //game.hand[2][2] = copper; //adding copper to players 3 hand
        //game.hand[3][1] = copper; //adding copper to players 4 hand
        updateCoins(0, &preGame, 0);
        //printHand(1, &game);
        cardCutpurse(&game, 0); //setup preGame coin count for compare

        //printHand(0, &preGame);
        //printf("%d %d\n", preGame.coins, game.coins);
        if (preGame.coins + 2 != game.coins)
        {
            errorCount++;
            printf("cardCutpurse() error %d\n", errorCount);
            printf("player 0 did not get +2 coins\n");
            printf("Num of Players: %d\n", i);
            printf("\n");
        }

        if (i >= 2)
        {
            //printDiscard(1, &game);
            //printHand(1, &game);
            if (!memcmp(&game.hand[2][0], &preGame.hand[2][0], sizeof(game.hand[2])) == 0)
            {
                printf("cardCutpurse() error %d\n", errorCount);
                printf("players 2 hand was moded when it should not of been\n");
                printf("Num of Players: %d\n", i);
                printf("\n");
            }

        }

        if (i >= 3)
        {
            if (!memcmp(&game.hand[3][0], &preGame.hand[3][0], sizeof(game.hand[3])) == 0)
            {
                printf("cardCutpurse() error %d\n", errorCount);
                printf("players 3 hand was moded when it should not of been\n");
                printf("Num of Players: %d\n", i);
                printf("\n");
            }
        }

        if (i >= 4)
        {
            if (!memcmp(&game.hand[3][0], &preGame.hand[3][0], sizeof(game.hand[3])) == 0)
            {
                printf("cardCutpurse() error %d\n", errorCount);
                printf("players 4 hand was moded when it should not of been\n");
                printf("Num of Players: %d\n", i);
                printf("\n");
            }
        }
    }


    if (errorCount == 0)
    {
        printf("ALL TESTS PASSED FOR CUTPURSE\n");
    }
    printf("***END OF CUTPURSE TESTS***\n\n");
    return 0;
}
/*-----------------------------------------------
* Christopher Grant
* CS-362
* Winter 2017
* Assignment-3
* Card Test 2 - test for greatHall()
------------------------------------------------*/

/*
Card rules.
1. Adds one card to players hand. checked!
2. +1 action point. Checked!
3. greatHall card is removed form hand after its played. checked!
4. greatHall is placed into played cards pile. checked!
5. Other players hands are not changed. checked!
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
    int i, j;
    int errorCount = 0;
    int seed = 123456;
    int handCount = 0;
    struct gameState game, preGame;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    printf("***START OF GREAT HALL TESTS***\n\n");
    for (i = 2; i <= MAX_PLAYERS; i++)
    {
        for (j = 0 ; j < 5; j++)
        {
            returnValue = initializeGame(i, k, seed, &game);
            game.hand[0][j] = 16;
            memcpy (&preGame, &game, sizeof(struct gameState));
            handCount = numHandCards(&game);
            cardGreatHall(&game, j);
            if (numHandCards(&game) != (handCount)) //it added one but discarded one for a net change of 0.
            {
                errorCount++;
                printf("cardGreatHall() error %d\n", errorCount);
                printf("player 1 hand should have %d but has %d cards\n", handCount + 2, numHandCards(&game));
                printf("Num of Players: %d Hand pos: %d\n", i, j);
                printf("\n");
            }

            if (i >= 2)
            {
               if (!memcmp(&game.hand[1][0], &preGame.hand[1][0], sizeof(game.hand[1])) == 0)
               {
                    errorCount++;
                    printf("cardGreatHall() error %d\n", errorCount);
                    printf("Player 2 hand was modified when player 1 was updated\n");
                    printf("Num of Players: %d Hand pos: %d\n", i, j);
                    printf("\n");
               }
            }

            if (i >= 3)
            {
                if (!memcmp(&game.hand[2][0], &preGame.hand[2][0], sizeof(game.hand[2])) == 0)
                {
                    errorCount++;
                    printf("cardGreatHall() error %d\n", errorCount);
                    printf("Player 3 hand was modified when player 1 was updated\n");
                    printf("Num of Players: %d Hand pos: %d\n", i, j);
                    printf("\n");
                }
            }

            if (i >= 4)
            {
                if (!memcmp(&game.hand[3][0], &preGame.hand[3][0], sizeof(game.hand[3])) == 0)
                {
                    errorCount++;
                    printf("cardGreatHall() error %d\n", errorCount);
                    printf("Player 4 hand was modified when player 1 was updated\n");
                    printf("Num of Players: %d Hand pos: %d\n", i, j);
                    printf("\n");
                }
            }

            if (game.hand[0][j] == 16)
            {
                errorCount++;
                printf("cardGreatHall() error %d\n", errorCount);
                printf("Great Hall is still in players hand after discard\n");
                printf("Num of Players: %d Hand pos: %d\n", i, j);
                printf("\n");
            }

            if (game.playedCards[0] != 16)
            {
                errorCount++;
                printf("cardGreatHall() error %d\n", errorCount);
                printf("Great Hall is not in played pile.\n");
                printf("Num of Players: %d Hand pos: %d\n", i, j);
                printf("\n");
            }

            if ((preGame.numActions + 1) != (game.numActions))
            {
                errorCount++;
                printf("cardGreatHall() error %d\n", errorCount);
                printf("Card did not add +1 Action\n");
                printf("Num of Players: %d Hand pos: %d\n", i, j);
                printf("\n");
            }
        }
    }

    if (errorCount == 0)
    {
        printf("ALL TESTS PASSED FOR GREAT HALL\n\n");
    }
    printf("***END OF GREAT HALL TESTS***\n\n");
    return 0;
}
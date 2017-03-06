/*-----------------------------------------------
* Christopher Grant
* CS-362
* Winter 2017
* Assignment-5
* Card Test 1 - test for playSmithy()
* Testing dominion.c code from Craig Allan Reitan (reitanc).
------------------------------------------------*/

/*
Card rules.
1. Adds three cards to players hand. checked!
2. smithly card is removed form hand after its played. checked!
3. Smithy is placed into played cards pile. checked!
4. Other players hands are not changed. checked!
5. Other players decks not changed. checked!
6. the 3 new cards are from the players deck. checked!
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

    printf("***START OF SMITHY TESTS***\n");
    for (i = 2; i <= MAX_PLAYERS; i++)
    {
        for (j = 0 ; j < 5; j++)
        {
            returnValue = initializeGame(i, k, seed, &game);
            game.hand[0][j] = 13;
            memcpy (&preGame, &game, sizeof(struct gameState));
            handCount = numHandCards(&game);
            playSmithy(&game, j);
            if (numHandCards(&game) != (handCount + 2)) //it added three but discarded one for a net change of +2.
            {
                errorCount++;
                printf("playSmithy() error %d\n", errorCount);
                printf("player 1 hand should have %d but has %d cards\n", handCount + 2, numHandCards(&game));
                printf("Num of Players: %d Hand pos: %d\n", i, j);
                printf("\n");
            }

            if (game.hand[0][j] == 13)
            {
                errorCount++;
                printf("playSmithy() error %d\n", errorCount);
                printf("Smithy is still in players hand after discard\n");
                printf("Num of Players: %d Hand pos: %d\n", i, j);
                printf("\n");
            }

            if (game.playedCards[0] != 13)
            {
                errorCount++;
                printf("playSmithy() error %d\n", errorCount);
                printf("Smithy is not in played pile.\n");
                printf("Num of Players: %d Hand pos: %d\n", i, j);
                printf("\n");
            }

            if (game.deckCount[0] == preGame.deckCount[0])
            {
                errorCount++;
                printf("playSmithy() error %d\n", errorCount);
                printf("Did not pull cards from own deck.\n");
                printf("Num of Players: %d Hand pos: %d\n", i, j);
                printf("\n");
            }

            if (i >= 2)
            {
               if (!memcmp(&game.hand[1][0], &preGame.hand[1][0], sizeof(game.hand[1])) == 0)
               {
                    errorCount++;
                    printf("playSmithy() error %d\n", errorCount);
                    printf("Player 2 hand was modified when player 1 was updated\n");
                    printf("Num of Players: %d Hand pos: %d\n", i, j);
                    printf("\n");
               }

               if (!memcmp(&game.deck[1][0], &preGame.deck[1][0], sizeof(game.hand[1])) == 0)
               {
                    errorCount++;
                    printf("playSmithy() error %d\n", errorCount);
                    printf("Player 2 deck was modified when player 1 was updated\n");
                    printf("Num of Players: %d Hand pos: %d\n", i, j);
                    printf("\n");
               }
            }

            if (i >= 3)
            {
                if (!memcmp(&game.hand[2][0], &preGame.hand[2][0], sizeof(game.hand[2])) == 0)
                {
                    errorCount++;
                    printf("playSmithy() error %d\n", errorCount);
                    printf("Player 3 hand was modified when player 1 was updated\n");
                    printf("Num of Players: %d Hand pos: %d\n", i, j);
                    printf("\n");
                }

               if (!memcmp(&game.deck[2][0], &preGame.deck[2][0], sizeof(game.hand[2])) == 0)
               {
                    errorCount++;
                    printf("playSmithy() error %d\n", errorCount);
                    printf("Player 3 deck was modified when player 3 was updated\n");
                    printf("Num of Players: %d Hand pos: %d\n", i, j);
                    printf("\n");
               }
            }

            if (i >= 4)
            {
                if (!memcmp(&game.hand[3][0], &preGame.hand[3][0], sizeof(game.hand[3])) == 0)
                {
                    errorCount++;
                    printf("playSmithy() error %d\n", errorCount);
                    printf("Player 4 hand was modified when player 1 was updated\n");
                    printf("Num of Players: %d Hand pos: %d\n", i, j);
                    printf("\n");
                }

               if (!memcmp(&game.deck[3][0], &preGame.deck[3][0], sizeof(game.hand[3])) == 0)
               {
                    errorCount++;
                    printf("playSmithy() error %d\n", errorCount);
                    printf("Player 4 deck was modified when player 1 was updated\n");
                    printf("Num of Players: %d Hand pos: %d\n", i, j);
                    printf("\n");
               }
            }
        }
    }

    if (errorCount == 0)
    {
        printf("ALL TESTS PASSED FOR SMITHY\n");
    }
    printf("***END OF SMITHY TESTS***\n\n");
    return 0;
}
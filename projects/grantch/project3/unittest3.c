/*-----------------------------------------------
* Christopher Grant
* CS-362
* Winter 2017
* Assignment-3
* Unit Test 3 - test for discardCard()
------------------------------------------------*/

/*
1. if trashFlag is set it does not add card to playedcards.
2. if trashFlag is 0 than card is added to playedcards. checked!
3. card that is discarded is replaced by last card in hand. Checked!
4. hand count goes down by 1. checked!
5. other players hands do not change. checked!
6. other players dekcs do not change. checled!
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

    printf("***START OF DISCARDCARD TESTS***\n");

    for (i = 2; i <= MAX_PLAYERS; i++)
    {
        for (j = 0; j < 4; j++)
        {
            returnValue = initializeGame(i, kingdom, seed, &game);
            game.hand[0][0] = smithy;
            game.hand[0][1] = copper;
            game.hand[0][2] = silver;
            game.hand[0][3] = gold;
            game.hand[0][4] = adventurer;
            memcpy (&preGame, &game, sizeof(struct gameState));

            discardCard(j, 0, &game, 0);

            if (game.hand[0][j] != adventurer)
            {
                errorCount++;
                printf("discardCard() error %d\n", errorCount);
                printf("discarded card at pos %d was not replaced by last card in hand\n\n", j);
            }

            if (preGame.playedCardCount + 1 != game.playedCardCount)
            {
                errorCount++;
                printf("discardCard() error %d\n", errorCount);
                printf("played cards count was not ++\n\n");
            }

            if (preGame.hand[0][j] != game.playedCards[0])
            {
                errorCount++;
                printf("discardCard() error %d\n", errorCount);
                printf("The wrong card went into the played card pile\n\n");
            }

            if (preGame.handCount[0] - 1 != game.handCount[0])
            {
                errorCount++;
                printf("discardCard() error %d\n", errorCount);
                printf("Hand cound not --\n\n");
            }

            if (!memcmp(&game.hand[1][0], &preGame.hand[1][0], sizeof(game.hand[1])) == 0)
            {
                errorCount++;
                printf("discardCard() error %d\n", errorCount);
                printf("moded another players hand\n\n");
            }

            if (!memcmp(&game.deck[1][0], &preGame.deck[1][0], sizeof(game.deck[1])) == 0)
            {
                errorCount++;
                printf("discardCard() error %d\n", errorCount);
                printf("moded another players deck\n\n");
            }

            if (!memcmp(&game.hand[2][0], &preGame.hand[2][0], sizeof(game.hand[2])) == 0)
            {
                errorCount++;
                printf("discardCard() error %d\n", errorCount);
                printf("moded another players hand\n\n");
            }

            if (!memcmp(&game.deck[2][0], &preGame.deck[2][0], sizeof(game.deck[2])) == 0)
            {
                errorCount++;
                printf("discardCard() error %d\n", errorCount);
                printf("moded another players deck\n\n");
            }

            if (!memcmp(&game.hand[3][0], &preGame.hand[3][0], sizeof(game.hand[3])) == 0)
            {
                errorCount++;
                printf("discardCard() error %d\n", errorCount);
                printf("moded another players hand\n\n");
            }

            if (!memcmp(&game.deck[3][0], &preGame.deck[3][0], sizeof(game.deck[3])) == 0)
            {
                errorCount++;
                printf("discardCard() error %d\n", errorCount);
                printf("moded another players deck\n\n");
            }
        }

        for (j = 0; j < 4; j++)
        {
            returnValue = initializeGame(i, kingdom, seed, &game);
            game.hand[0][0] = smithy;
            game.hand[0][1] = copper;
            game.hand[0][2] = silver;
            game.hand[0][3] = gold;
            game.hand[0][4] = adventurer;
            memcpy (&preGame, &game, sizeof(struct gameState));

            discardCard(j, 0, &game, 1);

            if (preGame.playedCardCount != game.playedCardCount)
            {
                errorCount++;
                printf("discardCard() error %d\n", errorCount);
                printf("card was not trashed when the trash flag was 1\n\n");
            }
        }
    }



    if (errorCount == 0)
    {
        printf("ALL TESTS PASSED FOR DISCARDCARD\n");
    }
    printf("***END OF DISCARDCARD TESTS***\n\n");
    return 0;
}

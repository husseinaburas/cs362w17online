/*-----------------------------------------------
* Christopher Grant
* CS-362
* Winter 2017
* Assignment-3
* Card Test 3 - test for cardAdventurer()
------------------------------------------------*/

/*
Card rules.
1. +2 treasures are added to hand. checked!
2. the treasures come from that players deck. checked!
3. All other cards go to discard. checked!
4. no other players deck are touched. checked!
5. no other players hands are touched. checked!
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
    int lastCard;
    int lastCard2nd;
    struct gameState game, preGame;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    printf("***START OF ADVENTURER TESTS***\n");
    for (i = 2; i <= MAX_PLAYERS; i++)
    {
        returnValue = initializeGame(i, k, seed, &game);
        memcpy (&preGame, &game, sizeof(struct gameState));
        handCount = numHandCards(&game);
        game.deck[0][game.deckCount[0] - 1] = smithy; //adding non treasure cards to deck
        game.deck[0][game.deckCount[0] - 2] = smithy; //adding non treasure cards to deck

        //printDeck(0, &game);
        //printHand(0, &game);
        cardAdventurer(&game);
        //printDeck(0, &game);
        //printHand(0, &game);

        if ((handCount + 2) != numHandCards(&game))
        {
            errorCount++;
            printf("cardAdventurer() error %d\n", errorCount);
            printf("player 1 hand should have %d but has %d cards\n", handCount + 2, numHandCards(&game));
            printf("Num of Players: %d\n", i);
            printf("\n");
        }

        lastCard = game.hand[0][numHandCards(&game) - 1];
        lastCard2nd = game.hand[0][numHandCards(&game) - 2];
        if (lastCard != copper && lastCard != silver && lastCard != gold)
        {
            errorCount++;
            printf("cardAdventurer() error %d\n", errorCount);
            printf("Last card in hand is not a treasure\n");
            printf("Num of Players: %d\n", i);
            printf("\n");
        }

        if (lastCard2nd != copper && lastCard2nd != silver && lastCard2nd != gold)
        {
            errorCount++;
            printf("cardAdventurer() error %d\n", errorCount);
            printf("2nd to last card in hand is not a treasure\n");
            printf("Num of Players: %d\n", i);
            printf("\n");
        }

        if(game.discardCount[0] != 2){
            errorCount++;
            printf("cardAdventurer() error %d\n", errorCount);
            printf("non treasure cards are not in the discard\n");
            printf("Num of Players: %d\n", i);
            printf("\n");
        }

        //printf("size of discard: %d\n", game.discardCount[0]);




        //start of checking other players hands and decks
        if (i >= 2)
        {
           if (!memcmp(&game.hand[1][0], &preGame.hand[1][0], sizeof(game.hand[1])) == 0)
           {
                errorCount++;
                printf("cardAdventurer() error %d\n", errorCount);
                printf("Player 2 hand was modified when player 1 was updated\n");
                printf("Num of Players: %d Hand pos: %d\n", i, j);
                printf("\n");
           }

           if (!memcmp(&game.deck[1][0], &preGame.deck[1][0], sizeof(game.hand[1])) == 0)
           {
                errorCount++;
                printf("cardAdventurer() error %d\n", errorCount);
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
                printf("cardAdventurer() error %d\n", errorCount);
                printf("Player 3 hand was modified when player 1 was updated\n");
                printf("Num of Players: %d Hand pos: %d\n", i, j);
                printf("\n");
            }

           if (!memcmp(&game.deck[2][0], &preGame.deck[2][0], sizeof(game.hand[2])) == 0)
           {
                errorCount++;
                printf("cardAdventurer() error %d\n", errorCount);
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
                printf("cardAdventurer() error %d\n", errorCount);
                printf("Player 4 hand was modified when player 1 was updated\n");
                printf("Num of Players: %d Hand pos: %d\n", i, j);
                printf("\n");
            }

           if (!memcmp(&game.deck[3][0], &preGame.deck[3][0], sizeof(game.hand[3])) == 0)
           {
                errorCount++;
                printf("cardAdventurer() error %d\n", errorCount);
                printf("Player 4 deck was modified when player 1 was updated\n");
                printf("Num of Players: %d Hand pos: %d\n", i, j);
                printf("\n");
           }
        }
    }



    if (errorCount == 0)
    {
        printf("ALL TESTS PASSED FOR ADVENTURER\n");
    }
    printf("***END OF ADVENTURER TESTS***\n\n");
    return 0;
}
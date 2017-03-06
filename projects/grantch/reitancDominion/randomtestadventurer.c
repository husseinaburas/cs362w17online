/*-----------------------------------------------
* Christopher Grant
* CS-362
* Winter 2017
* Assignment-5
*  test for playAdventurer()
* Randomize game states for testing
* Testing dominion.c code from Craig Allan Reitan (reitanc).
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
#include <time.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    if(argc == 2)
    {
        printf("useing arg as seed\n");
        srand(atoi(argv[1]));
    }
    else if (argc == 1)
    {
        srand(time(NULL));
    }
    else
    {
        printf("Wrong args\n");
        exit(1);
    }

    int returnValue;
    int i, j;
    int errorCount = 0;
    int seed = rand();
    int handCount = 0;
    int lastCard;
    int lastCard2nd;
    int numOfPlayers;
    int deckTreasure;
    int randNum;
    int returnVal;
    struct gameState game, preGame;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    int cardsToPut[13] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy, copper, silver, gold};

    printf("***START OF ADVENTURER TESTS***\n");
    for (i = 0; i < 10000; i++)
    {
        deckTreasure = 0;
        numOfPlayers = (rand() % (MAX_PLAYERS + 1 - 2) + 2);
        returnValue = initializeGame(numOfPlayers, k, seed, &game);

        handCount = numHandCards(&game);
        game.deckCount[0] = rand() % MAX_DECK;
        //printf("Deck count: %d\n", game.deckCount[0]);


        for (j = 0; j < MAX_DECK; j++)
        {
            randNum = rand() % 13;
            //printf("randNum: %d Loc: %d\n", randNum, j);
            game.deck[0][j] = cardsToPut[randNum];
            if (game.deck[0][j] == copper || game.deck[0][j] == silver || game.deck[0][j] == gold)
            {
                deckTreasure++;
            }
        }
        memcpy (&preGame, &game, sizeof(struct gameState));

        //printf("deckTreasure: %d\n", deckTreasure);
        //printf("test5\n");
        returnVal = playAdventurer(&game);
        //printf("test6\n");

        //printf("returnValue: %d\n", returnVal);
        if (deckTreasure < 2 && returnVal == 0)
        {
            if ((handCount + 2) == numHandCards(&game))
            {
                errorCount++;
                printf("playAdventurer() error %d\n", errorCount);
                printf("player 1 hand should have %d cards but has %d cards\n", handCount + deckTreasure, numHandCards(&game));
                printf("Num of Players: %d test number %d\n", numOfPlayers, i + 1);
                printf("\n");
            }
        }
        else if (deckTreasure >= 2 && returnVal == 0)
        {
            if ((handCount + 2) != numHandCards(&game))
            {
                errorCount++;
                printf("playAdventurer() error %d\n", errorCount);
                printf("player 1 hand should have %d cards but has %d cards\n", handCount + 2, numHandCards(&game));
                printf("Num of Players: %d test number %d\n", numOfPlayers, i + 1);
                printf("\n");
            }

            if (game.discardCount[0] != abs(game.deckCount[0] - preGame.deckCount[0]) - 2)
            {
                errorCount++;
                printf("playAdventurer() error %d\n", errorCount);
                printf("discard: %d\n", game.discardCount[0]);
                printf("new deck: %d old deck: %d\n", game.deckCount[0], preGame.deckCount[0]);
                printf("Diff (if two tres cards have been put in hand): %d\n", abs(game.deckCount[0] - preGame.deckCount[0]) - 2);
                printf("Num of Players: %d test number %d\n", numOfPlayers, i + 1);
                printf("\n");
            }
        }

        //start of checking other players hands and decks


       if (!memcmp(&game.hand[1][0], &preGame.hand[1][0], sizeof(game.hand[1][0] * MAX_HAND)) == 0)
       {
            errorCount++;
            printf("playAdventurer() error %d\n", errorCount);
            printf("Player 2 hand was modified when player 1 was updated\n");
            printf("Num of Players: %d test number %d\n", numOfPlayers, i);
            printf("\n");
       }

       if (!memcmp(&game.deck[1][0], &preGame.deck[1][0], sizeof(game.deck[1][0] * MAX_DECK)) == 0)
       {
            errorCount++;
            printf("playAdventurer() error %d\n", errorCount);
            printf("Player 2 deck was modified when player 1 was updated\n");
            printf("Num of Players: %d test number %d\n", numOfPlayers, i);
            printf("\n");
       }



        if (!memcmp(&game.hand[2][0], &preGame.hand[2][0], sizeof(game.hand[2][0] * MAX_HAND)) == 0)
        {
            errorCount++;
            printf("playAdventurer() error %d\n", errorCount);
            printf("Player 3 hand was modified when player 1 was updated\n");
            printf("Num of Players: %d test number %d\n", numOfPlayers, i);
            printf("\n");
        }

       if (!memcmp(&game.deck[2][0], &preGame.deck[2][0], sizeof(game.deck[2][0] * MAX_DECK)) == 0)
       {
            errorCount++;
            printf("playAdventurer() error %d\n", errorCount);
            printf("Player 3 deck was modified when player 3 was updated\n");
            printf("Num of Players: %d test number %d\n", numOfPlayers, i);
            printf("\n");
       }



        if (!memcmp(&game.hand[3][0], &preGame.hand[3][0], sizeof(game.hand[3][0] * MAX_HAND)) == 0)
        {
            errorCount++;
            printf("playAdventurer() error %d\n", errorCount);
            printf("Player 4 hand was modified when player 1 was updated\n");
            printf("Num of Players: %d test number %d\n", numOfPlayers, i);
            printf("\n");
        }

       if (!memcmp(&game.deck[3][0], &preGame.deck[3][0], sizeof(game.deck[3][0] * MAX_DECK)) == 0)
       {
            errorCount++;
            printf("playAdventurer() error %d\n", errorCount);
            printf("Player 4 deck was modified when player 1 was updated\n");
            printf("Num of Players: %d test number %d\n", numOfPlayers, i);
            printf("\n");
       }

    }

    if (errorCount == 0)
    {
        printf("ALL TESTS PASSED FOR ADVENTURER\n");
    }
    printf("***END OF ADVENTURER TESTS***\n\n");
    return 0;
}
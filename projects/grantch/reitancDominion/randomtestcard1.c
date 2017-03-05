/*-----------------------------------------------
* Christopher Grant
* CS-362
* Winter 2017
* Assignment-5
* Random Card Test 1 - test for playSmithy()
* Randomize game states for testing
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
    int numOfPlayers;
    int cardPosInput;
    int randNum;
    struct gameState game, preGame;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    int cardsToPut[13] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy, copper, silver, gold};

    printf("***START OF SMITHY TESTS***\n");
    for (i = 0; i < 10000; i++)
    {
        numOfPlayers = (rand() % (MAX_PLAYERS + 1 - 2) + 2);

        returnValue = initializeGame(numOfPlayers, k, seed, &game);

        game.handCount[0] = (rand() % (MAX_HAND + 1 - 2) + 2);
        cardPosInput = rand() % game.handCount[0];

        for (j = 0; j < MAX_HAND; j++)
        {
            randNum = rand() % 13;
            //printf("randNum: %d Loc: %d\n", randNum, j);
            game.hand[0][j] = cardsToPut[randNum];
        }


        game.hand[0][cardPosInput] = 13;


        //game.hand[0][j] = 13;
        memcpy (&preGame, &game, sizeof(struct gameState));
        handCount = numHandCards(&game);
        playSmithy(&game, cardPosInput);
        if (numHandCards(&game) != (handCount + 2)) //it added three but discarded one for a net change of +2.
        {
            errorCount++;
            printf("playSmithy() error %d\n", errorCount);
            printf("player 1 hand should have %d but has %d cards\n", handCount + 2, numHandCards(&game));
            printf("Num of Players: %d Hand pos: %d test number %d\n", numOfPlayers, cardPosInput, i);
            printf("\n");
        }

        if (game.hand[0][cardPosInput] == 13)
        {
            errorCount++;
            printf("playSmithy() error %d\n", errorCount);
            printf("Smithy is still in players hand after discard\n");
            printf("Num of Players: %d Hand pos: %d test number %d\n", numOfPlayers, cardPosInput, i);
            printf("\n");
        }

        if (game.playedCards[0] != 13)
        {
            errorCount++;
            printf("playSmithy() error %d\n", errorCount);
            printf("Smithy is not in played pile.\n");
            printf("Num of Players: %d Hand pos: %d test number %d\n", numOfPlayers, cardPosInput, i);
            printf("\n");
        }

        if (game.deckCount[0] == preGame.deckCount[0])
        {
            errorCount++;
            printf("playSmithy() error %d\n", errorCount);
            printf("Did not pull cards from own deck.\n");
            printf("Num of Players: %d Hand pos: %d test number %d\n", numOfPlayers, cardPosInput, i);
            printf("\n");
        }



       if (!memcmp(&game.hand[1][0], &preGame.hand[1][0], sizeof(game.hand[1][0] * MAX_HAND)) == 0)
       {
            errorCount++;
            printf("playSmithy() error %d\n", errorCount);
            printf("Player 2 hand was modified when player 1 was updated\n");
            printf("Num of Players: %d test number %d\n", numOfPlayers, i);
            printf("\n");
       }

       if (!memcmp(&game.deck[1][0], &preGame.deck[1][0], sizeof(game.deck[1][0] * MAX_DECK)) == 0)
       {
            errorCount++;
            printf("playSmithy() error %d\n", errorCount);
            printf("Player 2 deck was modified when player 1 was updated\n");
            printf("Num of Players: %d test number %d\n", numOfPlayers, i);
            printf("\n");
       }



        if (!memcmp(&game.hand[2][0], &preGame.hand[2][0], sizeof(game.hand[2][0] * MAX_HAND)) == 0)
        {
            errorCount++;
            printf("playSmithy() error %d\n", errorCount);
            printf("Player 3 hand was modified when player 1 was updated\n");
            printf("Num of Players: %d test number %d\n", numOfPlayers, i);
            printf("\n");
        }

       if (!memcmp(&game.deck[2][0], &preGame.deck[2][0], sizeof(game.deck[2][0] * MAX_DECK)) == 0)
       {
            errorCount++;
            printf("playSmithy() error %d\n", errorCount);
            printf("Player 3 deck was modified when player 3 was updated\n");
            printf("Num of Players: %d test number %d\n", numOfPlayers, i);
            printf("\n");
       }



        if (!memcmp(&game.hand[3][0], &preGame.hand[3][0], sizeof(game.hand[3][0] * MAX_HAND)) == 0)
        {
            errorCount++;
            printf("playSmithy() error %d\n", errorCount);
            printf("Player 4 hand was modified when player 1 was updated\n");
            printf("Num of Players: %d test number %d\n", numOfPlayers, i);
            printf("\n");
        }

       if (!memcmp(&game.deck[3][0], &preGame.deck[3][0], sizeof(game.deck[3][0] * MAX_DECK)) == 0)
       {
            errorCount++;
            printf("playSmithy() error %d\n", errorCount);
            printf("Player 4 deck was modified when player 1 was updated\n");
            printf("Num of Players: %d test number %d\n", numOfPlayers, i);
            printf("\n");
       }

    }

    if (errorCount == 0)
    {
        printf("ALL TESTS PASSED FOR SMITHY\n");
    }
    printf("***END OF SMITHY TESTS***\n\n");
    return 0;
}
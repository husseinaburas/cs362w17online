/***************************************************************
 * random testing for ADVENTURER card
 *
 *  TO COMPILE
 * type: make randomtestadventurer
 * type in compiler: randomtestadventurer <number>
 *
 * to get the .out file
 * type: make randomtestadventurer.out
 ***************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//assertTrue takes a an int and int testNumber and if the test is true (equal to 1)
//  the string is returned to indicate that the test was successful, otherwise it failed.
int assertTrue(int test, int testNumber) {
    printf("Random card ADVENTURER - ");

    if (test == 1) {
        printf("TEST %d SUCCESSFULLY COMPLETED\n", testNumber);
        return 1;
    }
    else {
        printf("TEST %d FAILED.\n", testNumber);
        return 0;
    }
}


int main(int argc, char* argv[]) {
    if (argc != 2 || argv[1] < 0) {
        printf("Correct Usage: randomtestadventurer <positive random seed>\n");
        exit(0);
    }
    int randSeed = atoi(argv[1]);
    srand(randSeed);

    int i, testsFailed = 0;
    for (i = 0; i < 1000; i++) {

        //initialize variables
        struct gameState g1, g2;
        int k[10] = {great_hall, smithy, gardens, minion, mine, cutpurse, tribute, sea_hag, adventurer, council_room};
        int numPlayers = rand() % 3 + 2;        //Random number of players from 2 - 4
        int currPlayer = rand() % numPlayers;

        //initialize game with random # of players
        initializeGame(numPlayers, k, (rand() % 1000 + 1), &g1);
        g1.whoseTurn = currPlayer;


        //1 - Test that the first player gets an adventurer card in their hand (last position)
        gainCard(adventurer, &g1, 2, currPlayer);
        if(assertTrue((g1.hand[currPlayer][g1.handCount[currPlayer] - 1] == adventurer), 1) == 0) { testsFailed++; }

        //Copying g1 state to g2 state
        memcpy(&g2, &g1, sizeof(struct gameState));


        //set up deck so that if adventurer is played, smithy will be discarded, then cutpurse, etc...
        int testDeck[10] = {village, copper, smithy, gold, great_hall, gardens, silver, cutpurse, gold, smithy};
        int j, y;
        g1.deckCount[currPlayer] = 0;
        for (j = 0; j < 10; j++) {
            g1.deck[currPlayer][j] = testDeck[j];
            g1.deckCount[currPlayer]++;
        }
        //Play the Adventurer card in the first players hand
        playAdventurer(&g1, 0, 0);

        //2 - Test to see if curpurse is up
        if(assertTrue((g1.discard[currPlayer][0] == cutpurse), 2) == 0) { testsFailed++; }

        //3 and 4 - Test if smithy in right place
        if(assertTrue((g1.discard[currPlayer][1] == smithy), 3) == 0) { testsFailed++; }
        if(assertTrue((g1.discard[currPlayer][1] == smithy), 4) == 0) { testsFailed++; }

        //5 - Test that played gained 2 treasure cards
        int numberTreasureOld = 0;
        for (j = 0; j < g2.handCount[currPlayer]; j++) {
            if (g2.hand[currPlayer][j] == gold || g2.hand[currPlayer][j] == silver ||
                g2.hand[currPlayer][j] == copper)
                numberTreasureOld++;
        }

        int numberTreasureNew = 0;
        for (j = 0; j < g1.handCount[currPlayer]; j++) {
            if (g1.hand[currPlayer][j] == gold || g1.hand[currPlayer][j] == silver ||
                g1.hand[currPlayer][j] == copper)
                numberTreasureNew++;
        }

        //5 test here
        if(assertTrue((numberTreasureNew == numberTreasureOld + 2), 5) == 0) { testsFailed++; }


        //Looping through the other players to test that their decks, discard piles, hands have not changed
        for (j = 0; j < numPlayers; j++) {
            if (j != currPlayer) {
                //6 - Test that other players hand have the same number of cards that they started with
                if(assertTrue((g1.handCount[j] == g2.handCount[j]), 6) == 0) { testsFailed++; }

                //7 - Test other deckcount that they have same #
                if(assertTrue((g1.deckCount[j] == g2.deckCount[j]), 7) == 0) { testsFailed++; }

                //8 - Test other players discard pile has same # cards from original
                if(assertTrue((g1.discardCount[j] == g2.discardCount[j]), 8) == 0) { testsFailed++; }

                //9 - Test that players have same as when game initialized
                if(assertTrue((g1.handCount[j] == 0), 9)  == 0) { testsFailed++; }
                printf("Player %d has a handcount of 0\n", j + 1);
            }
            else {
                for (y = 0; y < g1.handCount[j]; y++) {
                    //10 - test that hands are all the same
                    if(assertTrue((g1.hand[j][y] == g2.hand[j][y]), 10) == 0) { testsFailed++; }
                }
            }


        }
        //11 - Test that players hand has 2 more cards
        if(assertTrue((g1.handCount[currPlayer] == g2.handCount[currPlayer] + 2), 11) == 0) { testsFailed++; }


        //12 / 13 - Test that top two cards in players hand are treasure
        int count = g1.handCount[currPlayer];
        if(assertTrue((g1.hand[currPlayer][count - 1] == copper || g1.hand[currPlayer][count - 1] == silver ||
                       g1.hand[currPlayer][count - 1] == gold), 12) == 0) { testsFailed++; }

        if(assertTrue((g1.hand[currPlayer][count - 2] == copper || g1.hand[currPlayer][count - 2] == silver ||
                       g1.hand[currPlayer][count - 2] == gold), 13) == 0) { testsFailed++; }

    }


    return 0;
}
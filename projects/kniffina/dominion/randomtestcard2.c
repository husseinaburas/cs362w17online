/***************************************************************
 * random testing for VILLAGE card
 *
  *  TO COMPILE
 * type: make randtomtestcard2
 * type in compiler: randtomtestcard2 <number>
 *
 * to get the .out file
 * type: make randtomtestcard2.out
 ***************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>

//assertTrue takes a an int and int testNumber and if the test is true (equal to 1)
//  the string is returned to indicate that the test was successful, otherwise it failed.
int assertTrue(int test, int testNumber) {
    printf("Random card VILLAGE - ");

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

    if(argc != 2 || argv[1] < 0) {
        printf("Usage: randomtestcard2 <positive integer seed value>\n");
        exit(0);
    }

    int i;
    int testsFailed = 0;
    int seed = atoi(argv[1]);
    srand(seed);

    for(i = 0; i < 1000; i++) {
        struct gameState g1, g2;

        int k[10] = {great_hall, smithy, gardens, minion, mine, cutpurse, tribute, sea_hag, adventurer, council_room};

        int x, j;
        int numPlayers = rand() % 3 + 2; //create random number for players between 2 and 4
        int currPlayer = rand() % numPlayers; //randomly assign current

        initializeGame(numPlayers, k, (rand() % 1000 + 1), &g1);

        g1.whoseTurn = currPlayer;

        g1.hand[currPlayer][g1.handCount[currPlayer] - 1] = village;

        //1 - Test that the current player has a village card in the last position of their hand
        if(assertTrue((g1.hand[currPlayer][g1.handCount[currPlayer] - 1] == village), 1) == 0) { testsFailed++; }

        //copy the original state from g2
        memcpy(&g2, &g1, sizeof(struct gameState));

        //call playVillage with card in first players hand
        playVillage(&g1, g1.handCount[currPlayer] - 1);

        //2 - Test that the played card from played cards array is the village card
        if(assertTrue((g1.playedCards[0] == village), 2)  == 0) { testsFailed++; }

        //3 - Test that the players hand stayed the same b/c 1 card discarded and 1 drawn
        if(assertTrue((g1.handCount[currPlayer] == g2.handCount[currPlayer]), 3)  == 0) { testsFailed++; }

        //4 - Test that a card was drawn from the deck
        if(assertTrue((g1.deckCount[currPlayer] == g2.deckCount[currPlayer] - 1), 4)  == 0) { testsFailed++; }

        //5 - Test that players number of actions has increased by two
        if(assertTrue((g1.numActions == g2.numActions + 2), 5)  == 0) { testsFailed++; }

        //6 - Test that 1 card has been played
        if(assertTrue((g1.playedCardCount == 1), 6)  == 0) { testsFailed++; }

        //loop through other players to test that their decks and cards have not changed
        for(j = 0; j < numPlayers; j++) {
            if (j != currPlayer) {

                //7 - Test that the other player's have the same number of cards they started with
                if (assertTrue((g1.handCount[j] == g2.handCount[j]), 7) == 0) { testsFailed++; }

                //8 - Test that other player's decks have same cards compared to when game created
                if (assertTrue((g1.handCount[j] == 0), 8) == 1) {} //if its true do nothing
                else {
                    testsFailed++;
                    for (x = 0; x < g1.handCount[j]; x++) {
                        //9 - Test, print the card and test that each card is the same
                        printf("Card number: %d\n", x);
                        if (assertTrue((g1.hand[j][x] == g2.hand[j][x]), 9) == 0) { testsFailed++; }
                    }
                }
            }
        }
    }
    printf("Failed test count for VILLAGE card is: %d\n", testsFailed);

    return 0;
}
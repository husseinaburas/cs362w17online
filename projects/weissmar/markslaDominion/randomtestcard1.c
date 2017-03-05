/************************************************************************
*
* Rachel Weissman-Hohler
* CS 362-400
* 03/05/17
* Assignment 5
* randomtestcard1.c 
* Testing: int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
*           (with baron as first parameter)
*
************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int asserttrue(int x, int y, float testNum);
int assertfalse(int x, int y, float testNum);

int main(int argc, char *argv[]) {
    int possibleKingdomCards[] = {
        adventurer, council_room, feast, gardens, mine, 
        remodel, smithy, village, -1, great_hall, 
        minion, steward, tribute, ambassador, cutpurse,
        embargo, outpost, salvager, sea_hag, treasure_map};
    int numPlayers;
    int kingdomCards[10]; 
    int seed;
    struct gameState actualState, copyState;
    int success, subSuccess;
    int i, num;
    int actualCount, copyCount;
    float testNum = 0;
    int choice;
    int activePlayer;
    int estateInHand;
    int numEstates;
    int numInitBuys;
    int numInitCoins;

    /* check for command line input */
    if (argc > 1){
        seed = atoi(argv[1]);
    } else {
        seed = time(NULL);
    }

    /* seed random number generator */
    srand(seed);

    printf("\nTesting playBaron()\n\n");

    /* randomly generate inputs */
    /* generate a number of players between 2 and 4, inclusive */
    numPlayers = (rand() % 3) + 2;  
    fprintf(stdout, "Number of players = %d\n", numPlayers);
    /* generate a random selection of kingdom cards, except for the card being tested */
    kingdomCards[0] = baron;
    fprintf(stdout, "kingdomCards[0] = %d\n", baron);
    for (i = 1; i < 10; i++){
        success = 0;
        while (success == 0){
            num = rand() % 20;
            if (possibleKingdomCards[num] != -1){
                kingdomCards[i] = possibleKingdomCards[num];
                fprintf(stdout, "kingdomCards[%d] = %d\n", i, kingdomCards[i]);
                possibleKingdomCards[num] = -1;
                success = 1;
            }
        }
    }

    /* initialize a game */
    initializeGame(numPlayers, kingdomCards, seed, &actualState);

    while(testNum < 1000){
        /* randomly determine active player */
        activePlayer = rand() % numPlayers;

        /* set active player */
        actualState.whoseTurn = activePlayer;

        /* give active player a copy of Baron to play */
        actualState.hand[activePlayer][0] = baron;

        /* randomly determine if the player has an estate in hand */
        estateInHand = rand() % 2;
        if (estateInHand == 1){
            /* give activePlayer an estate in hand */
            actualState.hand[activePlayer][1] = estate;
            actualState.hand[activePlayer][2] = copper;
            actualState.hand[activePlayer][3] = copper;
            actualState.hand[activePlayer][4] = copper;
        } else {
            /* make sure activePlayer doesn't have an estate in hand */
            actualState.hand[activePlayer][1] = copper;
            actualState.hand[activePlayer][2] = copper;
            actualState.hand[activePlayer][3] = copper;
            actualState.hand[activePlayer][4] = copper;
        }
        actualState.handCount[activePlayer] = 5;

        /* randomly determine how many cards are in discard */
        actualState.discardCount[activePlayer] = rand() % 50;
        /* fill discard with copper */
        for (i = 0; i < actualState.discardCount[activePlayer]; i++){
            actualState.discard[activePlayer][i] = copper;
        }

        /* randomly determine how many estates there are in the supply */
        if (numPlayers == 2)
            numEstates = rand() % 9;
        else
            numEstates = rand() % 13;
        actualState.supplyCount[estate] = numEstates;

        /* randomly determine how many buys and coins the player starts with */
        numInitBuys = rand() % 10;
        actualState.numBuys = numInitBuys;
        numInitCoins = rand() % 16;
        actualState.coins = numInitCoins;

        /* copy game state */
        memcpy(&copyState, &actualState, sizeof(struct gameState));

        /* randomly determine if player chooses to discard an estate */
        choice = rand() % 2;

        success = 0;
        testNum += 1;

        /* print details of test */
        fprintf(stdout, "********************************\nTEST %.0f:\n", testNum);
        fprintf(stdout, "Active player = %d\n", activePlayer);
        fprintf(stdout, "Estate in hand = %d\n", estateInHand);
        fprintf(stdout, "Estates in supply = %d\n", numEstates);
        fprintf(stdout, "Discard count = %d\n", actualState.discardCount[activePlayer]);
        fprintf(stdout, "Choice = %d\n", choice);
        fprintf(stdout, "Initial number of buys = %d\n", numInitBuys);
        fprintf(stdout, "Initial number of coins  = %d\n", numInitCoins);

        /* play Baron */
        cardEffect(baron, choice, -1, -1, &actualState, 0, NULL);

        /* if choice == 1 and estateInHand == 1, check that one estate and one baron were removed from the active player's hand */
        subSuccess = 0;
        if ((choice == 1) && (estateInHand == 1)){
            subSuccess += asserttrue(actualState.handCount[activePlayer], copyState.handCount[activePlayer] - 2, testNum + 0.11);
            actualCount = 0;
            copyCount = 0;
            for (i = 0; i < actualState.handCount[activePlayer]; i++){
                if (actualState.hand[activePlayer][i] == estate)
                    actualCount++;
            }
            for (i = 0; i < copyState.handCount[activePlayer]; i++){
                if (copyState.hand[activePlayer][i] == estate)
                    copyCount++;
            }
            subSuccess += asserttrue(actualCount, copyCount - 1, testNum + 0.12);
        } else {
            /* check that one baron was removed from the active player's hand and no estates were added or removed */
            subSuccess += asserttrue(actualState.handCount[activePlayer], copyState.handCount[activePlayer] - 1, testNum + 0.11);
            actualCount = 0;
            copyCount = 0;
            for (i = 0; i < actualState.handCount[activePlayer]; i++){
                if (actualState.hand[activePlayer][i] == estate)
                    actualCount++;
            }
            for (i = 0; i < copyState.handCount[activePlayer]; i++){
                if (copyState.hand[activePlayer][i] == estate)
                    copyCount++;
            }
            subSuccess += asserttrue(actualCount, copyCount, testNum + 0.12);
        }
        if (subSuccess == 2){
            success += 1;
        }

        /* check that the played copy of Baron was moved from hand to playedCards */
        subSuccess = 0;
        subSuccess += asserttrue(actualState.playedCardCount, copyState.playedCardCount + 1, testNum + 0.21);
        subSuccess += asserttrue(actualState.playedCards[actualState.playedCardCount - 1], baron, testNum + 0.22);
        for (i = 0; i < actualState.handCount[activePlayer]; i++){
            subSuccess += assertfalse(actualState.hand[activePlayer][i], baron, testNum + 0.23);
        }
        if (subSuccess == (2 + actualState.handCount[activePlayer])){
            success += 1;
        }

        /* if choice == 0 and numEstates == 0, check that active player's discard count didn't change */
        subSuccess = 0;
        if (((choice == 0) && (numEstates == 0)) || ((choice == 1) && (estateInHand == 0) && (numEstates == 0))){
            subSuccess += asserttrue(actualState.discardCount[activePlayer], copyState.discardCount[activePlayer], testNum + 0.31);
            if (subSuccess == 1){
                success += 1;
            }
        } else {
            /* check that one estate was added to active player's discard */
            subSuccess += asserttrue(actualState.discardCount[activePlayer], copyState.discardCount[activePlayer] + 1, testNum + 0.31);
            actualCount = 0;
            copyCount = 0;
            for (i = 0; i < actualState.discardCount[activePlayer]; i++){
                if (actualState.discard[activePlayer][i] == estate)
                    actualCount++;
            }
            for (i = 0; i < copyState.discardCount[activePlayer]; i++){
                if (copyState.discard[activePlayer][i] == estate)
                    copyCount++;
            }
            subSuccess += asserttrue(actualCount, copyCount + 1, testNum + 0.32);
            if (subSuccess == 2){
                success += 1;
            }
        }

        /* if choice == 1 and estateInHand == 1 check that coins were increased by 4 */
        subSuccess = 0;
        if ((choice == 1) && (estateInHand == 1)){
            subSuccess += asserttrue(actualState.coins, copyState.coins + 4, testNum + 0.41);
        } else {
            /* check that coins remained the same */
            subSuccess += asserttrue(actualState.coins, copyState.coins, testNum + 0.41);
        }
        if (subSuccess == 1){
            success += 1;
        }

        /* check that buys were increased by 1 */
        success += asserttrue(actualState.numBuys, copyState.numBuys + 1, testNum + 0.51);

        /* check that active player's deck count hasn't changed */
        success += asserttrue(actualState.deckCount[activePlayer], copyState.deckCount[activePlayer], testNum + 0.61);
        
        /* if choice == 0 and numEstates != 0, check that the estate supply count has decreased by one */
        subSuccess = 0;
        if (((choice == 0) && (numEstates != 0)) || ((choice == 1) && (estateInHand == 0) && (numEstates != 0))){
            subSuccess += asserttrue(actualState.supplyCount[estate], copyState.supplyCount[estate] - 1, testNum + 0.71);
            /* check that no other supply counts have changed */
            for (i = 0; i <= treasure_map; i++){
                if (i != estate)
                    subSuccess += asserttrue(actualState.supplyCount[i], copyState.supplyCount[i], testNum + 0.72);
            }
        } else {
            /* check that no supply counts have changed */
            for (i = 0; i <= treasure_map; i++){
                subSuccess += asserttrue(actualState.supplyCount[i], copyState.supplyCount[i], testNum + 0.71);
            }
        }
        if (subSuccess == (1 + treasure_map)){
            success += 1;
        }

        /* check that the non-active players' deck, hand, and discard haven't changed */
        subSuccess = 0;
        for (i = 0; i < numPlayers; i++) {
            if (i != activePlayer) {
                subSuccess += asserttrue(actualState.deckCount[i], copyState.deckCount[i], testNum + 0.81);
                subSuccess += asserttrue(actualState.handCount[i], copyState.handCount[i], testNum + 0.82);
                subSuccess += asserttrue(actualState.discardCount[i], actualState.discardCount[i], testNum + 0.83);
            }
        }
        if (subSuccess == (3 * (numPlayers - 1))){
            success += 1;
        }


        /* if all subtests passed, print success message */
        if (success == 8){
            printf("TEST %.0f COMPLETED SUCCESSFULLY\n", testNum);
        }
    }
    
    return 0;
}

int asserttrue(int x, int y, float testNum) {
    if (x == y) {
        return 1;
    } else {
        fprintf(stdout, "TEST %.2f FAILED\n", testNum);
        return 0;
    }
}

int assertfalse(int x, int y, float testNum) {
    if (x != y) {
        return 1;
    } else {
        fprintf(stdout, "TEST %.2f FAILED\n", testNum);
        return 0;
    }
}
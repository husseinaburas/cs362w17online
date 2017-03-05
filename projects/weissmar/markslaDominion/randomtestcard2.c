/************************************************************************
*
* Rachel Weissman-Hohler
* CS 362-400
* 03/05/17
* Assignment 5
* randomtestcard2.c 
* Testing: int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
*           (with remodel as first argument)
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
        -1, smithy, village, baron, great_hall, 
        minion, steward, tribute, ambassador, cutpurse,
        embargo, outpost, salvager, sea_hag, treasure_map};
    int numPlayers;
    int kingdomCards[10];
    int allCards[17];
    int seed;
    struct gameState actualState, copyState;
    int success, subSuccess;
    float testNum = 0;
    int i, num;
    int actualCount, copyCount;
    int activePlayer, positionOfTrash, cardToGain, positionOfRemodel;
    int cardToTrash, costDiff, trashRemodel;
    int numInSupply;
    int validConfig;

    /* check for command line input */
    if (argc > 1){
        seed = atoi(argv[1]);
    } else {
        seed = time(NULL);
    }

    /* seed random number generator */
    srand(seed);

    printf("\nTesting playRemodel()\n\n");

    /* randomly generate inputs */
    /* generate a number of players between 2 and 4, inclusive */
    numPlayers = (rand() % 3) + 2;  
    fprintf(stdout, "Number of players = %d\n", numPlayers);
    /* generate a random selection of kingdom cards, except for the card being tested */
    kingdomCards[0] = remodel;
    allCards[0] = remodel;
    fprintf(stdout, "kingdomCards[0] = %d\n", remodel);
    for (i = 1; i < 10; i++){
        success = 0;
        while (success == 0){
            num = rand() % 20;
            if (possibleKingdomCards[num] != -1){
                kingdomCards[i] = possibleKingdomCards[num];
                allCards[i] = kingdomCards[i];
                fprintf(stdout, "kingdomCards[%d] = %d\n", i, kingdomCards[i]);
                possibleKingdomCards[num] = -1;
                success = 1;
            }
        }
    }
    allCards[10] = curse;
    allCards[11] = estate;
    allCards[12] = duchy;
    allCards[13] = province;
    allCards[14] = copper;
    allCards[15] = silver;
    allCards[16] = gold;

    /* initialize a game */
    initializeGame(numPlayers, kingdomCards, seed, &actualState);

    while (testNum < 1000){
        /* randomly determine active player */
        activePlayer = rand() % numPlayers;

        /* set active player */
        actualState.whoseTurn = activePlayer;

        /* give active player a copy of Remodel to play */
        /* randomly determine hand size*/
        actualState.handCount[activePlayer] = (rand() % MAX_HAND) + 1;
        /* randomly determine position of Remodel */
        positionOfRemodel = rand() % actualState.handCount[activePlayer];
        actualState.hand[activePlayer][positionOfRemodel] = remodel;

        /* randomly determine remainder of hand */
        for (i = 0; i < actualState.handCount[activePlayer]; i++){
            if (i != positionOfRemodel){
                actualState.hand[activePlayer][i] = allCards[rand() % 17];
            }
        }

        /* randomly determine card to trash (by position in hand) */
        positionOfTrash = rand() % actualState.handCount[activePlayer];
        cardToTrash = actualState.hand[activePlayer][positionOfTrash];

        /* randomly determine card to gain */
        cardToGain = allCards[rand() % 17];

        /* randomly determine number of card to gain in supply */
        if ((cardToGain == copper) || (cardToGain == silver) || (cardToGain == gold)){
            numInSupply = rand() % 31;
        } else if ((cardToGain == estate) || (cardToGain == duchy) || (cardToGain == province) || (cardToGain == gardens)){
            if (numPlayers == 2){
                numInSupply = rand() % 9;
            } else {
                numInSupply = rand() % 13;
            }
        } else {
            numInSupply = rand() % 10;
        }
        actualState.supplyCount[cardToGain] = numInSupply;

        /* calculate difference in cost */
        costDiff = getCost(cardToGain) - getCost(cardToTrash);

        /* check if card to trash is copy of remodel being played */
        if (positionOfTrash == positionOfRemodel){
            trashRemodel = 1;
        } else {
            trashRemodel = 0;
        }

        /* check if this configuration is a valid play of Remodel */
        if ((costDiff <= 2) && (trashRemodel == 0) && (numInSupply > 0)){
            validConfig = 1;
        } else {
            validConfig = 0;
        }

        /* copy game state */
        memcpy(&copyState, &actualState, sizeof(struct gameState));

        success = 0;
        testNum += 1;

        /* print details of test */
        fprintf(stdout, "********************************\nTEST %.0f:\n", testNum);
        fprintf(stdout, "Active player = %d\n", activePlayer);
        fprintf(stdout, "Hand size = %d\n", actualState.handCount[activePlayer]);
        fprintf(stdout, "Position of Remodel = %d\n", positionOfRemodel);
        fprintf(stdout, "Position of card to trash = %d\n", positionOfTrash);
        fprintf(stdout, "Card to trash = %d\n", cardToTrash);
        fprintf(stdout, "Card to gain = %d\n", cardToGain);
        fprintf(stdout, "Number in supply = %d\n", numInSupply);
        fprintf(stdout, "Cost difference = %d\n", costDiff);
        fprintf(stdout, "Trashing copy of Remodel being played = %d\n", trashRemodel);
        fprintf(stdout, "Valid configuration = %d\n", validConfig);

        /* play Remodel */
        cardEffect(remodel, positionOfTrash, cardToGain, -1, &actualState, positionOfRemodel, NULL);

        /* if valid, check that one card to trash and one remodel were removed from active player's hand */
        subSuccess = 0;
        if (validConfig == 1){
            subSuccess += asserttrue(actualState.handCount[activePlayer], copyState.handCount[activePlayer] - 2, testNum + 0.11);
            actualCount = 0;
            copyCount = 0;
            for (i = 0; i < actualState.handCount[activePlayer]; i++){
                if (actualState.hand[activePlayer][i] == cardToTrash)
                    actualCount++;
            }
            for (i = 0; i < copyState.handCount[activePlayer]; i++){
                if (copyState.hand[activePlayer][i] == cardToTrash)
                    copyCount++;
            }
            subSuccess += asserttrue(actualCount, copyCount - 1, testNum + 0.12);
            actualCount = 0;
            copyCount = 0;
            for (i = 0; i < actualState.handCount[activePlayer]; i++){
                if (actualState.hand[activePlayer][i] == remodel)
                    actualCount++;
            }
            for (i = 0; i < copyState.handCount[activePlayer]; i++){
                if (copyState.hand[activePlayer][i] == remodel)
                    copyCount++;
            }
            subSuccess += asserttrue(actualCount, copyCount - 1, testNum + 0.13);
        } else {
            /* check that active player's hand hasn't changed */
            subSuccess += asserttrue(actualState.handCount[activePlayer], copyState.handCount[activePlayer], testNum + 0.11);
            actualCount = 0;
            copyCount = 0;
            for (i = 0; i < actualState.handCount[activePlayer]; i++){
                if (actualState.hand[activePlayer][i] == cardToTrash)
                    actualCount++;
            }
            for (i = 0; i < copyState.handCount[activePlayer]; i++){
                if (copyState.hand[activePlayer][i] == cardToTrash)
                    copyCount++;
            }
            subSuccess += asserttrue(actualCount, copyCount, testNum + 0.12);
            actualCount = 0;
            copyCount = 0;
            for (i = 0; i < actualState.handCount[activePlayer]; i++){
                if (actualState.hand[activePlayer][i] == remodel)
                    actualCount++;
            }
            for (i = 0; i < copyState.handCount[activePlayer]; i++){
                if (copyState.hand[activePlayer][i] == remodel)
                    copyCount++;
            }
            subSuccess += asserttrue(actualCount, copyCount, testNum + 0.13);
        }
        if (subSuccess == 3){
            success += 1;
        }

        /* if valid, check that the played copy of Remodel was moved from hand to playedCards */
        subSuccess = 0;
        if (validConfig){
            subSuccess += asserttrue(actualState.playedCardCount, copyState.playedCardCount + 1, testNum + 0.21);
            subSuccess += asserttrue(actualState.playedCards[actualState.playedCardCount - 1], remodel, testNum + 0.22);
        } else {
            /* check that played card count hasn't changed */
            subSuccess += asserttrue(actualState.playedCardCount, copyState.playedCardCount, testNum + 0.21);
            subSuccess += asserttrue(actualState.playedCards[actualState.playedCardCount - 1], copyState.playedCards[copyState.playedCardCount - 1], testNum + 0.22);
        }
        if (subSuccess == 2){
            success += 1;
        }

        /* if valid, check that one card to gain was gained to the discard */
        subSuccess = 0;
        if (validConfig){
            subSuccess += asserttrue(actualState.discardCount[activePlayer], copyState.discardCount[activePlayer] + 1, testNum + 0.31);
            actualCount = 0;
            copyCount = 0;
            for (i = 0; i < actualState.discardCount[activePlayer]; i++){
                if (actualState.discard[activePlayer][i] == cardToGain)
                    actualCount++;
            }
            for (i = 0; i < copyState.discardCount[activePlayer]; i++){
                if (copyState.discard[activePlayer][i] == cardToGain)
                    copyCount++;
            }
            subSuccess += asserttrue(actualCount, copyCount + 1, testNum + 0.32);
        } else {
            /* check that discard hasn't changed */
            subSuccess += asserttrue(actualState.discardCount[activePlayer], copyState.discardCount[activePlayer], testNum + 0.31);
            actualCount = 0;
            copyCount = 0;
            for (i = 0; i < actualState.discardCount[activePlayer]; i++){
                if (actualState.discard[activePlayer][i] == cardToGain)
                    actualCount++;
            }
            for (i = 0; i < copyState.discardCount[activePlayer]; i++){
                if (copyState.discard[activePlayer][i] == cardToGain)
                    copyCount++;
            }
            subSuccess += asserttrue(actualCount, copyCount, testNum + 0.32);
        }
        if (subSuccess == 2){
            success += 1;
        }

        /* if valid, check that one card to gain was removed from supply */
        subSuccess = 0;
        if (validConfig == 1){
            subSuccess += asserttrue(actualState.supplyCount[cardToGain], copyState.supplyCount[cardToGain] - 1, testNum + 0.41);
        } else {
            /* check that card to gain's supply hasn't changed */
            subSuccess += asserttrue(actualState.supplyCount[cardToGain], copyState.supplyCount[cardToGain], testNum + 0.41);
        }
        if (subSuccess == 1){
            success += 1;
        }
        
        /* check that active player's deck count hasn't changed */
        success += asserttrue(actualState.deckCount[0], copyState.deckCount[0], testNum + 0.51);

        /* check that no supply counts other than card to gain have changed */
        subSuccess = 0;
        for (i = 0; i <= treasure_map; i++){
            if (i != cardToGain)
                subSuccess += asserttrue(actualState.supplyCount[i], copyState.supplyCount[i], testNum + 0.61);
        }
        if (subSuccess == treasure_map){
            success += 1;
        }

        /* check that the non-active players' deck, hand, and discard haven't changed */
        subSuccess = 0;
        for (i = 0; i < numPlayers; i++) {
            if (i != activePlayer) {
                subSuccess += asserttrue(actualState.deckCount[i], copyState.deckCount[i], testNum + 0.71);
                subSuccess += asserttrue(actualState.handCount[i], copyState.handCount[i], testNum + 0.72);
                subSuccess += asserttrue(actualState.discardCount[i], actualState.discardCount[i], testNum + 0.73);
            }
        }
        if (subSuccess == (3 * (numPlayers - 1))){
            success += 1;
        }

        /* if all subtests passed, print success message */
        if (success == 7){
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
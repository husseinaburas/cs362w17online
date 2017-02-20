/************************************************************************
*
* Rachel Weissman-Hohler
* CS 362-400
* 2/18/17
* Assignment 4
* randomtestadventurer.c 
* Testing: void playAdventurer(int currentPlayer, struct gameState *state)
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
        -1, council_room, feast, gardens, mine, 
        remodel, smithy, village, baron, great_hall, 
        minion, steward, tribute, ambassador, cutpurse,
        embargo, outpost, salvager, sea_hag, treasure_map};
    int numPlayers;
    int kingdomCards[10];
    int allCards[17];
    int seed;
    struct gameState actualState, copyState;
    int success, subSuccess;
    int i, num;
    int activePlayer;
    int deckTreasure, discardTreasure, totalTreasure;
    float testNum = 0;
    int actualCount, copyCount;

    /* check for command line input */
    if (argc > 1){
        seed = atoi(argv[1]);
    } else {
        seed = time(NULL);
    }

    /* seed random number generator */
    srand(seed);

    printf("\nTesting playAdventurer()\n\n");

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

    while(testNum < 100){
        /* randomly determine active player */
        activePlayer = rand() % numPlayers;

        /* give active player a copy of Adventurer to play */
        actualState.hand[activePlayer][0] = adventurer;
        actualState.hand[activePlayer][1] = smithy;
        actualState.handCount[activePlayer] = 2;

        /* randomly determine deck and discard sizes */
        actualState.deckCount[activePlayer] = rand() % 11;
        actualState.discardCount[activePlayer] = rand() % 11;

        /* randomly determine contents of deck */
        deckTreasure = 0;
        for (i = 0; i < actualState.deckCount[activePlayer]; i++){
            actualState.deck[activePlayer][i] = allCards[rand() % 17];
            if ((copper <= actualState.deck[activePlayer][i]) && (actualState.deck[activePlayer][i] <= gold)){
                deckTreasure++;
            }
        }

        /* randomly determine contents of discard */
        discardTreasure = 0;
        for (i = 0; i < actualState.discardCount[activePlayer]; i++){
            actualState.discard[activePlayer][i] = allCards[rand() % 17];
            if ((copper <= actualState.discard[activePlayer][i]) && (actualState.discard[activePlayer][i] <= gold)){
                discardTreasure++;
            }
        }

        /* calculate total treasure in deck and discard */
        totalTreasure = deckTreasure + discardTreasure;

        /* copy game state */
        memcpy(&copyState, &actualState, sizeof(struct gameState));

        success = 0;
        testNum += 1;

        /* print details of test */
        fprintf(stdout, "********************************\nTEST %.0f:\n", testNum);
        fprintf(stdout, "Active player = %d\n", activePlayer);
        fprintf(stdout, "Deck size =  %d\n", actualState.deckCount[activePlayer]);
        fprintf(stdout, "Discard size =  %d\n", actualState.discardCount[activePlayer]);
        fprintf(stdout, "Deck treasure count =  %d\n", deckTreasure);
        fprintf(stdout, "Discard treasure count =  %d\n", discardTreasure);

        /* play adventurer */
        playAdventurer(activePlayer, &actualState);
        
        subSuccess = 0;
        if (totalTreasure >= 2){
            /* check that one card was added (two treasure added, one Adventurer removed) to active player's hand */
            subSuccess += asserttrue(actualState.handCount[0], copyState.handCount[0] + 1, testNum + 0.11);   
        } else if (totalTreasure == 1) {
            /* check that active player's hand count didn't change (one treasure added, one Adventurer removed) */
            subSuccess += asserttrue(actualState.handCount[0], copyState.handCount[0], testNum + 0.11); 
        } else {
            /* check that one card was removed (no treasure added, one Adventurer removed) from active player's hand */
            subSuccess += asserttrue(actualState.handCount[0], copyState.handCount[0] - 1, testNum + 0.11); 
        }
        if (subSuccess == 1){
            success += 1;
        }
        
        subSuccess = 0;
        if (totalTreasure >= 2){
            /* check that two treasure cards were added to active player's hand */
            actualCount = 0;
            copyCount = 0;
            for (i = 0; i < actualState.handCount[activePlayer]; i++){
                if ((copper <= actualState.hand[activePlayer][i]) && (actualState.hand[activePlayer][i] <= gold))
                    actualCount++;
            }
            for (i = 0; i < copyState.handCount[activePlayer]; i++){
                if ((copper <= actualState.hand[activePlayer][i]) && (actualState.hand[activePlayer][i] <= gold))
                    copyCount++;
            }
            subSuccess += asserttrue(actualCount, copyCount + 2, testNum + 0.21);
        } else if (totalTreasure == 1) {
            /* check that one treasure card was added to active player's hand */
            actualCount = 0;
            copyCount = 0;
            for (i = 0; i < actualState.handCount[activePlayer]; i++){
                if ((copper <= actualState.hand[activePlayer][i]) && (actualState.hand[activePlayer][i] <= gold))
                    actualCount++;
            }
            for (i = 0; i < copyState.handCount[activePlayer]; i++){
                if ((copper <= actualState.hand[activePlayer][i]) && (actualState.hand[activePlayer][i] <= gold))
                    copyCount++;
            }
            subSuccess += asserttrue(actualCount, copyCount + 1, testNum + 0.21);
        } else {
            /* check that no treasure cards were added to active player's hand */
            actualCount = 0;
            copyCount = 0;
            for (i = 0; i < actualState.handCount[activePlayer]; i++){
                if ((copper <= actualState.hand[activePlayer][i]) && (actualState.hand[activePlayer][i] <= gold))
                    actualCount++;
            }
            for (i = 0; i < copyState.handCount[activePlayer]; i++){
                if ((copper <= actualState.hand[activePlayer][i]) && (actualState.hand[activePlayer][i] <= gold))
                    copyCount++;
            }
            subSuccess += asserttrue(actualCount, copyCount, testNum + 0.21);
        }
        if (subSuccess == 1){
            success += 1;
        }

        /* check that the played copy of adventurer was moved from hand to playedCards */
        subSuccess = 0;
        subSuccess += asserttrue(actualState.playedCardCount, copyState.playedCardCount + 1, testNum + 0.31);
        subSuccess += asserttrue(actualState.playedCards[actualState.playedCardCount - 1], adventurer, testNum + 0.32);
        for (i = 0; i < actualState.handCount[activePlayer]; i++){
            subSuccess += assertfalse(actualState.hand[activePlayer][i], adventurer, testNum + 0.33);
        }
        if (subSuccess == (2 + actualState.handCount[activePlayer])){
            success += 1;
        }

        subSuccess = 0;
        if (totalTreasure >= 2){
            /* check that active player's discard + deck count has decreased by 2 */
            subSuccess += asserttrue(actualState.discardCount[0] + actualState.deckCount[0], copyState.discardCount[0] + copyState.deckCount[0] - 2, testNum + 0.41);
        } else if (totalTreasure == 1){
            /* check that active player's discard + deck count has decreased by 1 */
            subSuccess += asserttrue(actualState.discardCount[0] + actualState.deckCount[0], copyState.discardCount[0] + copyState.deckCount[0] - 1, testNum + 0.41);
        } else {
            /* check that active player's discard + deck count has decreased by 0 */
            subSuccess += asserttrue(actualState.discardCount[0] + actualState.deckCount[0], copyState.discardCount[0] + copyState.deckCount[0], testNum + 0.41);
        }
        if (subSuccess == 1){
            success += 1;
        }

        /* check that no supply counts have changed */
        subSuccess = 0;
        for (i = 0; i <= treasure_map; i++){
            subSuccess += asserttrue(actualState.supplyCount[i], copyState.supplyCount[i], testNum + 0.51);
        }
        if (subSuccess == (treasure_map + 1)){
            success += 1;
        }

        //* check that the non-active players' deck, hand, and discard haven't changed */
        subSuccess = 0;
        for (i = 0; i < numPlayers; i++) {
            if (i != activePlayer) {
                subSuccess += asserttrue(actualState.deckCount[i], copyState.deckCount[i], testNum + 0.61);
                subSuccess += asserttrue(actualState.handCount[i], copyState.handCount[i], testNum + 0.62);
                subSuccess += asserttrue(actualState.discardCount[i], actualState.discardCount[i], testNum + 0.63);
            }
        }
        if (subSuccess == (3 * (numPlayers - 1))){
            success += 1;
        }

        /* if all subtests passed, print success message */
        if (success == 6){
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
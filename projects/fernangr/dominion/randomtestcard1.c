#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "assertFunction.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int treasureCount(int player, struct gameState *state);

// Number of tests to run and their names
const int NUM_TESTS = 4;

/*
  Test of smithyCard function.
*/

void randTestSmithy(int seed, int* tally)
{
    int i, j;
    // Constants defining limits of deck and discard pile sizes at init time
    const int START_MAX_DECK = 100;
    const int START_MIN_HAND = 1;
    const int START_MAX_HAND = 20;

    // Setup test conditions
    struct gameState testState;
    int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    int currentPlayer;

    // Declare and initialize variables needed for tests
    int expected = 0;
    int got = 0;
    int result = 0;

    // Size counts for all players
    int deckSizeBefore[MAX_PLAYERS];
    int deckSizeAfter[MAX_PLAYERS];
    int discardSizeBefore[MAX_PLAYERS];
    int discardSizeAfter[MAX_PLAYERS];

    // Current player values
    int handSizeBeforePlaying = 0;
    int handSizeAfterPlaying = 0;
    int playedCardsBefore = 0;
    int playedCardsAfter = 0;
    int cardPos;

    // Re-initialize the currentTest count every time this is ran
    int currentTest = 1;

    /*
      SETUP PHASE - Randomize deck, discard pile, number of players
    */

    // Set a random number of players between 2 and 4
    int numPlayers = rand() % (MAX_PLAYERS - 1) + 2;

    // Initialize game
    initializeGame(numPlayers, cards, seed, &testState);

    // Choose current player randomly
    currentPlayer = testState.whoseTurn = rand() % numPlayers;

    // Randomize deck and discard piles for all the players
    for (i = 0; i < numPlayers; i++)
    {
        deckSizeBefore[i] = testState.deckCount[i] = rand() % START_MAX_DECK;
        for (j = 0; j < deckSizeBefore[i]; j++)
        {
            testState.deck[i][j] = rand() % (treasure_map + 1);
        }

        discardSizeBefore[i] = testState.discardCount[i] = rand() % START_MAX_DECK;
        for (j = 0; j < discardSizeBefore[i]; j++)
        {
            testState.discard[i][j] = rand() % (treasure_map + 1);
        }
    }

    //printf("\nDECK SIZE BEFORE PLAYING: %d\n", deckSizeBefore[0]);
    //printf("\nDISCARD SIZE BEFORE PLAYING: %d\n", discardSizeBefore[0]);

    // Give the player a random number of cards
    testState.handCount[currentPlayer] = rand() % (START_MAX_HAND - 1) + START_MIN_HAND;
    handSizeBeforePlaying = testState.handCount[currentPlayer];

    // printf("\nHAND SIZE BEFORE PLAYING: %d\n", handSizeBeforePlaying);

    // Make one of those cards the smithy
    testState.hand[currentPlayer][0] = smithy;
    cardPos = 0;

    // Start the current player off with a random number of played cards
    testState.playedCardCount = rand() % (discardSizeBefore[currentPlayer] + 1);
    playedCardsBefore = testState.playedCardCount;

    // printf("\nINITIAL PLAYED CARD COUNT: %d\n", playedCardsBefore);

    // And randomize the rest of them
    for (i = 1; i < handSizeBeforePlaying; i++)
    {
        testState.hand[currentPlayer][i] = rand() % (treasure_map + 1);
    }

    // for (i = 0; i < inHandBeforePlaying; i++)
    // {
    //     printf("CARD at %d is %d\n", i, testState.hand[currentPlayer][i]);
    // }


    /*
        SETUP PHASE COMPLETE - PLAYING CARD
    */

    smithyCard(&testState, cardPos);

    /*
        RECORDING CHANGES TO STATE PHASE
    */

    // Store the deck and discard pile size for all players
    for (i = 0; i < numPlayers; i++)
    {
        deckSizeAfter[i] = testState.deckCount[i];
        // printf("\nDECK SIZE AFTER PLAYING: %d\n", deckSizeAfter[i]);
        discardSizeAfter[i] = testState.discardCount[i];
        // printf("\nDISCARD SIZE AFTER PLAYING: %d\n", discardSizeBefore[i]);
    }

    // Store the current player's new hand and played card count
    handSizeAfterPlaying = testState.handCount[currentPlayer];
    playedCardsAfter = testState.playedCardCount;

    /*
        BEGIN TESTING RESULTS
    */

    // Testing general effects of playing a card on game state

    //      "OTHER PLAYER DECK SIZE"
    // Resetting testing variables
    expected = 0;
    result = 0;
    got = 0;
    // Count the number of other players who had their deck size affected
    for (i = 0; i < numPlayers; i++)
    {
        if (i != currentPlayer)
        {
            if (deckSizeBefore[i] != deckSizeAfter[i])
                got++;
        }
    }

    printf("\n--> Testing For: OTHER PLAYER DECK SIZE\n");
    result = assertEquals(expected, got); // storing result
    tally[currentTest++] += result; // add the result to the tally

    //      "OTHER PLAYER DISCARD PILE SIZE"
    // Resetting testing variables
    expected = 0;
    result = 0;
    got = 0;
    // Count the number of other players who had their deck size affected
    for (i = 0; i < numPlayers; i++)
    {
        if (i != currentPlayer)
        {
            if (discardSizeBefore[i] != discardSizeAfter[i])
                got++;
        }
    }

    printf("\n--> Testing For: OTHER PLAYER DISCARD PILE SIZE\n");
    result = assertEquals(expected, got); // storing result
    tally[currentTest++] += result; // add the result to the tally


    //     "PLAYED CARD COUNT"
    // Resetting testing variables
    expected = 0;
    result = 0;
    got = 0;

    printf("\n--> Testing For: PLAYED CARD COUNT\n");
    result = assertEquals(playedCardsBefore + 1, playedCardsAfter);
    tally[currentTest++] += result;

    // Testing direct effects of smithy card
    //      "CURRENT PLAYER CARDS IN HAND"
    // Resetting testing variables
    expected = 3;
    result = 0;
    got = 0;

    printf("\n--> Testing For: CURRENT PLAYER CARDS IN HAND\n");
    expected = handSizeBeforePlaying + expected; // updating expected value
    got = handSizeAfterPlaying;
    result = assertEquals(expected, got); // storing result
    tally[currentTest++] += result; // add the result to the tally
}


int main(int argc, char *argv[])
{
    int i;
    int seed = time(0);
    int runs = 10000;
    int ran = 0;
    int tally[NUM_TESTS + 1];

    for (i = 0; i <= NUM_TESTS; i++) {tally[i] = 0;} // set the # of passes to 0

    if (argc > 1) { seed = atoi(argv[1]); }

    else { printf("\nNo value passed for rand() seed. Using time(0).\n"); }

    srand(seed);

    printf("\n--- TESTING smithyCard FUNCTION ---\n");

    // Run amount of times given above
    for (i = 0; i < runs; i++)
    {
        randTestSmithy(seed, tally);
        ran++;
    }

    printf("\n");

    // Print the tally of passes for each test
    for (i = 1; i <= NUM_TESTS; i++)
    {
        printf("Test #%d passed %d times.\n", i, tally[i]);
    }

    printf("\n--- RAN TESTS %d TIMES ---", ran);
    printf("\n--- DONE TESTING smithy FUNCTION ---\n\n");

    return 0;
}

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "assertFunction.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int treasureCount(int player, struct gameState *state);

// const char* TEST_NAMES[7] =
// {
//     "OTHER PLAYER DECK SIZE",
//     "OTHER PLAYER DISCARD PILE SIZE",
//     "TREASURE CARDS IN CURRENT PLAYER DECK",
//     "TREASURE CARDS IN CURRENT PLAYER DISCARD PILE",
//     "PLAYED CARD COUNT",
//     "CURRENT PLAYER CARDS IN HAND",
//     "CURRENT PLAYER TREASURE CARDS IN HAND"
// };
// Number of tests to run and their names
const int NUM_TESTS = 7;

/*
  Test of adventurerCard function.
*/

void randTestAdv(int seed, int* tally)
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
    //char* testName;

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

    // Treasure count for current player
    int inHandBeforePlaying = 0;
    int inHandAfterPlaying = 0;
    int inDeckBeforePlaying = 0;
    int inDeckAfterPlaying = 0;
    int inDiscardBeforePlaying = 0;
    int inDiscardAfterPlaying = 0;

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

    // Make one of those cards the Adventurer
    testState.hand[currentPlayer][0] = adventurer;

    // Start the current player off with a random number of played cards
    testState.playedCardCount = rand() % (discardSizeBefore[currentPlayer] + 1);
    playedCardsBefore = testState.playedCardCount;

    // printf("\nINITIAL PLAYED CARD COUNT: %d\n", playedCardsBefore);

    // And randomize the rest of them
    for (i = 1; i < inHandBeforePlaying; i++)
    {
        testState.hand[currentPlayer][i] = rand() % (treasure_map + 1);
    }

    // for (i = 0; i < inHandBeforePlaying; i++)
    // {
    //     printf("CARD at %d is %d\n", i, testState.hand[currentPlayer][i]);
    // }

    // Count treasure cards in deck
    for (i = 0; i < deckSizeBefore[currentPlayer]; i++)
    {
        j = testState.deck[currentPlayer][i];
        if (j >= copper && j <= gold)
        {
            inDeckBeforePlaying++;
        }
    }
    // printf("\nTREASURE IN DECK BEFORE PLAYING: %d\n", inDeckBeforePlaying);

    // Count treasure cards in discard pile
    for (i = 0; i < discardSizeBefore[currentPlayer]; i++)
    {
        j = testState.discard[currentPlayer][i];
        if (j >= copper && j <= gold)
        {
            inDiscardBeforePlaying++;
        }
    }
    // printf("\nTREASURE IN DISCARD BEFORE PLAYING: %d\n", inDiscardBeforePlaying);

    // Count treasure cards in hand
    for (i = 0; i < handSizeBeforePlaying; i++)
    {
        j = testState.hand[currentPlayer][i];
        if (j >= copper && j <= gold)
        {
            inHandBeforePlaying++;
        }
    }
    // printf("\nTREASURE IN HAND BEFORE PLAYING: %d\n", inHandBeforePlaying);


    /*
        SETUP PHASE COMPLETE - PLAYING CARD
    */

    adventurerCard(&testState);

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

    // printf("\nHAND SIZE AFTER PLAYING: %d\n", handSizeAfterPlaying);
    // printf("\nTERMINAL PLAYED CARD COUNT: %d\n", playedCardsAfter);

    // Count treasure cards in deck
    for (i = 0; i < deckSizeAfter[currentPlayer]; i++)
    {
        j = testState.deck[currentPlayer][i];
        if (j >= copper && j <= gold)
        {
            inDeckAfterPlaying++;
        }
    }
    // printf("\nTREASURE IN DECK AFTER PLAYING: %d\n", inDeckAfterPlaying);

    // Count treasure cards in discard pile
    for (i = 0; i < discardSizeAfter[currentPlayer]; i++)
    {
        j = testState.discard[currentPlayer][i];
        if (j >= copper && j <= gold)
        {
            inDiscardAfterPlaying++;
        }
    }
    // printf("\nTREASURE IN DISCARD AFTER PLAYING: %d\n", inDiscardAfterPlaying);

    // Count treasure cards in hand
    for (i = 0; i < handSizeAfterPlaying; i++)
    {
        j = testState.hand[currentPlayer][i];
        if (j >= copper && j <= gold)
        {
            inHandAfterPlaying++;
        }
    }
    // printf("\nTREASURE IN HAND AFTER PLAYING: %d\n", inHandAfterPlaying);

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


    // Testing direct effects of Adventurer card

    //      "TREASURE CARDS IN CURRENT PLAYER DECK"
    // Resetting testing variables
    expected = 0;
    result = 0;
    got = 0;

    // Determine the expected variation in treasure cards in deck
    if (inDeckBeforePlaying >= 2)
        expected = inDeckBeforePlaying - 2;
    else if (inDeckBeforePlaying == 1 && inDiscardBeforePlaying >= 1)
        expected = inDiscardBeforePlaying - 1;
    else if (inDeckBeforePlaying == 0 && inDiscardBeforePlaying >= 2)
        expected = inDiscardBeforePlaying - 2;
    else
        expected = 0;

    printf("\n--> Testing For: TREASURE CARDS IN CURRENT PLAYER DECK\n");
    got = inDeckAfterPlaying;
    result = assertEquals(expected, got);
    tally[currentTest++] += result;

    //     "TREASURE CARDS IN CURRENT PLAYER DISCARD PILE"
    // Resetting testing variables
    expected = 0;
    result = 0;
    got = 0;

    // Determine the expected variation in treasure cards in discard pile
    if (inDeckBeforePlaying >= 2)
        expected = inDeckBeforePlaying;
    else if (inDiscardBeforePlaying >= 2)
        expected = 0;

    printf("\n--> Testing For: TREASURE CARDS IN CURRENT PLAYER DISCARD PILE\n");
    got = inDiscardAfterPlaying;
    result = assertEquals(expected, got);
    tally[currentTest++] += result;


    //     "PLAYED CARD COUNT"
    // Resetting testing variables
    expected = 0;
    result = 0;
    got = 0;

    printf("\n--> Testing For: PLAYED CARD COUNT\n");
    result = assertEquals(playedCardsBefore + 1, playedCardsAfter);
    tally[currentTest++] += result;

    //      "CURRENT PLAYER CARDS IN HAND"
    // Resetting testing variables
    expected = 0;
    result = 0;
    got = 0;

    if (inDeckBeforePlaying + inDiscardBeforePlaying >= 2)
    {
        expected = 2;
    }
    else
    {
        expected = inDeckBeforePlaying + inDiscardBeforePlaying;
    }

    printf("\n--> Testing For: CURRENT PLAYER CARDS IN HAND\n");
    expected = handSizeBeforePlaying + expected - 1; // updating expected value
    result = assertEquals(expected, handSizeAfterPlaying); // storing result
    tally[currentTest++] += result; // add the result to the tally


    // Resetting testing variables
    expected = 0;
    result = 0;
    got = 0;

    if (inDeckBeforePlaying + inDiscardBeforePlaying >= 2)
    {
        expected = 2;
    }
    else
    {
        expected = inDeckBeforePlaying + inDiscardBeforePlaying;
    }

    printf("\n--> Testing For: CURRENT PLAYER TREASURE CARDS IN HAND\n");
    expected = inHandBeforePlaying + expected;
    got = inHandAfterPlaying;
    result = assertEquals(expected, got);;
    tally[currentTest++] += result;
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

    printf("\n--- TESTING adventurerCard FUNCTION ---\n");

    // Run amount of times given above
    for (i = 0; i < runs; i++)
    {
        randTestAdv(seed, tally);
        ran++;
    }

    printf("\n");

    // Print the tally of passes for each test
    for (i = 1; i <= NUM_TESTS; i++)
    {
        printf("Test #%d passed %d times.\n", i, tally[i]);
    }

    printf("\n--- RAN TESTS %d TIMES ---", ran);
    printf("\n--- DONE TESTING adventurerCard FUNCTION ---\n\n");

    return 0;

}

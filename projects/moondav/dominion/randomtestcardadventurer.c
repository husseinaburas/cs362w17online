/*********************************************************************
randomtestcardadventurer.c

Author: David Moon
Date: 2-13-2017
Description:
    This is a random tester for the adventurer card in dominion.c. The variables
    that are selected randomly are:
    - numPlayers: The number of players in the game during testing.
    - currentPlayer: Which player's turn it is.
    - deckCount: The number of cards in a player's deck (each player has a
                 different random number of cards in their deck).
    - card: A card from the possible cards in the dominion game.
    - numTreasures: The number of treasure cards placed in the
                    player's deck.
    
    The following are key points the test will check:
    - The current player's played card count increases by 1
    - The player's deck decreases by the appropriate number of cards.
      i.e. The player draws until 2 treasures are revealed or the deck
      is depleted.
      Note: Currently, the test is setup with the player's played pile
      at 0, so there will not be a shuffle after depleting the deck.
    - The player's discard count increases by the appropriate amount
      of cards.
    - The player's hand count increases by the appropriate amount of
      cards, either 0, 1, or 2 depending on the number of treasures
      in the player's deck.

Note: Some skeleton code for game setup was taken from cardtest4.c,
    which was posted to the OSU CS-362 course web page.

Include the following lines in your makefile:

CFLAGS = -Wall -fpic -coverage -lm

randomtestcardadventurer: randomtestcardadventurer.c dominion.o rngs.o
    gcc -o randomtestcardadventurer -g randomtestcardadventurer.c dominion.o rngs.o $(CFLAGS)

**********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "unittest1.h"  // custom assert function, printPlayerHand(), printPlayerDeck()

#define NUM_TESTS 100
#define ACCEPTED_FAILURES 0


/******************************************************************
Description: 
    Get the index of the second treasure card from the top of the
    deck. Returns -1, if the deck does not contain 2 treasures.
Input: 
    int *deck - An array of ints representing cards in the dominion
                game.
    int numCards - The number of elements in the deck parameter.
Output:
    Returns the index of the second treasure card from the end of
    the array (representing the top of the deck). If there are not
    2 treasure cards in the deck, returns -1.
******************************************************************/
int getIndexOfSecondTreasure(int *deck, int numCards){
    int i = numCards;
    int treasuresFound = 0;

    for(i = numCards - 1; i >= 0; i--){
        if(deck[i] >= copper && deck[i] <= gold){
            treasuresFound++;
        }
        if(treasuresFound >= 2){
            return i;
        }
    }
    return -1;
}

/****************************************************************
Description:
    Get the number of treasure cards in a deck.
Input:
    int *deck - An array of ints representing cards in the dominion
                game.
    int numCards - The number of elements in the deck parameter.
Output:
    Returns the number of treasures in the deck.
****************************************************************/
int getNumTreasures(int *deck, int numCards){
    int numTreasures = 0;
    int i = 0;
    for(i = 0; i < numCards; i++){
        if(deck[i] >= copper && deck[i] <= gold){
            numTreasures++;
        }
    }
    return numTreasures;
}


struct TestResult randomtestAdventurer(){
    int testResult = FAIL;
    int observed;
    int expected;
    int gameSeed = 5;
    int numPlayers;  // to randomly set the number of players
    int minPlayers = 1;
    int maxPlayers = 4;
    int deckCount;   // to randomly set a deck count
    int minDeck = 10;
    int maxDeck = 100;
    int card;        // to randomly select a card
    int minCard = 0;
    int maxCard = 26;
    int currentPlayer; // randomly set the current player
    int player = 0;
    int handPos = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int bonus = 0; 
    int numTreasures;  // number of treasures to randomly place in the player's deck
    int minTreasures = 0;
    int maxTreasures = 3;
    int secondTreasureIndex = 0;
    int numCardsToDraw = 0;
    int playersTreasures = 0;
    int handGain = 0;
    int discardGain = 0;


    struct TestResult result;
    result.numPassed = 0;
    result.numFailed = 0;

    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};
    int testCard = adventurer;
    char *testCardName = "adventurer";
    int card1, card2, card3, card4, card5;
    int i = 0;

    // between minPlayers and maxPlayers
    numPlayers = (rand() % maxPlayers) + minPlayers;
    printf("Number of players selected: %d\n", numPlayers);

    // between minTreasures and maxTreasures
    numTreasures = (rand() % maxTreasures) + minTreasures;

    // initialize a game state and player cards
    initializeGame(numPlayers, k, gameSeed, &G);

    // Setup
    // Randomly set the current player
    currentPlayer = rand() % numPlayers;
    printf("Current player is: %d\n", currentPlayer);

    // Put the test card at handPos 0, and randomly populate the rest of the
    // player's hand.
    handPos = 0;
    card1 = testCard;
    card2 = rand() % 26;
    card3 = rand() % 26;
    card4 = rand() % 26;
    card5 = rand() % 26;

    // construct the hand
    G.hand[currentPlayer][0] = card1;
    G.hand[currentPlayer][1] = card2;
    G.hand[currentPlayer][2] = card3;
    G.hand[currentPlayer][3] = card4;
    G.hand[currentPlayer][4] = card5;

    G.handCount[currentPlayer] = 5;

    // Populate all player's decks with a random number of random cards
    // Each deck size will be between minDeck and maxDeck cards
    for(player = 0; player < numPlayers; player++){
        deckCount = (rand() % (maxDeck - minDeck)) + minDeck;
        G.deckCount[player] = deckCount;
        for(i = 0; i < G.deckCount[player]; i++){
            G.deck[player][i] = rand() % 26;
        }
    }

    printf("SETUP\n");
    printf("Current player deck count: %d\n", G.deckCount[currentPlayer]);
    printPlayerDeck(&G, currentPlayer);

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // Ensure the player's hand is populated correctly
    printPlayerDeck(&testG, currentPlayer);
    printPlayerHand(&testG, currentPlayer);
    printExpectedHand(card1, card2, card3, card4, card5);
    printf("\n");

    // Play the test card
    playCard(0, choice1, choice2, choice3, &testG);
    // cardEffect(testCard, choice1, choice2, choice3, &testG, handPos, &bonus);

    secondTreasureIndex = getIndexOfSecondTreasure(testG.deck[currentPlayer], testG.deckCount[currentPlayer]);
    printf("Second treasure index: %d.\n", secondTreasureIndex);
    // Get the number of cards the player is expected to draw.
    if(secondTreasureIndex == -1){
        numCardsToDraw = testG.deckCount[currentPlayer];
    }
    else{
        numCardsToDraw = testG.deckCount[currentPlayer] - secondTreasureIndex;
    }
    printf("Player is drawing %d cards.\n", numCardsToDraw);

    // Check if the player's deck count decreased by numCardsToDraw.
    observed = testG.deckCount[currentPlayer];
    expected = G.deckCount[currentPlayer] - numCardsToDraw;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Deck Count", observed, expected, &result);

    // Check if the player's hand count was increased by 0, 1, or 2,
    // depending on how many treasures were in the player's deck.
    playersTreasures = getNumTreasures(testG.deck[currentPlayer], testG.deckCount[currentPlayer]);
    if(playersTreasures >= 2){
        handGain = 2;
    }
    else{
        handGain = playersTreasures;
    }
    observed = testG.handCount[currentPlayer];
    expected = G.handCount[currentPlayer] + handGain;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Hand Count", observed, expected, &result);
    printPlayerHand(&testG, currentPlayer);

    // Check if the player's discard count increased by (numCardsToDraw - handGain)
    discardGain = numCardsToDraw - handGain;
    observed = testG.discardCount[currentPlayer];
    expected = G.discardCount[currentPlayer] + discardGain;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Discard Count", observed, expected, &result);

    // Check that the played card count increased by 1.
    observed = testG.playedCardCount;
    expected = G.playedCardCount + 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Played Card Count", observed, expected, &result);

    // Check that all other player's deck count stayed the same.
    for(i = 0; i < maxPlayers; i++){
        if(i != currentPlayer){
            observed = testG.deckCount[i];
            expected = G.deckCount[i];
            if(observed == expected){testResult = PASS;}
            else{testResult = FAIL;}
            char message[20];
            sprintf(message, "Player %d Deck Count", i);
            customAssert(testResult, message, observed, expected, &result);
        }
    }

    // Check that the players number of actions decreased by 1.
    observed = testG.numActions;
    expected = G.numActions - 1;
    if(observed == expected){testResult = PASS;}
    else{testResult = FAIL;}
    customAssert(testResult, "Number of Actions", observed, expected, &result);

    printf("Number of tests passed: %d\n", result.numPassed);
    printf("Number of tests failed: %d\n", result.numFailed);

    return result;
}

int main(int argc, char *argv[]) {  
    int rand_seed = atoi(argv[1]);
    printf("rand_seed: %d\n\n", rand_seed);
    srand(rand_seed);

    struct TestResult curTestResult;  // results of current test
    curTestResult.numPassed = 0;
    curTestResult.numFailed = 0;


    struct TestResult totalTestResults; // running tally of passes/fails of individual tests
    totalTestResults.numPassed = 0;
    totalTestResults.numFailed = 0;

    int test = 1;

    printf("\n\n############# RANDOM TESTING OF Adventurer CARD ###############\n");
    for(test = 1; test <= NUM_TESTS; test++){
        printf("\n\nRunning test %d of %d\n", test, NUM_TESTS);
        curTestResult = randomtestAdventurer();
        if(curTestResult.numFailed > ACCEPTED_FAILURES){
            totalTestResults.numFailed++;
        }
        else{
            totalTestResults.numPassed++;
        }
    }

    // Note: Every call to randomTestAdventurer() tests several expected values.
    //       If more than ACCEPTED_FAILURES of those values are not the
    //       expected values, the entire test is counted as a failure in the
    //       summary of random testing Adventurer card.
    // Note: At the time of testing the Adventurer card, there were known bugs
    //       that result in a 100% failure rate for this test.
    printf("\n\n************* Summary of random testing Adventurer card. ****************\n");
    printf("Total number of tests passed: %d\n", totalTestResults.numPassed);
    printf("Total number of tests failed: %d\n", totalTestResults.numFailed);
    float percentPassed = (totalTestResults.numPassed / NUM_TESTS);
    printf("Passed %2.f%% of tests.\n", percentPassed);
    printf("*********************************************************************\n");
    printf("\n\n############## END OF RANDOM TESTING OF ADVENTURER CARD #################\n\n");

    return 0;
}

#define PASS 1
#define FAIL 0

struct TestResult{
    int numPassed;
    int numFailed;
};

// testStatus: Pass = 0; Fail = 1
void customAssert(int testStatus, char *testName, int observed, int expected, struct TestResult *result){
    if(testStatus){
        printf("PASSED TEST %s: observed = %d, expected = %d\n", testName, observed, expected);
        result->numPassed++;
    }
    else{
        printf("FAILED TEST %s: observed = %d, expected = %d\n", testName, observed, expected);
        result->numFailed++;
    }
    printf("passed: %d, failed: %d\n", result->numPassed, result->numFailed);
}

// Print the current player's hand
void printPlayerHand(struct gameState *state, int currentPlayer){
	int i = 0;
    printf("Player hand: \t");
    for(i = 0; i < state->handCount[currentPlayer]; i++){
        printf("%d ", state->hand[currentPlayer][i]);
    }
    printf("\n");
}

// Pirnt the current player's deck
void printPlayerDeck(struct gameState *state, int currentPlayer){
	int i = 0;
    printf("Player deck: \t");
    for(i = 0; i < state->deckCount[currentPlayer]; i++){
        printf("%d ", state->deck[currentPlayer][i]);
    }
    printf("\n");
}

// Print expected hand
void printExpectedHand(int card1, int card2, int card3, int card4, int card5){
    printf("Expected hand: \t%d %d %d %d %d\n", card1, card2, card3, card4, card5);
}

#define PASS 1
#define FAIL 0

// testStatus: Pass = 0; Fail = 1
void customAssert(int testStatus, char *testName, int observed, int expected){
    if(testStatus){
        printf("PASSED TEST %s: observed = %d, expected = %d\n", testName, observed, expected);
    }
    else{
        printf("FAILED TEST %s: observed = %d, expected = %d\n", testName, observed, expected);
    }
}

// Print the current player's hand
void printPlayerHand(struct gameState *state){
	int i = 0;
	int currentPlayer = whoseTurn(state);
    printf("Player hand: \t");
    for(i = 0; i < state->handCount[currentPlayer]; i++){
        printf("%d ", state->hand[currentPlayer][i]);
    }
    printf("\n");
}

// Pirnt the current player's deck
void printPlayerDeck(struct gameState *state){
	int i = 0;
	int currentPlayer = whoseTurn(state);
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
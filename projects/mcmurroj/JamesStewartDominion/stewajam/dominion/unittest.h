/***************************************
* Name: James Stewart
* Date: 1/31/2017
* File: cardtest1.c
* Description: Header for Unit Tests
***************************************/

#define PASS 1
#define FAIL 0

void assertTrue(int result, char *name, int actual, int expected){
    if(result){
        printf("TEST SUCCESSFULLY COMPLETED\n%s\nActual: %d Expected: %d\n\n", name, actual, expected);
    }
    else{
        printf("TEST FAILED\n%s\nActual: %d Expected: %d\n\n", name, actual, expected);
    }
}

void printHand(struct gameState *state){
	int i = 0;
	int player = whoseTurn(state);
    printf("Player's hand: \t");
    for(i = 0; i < state->handCount[player]; i++){
        printf("%d ", state->hand[player][i]);
    }
    printf("\n");
}

void printDeck(struct gameState *state){
	int i = 0;
	int player = whoseTurn(state);
    printf("Player's deck: \t");
    for(i = 0; i < state->deckCount[player]; i++){
        printf("%d ", state->deck[player][i]);
    }
    printf("\n");
}

void printExpHand(int card1, int card2, int card3, int card4, int card5){
    printf("Expected hand: \t%d %d %d %d %d\n", card1, card2, card3, card4, card5);
}
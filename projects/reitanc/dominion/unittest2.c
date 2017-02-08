/*
 * unittest2.c
 */

/*
 * Include the following lines in your makefile:
 *
 * unitest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

void testScoreFor(){
	struct gameState MyGame;
	int ReturnValue;
	
	// Setup a Game for testing
	int p1Hand[4] = {estate, duchy, feast, copper};
	int p2Hand[4] = {curse, copper, silver, baron};
	int p3Hand[4] = {duchy, smithy, silver, baron};
	int p4Hand[4] = {gardens, province, gold, cutpurse};

	// initializeGame(2, kCards, 10, &MyGame);
	MyGame.numPlayers = 4;

	/* Setup Test Hands */
	for (int i = 0; i < MyGame.numPlayers; i++){
		MyGame.hand[0][i] = p1Hand[i];
		MyGame.hand[1][i] = p2Hand[i];
		MyGame.hand[2][i] = p3Hand[i];
		MyGame.hand[3][i] = p4Hand[i];
	}
	MyGame.handCount[1] = MyGame.handCount[2] = MyGame.handCount[3] = MyGame.handCount[4] = 4;

	/* Setup Discard Hands */
	MyGame.discard[0][0] = (int){curse}; 
	MyGame.discard[0][1] = (int){province};
	MyGame.discardCount[0] = 2;

	MyGame.discard[1][0] = (int){feast};
	MyGame.discard[1][1] = (int){adventurer};
	MyGame.discard[1][2] = (int){sea_hag};
	MyGame.discardCount[1] = 3;

	MyGame.discard[2][0] = (int){province}; 
	MyGame.discard[2][1] = (int){village};
	MyGame.discard[2][2] = (int){steward};
	MyGame.discard[2][3] = (int){gardens};
	MyGame.discardCount[2] = 4;


	MyGame.discard[3][0] = (int){baron};
	MyGame.discard[3][1] = (int){sea_hag};
	MyGame.discard[3][2] = (int){council_room};
	MyGame.discard[3][3] = (int){minion};
	MyGame.discardCount[3] = 4;

	/* Setup Deck Hands */
	MyGame.deck[0][0] = (int){estate};
	MyGame.deck[0][1] = (int){estate};
	MyGame.deck[0][2] = (int){great_hall};
	MyGame.deckCount[0] = 3;
	
	MyGame.deck[1][0] = (int){embargo};
	MyGame.deck[1][1] = (int){cutpurse};
	MyGame.deck[1][2] = (int){copper};
	MyGame.deck[1][3] = (int){silver};
	MyGame.deck[1][4] = (int){silver};
	MyGame.deck[1][5] = (int){gold};
	MyGame.deck[1][6] = (int){gold};
	MyGame.deckCount[1] = 7;
	
	MyGame.deck[2][0] = (int){outpost};
	MyGame.deck[2][1] = (int){smithy};
	MyGame.deck[2][2] = (int){copper};
	MyGame.deck[2][3] = (int){copper};
	MyGame.deck[2][4] = (int){silver};
	MyGame.deck[2][5] = (int){gold};
	MyGame.deck[2][6] = (int){minion};
	MyGame.deck[2][7] = (int){steward};
	MyGame.deck[2][8] = (int){smithy};
	MyGame.deck[2][9] = (int){mine};
	MyGame.deck[2][10] = (int){remodel};
	MyGame.deckCount[2] = 11;

	MyGame.deck[3][0] = (int){curse};
	MyGame.deck[3][1] = (int){outpost};
	MyGame.deck[3][2] = (int){smithy};
	MyGame.deck[3][3] = (int){copper};
	MyGame.deck[3][4] = (int){silver};
	MyGame.deck[3][5] = (int){gold};
	MyGame.deckCount[3] = 6;


    printf("\n=== BEGINNING UNIT TESTS for scoreFor()\n\n");
	/* --- TEST 1: Player 1 --- */
	ReturnValue = scoreFor(0, &MyGame);
	if (ReturnValue == 12)
        printf("scoreFor(): PASS when testing Player 1.\n");
    else
        printf("scoreFor(): FAIL when testing Player 1. ReturnValue = %i\n", ReturnValue);
	/* --- TEST 1: Player 1 --- */

	/* --- TEST 2: Player 2 --- */
	ReturnValue = scoreFor(1, &MyGame);
	if (ReturnValue == -1)
        printf("scoreFor(): PASS when testing Player 2.\n");
    else
        printf("scoreFor(): FAIL when testing Player 2. ReturnValue = %i\n", ReturnValue);
	/* --- TEST 2: Player 2 --- */

	/* --- TEST 3: Player 3 --- */
	ReturnValue = scoreFor(2, &MyGame);
	if (ReturnValue == 10)
        printf("scoreFor(): PASS when testing Player 3.\n");
    else
        printf("scoreFor(): FAIL when testing Player 3. ReturnValue = %i\n", ReturnValue);
	/* --- TEST 3: Player 3 --- */

	/* --- TEST 4: Player 4 --- */
	ReturnValue = scoreFor(3, &MyGame);
	if (ReturnValue == 6)
        printf("scoreFor(): PASS when testing Player 4.\n");
    else
        printf("scoreFor(): FAIL when testing Player 4. ReturnValue = %i\n", ReturnValue);
	/* --- TEST 4: Player 4 --- */
    printf("\n=== COMPLETED UNIT TESTS for scoreFor()\n\n");

    return;
}

int main(){

	testScoreFor();
	return 0;
}
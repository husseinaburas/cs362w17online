//int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
/*
* Unit Test 3 - gainCard
* Parameters:  Target Supply Position, Current Game State, Where does it go Flag, Target Player
* //Note: supplyPos is enum of choosen card
*/

/*
* Include the following lines in your makefile:
*
* unittest3: unittest3.c dominion.o rngs.o
*      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Gain Card"

int main() {
	int newCards = 0;
	int discarded = 1;
	int xtraCoins = 0;
	int shuffledCards = 0;

	int i, j, m;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int remove1, remove2;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	int otherPlayer = 1;
	struct gameState G, testG;
	int k[10] = { adventurer, remodel, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Unit: %s ----------------\n", TESTCARD);

	// ----------- TEST a: This Player puts Smithy to discard --------------
	printf("Test a: This Player Adds Smithy from Kingdom Pile to Discard\n");

	// copy the game state to a test case - Control
	memcpy(&testG, &G, sizeof(struct gameState));
	gainCard(smithy, &testG, 0, thisPlayer);

	newCards = 1;
	xtraCoins = 0;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	printf("Discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] - newCards + shuffledCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	if(!(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded)){
		printf("This Player's Hand Count Was Wrong");//
	};
		
	if(!(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards)){
		printf("This Player's Deck Count Was Wrong");//
	};
	if(!(testG.discardCount[thisPlayer] == (G.discardCount[thisPlayer]))){
		printf("This Player's Discard pile Count Was Wrong");//
	};
	if(!(testG.numActions == (G.numActions - 1)){
		printf("This Player's Action Count Was Wrong");//
	};
	if(!(testG.coins == G.coins + xtraCoins)){
		printf("This Player's Coin Count Was Wrong");//
	};
		
	// ----------- TEST b: This Player puts Smithy to Hand --------------
	printf("Test b: This Player Adds Smithy from Kingdom Pile to Hand\n");

	// copy the game state to a test case - Control
	memcpy(&testG, &G, sizeof(struct gameState));
	gainCard(smithy, &testG, 2, thisPlayer);

	newCards = 1;
	xtraCoins = 0;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards);
	assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer]);
	assert(testG.coins == G.coins + xtraCoins);

	// ----------- TEST c: This Player puts Smithy to deck --------------
	printf("Test c: This Player Adds Smithy from Kingdom Pile to deck\n");

	// copy the game state to a test case - Control
	memcpy(&testG, &G, sizeof(struct gameState));
	gainCard(smithy, &testG, 1, thisPlayer);

	newCards = 1;
	xtraCoins = 0;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] + newCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	if(!(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded)){
		printf("This Player's Hand Count Was Wrong");//
	};
		
	if(!(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards)){
		printf("This Player's Deck Count Was Wrong");//
	};
	if(!(testG.discardCount[thisPlayer] == (G.discardCount[thisPlayer]))){
		printf("This Player's Discard pile Count Was Wrong");//
	};
	if(!(testG.numActions == (G.numActions - 1)){
		printf("This Player's Action Count Was Wrong");//
	};
	if(!(testG.coins == G.coins + xtraCoins)){
		printf("This Player's Coin Count Was Wrong");//
	};

	// ----------- TEST d: Other State's Conditions --------------
	printf("Test d: Other State's Conditions\n");

	printf("hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
	printf("deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
	printf("copper count = %d, expected = %d\n", testG.supplyCount[copper], G.supplyCount[copper]);
	printf("silver count = %d, expected = %d\n", testG.supplyCount[silver], G.supplyCount[silver]);
	printf("gold count = %d, expected = %d\n", testG.supplyCount[gold], G.supplyCount[gold]);
	printf("estate count = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);
	printf("duchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
	printf("adventurer count = %d, expected = %d\n", testG.supplyCount[adventurer], G.supplyCount[adventurer]);
	printf("remodel count = %d, expected = %d\n", testG.supplyCount[remodel], G.supplyCount[remodel]);
	printf("village count = %d, expected = %d\n", testG.supplyCount[village], G.supplyCount[village]);
	printf("minion count = %d, expected = %d\n", testG.supplyCount[minion], G.supplyCount[minion]);
	printf("mine count = %d, expected = %d\n", testG.supplyCount[mine], G.supplyCount[mine]);
	printf("cutpurse count = %d, expected = %d\n", testG.supplyCount[cutpurse], G.supplyCount[cutpurse]);
	printf("sea_hag count = %d, expected = %d\n", testG.supplyCount[sea_hag], G.supplyCount[sea_hag]);
	printf("tribute count = %d, expected = %d\n", testG.supplyCount[tribute], G.supplyCount[tribute]);
	printf("smithy count = %d, expected = %d\n", testG.supplyCount[smithy], G.supplyCount[smithy]);
	printf("council_room count = %d, expected = %d\n", testG.supplyCount[council_room], G.supplyCount[council_room]);

	if(!(testG.handCount[otherPlayer] == G.handCount[otherPlayer])){
		printf("The Other Player's Hand Count Was Wrong");//
	};
	if(!(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer])){
		printf("The Other Player's Deck Count Was Wrong");//
	};
	if(!(testG.supplyCount[copper] == G.supplyCount[copper])){
		printf("The Supply's Copper Count Was Wrong");//
	};
	if(!(testG.supplyCount[silver] == G.supplyCount[silver])){
		printf("The Supply's Silver Count Was Wrong");//
	};
	if(!(testG.supplyCount[gold] == G.supplyCount[gold])){
		printf("The Supply's Gold Count Was Wrong");
	};
	if(!(testG.supplyCount[estate] == G.supplyCount[estate])){
		printf("The Supply's estate Count Was Wrong");//
	};
	if(!(testG.supplyCount[duchy] == G.supplyCount[duchy])){
		printf("The Supply's Duchy Count Was Wrong");//
	};
	if(!(testG.supplyCount[adventurer] == G.supplyCount[adventurer])){
		printf("The Supply's adventurer Count Was Wrong");//
	};
	if(!(testG.supplyCount[remodel] == G.supplyCount[remodel])){
		printf("The Supply's remodel Count Was Wrong");//
	};
	if(!(testG.supplyCount[village] == G.supplyCount[village])){
		printf("The Supply's village Count Was Wrong");//
	};
	if(!(testG.supplyCount[minion] == G.supplyCount[minion])){
		printf("The Supply's minion Count Was Wrong");//
	};
	if(!(testG.supplyCount[mine] == G.supplyCount[mine])){
		printf("The Supply's mine Count Was Wrong");//
	};
	if(!(testG.supplyCount[cutpurse] == G.supplyCount[cutpurse])){
		printf("The Supply's cutpurse Count Was Wrong");//
	};
	if(!(testG.supplyCount[sea_hag] == G.supplyCount[sea_hag])){
		printf("The Supply's Sea Hag Count Was Wrong");//
	};
	if(!(testG.supplyCount[tribute] == G.supplyCount[tribute])){
		printf("The Supply's tribute Count Was Wrong");//
	};
	if(!(testG.supplyCount[smithy] == (G.supplyCount[smithy]))){
		printf("The Supply's Smithy Count Was Wrong");//
		};
	if(!(testG.supplyCount[council_room] == G.supplyCount[council_room])){
		printf("The Supply's Council Room Count Was Wrong");//
	};


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}
#include "dominion.h"
#include "dominion_helpers.h"
#include "test_help.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

//random tester for adventurer card
//
//!!!!!CHANGED PARAMETERS IN ADVENTURER CARD FUNCTION IN DOMINION.C
//!!!!REMEMBER TO PUSH NEW DOMINION.C/DOMINION_HELPERS.H FILES TO GITHUB!!!!
//unit test for adventurer card
void testAdventurerCard(int currentPlayer, struct gameState *state)
{
    if (assertIsValid("test adventurer card", currentPlayer, state))
    {
        int handCtpre = state->handCount[currentPlayer];
	int deckCtpre = state->deckCount[currentPlayer];
	int discardCountpre = state->discardCount[currentPlayer];
	printf("Player: %d, pre hand count: %d, pre deck count: %d.\n", currentPlayer, handCtpre, deckCtpre);
        adventurerCard(currentPlayer, state);
	//testCounts(currentPlayer, state, handCtpre, deckCtpre, 0, 2,-2, 0);
	int disCardTot = (state->discardCount[currentPlayer] - discardCountpre);
	assertIsEqual("testing hand count", (handCtpre + 2), state->handCount[currentPlayer]);
	assertIsEqual("testing deck count", (deckCtpre - disCardTot - 2), state->deckCount[currentPlayer]);
	printf("Current player: %d, hand count after: %d (expected %d), deck count after: %d (expected %d)", currentPlayer, (state->handCount[currentPlayer]), (handCtpre + 2), (state->deckCount[currentPlayer]), (deckCtpre - disCardTot - 2)); 
    }
}

int main(int argc, char ** argv)
{
    int i, j;	//for loop counters
    int player;
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    printf("Starting Adventurer card random test.\n");
    initializeGame(MAX_PLAYERS, k, atoi(argv[1]), &G);
    //initialize each player to have handCount = MAX_HAND
    //and deckCount = MAX_DECK
    for (i = 0; i < G.numPlayers; i++)
    {
	G.handCount[i] = MAX_HAND;
	G.deckCount[i] = 333;
    
    //initialize 1/3 of deck to be copper
   	for (j = 0; j < 111; j++)
	{
	    if (j%2 == 0)	//even number
	    	G.deck[i][j] = copper;
	    else
	 	G.deck[i][j] = smithy; //non-treasure card
	}
    //initialize 1/3 of deck to be silver
        for (j = 111; j < 222; j++)
	{
	    if (j%2 == 0)	//even number
	    	G.deck[i][j] = silver;
	    else
	 	G.deck[i][j] = smithy; //non-treasure card
	} 
    //initialize 1/3 of deck to be gold
    	for (j = 222; j < 333; j++)
	{
	    if (j%2 == 0)	//even number
	    	G.deck[i][j] = gold;
	    else
	 	G.deck[i][j] = smithy; //non-treasure card
	}
    }
    srand(atoi(argv[1]));
    struct timeval start, end;
    float total;
    gettimeofday(&start, 0);
    for ( i = 0; i < 1000; i++)
    {
	printf("TEST CASE %d: ", i);
	//choose random player
	player = rand()%MAX_PLAYERS;
	testAdventurerCard(player, &G);
    }
    gettimeofday(&end, 0);
    //from http://stackoverflow.com/questions/10192903/time-in-milliseconds
    total = (end.tv_sec - start.tv_sec) * 1000.0f + (end.tv_usec - start.tv_usec)/1000.0f;
    printf("Total time: %f ms.\n", total);
    return 0;
}

#include "dominion.h"
#include "dominion_helpers.h"
#include "test_help.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

//unittest for smithy card
void testSmithyCard(int currentPlayer, int handPos, struct gameState *state)
{
    if (assertIsValid("test smithy card: valid player", currentPlayer, state))
    {
	int handCtpre = state->handCount[currentPlayer];
	int deckCtpre = state->deckCount[currentPlayer];
	int playedCtpre = state->playedCardCount;
	printf("Player: %d, handPos: %d, pre hand count: %d, pre deck count: %d, pre played card count: %d.\n", currentPlayer, handPos, handCtpre, deckCtpre, playedCtpre);
	playSmithy(currentPlayer, state, handPos);
	//hand count should increase by 2
	//deck count should decrease by 3
	//played card count should increase by 1
	testCounts(currentPlayer, state, handCtpre, deckCtpre, playedCtpre, 2, -3, 1);
    }
}

int main(int argc, char** argv)
{
    int i, j; //for loop counter
    int player, handPos;
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
    printf("Starting Smithy card random test.\n");
    initializeGame(MAX_PLAYERS, k, atoi(argv[1]), &G);
    //initialize each player to have handCount = MAX_HAND
    //and deckCount = MAX_DECK
    for (i = 0; i < G.numPlayers; i++)
    {
	G.handCount[i] = 300;
	G.deckCount[i] = 300;
	G.discardCount[i]=300;
	//set all cards in hand to smithy card
	for (j = 0; j < 300; j++)
	{
	    G.hand[i][j] = smithy;
	}
	//set all cards in deck to smithy card
	for (j = 0; j < 300; j++)
	{
	    G.deck[i][j] = smithy;
	}
	//set all cards in discard to smithy card
	for (j = 0; j < 300; j++)
	{
	    G.discard[i][j] = smithy;
	}
    }
    srand(atoi(argv[1]));
    struct timeval start, end;
    float total;
    gettimeofday(&start, 0);
    for (i = 0; i < 1000; i++)	//run 1000 random tests
    {
	printf("TEST CASE %d:", i);
	//choose random player
	player = rand()%MAX_PLAYERS;
	//choose random handPos
	handPos = rand()%300;
	if (G.hand[player][handPos] == smithy)
	{ 
	    testSmithyCard(player, handPos, &G);
	}
	else
	    printf("handPos not a smithy card\n");
    }
    gettimeofday(&end, 0);
    //from http://stackoverflow.com/questions/10192903/time-in-milliseconds
    total = (end.tv_sec - start.tv_sec) * 1000.0f + (end.tv_usec - start.tv_usec)/1000.0f;
    printf("Total time: %f ms.\n", total);

    return 0;
}

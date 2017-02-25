//Dominic Giacoppe, SF2, card test 1
//tests smithy
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "rngs.h"


//creates a dummy state with x players who have a bunch of test cards in hand and discard.
struct gameState * stateMaker(int numplayers, struct gameState * current)
{
int i = 0;
int j = 0;
current->numPlayers = numplayers;
for(; i < numplayers; i++)
{
for(j = 0; j < numplayers; j++)
{
current->hand[i][j] = -12;
current->deck[i][j] = -12;
current->discard[i][j] = -12;
}
current->handCount[i] = numplayers;
current->deckCount[i] = numplayers;
current->discardCount[i] = numplayers;
}
current->whoseTurn = 0;
//current.playedCards = NULL;
current->playedCardCount = 0;
return current;
}

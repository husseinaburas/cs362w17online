//Dominic Giacoppe, SF2, card test 1
//tests smithy
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "rngs.h"
#include <time.h>

void abortDump(struct gameState * current, int cycle, int priorHandCount)
{
int i = 0;
printf("%d prior hand size\n", priorHandCount);
printf("%d hand size\n", current->handCount[0]);
for(i = 0; i < current->handCount[0]; i++)
	printf("%d ", current->hand[0][i]);
printf("\n");
printf("%d deck size\n", current->deckCount[0]);
for(i = 0; i < current->deckCount[0]; i++)
	printf("%d ", current->deck[0][i]);
printf("\n");
printf("%d dis size\n", current->discardCount[0]);
for(i = 0; i < current->discardCount[0]; i++)
	printf("%d ", current->discard[0][i]);
printf("\n%d error #\n", cycle);
exit(cycle);
}

int randocard()
{
return (rand()%26);
}

//26 cards total 0 - 25
void randomizer(struct gameState * current, int size)
{
int j = 0;
current->handCount[0] = rand() % size; 
for(j = 0; j < current->handCount[0]; j++)
	current->hand[0][j] = randocard();

current->hand[0][current->handCount[0]] = smithy; //put a smithy card on top to test 
current->handCount[0]++;

current->deckCount[0] = rand() % size;
for(j = 0; j < current->deckCount[0]; j++)
	current->deck[0][j] = randocard();


current->discardCount[0] = rand() % size;
for(j = 0; j < current->discardCount[0]; j++)
	current->discard[0][j] = randocard();
}


int main(int argc, char * args[])
{
struct gameState * current = newGame();
srand(atoi(args[1])); //the random seed as requested by the assignment.
int limit = 100;
int priorHandCount = 0;
int noCards = -1;
if(argc > 2)
	limit = atoi(args[2]); //if you want to limit your tests to a specific number
int size = 30;
if(argc > 3)
	size = atoi(args[3]); //mess with the max hand/deck/discard size as well

for(int i = 0; i < limit; i++)
{
noCards = -1;
randomizer(current, size); 
priorHandCount = current->handCount[0];
if((current->deckCount[0] + current->discardCount[0]) == 0) //if there is nothing in either pile
	noCards = 0;
if((current->deckCount[0] + current->discardCount[0]) == 1) //if there is only 1 card
	noCards = 1;
if((current->deckCount[0] + current->discardCount[0]) == 2) //if there are only 2 cards
	noCards = 2;
cardEffect(smithy, 0,0,0, current, current->deckCount[0], 0); //play smithy
//so these check for a couple things. All check to make sure we have the appropriate number of cards in hand
if(noCards == 0 && (current->handCount[0] != priorHandCount-1))
	abortDump(current, 1, priorHandCount);

if(noCards == 1 && (current->handCount[0] != priorHandCount))
	abortDump(current, 2, priorHandCount);

if(noCards == 2 && (current->handCount[0] != priorHandCount+1))
	abortDump(current, 3, priorHandCount);

if(noCards == -1 && (current->handCount[0] != priorHandCount+2))
	abortDump(current, 4, priorHandCount);

}
//we made it
printf("%s\n", "All clear in smithy random");
return 0;
}

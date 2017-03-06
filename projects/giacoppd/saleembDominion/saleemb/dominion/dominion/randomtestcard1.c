//Dominic Giacoppe, SF2, card test 1
//tests village
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "rngs.h"
#include <time.h>

void abortDump(struct gameState * current, int cycle)
{
int i = 0;
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
current->numActions = 1;
int j = 0;
current->handCount[0] = rand() % size; 
for(j = 0; j < current->handCount[0]; j++)
	current->hand[0][j] = randocard();

current->hand[0][current->handCount[0]] = village; //put an adventurer card on top to test 
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
int priorActionCount = 0;
int noCards = 0;
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
priorActionCount = 1; //you always start your turn with 1 action
if(current->deckCount[0] + current->discardCount[0] == 0) //if there is nothing in either pile
	noCards = 0;
cardEffect(village, 0,0,0, current, current->deckCount[0], 0); //play village
//so these check for a couple things. All check to make sure we have the appropriate number of cards in hand
if((noCards == 0) && ((current->handCount[0] != priorHandCount-1) || (current->numActions != priorActionCount+1)))
	abortDump(current, 1);

if(noCards == -1)
	if((current->handCount[0] != priorHandCount) || (current->numActions != priorActionCount+1))
		abortDump(current, 2);
}
//we made it
printf("%s\n", "All clear in villager random");
return 0;
}

//Dominic Giacoppe, SF2, card test 1
//tests adventurer
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "rngs.h"
#include <time.h>

void abortDump(struct gameState * current, int cycle, int * flags)
{
//to be added
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
printf("\n");
for(i = 0; i < 8; i++)
	printf("%d ", flags[i]);
printf("\n%d error #\n", cycle);
exit(cycle);
}

int randocard()
{
return (rand()%26);
}

//26 cards total 0 - 25
//gold is 6 copper is 4 silver 5
void randomizer(struct gameState * current, int * flags, int size)
{
int tempCard = 0;
int count = 0;
int j = 0;
current->handCount[0] = rand() % size; //don't need to keep track of the coins in hand
for(j = 0; j < current->handCount[0]; j++)
{	
tempCard = randocard();
current->hand[0][j] = tempCard;
}
current->hand[0][current->handCount[0]] = adventurer; //put an adventurer card on top to test 
current->handCount[0]++;

current->deckCount[0] = rand() % size;
for(j = 0; j < current->deckCount[0]; j++)
{
tempCard = randocard();
switch(tempCard) //count how many coins we put in the deck for later
{
	case 4:
	flags[0]++;
	if(count < 2)
	{
	 flags[count+6] = 4;
	 count++;
	}
	break;
	case 5:
	if(count < 2)
	{
	 flags[count+6] = 5;
	 count++;
	}
	flags[1]++;
	break;
	case 6:
	if(count < 2)
	{
	 flags[count+6] = 6;
	 count++;
	}
	flags[2]++;
	break;
}
current->deck[0][j] = randocard();
}

current->discardCount[0] = rand() % size;
for(j = 0; j < current->discardCount[0]; j++)
{
tempCard = randocard();
switch(tempCard) //count how many coins we put in the discard for later
{
	case 4:
	flags[3]++;
	{
	 flags[count+6] = 4;
	 count++;
	}
	break;
	case 5:
	flags[4]++;
	{
	 flags[count+6] = 5;
	 count++;
	}
	break;
	case 6:
	flags[5]++;
	{
	 flags[count+6] = 6;
	 count++;
	}
	break;
}
current->discard[0][j] = tempCard;
}
}


int main(int argc, char * args[])
{
struct gameState * current = newGame();
srand(time(NULL)); //the random seed as requested by the assignment.
int coins = 0; //number of coins in discard and deck
int limit = 100;
int priorHandCount = 0;
if(argc > 1)
	limit = atoi(args[1]); //if you want to limit your tests to a specific number
int size = 15;
if(argc > 2)
	size = atoi(args[2]);
int flags[8] = {0,0,0,0,0,0,0,0};

for(int i = 0; i < limit; i++)
{
randomizer(current, flags, size); 
priorHandCount = current->handCount[0];
coins = flags[3] + flags[4] + flags[5] + flags[0] + flags[1] + flags[2]; //count the number of coins we have to draw
coins = coins % 3; //We only need to see if there is at least 2 coins to draw
cardEffect(adventurer, 0,0,0, current, current->deckCount[0], 0); //play adventurer
//so these check for a couple things. All check to make sure we have the appropriate number of cards in hand
if(coins == 0)
if((current->handCount[0] + 1) != priorHandCount)
	abortDump(current, 0, flags);
//this one makes sure that if we only should draw 1 coin, that it's added to our hand and that it's the right kind of coin
if(coins == 1)
if(((current->handCount[0]) != (priorHandCount)) || (current->hand[0][current->handCount[0]-1] != flags[6]))
	abortDump(current, 1, flags);
//this one does the same as above, but with 2 coins. 
if(coins == 2)
if(((current->handCount[0]) != (priorHandCount+1)) || (current->hand[0][current->handCount[0]-1] != flags[7]) || (current->hand[0][current->handCount[0]-2] != flags[6]))  
	abortDump(current, 2, flags); //if the above fails something bad happened to adventurer, dump the gameState
}
//we made it
printf("%s\n", "All clear in adventurer random");
return 0;
}

//Dominic Giacoppe, SF2, card test 1
//tests village
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "rngs.h"
#include "createTestState.c"

void aborttest(char * msg)
{
printf("%s\n", msg);
exit(1);
//this func just prints things for me
}

int main()
{
struct gameState * current = newGame();
current = stateMaker(3, current);
current->hand[0][3] = village;
current->handCount[0]++; //add village to hand on top of the fake game state
printf("Current # of cards for player 0: %d\n", (*current).handCount[0]);
printf("Current # of actions for player 0: %d\n", (*current).numActions);
int actions = current->numActions;
int handnum = current->handCount[0];
cardEffect(village, 0,0,0, current, 3, 0);
printf("Current # of cards for player 0 after village: %d\n", current->handCount[0]);
if(handnum != current->handCount[0]) //discards the village card and draws 1, so no net change
	aborttest("Cards wrong, cardtest4\n");
printf("Current # of actions for player 0 after village: %d\n", (*current).numActions);
if(actions+1 != current->numActions) //playing village used 1 action, so you net gain 1
	aborttest("actions wrong, cardtest4\n");
return 0;
}

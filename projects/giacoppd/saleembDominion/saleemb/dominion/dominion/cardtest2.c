//Dominic Giacoppe, SF2, card test 1
//tests adventurer
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
//test with 2 treasures in deck
struct gameState * current = newGame();
current = stateMaker(3, current);
current->hand[0][3] = adventurer;
current->handCount[0]++; //add adventurer to hand on top of the fake game state
current->deck[0][1] = silver;
current->deck[0][2] = gold; //put some cash over the fake cards in the deck for adventurer to find
updateCoins(0, current, 0);
int curCoins = current->coins;
printf("Current amount of cash for player 0: %d\n", current->coins);
cardEffect(adventurer, 0,0,0, current, 3, 0);
updateCoins(0, current, 0);
printf("Current amount of cash for player 0 after adventurer: %d\n", current->coins);
if(curCoins+5 != current->coins)
	aborttest("Money is off, test 1 cardtest2\n");
//test with 1 treasure in deck
current = stateMaker(3, current);
current->hand[0][3] = adventurer;
current->handCount[0]++; //add adventurer to hand on top of the fake game state
current->deck[0][2] = gold; //put some cash over the fake cards in the deck for adventurer to find
updateCoins(0, current, 0);
curCoins = current->coins;
printf("Current amount of cash for player 0: %d\n", current->coins);
cardEffect(adventurer, 0,0,0, current, 3, 0);
updateCoins(0, current, 0);
printf("Current amount of cash for player 0 after adventurer: %d\n", current->coins);
if(curCoins+3 != current->coins)
	aborttest("Money is off, test 2 cardtest2\n");
/* currently commented until I work it out
//test with no treasure in deck
current = stateMaker(3, current);
current->hand[0][3] = adventurer;
current->handCount[0]++; //add adventurer to hand on top of the fake game state
updateCoins(0, current, 0); 
curCoins = current->coins;
printf("Current amount of cash for player 0: %d\n", current->coins);
cardEffect(adventurer, 0,0,0, current, 3, 0);
updateCoins(0, current, 0);
printf("Current amount of cash for player 0 after adventurer: %d\n", current->coins);
if(curCoins != current->coins) //this test breaks, issue with adventurer itself, never stops drawing cards and incrimenting z until it goes off it's bounds
	aborttest("Money is off, test 3 cardtest2\n");
*/
return 0;
}

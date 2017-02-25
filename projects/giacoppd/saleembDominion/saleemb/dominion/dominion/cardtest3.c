//Dominic Giacoppe, SF2, card test 1
//tests mine
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
int * k = kingdomCards(copper, silver, gold, -12, -13, -14, -15, -62, -16, -22);
initializeGame(3, k, 123, current); //inits depos so we can trash properly
//copper -> silver
current = stateMaker(3, current); //then init cards and player decks so that initGame doesn't override 
current->hand[0][3] = mine;
current->handCount[0]++; //add mine to hand on top of the fake game state
current->hand[0][4] = copper;
current->handCount[0]++; //add a copper so we have something to trash as well
updateCoins(0, current, 0);
int curCoins = current->coins;
printf("Current amount of cash for player 0: %d\n", current->coins);
cardEffect(mine, 4, 5, 0, current, 3, 0);
updateCoins(0, current, 0);
printf("Current amount of cash for player 0 after mine: %d\n", current->coins);
if(curCoins+1 != current->coins) //copper is 1, silver is 2, so difference is 1
	aborttest("Money is off, test 1 cardtest3\n");
//silver -> gold test
current = stateMaker(3, current); //then init cards and player decks so that initGame doesn't override 
current->hand[0][3] = mine;
current->handCount[0]++; //add mine to hand on top of the fake game state
current->hand[0][4] = silver;
current->handCount[0]++; //add a silver so we have something to trash as well
updateCoins(0, current, 0);
curCoins = current->coins;
printf("Current amount of cash for player 0: %d\n", current->coins);
cardEffect(mine, 4, 6, 0, current, 3, 0);
updateCoins(0, current, 0);
printf("Current amount of cash for player 0 after mine: %d\n", current->coins);
if(curCoins+1 != current->coins) //silver is 2, gold is 3, so difference is 1 again
	aborttest("Money is off, test 2 cardtest3\n");
//gold test (shouldn't do anything)
current = stateMaker(3, current); //then init cards and player decks so that initGame doesn't override 
current->hand[0][3] = mine;
current->handCount[0]++; //add mine to hand on top of the fake game state
current->hand[0][4] = gold;
current->handCount[0]++; //add a gold
updateCoins(0, current, 0);
curCoins = current->coins;
printf("Current amount of cash for player 0: %d\n", current->coins);
cardEffect(mine, 4, 6, 0, current, 3, 0);
updateCoins(0, current, 0);
printf("Current amount of cash for player 0 after mine: %d\n", current->coins);
if(curCoins != current->coins) //Should be the same, since I'm trashing gold for gold
	aborttest("Money is off, test 3 cardtest3\n"); 
//no money test
current = stateMaker(3, current); //then init cards and player decks so that initGame doesn't override 
current->hand[0][3] = mine;
current->handCount[0]++; //add mine to hand on top of the fake game state
updateCoins(0, current, 0); //but no golds or anything to trash this time
curCoins = current->coins;
printf("Current amount of cash for player 0: %d\n", current->coins);
cardEffect(mine, 4, 6, 0, current, 3, 0);
updateCoins(0, current, 0);
printf("Current amount of cash for player 0 after mine: %d\n", current->coins);
if(curCoins != current->coins) //Should be the same, since nothing actually happened.
	aborttest("Money is off, test 3 cardtest3\n");
//the "who would do this" test: trash gold for copper
/* doesn't work due to implimentation, see line 864 in dominion.c
current = stateMaker(3, current); //then init cards and player decks so that initGame doesn't override 
current->hand[0][3] = mine;
current->handCount[0]++; //add mine to hand on top of the fake game state
current->hand[0][4] = gold;
current->handCount[0]++; //add a gold
updateCoins(0, current, 0);
curCoins = current->coins;
printf("Current amount of cash for player 0: %d\n", current->coins);
cardEffect(mine, 4, 4, 0, current, 3, 0);
updateCoins(0, current, 0);
printf("Current amount of cash for player 0 after mine: %d\n", current->coins);
if(curCoins-2 != current->coins) //copper 1, gold 3, so you should have 2 less money than you started with
	aborttest("Money is off, test 4 cardtest3\n");
*/
return 0;
}

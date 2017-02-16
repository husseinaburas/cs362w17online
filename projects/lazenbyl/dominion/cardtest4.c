#include<stdio.h>
#include<stdlib.h>

#include "dominion.h"


void testPerformGreatHallAction(){

  struct gameState state;
  int k[10] = {adventurer, gardens, great_hall, village, minion, mine, cutpurse,
  sea_hag, tribute, smithy};

  initializeGame(2, k, 1, &state);
	
  int currentPlayer = whoseTurn(&state);

   state.hand[currentPlayer][0] = smithy;
   state.hand[currentPlayer][1] = mine;
   state.hand[currentPlayer][2] = copper;
   state.hand[currentPlayer][3] = great_hall;
   state.handCount[currentPlayer] = 4;
   state.numActions = 1;
   state.playedCardCount = 0;

    performGreatHallAction(currentPlayer, &state, 3);	


   if(state.handCount[currentPlayer]==4){

   		 printf("Function testPerformGreatHallAction PASS. Hand count size == 4.\n");

   }
   else{

   		 printf("Function testPerformGreatHallAction FAIL. Hand count size != 4.\n");

   }

   if(state.numActions==2){

   		 printf("Function testPerformGreatHallAction PASS. Number of actions = 2.\n");

   }
   else{

   		 printf("Function testPerformGreatHallAction FAIL. Number of actions != 2.\n");

   }

   if(state.playedCardCount ==1) {

   		printf("Function test testPerformGreatHallAction PASS. Number of played cards == 1.\n");
   }
   else{
   	 printf("Function test testPerformGreatHallAction FAIL. Number of played cards != 1.\n");
   }
}


int main(int argc, char *argv[])
{
    testPerformGreatHallAction();
    return 0;
}
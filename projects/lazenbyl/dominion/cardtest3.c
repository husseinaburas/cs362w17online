#include<stdio.h>
#include<stdlib.h>

#include "dominion.h"


void testPerformVillageAction(){

	
  struct gameState state, testState;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
  sea_hag, tribute, smithy};

  initializeGame(2, k, 1, &state);
	
  int currentPlayer = 0;

  /*********Test 1**************/
  // Test village adds two actions, adds one card to played cards, and hand count stays same
   state.hand[currentPlayer][0] = smithy;
   state.hand[currentPlayer][1] = gardens;
   state.hand[currentPlayer][2] = copper;
   state.hand[currentPlayer][3] = village;
   state.handCount[currentPlayer] = 4;
   state.numActions = 1;
   state.playedCardCount = 0;
   state.whoseTurn = currentPlayer;
   memcpy(&testState, &state, sizeof(struct gameState));

   performVillageAction(currentPlayer, &testState, 3);

   if(testState.handCount[currentPlayer]==4){
   		 printf("Function testPerformVillageAction PASS. Hand count size == 4.\n");

   }
   else{

   		 printf("Function testperformVillageAction FAIL. Hand count size != 4.\n");

   }

   if(testState.numActions==3){

   		 printf("Function testperformVillageAction PASS. Number of actions = 3.\n");

   }
   else{

   		 printf("Function testperformVillageAction FAIL. Number of actions != 3.\n");

   }

   if (testState.playedCardCount == 1) {
   		 printf("Function testperformVillageAction PASS. Played card count == 1\n");
   }
   else {

		 printf("Function testperformVillageAction FAIL. Played card count != 1\n");
   }

   int otherPlayer = 1;
   for (int x = 0; x < state.handCount[otherPlayer]; x++) {
   		if (testState.hand[otherPlayer][x] != state.hand[otherPlayer][x]) {
   			printf("FAIL - changed state for other player\n");
   		}
   }

    for (int x = 0; x < state.deckCount[otherPlayer]; x++) {
   		if (testState.deck[otherPlayer][x] != state.deck[otherPlayer][x]) {
   			printf("FAIL - changed state for other player\n");
   		}
   }

    for (int x = 0; x < state.discardCount[otherPlayer]; x++) {
   		if (testState.discard[otherPlayer][x] != state.discard[otherPlayer][x]) {
   			printf("FAIL - changed state for other player\n");
   		}
   }
}


int main(int argc, char *argv[])
{
    testPerformVillageAction();
    return 0;
}
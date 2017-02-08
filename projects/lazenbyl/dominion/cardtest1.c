#include<stdio.h>
#include<stdlib.h>

#include "dominion.h"


void testPerformSmithyAction(){


  struct gameState state;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
  sea_hag, tribute, smithy};

  initializeGame(2, k, 1, &state);
	
  int currentPlayer = whoseTurn(&state);
/*******************Test 1*********************/    
//deck needs to be shuffled in order to pull enough cards for smithy 

  state.deckCount[currentPlayer] = 1;
  state.deck[currentPlayer][0] = copper;
  state.discardCount[currentPlayer] = 5;
  state.discard[currentPlayer][0] = village;
  state.discard[currentPlayer][1] = silver;
  state.discard[currentPlayer][2] = minion;
  state.discard[currentPlayer][3] = gold;
  state.discard[currentPlayer][4] = mine;
  state.playedCardCount = 0;
  state.hand[currentPlayer][0] = smithy;
  state.handCount[currentPlayer] = 1;


  performSmithyAction(currentPlayer, &state, 0);
  //discarded smithy from hand to be 0 in hand but added 3 from smithy action 
  if(state.handCount[currentPlayer]==3){

        printf("Test 1 Function testPerformSmithyAction PASS. Hand count == 3.\n");
  }
  else{
        printf("Test 1 Function testPerformSmithyAction FAIL. Hand count != 3.\n");
  }

  //one card was played from deck, then 5 were shuffled in from discard and 2 more were drawn, so 3 should be left
  if(state.deckCount[currentPlayer]==3){

        printf("Test 1 Function testPerformSmithyAction PASS. Deck count == 3.\n");
  }
  else{
        printf("Test 1 Function testPerformSmithyAction FAIL. Deck count != 3.\n");
  }

int i = state.playedCardCount;
	//only one card should be played after performing action
  if(i==1){

        printf("Test 1 Function testPerformSmithyAction PASS. Played card count == 1.\n");
  }
  else{
        printf("Test 1 Function testPerformSmithyAction FAIL. Played card count != 1. %i \n",i);
  }

	//we should shuffle the discard since we only had one card in the deck and discard should be 0 
  if(state.discardCount[currentPlayer]==0){

        printf("Test 1 Function testPerformSmithyAction PASS. Discard count == 0.\n");
  }
  else{
        printf("Test 1 Function testPerformSmithyAction FAIL. Discard count != 0. %i \n",i);
  }

/*******************Test 2*********************/
//deck has enough cards to handle smithy action 

  state.deckCount[currentPlayer] = 4;
  state.deck[currentPlayer][0] = copper;
  state.discardCount[currentPlayer] = 1;
  state.deck[currentPlayer][0] = village;
  state.deck[currentPlayer][1] = silver;
  state.deck[currentPlayer][2] = minion;
  state.deck[currentPlayer][3] = gold;
  state.playedCardCount = 0;
  state.hand[currentPlayer][0] = smithy;
  state.handCount[currentPlayer] = 1;


  performSmithyAction(currentPlayer, &state, 0);
  //discarded smithy from hand to be 0 in hand but added 3 from smithy action 
  if(state.handCount[currentPlayer]==3){

        printf("Test 2 Function testPerformSmithyAction PASS. Hand count == 3.\n");
  }
  else{
        printf("Test 2 Function testPerformSmithyAction FAIL. Hand count != 3.\n");
  }

  //all 3 cards were taken from deck so only 1 should be left 
  if(state.deckCount[currentPlayer]==1){

        printf("Test 2 Function testPerformSmithyAction PASS. Deck count == 1.\n");
  }
  else{
        printf("Test 2 Function testPerformSmithyAction FAIL. Deck count != 1.\n");
  }

	int j = state.playedCardCount;
	//only one card should be played after performing action
  if(j==1){

        printf("Test 2 Function testPerformSmithyAction PASS. Played card count == 1.\n");
  }
  else{
        printf("Test 2 Function testPerformSmithyAction FAIL. Played card count != 1. %i \n",j);
  }

	//discard count should remain the same  
  if(state.discardCount[currentPlayer]==1){

        printf("Test 2 Function testPerformSmithyAction PASS. Discard count == 1.\n");
  }
  else{
        printf("Test 2 Function testPerformSmithyAction FAIL. Discard count != 1. %i \n",i);
  }

}


int main(int argc, char *argv[])
{
    testPerformSmithyAction();
    return 0;
}
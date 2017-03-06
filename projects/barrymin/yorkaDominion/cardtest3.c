#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"

int main(){
  int i;
  int handPos = 0;
  int pass = 1;
  int player = 0;
	struct gameState state, tempState;
	int k[10] = {smithy, great_hall, gardens, minion, mine, cutpurse,
    sea_hag, tribute, adventurer, council_room};
	initializeGame(2, k, 1000, &state);
  memcpy(&tempState, &state, sizeof(struct gameState));

	printf("-------------------------- Testing Great Hall ------------------------\n");
	printf("\nTEST 1:\n Using Great Hall \n");
   //set player hand with great hall
  tempState.hand[player][handPos]= great_hall;
  cardEffect(great_hall,0,0,0,&tempState,handPos,0);
  // assert deck - 1
  printf(" new deckCount = %d, expected %d\n",tempState.deckCount[player],state.deckCount[player]-1);
  pass = tempState.deckCount[player]==state.deckCount[player]-1;

  // assert hand count +1 drawn card - 1 great hall
  printf(" new handCount = %d, expected %d\n",tempState.handCount[player],state.handCount[player]);
  pass = pass && tempState.handCount[player]==state.handCount[player];

  // assert discard got great hall
  printf(" new discardCount = %d, expected %d\n",tempState.discardCount[player],state.discardCount[player]+1);
  pass = pass && tempState.discardCount[player]==state.discardCount[player]+1;

  // assert state->actions + 1
  printf(" new # actions = %d, expected %d\n",tempState.numActions,state.numActions+1);
  pass = pass && tempState.numActions==state.numActions+1;

  if(pass)
    printf("--------------------------------------------------------------------\nGreat Hall test SUCCESSFUL\n");
  else
    printf("--------------------------------------------------------------------\nGreat Hall test FAILED\n");
  printf("------------------------- Testing complete -------------------------\n");
  return 0;
}

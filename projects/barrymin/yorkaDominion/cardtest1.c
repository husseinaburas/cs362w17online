#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"

int main(){
  int i;
  int handPos = 0;
  int pass = 1;
  int player = 0;
  int test=0;
	struct gameState state, tempState;
	int k[10] = {smithy, great_hall, gardens, minion, mine, cutpurse,
    sea_hag, tribute, adventurer, council_room};
	initializeGame(2, k, 1000, &state);
  memcpy(&tempState, &state, sizeof(struct gameState));

	printf("-------------------------- Testing Smithy ------------------------\n");
	printf("\nTEST 1:\n Using smithy \n");

  //set player hand with smithy
  tempState.hand[player][handPos]= smithy;
  cardEffect(smithy,0,0,0,&tempState,handPos,0);

  // assert new handCount of whosTurn == prev HandCount + 3 cards - smithy
  printf(" new handCount = %d, expected %d\n",tempState.handCount[player],state.handCount[player]+3-1);
  test = tempState.handCount[player]==state.handCount[player]+3-1;

  // assert new deck == prev deck -3
  printf(" new deckCount = %d, expected %d\n",tempState.deckCount[player],state.deckCount[player]-3);
  test = test && tempState.deckCount[player]==state.deckCount[player]-3;

  // assert discard has smithy
  printf(" new discardCount = %d, expected %d\n",tempState.discardCount[player],state.discardCount[player]+1);
  test = test && tempState.discardCount[player]==state.discardCount[player]+1;

  if(test){
    printf(" Test SUCCESSFUL\n");
  }else{
    printf(" Test FAILED\n");
    pass = 0;
  }
  if(pass)
    printf("--------------------------------------------------------------------\nSmithy test SUCCESSFUL\n");
  else
    printf("--------------------------------------------------------------------\nSmithy test FAILED\n");
  printf("------------------------- Testing complete -------------------------\n");
  return 0;
}

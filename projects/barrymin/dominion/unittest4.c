#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"

int main(){
  int i;
  int result;
  int trueTotal;
  int pass = 1;
  int player = 0;
	struct gameState state, tempState;
	int k[10] = {steward, great_hall, gardens, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};
	initializeGame(2, k, 1000, &state);
  memcpy(&tempState, &state, sizeof(struct gameState));

	printf("------------------------ Testing fullDeckCount() -------------------------\n");
	printf("\nTEST 1:\n Card not in deck\n");
	trueTotal = 0;
	//adventurer was not in the game
	result = fullDeckCount(player, adventurer, &tempState);
	printf(" fullDeckCount returned %d, expected %d\n",result,trueTotal);
  if(result == trueTotal){
    printf(" test SUCCESSFUL\n");
  }else{
    printf(" test FAILED\n");
    pass = 0;
  }

  printf("\nTEST 2:\n Two of card in hand\n");
  memcpy(&tempState, &state, sizeof(struct gameState));

	trueTotal = 2;
	for(i=0; i<tempState.deckCount[player];i++){
      tempState.deck[player][i]=adventurer;
	}
	tempState.handCount[player]=5;
	for(i=0; i<tempState.handCount[player];i++){
      tempState.hand[player][i]=adventurer;
	}
	for(i=0; i<tempState.discardCount[player];i++){
      tempState.discard[player][i]=adventurer;
	}
	tempState.hand[player][0] = copper;
	tempState.hand[player][tempState.handCount[player]-1] = copper;
	result = fullDeckCount(player, copper, &tempState);
	printf(" fullDeckCount returned %d, expected %d\n",result,trueTotal);
  if(result == trueTotal){
    printf(" test SUCCESSFUL\n");
  }else{
    printf(" test FAILED\n");
    pass = 0;
  }

  printf("\nTEST 3:\n Two of card in deck\n");
  memcpy(&tempState, &state, sizeof(struct gameState));

	trueTotal = 2;
  tempState.deckCount[player]=5;
	for(i=0; i<tempState.deckCount[player];i++){
      tempState.deck[player][i]=adventurer;
	}
	for(i=0; i<tempState.handCount[player];i++){
      tempState.hand[player][i]=adventurer;
	}
	for(i=0; i<tempState.discardCount[player];i++){
      tempState.discard[player][i]=adventurer;
	}
	tempState.deck[player][0] = copper;
	tempState.deck[player][tempState.deckCount[player]-1] = copper;
	result = fullDeckCount(player, copper, &tempState);
	printf(" fullDeckCount returned %d, expected %d\n",result,trueTotal);
  if(result == trueTotal){
    printf(" test SUCCESSFUL\n");
  }else{
    printf(" test FAILED\n");
    pass = 0;
  }

  printf("\nTEST 4:\n Two of card in discard\n");
  memcpy(&tempState, &state, sizeof(struct gameState));

	trueTotal = 2;

	for(i=0; i<tempState.deckCount[player];i++){
      tempState.deck[player][i]=adventurer;
	}
	for(i=0; i<tempState.handCount[player];i++){
      tempState.hand[player][i]=adventurer;
	}
	tempState.discardCount[player]=5;
	for(i=0; i<tempState.discardCount[player];i++){
      tempState.discard[player][i]=adventurer;
	}
	tempState.discard[player][0] = copper;
	tempState.discard[player][tempState.discardCount[player]-1] = copper;
	result = fullDeckCount(player, copper, &tempState);
	printf(" fullDeckCount returned %d, expected %d\n",result,trueTotal);
  if(result == trueTotal){
    printf(" test SUCCESSFUL\n");
  }else{
    printf(" test FAILED\n");
    pass = 0;
  }


  if(pass)
    printf("----------------------------------------------------------------------\nfullDeckCount test SUCCESSFUL\n");
  else
    printf("----------------------------------------------------------------------\fullDeckCount test FAILED\n");
  printf("-------------------------- Testing complete --------------------------\n");
  return 0;
}

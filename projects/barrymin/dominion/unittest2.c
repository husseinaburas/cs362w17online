#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {
  int i;
  int pass = 1;
  int result;
	struct gameState state;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	initializeGame(2, k, 1000, &state);

	printf("------------------------ Testing isGameOver() -------------------------\n");
	//Game ends if province supply is empty or any three other supplies are empty
  printf("\nTEST 1:\n No end game condition met (All supplies are not empty)\n");
  //set all supply piles > 0
  for(i=0; i<=treasure_map; i++){
    state.supplyCount[i] = 1;
  }
  result = isGameOver(&state);
  printf(" isGameOver returned %d, expected %d\n",result,0);
  if(result == 0){
    printf(" test SUCCESSFUL\n");
  }else{
    printf(" test FAILED\n");
    pass = 0;
  }

  printf("\nTEST 2:\n No end game condition met with 2 empty supplies (treasure_map, sea_hag)\n");
  //set all supply piles > 0
  for(i=0; i<treasure_map-1; i++){
    state.supplyCount[i] = 1;
  }
  state.supplyCount[treasure_map-1] = 0;
  state.supplyCount[treasure_map] = 0;
  result = isGameOver(&state);
  printf(" isGameOver returned %d, expected %d\n",result,0);
  if(result == 0){
    printf(" test SUCCESSFUL\n");
  }else{
    printf(" test FAILED\n");
    pass = 0;
  }

  printf("\nTEST 3:\n province supply is empty\n");
  state.supplyCount[province] = 0;
  result = isGameOver(&state);
  printf(" isGameOver returned %d, expected %d\n",result,1);
  if(result == 1){
    printf(" test SUCCESSFUL\n");
  }else{
    printf(" test FAILED\n");
    pass = 0;
  }

  printf("\nTEST 4:\n Three supplies are empty (curse, gold, treasure map)\n");
  state.supplyCount[province] = 1;
  state.supplyCount[gold] = 0;
  state.supplyCount[curse] = 0;
  state.supplyCount[treasure_map] = 0;
  result = isGameOver(&state);
  printf(" isGameOver returned %d, expected %d\n",result,1);
  if(result == 1){
    printf(" test SUCCESSFUL\n");
  }else{
    printf(" test FAILED\n");
    pass = 0;
  }

  if(pass)
    printf("--------------------------------------------------------------------\nisGameOver test SUCCESSFUL\n");
  else
    printf("--------------------------------------------------------------------\nisGameOver test FAILED\n");
  printf("-------------------------- Testing complete --------------------------\n");
  return 0;
}


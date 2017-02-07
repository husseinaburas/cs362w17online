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
	int k[10] = {adventurer, great_hall, gardens, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};
	initializeGame(2, k, 1000, &state);
  memcpy(&tempState, &state, sizeof(struct gameState));

	printf("------------------------ Testing scoreFor() -------------------------\n");
	printf("\nTEST 1:\n Hand has all player victory cards\n");
	//remove all victory cards from player
	for(i=0; i<tempState.deckCount[player];i++){
      tempState.deck[player][i]=adventurer;
	}
	for(i=0; i<tempState.handCount[player];i++){
      tempState.hand[player][i]=adventurer;
	}
	for(i=0; i<tempState.discardCount[player];i++){
      tempState.discard[player][i]=adventurer;
	}
	tempState.handCount[player]=5;
	tempState.hand[player][0]= estate;
	tempState.hand[player][1]= province;
	tempState.hand[player][2]= duchy;
	tempState.hand[player][3]= great_hall;
	tempState.hand[player][4]= curse;
	trueTotal = -1+1+3+6+1;

	result = scoreFor(player,&tempState);
	printf(" scoreFor returned %d, expected %d\n",result,trueTotal);
  if(result==trueTotal){
    printf(" test SUCCESSFUL\n");
  }else{
    printf(" test FAILED\n");
    pass = 0;
  }

  printf("\nTEST 2:\n deck has all player victory cards\n");
  memcpy(&tempState, &state, sizeof(struct gameState));
	//remove all victory cards from player
	for(i=0; i<tempState.deckCount[player];i++){
      tempState.deck[player][i]=adventurer;
	}
	for(i=0; i<tempState.handCount[player];i++){
      tempState.hand[player][i]=adventurer;
	}
	for(i=0; i<tempState.discardCount[player];i++){
      tempState.discard[player][i]=adventurer;
	}
	tempState.deckCount[player]=7;
	tempState.deck[player][0]= estate;
	tempState.deck[player][1]= province;
	tempState.deck[player][2]= duchy;
	tempState.deck[player][3]= great_hall;
	tempState.deck[player][4]= curse;
	tempState.deck[player][5]= curse;
	tempState.deck[player][6]= curse;
	trueTotal = -1-1-1+1+3+6+1;

	result = scoreFor(player,&tempState);
	printf(" scoreFor returned %d, expected %d\n",result,trueTotal);
  if(result==trueTotal){
    printf(" test SUCCESSFUL\n");
  }else{
    printf(" test FAILED\n");
    pass = 0;
  }

  printf("\nTEST 3:\n discard has all player victory cards\n");
  memcpy(&tempState, &state, sizeof(struct gameState));
	//remove all victory cards from player
	for(i=0; i<tempState.deckCount[player];i++){
      tempState.deck[player][i]=adventurer;
	}
	for(i=0; i<tempState.handCount[player];i++){
      tempState.hand[player][i]=adventurer;
	}
	tempState.discardCount[player] = 6;
	tempState.discard[player][0]= estate;
	tempState.discard[player][1]= province;
	tempState.discard[player][2]= duchy;
	tempState.discard[player][3]= great_hall;
	tempState.discard[player][4]= curse;
	tempState.discard[player][5]= province;
	trueTotal = 1+6+3+1-1+6;

	result = scoreFor(player,&tempState);
	printf(" scoreFor returned %d, expected %d\n",result,trueTotal);
  if(result==trueTotal){
    printf(" test SUCCESSFUL\n");
  }else{
    printf(" test FAILED\n");
    pass = 0;
  }

  printf("\nTEST 4:\n Player has one gardens card\n");
    memcpy(&tempState, &state, sizeof(struct gameState));
	//set number of player cards 20
	tempState.deckCount[player]=10;
	tempState.handCount[player]=5;
	tempState.discardCount[player]=5;
	//remove all victory cards from player
	for(i=0; i<tempState.deckCount[player];i++){
      tempState.deck[player][i]=adventurer;
	}
	for(i=0; i<tempState.handCount[player];i++){
      tempState.hand[player][i]=adventurer;
	}
	for(i=0; i<tempState.discardCount[player];i++){
      tempState.discard[player][i]=adventurer;
	}
	tempState.hand[player][0]= gardens;
	//int division round down
	trueTotal = (tempState.discardCount[player]+tempState.deckCount[player]+tempState.handCount[player])/10;

	result = scoreFor(player,&tempState);
	printf(" scoreFor returned %d, expected %d\n",result,trueTotal);
  if(result==trueTotal){
    printf(" test SUCCESSFUL\n");
  }else{
    printf(" test FAILED\n");
    pass = 0;
  }

  printf("\nTEST 5:\n Hand, deck and discard have victory cards\n");
  memcpy(&tempState, &state, sizeof(struct gameState));
	//remove all victory cards from player
	tempState.deckCount[player]=5;
	for(i=0; i<tempState.deckCount[player];i++){
      tempState.deck[player][i]=adventurer;
	}
	tempState.handCount[player]=2;
	for(i=0; i<tempState.handCount[player];i++){
      tempState.hand[player][i]=adventurer;
	}
	tempState.discardCount[player]=3;
	for(i=0; i<tempState.discardCount[player];i++){
      tempState.discard[player][i]=adventurer;
	}
	tempState.deck[player][0]= estate;
	tempState.deck[player][4]= province;
	tempState.hand[player][1]= duchy;
	tempState.discard[player][0]= great_hall;
	tempState.discard[player][2]= great_hall;
	trueTotal = 1+6+3+1+1;

	result = scoreFor(player,&tempState);
	printf(" scoreFor returned %d, expected %d\n",result,trueTotal);
  if(result==trueTotal){
    printf(" test SUCCESSFUL\n");
  }else{
    printf(" test FAILED\n");
    pass = 0;
  }
  printf("\nTEST 5:\n PLayer has no victory cards\n");
  memcpy(&tempState, &state, sizeof(struct gameState));
	//remove all victory cards from player
	for(i=0; i<tempState.deckCount[player];i++){
      tempState.deck[player][i]=adventurer;
	}
	for(i=0; i<tempState.handCount[player];i++){
      tempState.hand[player][i]=adventurer;
	}
	for(i=0; i<tempState.discardCount[player];i++){
      tempState.discard[player][i]=adventurer;
	}
	trueTotal = 0;
	result = scoreFor(player,&tempState);
	printf(" scoreFor returned %d, expected %d\n",result,trueTotal);
  if(result==trueTotal){
    printf(" test SUCCESSFUL\n");
  }else{
    printf(" test FAILED\n");
    pass = 0;
  }
  if(pass)
    printf("--------------------------------------------------------------------\nscoreFor test SUCCESSFUL\n");
  else
    printf("--------------------------------------------------------------------\nscoreFor test FAILED\n");
  printf("-------------------------- Testing complete --------------------------\n");
  return 0;
}

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
	int k[10] = {adventurer, great_hall, gardens, minion, mine, cutpurse,
    sea_hag, tribute,salvager , council_room};
	initializeGame(2, k, 1000, &state);
  memcpy(&tempState, &state, sizeof(struct gameState));

	printf("-------------------------- Testing Adventurer ------------------------\n");
	printf("\nTEST 1:\n Using Adventurer with treasure in deck \n");

	//set player hand with adventurer
  tempState.hand[player][handPos]= adventurer;
  //player must have at least 2 treasure cards or adventurer fails
  tempState.deckCount[player]=4;
  tempState.deck[player][0]= gold;
  tempState.deck[player][1]= province;
  tempState.deck[player][2]= province;
  tempState.deck[player][3]= gold;
  cardEffect(adventurer,0,0,0,&tempState,handPos,0);

  // assert cards were drawn till 2 treasures were found
  printf(" new deckCount = %d, expected %d\n",tempState.deckCount[player],0);
  test = tempState.deckCount[player]==0;

  // assert discard == prev discard + 2 provinces
  printf(" new discardCount = %d, expected %d\n",tempState.discardCount[player],state.discardCount[player]+3);
  test = test && tempState.discardCount[player]==state.discardCount[player]+3;
  printf("  new player discard: ");
  for(i=0; i<tempState.discardCount[player];i++){
    printf("%d ",tempState.discard[player][i]);
  }
  printf("\n  expected   discard: %d ",adventurer);
  for(i=0; i<state.discardCount[player];i++){
    printf("%d ",tempState.discard[player][i]);
  }
  printf("%d %d\n", province,province);
  // assert player has the two treasure cards and no adventurer
  printf(" new handCount = %d, expected %d\n",tempState.handCount[player],state.handCount[player]+1);
  printf("  new player hand: ");
  for(i=0; i<tempState.handCount[player];i++){
    printf("%d ",tempState.hand[player][i]);
  }
  printf("\n  expected   hand: ");
  for(i=1; i<state.handCount[player];i++){
    printf("%d ",tempState.hand[player][i]);
  }
  printf("%d %d\n", gold,gold);
  test = test && tempState.handCount[player]== state.handCount[player]+1;


  if(test){
    printf(" Test SUCCESSFUL\n");
  }else{
    printf(" Test FAILED\n");
    pass = 0;
  }




  printf("\nTEST 2:\n Using Adventurer with treasure in discard \n");
  memcpy(&tempState, &state, sizeof(struct gameState));
	//set player hand with adventurer
  tempState.hand[player][handPos]= adventurer;
  //player must have at least 2 treasure cards or adventurer fails
  tempState.deckCount[player]=0;
  tempState.discardCount[player]=4;
  tempState.discard[player][0]= gold;
  tempState.discard[player][1]= province;
  tempState.discard[player][2]= province;
  tempState.discard[player][3]= gold;
  cardEffect(adventurer,0,0,0,&tempState,handPos,0);

  // assert cards were drawn till 2 treasures were found
  printf(" new deckCount = %d, expected < %d\n",tempState.deckCount[player],3);
  test = tempState.deckCount[player] < 3;
  printf("  new player deck: ");
  for(i=0; i<tempState.deckCount[player];i++){
    printf("%d ",tempState.deck[player][i]);
  }
  // assert discard == prev discard + 2 provinces
  printf("\n new discardCount = %d, expected < %d\n",tempState.discardCount[player],4);
  test = test && tempState.discardCount[player]<4;
  printf("  new player discard: ");
  for(i=0; i<tempState.discardCount[player];i++){
    printf("%d ",tempState.discard[player][i]);
  }
  printf("\n  expected discard has a %d\n",adventurer);

  // assert player has the two treasure cards
  printf(" new handCount = %d, expected %d\n",tempState.handCount[player],state.handCount[player]+2-1);
  printf("  new player hand: ");
  for(i=0; i<tempState.handCount[player];i++){
    printf("%d ",tempState.hand[player][i]);
  }
  printf("\n  expected   hand: ");
  for(i=1; i<state.handCount[player];i++){
    printf("%d ",tempState.hand[player][i]);
  }
  printf("%d %d\n", gold,gold);
  test = test && tempState.handCount[player]== state.handCount[player]+2-1;


  if(test){
    printf(" Test SUCCESSFUL\n");
  }else{
    printf(" Test FAILED\n");
    pass = 0;
  }


  if(pass)
    printf("--------------------------------------------------------------------\nAdventurer test SUCCESSFUL\n");
  else
    printf("--------------------------------------------------------------------\nAdventurer test FAILED\n");
  printf("------------------------- Testing complete -------------------------\n");
  return 0;
}
//playAdventurer
/* ** note test discard adventurer
** note if player doesnt have treasure cards infnt loop
- draws cards until it gets 2 treasure cards
  - player deck has two treasures one in middle and one last and discard has none hand doesnt matter?
    - assert deck == 0
    - assert player has the two treasure cards
    - assert discard == deck
  - player deck has 2 at front
    - assert deck == prev deck -2
    - assert player has the two treasure cards
    - assert discard == prev discard
  - player deck has 2 at second and fourth positions
    - assert deck == prev deck -4
    - assert player has the two treasure cards
    - assert discard == prev discard + 2
*/

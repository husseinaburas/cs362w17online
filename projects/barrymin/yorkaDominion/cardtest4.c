#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"

int main(){
  int i;
  int handPos = 0;
  int pass = 1;
  int player = 0;
  int choice1 = 1;
  int choice1Cost = 6; //gold cost
	struct gameState state, tempState;
	int k[10] = {smithy, great_hall, salvager, minion, mine, cutpurse,
    sea_hag, tribute, adventurer, council_room};
	initializeGame(2, k, 1000, &state);
  memcpy(&tempState, &state, sizeof(struct gameState));

	printf("-------------------------- Testing Salvager ------------------------\n");
	printf("\nTEST 1:\n Using Salvager to trash card with cost 6 \n");
  //set player hand with Salvager
  tempState.hand[player][handPos]= salvager;
  //set player hand with card to be trashed
  tempState.hand[player][choice1]= gold;
  cardEffect(salvager,choice1,0,0,&tempState,handPos,0);

  // gain cost of trashed card
  printf(" new coins = %d, expected %d\n",tempState.coins, state.coins+choice1Cost);
  pass = tempState.coins == state.coins+choice1Cost;

  // assert new state->numBuys == state->numBuys++
  printf(" numBuys = %d, expected %d\n",tempState.numBuys, state.numBuys+1);
  pass = pass && tempState.numBuys== state.numBuys+1;


  // choice1 not in deck
  printf(" deckCount = %d, expected %d\n",tempState.deckCount[player],state.deckCount[player]);
  pass = pass && tempState.deckCount[player]==state.deckCount[player];

  // choice1 not in discard and salvager in discard
  printf(" discardCount = %d, expected %d\n",tempState.discardCount[player],state.discardCount[player]+1);
  pass = pass && tempState.discardCount[player]==state.discardCount[player]+1;

  // choice1 card not in hand
  printf(" choice1 position card = %d, expected != %d\n",tempState.hand[player][choice1], gold);
  pass = pass && tempState.hand[player][choice1] != gold;

   // salvager card not in hand
  printf(" salvager position card = %d, expected != %d\n",tempState.hand[player][handPos], salvager);
  pass = pass && tempState.hand[player][choice1] != gold;

  if(pass)
    printf("--------------------------------------------------------------------\nSalvager test SUCCESSFUL\n");
  else
    printf("--------------------------------------------------------------------\nSalvager test FAILED\n");
  printf("------------------------- Testing complete -------------------------\n");
  return 0;
}

//playSalvager
/*
- + 1 buy
  - set numbBuys = 0,5
  - assert new state->numBuys == state->numBuys++
- trash a card (choice1 which is hand[player][choice1])
  - set hand with choice1 as first, last and middle with different card types
  - choice1 card not in hand
  - choice1 not in discard
  - choice1 not in deck
    - also test hand with no cards
- gain cost of trashed card
  - set state->coins = 0, state->coins = 1
  - state->coins == state->coins+ choice1 cost (hard codded)
*/
